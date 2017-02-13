/*******************************************************************************************************************************//**
 * @details             Proyecto: Tetris
 * @file		main.c
 * @brief		Main del programa
 * @date		18/12/2016
 * @author		Franco Jatib, Diego Quispe, Emmanuel Carcomo
 *
 **********************************************************************************************************************************/
/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "headers.h"
#include "sys/wait.h"

int main(void)
{
    int pid, fd_ph[2], fd_hp[2];
    int flags1, flags2, flags3, flags4;
    
    pipe(fd_ph);
    pipe(fd_hp);
    
    pid = fork();
    
    if(pid == 0)
    {
        struct sockaddr_in my_addr, server_addr, cliente_addr;
        struct ifaddrs *ifa;
        struct sockaddr src_addr;
        char alias_oponente[6], alias[6], opcion_jugador, opcion_oponente, IP[20];
        int fd_sockserver, fd_sockcliente, len = sizeof(struct sockaddr), finalizacion, opcion=0, comprobacion = 0, a = 0, cliente_len = sizeof(struct sockaddr_in);
        int campo_jugador[22][12], campo_oponente[22][12], otra = 0;
        struct datos pieza_jugador, pieza_oponente, pieza_oponente_aux, pieza_jugador_aux;
        struct paquete pack_jugador, pack_oponente;
        
        close(fd_ph[1]);
        close(fd_hp[0]);
        
        read(fd_ph[0], (void *)&opcion, 4);
        read(fd_ph[0], (void *)alias, 6);
        
        if(opcion == 1)
        {
            
            fd_sockserver = socket(AF_INET, SOCK_STREAM, 0);
            
            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons(8081);
            server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
            memset(&(my_addr.sin_zero), '\0', 8);
            
            bind(fd_sockserver, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
            listen(fd_sockserver, 2);
            fd_sockcliente = accept(fd_sockserver, (struct sockaddr *)&cliente_addr, &cliente_len);
            
            recv(fd_sockcliente, alias_oponente, 6, 0);
            send(fd_sockcliente, (void *)alias, 6, 0);
            
            write(fd_hp[1], (void *)alias_oponente, 6);
            
            recv(fd_sockcliente, &pack_oponente, sizeof(struct paquete), 0);
            write(fd_hp[1], (void *)&pack_oponente, sizeof(struct paquete));
            
            read(fd_ph[0], &pack_jugador, sizeof(struct paquete));
            send(fd_sockcliente, (void *)&pack_jugador, sizeof(struct paquete), 0);
            
            flags1 = fcntl(fd_ph[0], F_GETFL, 0);
            flags4 = fcntl(fd_hp[1], F_GETFL, 0);
                        
            fcntl(fd_ph[0], F_SETFL, flags1 | O_NONBLOCK);
            fcntl(fd_hp[1], F_SETFL, flags4 | O_NONBLOCK);
            
            do
            {
                do
                {
                    if(pack_jugador.campo[0][0] != -1)
                    {
                        if(read(fd_ph[0], &pack_jugador, sizeof(struct paquete)) != -1)
                        {
                            send(fd_sockcliente, (void *)&pack_jugador, sizeof(struct paquete), 0);
                        }
                    }
                    
                    if(pack_oponente.campo[0][0] != -1)
                    {
                        if(recv(fd_sockcliente, &pack_oponente, sizeof(struct paquete), MSG_DONTWAIT) > 0)
                        {
                            write(fd_hp[1], (void *)&pack_oponente, sizeof(struct paquete));
                        }
                    }
                }while(pack_oponente.campo[0][0] != -1 || pack_jugador.campo[0][0] != -1);

                if(pack_jugador.campo[0][0] == -1)
                {
                    send(fd_sockcliente, (void *)&pack_jugador, sizeof(struct paquete), 0);
                    do
                    {
                        recv(fd_sockcliente, &pack_oponente, sizeof(struct paquete), 0);
                        write(fd_hp[1], (void *)&pack_oponente, sizeof(struct paquete));
                    }while(pack_oponente.campo[0][0] != -1);
                }
                
                if(pack_oponente.campo[0][0] == -1)
                {
                    write(fd_hp[1], (void *)&pack_oponente, sizeof(struct paquete));
                    do
                    {
                        read(fd_ph[0], &pack_jugador, sizeof(struct paquete));
                        send(fd_sockcliente, (void *)&pack_jugador, sizeof(struct paquete), 0);
                    }while(pack_jugador.campo[0][0] != -1);
                }
                
                while(read(fd_ph[0], &opcion_jugador, 1) == -1);
                while(recv(fd_sockcliente, &opcion_oponente, 1, 0) <= 0);
                printf("%c\n", opcion_oponente);
                send(fd_sockcliente, (void *)&opcion_jugador, 1, 0);
                
                if(opcion_jugador == 'S' && opcion_oponente == 'S')
                {
                    otra = 1;
                    write(fd_hp[1], (void *)&otra, 4);
                    finalizacion = 0;
                }
                else
                {
                    otra = 0;
                    write(fd_hp[1], (void *)&otra, 4);
                    finalizacion = 1;
                }
            }while(finalizacion == 0);
        }
        else if(opcion == 2)
        {
            do
            {
                read(fd_ph[0], (void *)IP, 20);
                
                fd_sockcliente = socket(AF_INET, SOCK_STREAM, 0);
        
                server_addr.sin_family = AF_INET;
                server_addr.sin_port = htons(8081);
                inet_aton(IP, &(server_addr.sin_addr));
                memset(&(server_addr.sin_zero), '\0', 8);
                
                if(connect(fd_sockcliente, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
                {
                    printf("Servidor no encontrado, revise la IP ingresada\n");
                    comprobacion = 0;
                }
                else
                {
                    comprobacion = 1;
                }
            }while(comprobacion == 0);
            
            send(fd_sockcliente, (void *)alias, 6, 0);
            recv(fd_sockcliente, alias_oponente, 6, 0);
            
            write(fd_hp[1], (void *)alias_oponente, 6);
            
            read(fd_ph[0], &pack_oponente, sizeof(struct paquete));
            send(fd_sockcliente, (void *)&pack_jugador, sizeof(struct paquete), 0);
            
            recv(fd_sockcliente, &pack_oponente, sizeof(struct paquete), 0);
            write(fd_hp[1], (void *)&pack_oponente, sizeof(struct paquete));
            
            flags1 = fcntl(fd_ph[0], F_GETFL, 0);
            flags4 = fcntl(fd_hp[1], F_GETFL, 0);
                        
            fcntl(fd_ph[0], F_SETFL, flags1 | O_NONBLOCK);
            fcntl(fd_hp[1], F_SETFL, flags4 | O_NONBLOCK);
            
            do
            {
                do
                {
                    if(pack_oponente.campo[0][0] != -1)
                    {
                        if(recv(fd_sockcliente, &pack_oponente, sizeof(struct paquete), MSG_DONTWAIT) > 0)
                        {
                            write(fd_hp[1], (void *)&pack_oponente, sizeof(struct paquete));
                        }
                    }
                    if(pack_jugador.campo[0][0] != -1)
                    {
                        if(read(fd_ph[0], &pack_jugador, sizeof(struct paquete)) != -1)
                        {
                            send(fd_sockcliente, (void *)&pack_jugador, sizeof(struct paquete), 0);
                        }
                    }
                }while(pack_oponente.campo[0][0] != -1 || pack_jugador.campo[0][0] != -1);
                
                if(pack_jugador.campo[0][0] == -1)
                {
                    send(fd_sockcliente, (void *)&pack_jugador, sizeof(struct paquete), 0);
                    do
                    {
                        recv(fd_sockcliente, &pack_oponente, sizeof(struct paquete), 0);
                        write(fd_hp[1], (void *)&pack_oponente, sizeof(struct paquete));
                    }while(pack_oponente.campo[0][0] != -1);
                }
                
                if(pack_oponente.campo[0][0] == -1)
                {
                    write(fd_hp[1], (void *)&pack_oponente, sizeof(struct paquete));
                    do
                    {
                        read(fd_ph[0], &pack_jugador, sizeof(struct paquete));
                        send(fd_sockcliente, (void *)&pack_jugador, sizeof(struct paquete), 0);
                        
                    }while(pack_jugador.campo[0][0] != -1);
                }
                
                while(read(fd_ph[0], &opcion_jugador, 1) == -1);
                send(fd_sockcliente, (void *)&opcion_jugador, 1, 0);
                while(recv(fd_sockcliente, &opcion_oponente, 1, 0) <= 0);
                printf("%c\n", opcion_oponente);
                
                if(opcion_jugador == 'S' && opcion_oponente == 'S')
                {
                    otra = 1;
                    write(fd_hp[1], (void *)&otra, 4);
                    finalizacion = 0;
                }
                else
                {
                    otra = 0;
                    write(fd_hp[1], (void *)&otra, 4);
                    finalizacion = 1;
                }
            }while(finalizacion == 0);
        }
    }
    else
    {
        if(al_init() == false)
        {
            perror("ERROR");
            exit(EXIT_FAILURE);
        }
        
        if(al_init_image_addon() == false)
        {
            perror("ERROR");
            exit(EXIT_FAILURE);
        }
        
        if(al_init_primitives_addon() == false)
        {
            perror("ERROR");
            exit(EXIT_FAILURE);
        }
        
        if(al_install_keyboard() == false)
        {
            perror("ERROR");
            exit(EXIT_FAILURE);
        }
        
        if(al_init_font_addon() == false)
        {
            perror("ERROR");
            exit(EXIT_FAILURE);
        }
        
        if(al_init_ttf_addon() == false)
        {
            perror("ERROR");
            exit(EXIT_FAILURE);
        }
        
        int campo[22][12],campo_2[16][25], campo_oponente[22][12], campo_oponente_aux[22][12], marca = 0, marca_oponente = 0, marca2 = 0, lineas, a, S2, j, i, b, y,opcion, z = 0, finalizacion = 0, x = 0, otra = 0, w = 0;
        ALLEGRO_DISPLAY *display;
        ALLEGRO_FONT *font = al_load_ttf_font("Font/ka1.ttf", 20, 0), *font_alias = al_load_ttf_font("Font/ka1.ttf", 20, 0);
        struct nodo *h = NULL, *l = NULL;
        struct datos pieza_jugador, pieza_next, pieza_oponente, pieza_AUX;
        ALLEGRO_BITMAP *colores[9],*colores_m[9], *campo_fondo, *fondo, *next_fondo, *score_fondo, *perdiste;
        ALLEGRO_TIMER *timer;
        ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
        ALLEGRO_EVENT events;
        double velocidad = 0.5, auxiliar = 0.5;
        char IP[20]={'0','0','0','.','0','0','0','.','0','0','0','.','0','0','0','\0'}, alias[6]={'A','A','A','A','A'}, alias_oponente[6], c = 'A', c_oponente = 'A',ip[20];
        struct paquete pack_jugador, pack_oponente;
        
        pack_jugador.lineas = 0;
        pack_jugador.puntos = 0;
        pack_jugador.nivel = 1;
        
        colores[0] = al_load_bitmap("Graphics/Piezas/clear.png");
        colores[1] = al_load_bitmap("Graphics/Piezas/pieza_gris.png");
        colores[2] = al_load_bitmap("Graphics/Piezas/pieza_rojo.png");
        colores[3] = al_load_bitmap("Graphics/Piezas/pieza_naranja.png");
        colores[4] = al_load_bitmap("Graphics/Piezas/pieza_amarillo.png");
        colores[5] = al_load_bitmap("Graphics/Piezas/pieza_verde.png");
        colores[6] = al_load_bitmap("Graphics/Piezas/pieza_cyan.png");
        colores[7] = al_load_bitmap("Graphics/Piezas/pieza_azul.png");
        colores[8] = al_load_bitmap("Graphics/Piezas/pieza_violeta.png");
        colores_m[0] = al_load_bitmap("Graphics/Piezas/clear_m.png");
        colores_m[1] = al_load_bitmap("Graphics/Piezas/pieza_gris_m.png");
        colores_m[2] = al_load_bitmap("Graphics/Piezas/pieza_rojo_m.png");
        colores_m[3] = al_load_bitmap("Graphics/Piezas/pieza_naranja_m.png");
        colores_m[4] = al_load_bitmap("Graphics/Piezas/pieza_amarillo_m.png");
        colores_m[5] = al_load_bitmap("Graphics/Piezas/pieza_verde_m.png");
        colores_m[6] = al_load_bitmap("Graphics/Piezas/pieza_cyan_m.png");
        colores_m[7] = al_load_bitmap("Graphics/Piezas/pieza_azul_m.png");
        colores_m[8] = al_load_bitmap("Graphics/Piezas/pieza_violeta_m.png");
        campo_fondo = al_load_bitmap("Graphics/campo_fondo.png");
        next_fondo = al_load_bitmap("Graphics/next_fondo.png");
        fondo = al_load_bitmap("Graphics/fondo.png");
        score_fondo = al_load_bitmap("Graphics/score_fondo.png");
        perdiste = al_load_bitmap("Graphics/perdiste.png");
        
        close(fd_ph[0]);
        close(fd_hp[1]);
        
        flags2 = fcntl(fd_ph[1], F_GETFL, 0);
        flags3 = fcntl(fd_hp[0], F_GETFL, 0);
        
        display = al_create_display(960, 600);
        opcion = menu(campo_2,display,colores_m,alias,IP);
        
        write(fd_ph[1], (void *)&opcion, sizeof(opcion));
        write(fd_ph[1], (void *)alias, 6);
        
        if(opcion == 2)
        {
            ip_f(IP,ip);
            write(fd_ph[1], (void *)ip, 20);
        }
        
        fcntl(fd_ph[1], F_SETFL, flags2 | O_NONBLOCK);
        fcntl(fd_hp[0], F_SETFL, flags3 | O_NONBLOCK);
        
        while(read(fd_hp[0], alias_oponente, 6) == -1)
        {
            if(i>8)
                i=0;
            borde(campo_2, i);
            print_campo_2(campo_2,colores_m);
            al_flip_display();
            i++;
            al_rest(0.1);
        }
        
        al_clear_to_color(al_map_rgb(0,0,0));
        
        if(!font)
        {
            perror("ERROR");
            exit(EXIT_FAILURE);
        }
        
        cargar_piezas(&h);
        al_register_event_source(event_queue, al_get_keyboard_event_source());
        init_campo(pack_jugador.campo);
        init_campo(pack_oponente.campo);
        srand(getpid());
        pieza_jugador = prandom(&h);
        pieza_next = prandom(&h);
        write(fd_ph[1], (void *)&pack_jugador, sizeof(struct paquete));
        while(read(fd_hp[0], (void *)&pack_oponente, sizeof(struct paquete)) == -1);
        al_draw_bitmap(fondo, 0, 0, 0);
        
        al_draw_textf(font_alias, al_map_rgb(255, 255, 255), 178, 30, ALLEGRO_ALIGN_CENTRE, "%s", alias);
        al_draw_textf(font_alias, al_map_rgb(255, 255, 255), 632, 30, ALLEGRO_ALIGN_CENTRE, "%s", alias_oponente);
        
        al_draw_textf(font, al_map_rgb(255, 255, 255), 384, 224, ALLEGRO_ALIGN_CENTRE, "%d", pack_jugador.puntos);
        al_draw_textf(font, al_map_rgb(255, 255, 255), 384, 291, ALLEGRO_ALIGN_CENTRE, "%d", pack_jugador.lineas);
        al_draw_textf(font, al_map_rgb(255, 255, 255), 384, 360, ALLEGRO_ALIGN_CENTRE, "%d", pack_jugador.nivel);
        
        al_draw_textf(font, al_map_rgb(255, 255, 255), 840, 224, ALLEGRO_ALIGN_CENTRE, "%d", pack_oponente.puntos);
        al_draw_textf(font, al_map_rgb(255, 255, 255), 840, 290, ALLEGRO_ALIGN_CENTRE, "%d", pack_oponente.lineas);
        al_draw_textf(font, al_map_rgb(255, 255, 255), 840, 360, ALLEGRO_ALIGN_CENTRE, "%d", pack_oponente.nivel);;
        
        do
        {
            if(pack_jugador.campo[0][0] == -1 && z == 0)
            {
                al_draw_bitmap(perdiste, 0, 0, 0);
                al_draw_text(font, al_map_rgb(255, 255, 255), 240, 218, ALLEGRO_ALIGN_CENTRE, "PERDISTE!");
                al_flip_display();
                z = 1;
                marca = 0;
            }
            
            if(pack_oponente.campo[0][0] == -1 && w == 0)
            {
                al_draw_bitmap(perdiste, 480, 0, 0);
                al_draw_text(font, al_map_rgb(255, 255, 255), 720, 218, ALLEGRO_ALIGN_CENTRE, "EL OPONENTE PERDIO!");
                al_flip_display();
                w = 1;
            }
            
            if(pack_jugador.campo[0][0] == -1 && pack_oponente.campo[0][0] == -1)
            {
                al_draw_bitmap(perdiste, 0, 0, 0); 
                al_draw_text(font, al_map_rgb(255, 255, 255), 240, 218, ALLEGRO_ALIGN_CENTRE, "REVANCHA?(PRESIONE S  N)");
                al_flip_display();
                
                al_flush_event_queue(event_queue);
                al_wait_for_event(event_queue, &events);
                
                if(events.type == ALLEGRO_EVENT_KEY_DOWN)
                {
                    switch(events.keyboard.keycode)
                    {
                        case ALLEGRO_KEY_S:
                            c = 'S';
                            break;
                                
                        case ALLEGRO_KEY_N:
                            c = 'N';
                            break;
                                
                        default:
                            c = 'N';
                            break;
                    }
                }
                
                al_draw_textf(font, al_map_rgb(255, 255, 255), 240, 258, ALLEGRO_ALIGN_CENTRE, "%c", c);
                al_flip_display();
                
                write(fd_ph[1], (void *)&c, 1);
                while(read(fd_hp[0], (void *)&otra, 4) == -1);
                printf("%d\n", otra);
                if(otra == 1)
                {
                    finalizacion = 0;
                }
                else
                {
                    finalizacion = 1;
                }
            }
            
            if(otra == 1)
            {
                w = 0;
                z = 0;
                c == 'N';
                c_oponente = 'N';
                init_campo(pack_jugador.campo);
                init_campo(pack_oponente.campo);
                al_draw_bitmap(fondo, 0, 0, 0);
                srand(getpid());
                pieza_jugador = prandom(&h);
                pieza_next = prandom(&h);
                write(fd_ph[1], (void *)&pack_jugador, sizeof(struct paquete));
                while(read(fd_hp[0], (void *)&pack_oponente, sizeof(struct paquete)) == -1);
                al_draw_bitmap(fondo, 0, 0, 0);
                
                al_draw_textf(font_alias, al_map_rgb(255, 255, 255), 178, 30, ALLEGRO_ALIGN_CENTRE, "%s", alias);
                al_draw_textf(font_alias, al_map_rgb(255, 255, 255), 632, 30, ALLEGRO_ALIGN_CENTRE, "%s", alias_oponente);
            }
            if(pack_jugador.campo[0][0] != -1)
            {
                marca = 0;
                put_pieza_campo(&pieza_jugador, pack_jugador.campo);
                write(fd_ph[1], (void *)&pack_jugador.campo, sizeof(struct paquete));
                print(&pieza_jugador, colores, 73, 91);
                al_draw_bitmap(next_fondo, 319, 98, 0);
                print_next(pieza_next, colores, 257, 99);
            }
            
            if(pack_jugador.campo[0][0] != -1)
            {
                al_draw_bitmap(score_fondo, 310, 178, 0);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 384, 224, ALLEGRO_ALIGN_CENTRE, "%d", pack_jugador.puntos);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 384, 290, ALLEGRO_ALIGN_CENTRE, "%d", pack_jugador.lineas);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 384, 360, ALLEGRO_ALIGN_CENTRE, "%d", pack_jugador.nivel);
                lineas = 0;
            }
            
            if(pack_oponente.campo[0][0] != -1)
            {
                al_draw_bitmap(score_fondo, 766, 178, 0);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 840, 224, ALLEGRO_ALIGN_CENTRE, "%d", pack_oponente.puntos);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 840, 290, ALLEGRO_ALIGN_CENTRE, "%d", pack_oponente.lineas);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 840, 360, ALLEGRO_ALIGN_CENTRE, "%d", pack_oponente.nivel);
            }
            
            al_flip_display();
            
            while(marca == 0)
            {
                timer = al_create_timer(velocidad);
                al_set_timer_count(timer, 0);
                al_start_timer(timer);
                
                while(al_get_timer_count(timer) < 1)
                {
                    if(pack_oponente.campo[0][0] != -1)
                    {
                        if(read(fd_hp[0], (void *)&pack_oponente, sizeof(struct paquete)) != -1)
                        {
                            al_draw_bitmap(campo_fondo, 529, 91, 0);
                            print_campo(pack_oponente.campo, colores, 529, 91);
                            al_flip_display();
                        }
                    }
                    if(pack_oponente.campo[0][0] == -1)
                    {
                        marca = 1;
                    }
                    
                    if(pack_jugador.campo[0][0] != -1)
                    {
                        al_get_next_event(event_queue, &events);
                
                        if(events.type == ALLEGRO_EVENT_KEY_DOWN)
                        {
                            clear(&pieza_jugador, colores, 73, 91);
                            switch(events.keyboard.keycode)
                            {
                                case ALLEGRO_KEY_RIGHT: 
                                    mover_derecha(&pieza_jugador, pack_jugador.campo);
                                    write(fd_ph[1], (void *)&pack_jugador.campo, sizeof(struct paquete));
                                    print(&pieza_jugador, colores, 73, 91);
                                    al_flip_display();
                                    break;
                                    
                                case ALLEGRO_KEY_LEFT:
                                    mover_izquierda(&pieza_jugador, pack_jugador.campo);
                                    write(fd_ph[1], (void *)&pack_jugador.campo, sizeof(struct paquete));
                                    print(&pieza_jugador, colores, 73, 91);
                                    al_flip_display();
                                    break;
                                    
                                case ALLEGRO_KEY_UP:
                                    rotar_pieza(&pieza_jugador, pack_jugador.campo);
                                    write(fd_ph[1], (void *)&pack_jugador.campo, sizeof(struct paquete));
                                    print(&pieza_jugador, colores, 73, 91);
                                    al_flip_display();
                                    break;
                                        
                                case ALLEGRO_KEY_DOWN:
                                    caer(&pieza_jugador, pack_jugador.campo);
                                    print(&pieza_jugador, colores, 73, 91);
                                    al_flip_display();
                                    break;
                                    
                                default: break;
                            }
                        }
                    }
                }
                al_stop_timer(timer);
                
                if(pack_jugador.campo[0][0] != -1)
                {
                    marca = mover_abajo(&pieza_jugador, pack_jugador.campo);
                    if(marca == 1)
                    {
                        lineas = delete_line(pack_jugador.campo);
                    }
                    write(fd_ph[1], (void *)&pack_jugador, sizeof(struct paquete));
                    al_draw_bitmap(campo_fondo, 73, 91, 0);
                    print_campo(pack_jugador.campo, colores, 73, 91);
                    al_flip_display();
                }
            }
            if(pack_jugador.campo[0][0] != -1)
            {
                pack_jugador.lineas = pack_jugador.lineas + lineas;
                pack_jugador.puntos = pack_jugador.puntos + (lineas*10*pack_jugador.nivel);
                if((pack_jugador.lineas != 0) && (pack_jugador.lineas >= pack_jugador.nivel*10) && (lineas != 0))
                {
                    pack_jugador.nivel = pack_jugador.nivel + 1;
                    al_draw_bitmap(campo_fondo, 52, 70, 0);
                    velocidad = velocidad - 0.01;
                }
                pieza_jugador = pieza_next;
                pieza_next = prandom(&h);
                
                if(comprobar(pieza_jugador, pack_jugador.campo) == -1)
                {
                    pack_jugador.campo[0][0] = -1;
                    write(fd_ph[1], (void *)&pack_jugador, sizeof(struct paquete));
                }
            }
        }while(finalizacion == 0);
        
        wait(NULL);
        descargar_lista(&h);
        al_destroy_event_queue(event_queue);
        al_destroy_timer(timer);
        for(i = 0; i < 10; i++)
        {
            al_destroy_bitmap(colores[i]);
        }
        for(i = 0; i < 9; i++)
        {
            al_destroy_bitmap(colores_m[i]);
        }
        al_destroy_display(display);
        }
}
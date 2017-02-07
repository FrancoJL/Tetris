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
        char alias_oponente[20], alias[20], opcion_jugador, opcion_oponente, IP[20];
        int fd_sockserver, fd_sockcliente, len = sizeof(struct sockaddr), finalizacion, opcion, comprobacion = 0, a = 0, cliente_len = sizeof(struct sockaddr_in);
        struct datos pieza_jugador, pieza_oponente, pieza_oponente_aux, pieza_jugador_aux;
        
        close(fd_ph[1]);
        close(fd_hp[0]);
        
        printf("Alias: ");
        scanf("%s", alias);
        
        printf("1-Crear servidor\n2-Unirse a un servidor\n");
        scanf("%d", &opcion);
        
        if(opcion == 1)
        {
            printf("Creando servidor...\n");
            
            fd_sockserver = socket(AF_INET, SOCK_STREAM, 0);
            
            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons(8081);
            server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
            memset(&(my_addr.sin_zero), '\0', 8);
            
            bind(fd_sockserver, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
            listen(fd_sockserver, 2);
            printf("Esperando oponente...\n");
            fd_sockcliente = accept(fd_sockserver, (struct sockaddr *)&cliente_addr, &cliente_len);
            
            recv(fd_sockcliente, alias_oponente, 20, 0);
            send(fd_sockcliente, (void *)alias, 20, 0);
            
            write(fd_hp[1], (void *)alias, 20);
            write(fd_hp[1], (void *)alias_oponente, 20);
            
            recv(fd_sockcliente, &pieza_oponente_aux, sizeof(struct datos), 0);
            write(fd_hp[1], (void *)&pieza_oponente_aux, sizeof(struct datos));
            
            read(fd_ph[0], &pieza_jugador_aux, sizeof(struct datos));
            send(fd_sockcliente, (void *)&pieza_jugador_aux, sizeof(struct datos), 0);
            
            flags1 = fcntl(fd_ph[0], F_GETFL, 0);
            flags4 = fcntl(fd_hp[1], F_GETFL, 0);
                        
            fcntl(fd_ph[0], F_SETFL, flags1 | O_NONBLOCK);
            fcntl(fd_hp[1], F_SETFL, flags4 | O_NONBLOCK);
            
            do
            {
                do
                {
                    if(pieza_jugador.centro_pos[0] != -1)
                    {
                        if(read(fd_ph[0], &pieza_jugador, sizeof(struct datos)) != -1)
                        {
                            if(piezacmp(pieza_jugador, pieza_jugador_aux) == 1)
                            {
                                send(fd_sockcliente, (void *)&pieza_jugador, sizeof(struct datos), 0);
                                pieza_jugador_aux = pieza_jugador;
                            }
                        }
                    }
                    
                    if(pieza_oponente.centro_pos[0] != -1)
                    {
                        if(recv(fd_sockcliente, &pieza_oponente, sizeof(struct datos), MSG_DONTWAIT) > 0)
                        {
                            if(piezacmp(pieza_oponente, pieza_oponente_aux) == 1)
                            {
                                write(fd_hp[1], (void *)&pieza_oponente, sizeof(struct datos));
                                pieza_oponente_aux = pieza_oponente;
                            }
                        }
                    }
                }while(pieza_oponente.centro_pos[0] != -1 || pieza_jugador.centro_pos[0] != -1);

                if(pieza_jugador.centro_pos[0] == -1)
                {
                    send(fd_sockcliente, (void *)&pieza_jugador, sizeof(struct datos), 0);
                    do
                    {
                        recv(fd_sockcliente, &pieza_oponente, sizeof(struct datos), 0);
                        write(fd_hp[1], (void *)&pieza_oponente, sizeof(struct datos));
                    }while(pieza_oponente.centro_pos[0] != -1);
                    
                    read(fd_ph[0], &opcion_jugador, 1);
                    
                    if(opcion_jugador == 'S' || opcion_jugador == 's')
                    {
                        send(fd_sockcliente, (void *)&opcion_jugador, 1, 0);
                        recv(fd_sockcliente, &opcion_oponente, 1, 0);
                        if(opcion_oponente == 'S' || opcion_oponente == 's')
                        {
                            finalizacion = 0;
                        }
                        else
                        {
                            finalizacion = 1;
                        }
                    }
                    else
                    {
                        send(fd_sockcliente, (void *)&opcion_jugador, 1, 0);
                        finalizacion = 1;
                    }
                }
                
                if(pieza_oponente.centro_pos[0] == -1)
                {
                    write(fd_hp[1], (void *)&pieza_oponente, sizeof(struct datos));
                    do
                    {
                        read(fd_ph[0], &pieza_jugador, sizeof(struct datos));
                        send(fd_sockcliente, (void *)&pieza_jugador, sizeof(struct datos), 0);
                    }while(pieza_jugador.centro_pos[0] != 1);
                    
                    recv(fd_sockcliente, &opcion_oponente, 1, 0);
                    
                    if(opcion_oponente == 'S' || opcion_oponente == 's')
                    {
                        write(fd_hp[1], (void *)&opcion_oponente, 1);
                        read(fd_ph[0], (void *)&opcion_jugador, 1);
                        if(opcion_jugador == 'S' || opcion_jugador == 's')
                        {
                            finalizacion = 0;
                        }
                        else
                        {
                            finalizacion = 1;
                        }
                    }
                    else
                    {
                        write(fd_hp[1], (void *)&opcion_oponente, 1);
                        finalizacion = 1;
                    }
                }
            }while(finalizacion == 0);
        }
        else
        {
            do
            {
                printf("Ingrese la IP del servidor: ");
                scanf("%s", IP);
                
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
            
            send(fd_sockcliente, (void *)alias, 20, 0);
            recv(fd_sockcliente, alias_oponente, 20, 0);
            
            write(fd_hp[1], (void *)alias, 20);
            write(fd_hp[1], (void *)alias_oponente, 20);
            
            read(fd_ph[0], &pieza_jugador_aux, sizeof(struct datos));
            send(fd_sockcliente, (void *)&pieza_jugador_aux, sizeof(struct datos), 0);
            
            recv(fd_sockcliente, &pieza_oponente_aux, sizeof(struct datos), 0);
            write(fd_hp[1], (void *)&pieza_oponente_aux, sizeof(struct datos));
            
            flags1 = fcntl(fd_ph[0], F_GETFL, 0);
            flags4 = fcntl(fd_hp[1], F_GETFL, 0);
                        
            fcntl(fd_ph[0], F_SETFL, flags1 | O_NONBLOCK);
            fcntl(fd_hp[1], F_SETFL, flags4 | O_NONBLOCK);
            
            do
            {
                do
                {
                    if(pieza_oponente.centro_pos[0] != -1)
                    {
                        if(recv(fd_sockcliente, &pieza_oponente, sizeof(struct datos), MSG_DONTWAIT) > 0)
                        {
                            if(piezacmp(pieza_oponente, pieza_oponente_aux) == 1)
                            {
                                write(fd_hp[1], (void *)&pieza_oponente, sizeof(struct datos));
                                pieza_oponente_aux = pieza_oponente;
                                a = 1;
                            }
                        }
                    }
                    if(pieza_jugador.centro_pos[0] != -1)
                    {
                        if(read(fd_ph[0], &pieza_jugador, sizeof(struct datos)) != -1)
                        {
                            if(piezacmp(pieza_jugador, pieza_jugador_aux) == 1)
                            {
                                send(fd_sockcliente, (void *)&pieza_jugador, sizeof(struct datos), 0);
                                pieza_jugador_aux = pieza_jugador;
                            }
                        }
                    }
                }while(pieza_oponente.centro_pos[0] != -1 || pieza_jugador.centro_pos[0] != -1);
                
                if(pieza_jugador.centro_pos[0] == -1)
                {
                    send(fd_sockcliente, (void *)&pieza_jugador, sizeof(struct datos), 0);
                    do
                    {
                        recv(fd_sockcliente, &pieza_oponente, sizeof(struct datos), 0);
                        write(fd_hp[1], (void *)&pieza_oponente, sizeof(struct datos));
                    }while(pieza_oponente.centro_pos[0] != -1);
                    
                    read(fd_ph[0], &opcion_jugador, 1);
                    
                    if(opcion_jugador == 'S' || opcion_jugador == 's')
                    {
                        send(fd_sockcliente, (void *)&opcion_jugador, 1, 0);
                        recv(fd_sockcliente, &opcion_oponente, 1, 0);
                        if(opcion_oponente == 'S' || opcion_oponente == 's')
                        {
                            finalizacion = 0;
                        }
                        else
                        {
                            finalizacion = 1;
                        }
                    }
                    else
                    {
                        send(fd_sockcliente, (void *)&opcion_jugador, 1, 0);
                        finalizacion = 1;
                    }
                }
                
                if(pieza_oponente.centro_pos[0] == -1)
                {
                    write(fd_hp[1], (void *)&pieza_oponente, 20);
                    do
                    {
                        if(read(fd_ph[0], &pieza_jugador, sizeof(struct datos)) != -1)
                        {
                            send(fd_sockcliente, (void *)&pieza_jugador, sizeof(struct datos), 0);
                        }
                    }while(pieza_jugador.centro_pos[0] != 1);
                    
                    recv(fd_sockserver, &opcion_oponente, 1, 0);
                    
                    if(opcion_oponente == 'S' || opcion_oponente == 's')
                    {
                        write(fd_hp[1], (void *)&opcion_oponente, 1);
                        if(read(fd_ph[0], (void *)&opcion_jugador, 1) != -1)
                        {
                            if(opcion_jugador == 'S' || opcion_jugador == 's')
                            {
                                finalizacion = 0;
                            }
                            else
                            {
                                finalizacion = 1;
                            }
                        }
                    }
                    else
                    {
                        write(fd_hp[1], (void *)&opcion_oponente, 1);
                        finalizacion = 1;
                    }
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
        
        int campo[22][12], campo_oponente[22][12], marca = 0, marca_oponente = 0, marca2 = 0, lineas_totales = 0, puntos = 0, nivel = 1, lineas, fd_w, fd_r, a, S2, j, lineas_totales_oponente = 0, puntos_oponente = 0, nivel_oponente = 1, lineas_oponente, i, b;
        ALLEGRO_DISPLAY *display;
        ALLEGRO_FONT *font = al_load_ttf_font("Font/ka1.ttf", 20, 0);
        struct nodo *h = NULL, *l = NULL;
        struct datos pieza_jugador, pieza_next, pieza_oponente, pieza_AUX;
        ALLEGRO_BITMAP *colores[9];
        ALLEGRO_TIMER *timer;
        ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
        ALLEGRO_EVENT events;
        double velocidad = 0.5, auxiliar = 0.5;
        char ip[20], alias[20], alias_oponente[20], c = 'N', c_oponente = 'N';
        
        colores[0] = al_load_bitmap("Graphics/Piezas/clear.png");
        colores[1] = al_load_bitmap("Graphics/Piezas/pieza_gris.png");
        colores[2] = al_load_bitmap("Graphics/Piezas/pieza_rojo.png");
        colores[3] = al_load_bitmap("Graphics/Piezas/pieza_naranja.png");
        colores[4] = al_load_bitmap("Graphics/Piezas/pieza_amarillo.png");
        colores[5] = al_load_bitmap("Graphics/Piezas/pieza_verde.png");
        colores[6] = al_load_bitmap("Graphics/Piezas/pieza_cyan.png");
        colores[7] = al_load_bitmap("Graphics/Piezas/pieza_azul.png");
        colores[8] = al_load_bitmap("Graphics/Piezas/pieza_violeta.png");
        
        close(fd_ph[0]);
        close(fd_hp[1]);
        
        read(fd_hp[0], alias, 20);
        read(fd_hp[0], alias_oponente, 20);
        
        display = al_create_display(960, 600);
        
        if(!font)
        {
            perror("ERROR");
            exit(EXIT_FAILURE);
        }
        
        flags2 = fcntl(fd_ph[1], F_GETFL, 0);
        flags3 = fcntl(fd_hp[0], F_GETFL, 0);
        
        cargar_piezas(&h);
        al_register_event_source(event_queue, al_get_keyboard_event_source());
        init_campo(campo);
        init_campo(campo_oponente);
        print_campo(campo, colores, 0, 0);
        print_campo(campo_oponente, colores, 25, 0);
        srand(getpid());
        pieza_jugador = prandom(&h);
        pieza_next = prandom(&h);
        
        do
        {
            fcntl(fd_ph[1], F_SETFL, flags2 | O_NONBLOCK);
            fcntl(fd_hp[0], F_SETFL, flags3 | O_NONBLOCK);
            if(pieza_jugador.centro_pos[0] == -1)
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, al_map_rgb(255, 255, 255), 250, 250, ALLEGRO_ALIGN_LEFT, "Revancha?(S/N)");
                
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
                write(fd_ph[1], (void *)&c, 1);
            }
            if(c == 'S' && c_oponente == 'S' && pieza_jugador.centro_pos[0] == -1 && pieza_oponente.centro_pos[0] == -1)
            {
                init_campo(campo);
                init_campo(campo_oponente);
                al_clear_to_color(al_map_rgb(0, 0, 0));
                print_campo(campo, colores, 0, 0);
                print_campo(campo_oponente, colores, 25, 0);
                srand(getpid());
                pieza_jugador = prandom(&h);
                pieza_next = prandom(&h);
            }
            if(pieza_jugador.centro_pos[0] != -1)
            {
                marca = 0;
                write(fd_ph[1], (void *)&pieza_jugador, sizeof(struct datos));
                put_pieza_campo(&pieza_jugador, campo);
                print(&pieza_jugador, colores, 0);
                print_next(pieza_next, colores, 15, 5);
            }
            if(pieza_oponente.centro_pos[0] != -1)
            {
                marca_oponente = 0;
                if(read(fd_hp[0], (void *)&pieza_oponente, sizeof(struct datos)) != -1)
                {
                    put_pieza_campo(&pieza_oponente, campo_oponente);
                    print(&pieza_oponente, colores, 25);
                }
            }
            
            if(pieza_jugador.centro_pos[0] != -1)
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), 380, 50, ALLEGRO_ALIGN_LEFT, "PROXIMO:");
                al_draw_textf(font, al_map_rgb(255, 255, 255), 380, 250, ALLEGRO_ALIGN_LEFT, "NIVEL: %d", nivel);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 380, 300, ALLEGRO_ALIGN_LEFT, "LINEAS:%d", lineas_totales);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 380, 350, ALLEGRO_ALIGN_LEFT, "PUNTOS:%d", puntos);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 380, 0, ALLEGRO_ALIGN_LEFT, "%s", alias);
                lineas = 0;
            }
            
            if(pieza_oponente.centro_pos[0] != -1)
            {
                al_draw_textf(font, al_map_rgb(255, 255, 255), 760, 250, ALLEGRO_ALIGN_LEFT, "NIVEL: %d", nivel_oponente);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 760, 300, ALLEGRO_ALIGN_LEFT, "LINEAS:%d", lineas_totales_oponente);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 760, 350, ALLEGRO_ALIGN_LEFT, "PUNTOS:%d", puntos_oponente);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 760, 0, ALLEGRO_ALIGN_LEFT, "%s", alias_oponente);
                lineas_oponente = 0;
            }
            
            al_flip_display();
            
            while(marca == 0)
            {
                timer = al_create_timer(velocidad);
                al_set_timer_count(timer, 0);
                al_start_timer(timer);
                
                while(al_get_timer_count(timer) < 1)
                {
                    if(pieza_jugador.centro_pos[0] != -1)
                    {
                        al_get_next_event(event_queue, &events);
                
                        if(events.type == ALLEGRO_EVENT_KEY_UP)
                        {
                            if(events.keyboard.keycode == ALLEGRO_KEY_DOWN)
                            {
                                velocidad = auxiliar;
                                marca2 = 0;
                            }
                        }
                        if(events.type == ALLEGRO_EVENT_KEY_DOWN)
                        {
                            clear(&pieza_jugador, colores, 0);
                            switch(events.keyboard.keycode)
                            {
                                case ALLEGRO_KEY_RIGHT: 
                                    mover_derecha(&pieza_jugador, campo);
                                    print(&pieza_jugador, colores, 0);
                                    al_flip_display();
                                    write(fd_ph[1], (void *)&pieza_jugador, sizeof(struct datos));
                                    break;
                                    
                                case ALLEGRO_KEY_LEFT:
                                    mover_izquierda(&pieza_jugador, campo);
                                    print(&pieza_jugador, colores, 0);
                                    al_flip_display();
                                    write(fd_ph[1], (void *)&pieza_jugador, sizeof(struct datos));
                                    break;
                                    
                                case ALLEGRO_KEY_UP:
                                    rotar_pieza(&pieza_jugador, campo);
                                    print(&pieza_jugador, colores, 0);
                                    al_flip_display();
                                    write(fd_ph[1], (void *)&pieza_jugador, sizeof(struct datos));
                                    break;
                                        
                                case ALLEGRO_KEY_DOWN:
                                    if(marca2 == 0)
                                    {
                                        auxiliar = velocidad;
                                        velocidad = 0.05;
                                        marca2 = 1;
                                        al_set_timer_count(timer, 2);
                                    }
                                    break;
                                    
                                default: break;
                            }
                        }
                    }
                    
//                     for(y = 0; y < 22; y++)
//                     {
//                         for(x = 0; x < 12; x++)
//                         {
//                             printf("%d ", campo[y][x]);
//                         }
//                         printf("\n");
//                     }
                    if(pieza_oponente.centro_pos[0] != -1)
                    {
                        if(read(fd_hp[0], &pieza_AUX, sizeof(struct datos)) != -1)
                        {
                            clear(&pieza_oponente, colores, 25);
                            print(&pieza_AUX, colores, 25);
                            pieza_oponente = pieza_AUX;
                        }
                    }
                    al_flip_display();
                }
                al_stop_timer(timer);
                
                if(pieza_jugador.centro_pos[0] != -1)
                {
                    clear(&pieza_jugador, colores, 0);
                    marca = mover_abajo(&pieza_jugador, campo);
                    write(fd_ph[1], (void *)&pieza_jugador, sizeof(struct datos));
                    if(marca == 1)
                    {
                        lineas = delete_line(campo);
                    }
                    print(&pieza_jugador, colores, 0);
                }
                
                if(pieza_oponente.centro_pos[0] != -1)
                {
                    clear(&pieza_oponente, colores, 25);
                    marca_oponente = mover_abajo(&pieza_oponente, campo_oponente);
                    if(marca_oponente == 1)
                    {
                        lineas_oponente = delete_line(campo_oponente);
                    }
                    print(&pieza_oponente, colores, 25);
                }
            }
            if(pieza_jugador.centro_pos[0] != -1)
            {
                lineas_totales = lineas_totales + lineas;
                puntos = puntos + (lineas*10*nivel);
                if((lineas_totales != 0) && (lineas_totales >= nivel*10) && (lineas != 0))
                {
                    nivel = nivel + 1;
                    velocidad = velocidad - 0.01;
                    print_campo(campo, colores, 0, 0);
                }
                pieza_jugador = pieza_next;
                pieza_next = prandom(&h);
            }
            if(pieza_oponente.centro_pos[0] != -1)
            {
                lineas_totales_oponente = lineas_totales_oponente + lineas_oponente;
                puntos_oponente = puntos_oponente + (lineas_oponente*10*nivel_oponente);
                if((lineas_totales_oponente != 0) && (lineas_totales_oponente >= nivel_oponente*10) && (lineas_oponente != 0))
                {
                    nivel_oponente = nivel_oponente + 1;
                    print_campo(campo_oponente, colores, 25, 0);
                }
            }
            if(comprobar(pieza_jugador, campo) == -1)
            {
                pieza_jugador.centro_pos[0] = -1;
                pieza_jugador.centro_pos[1] = -1;
                pieza_jugador.periferico_1_pos[0] = -1;
                pieza_jugador.periferico_1_pos[1] = -1;
                pieza_jugador.periferico_2_pos[0] = -1;
                pieza_jugador.periferico_2_pos[1] = -1;
                pieza_jugador.periferico_3_pos[0] = -1;
                pieza_jugador.periferico_3_pos[1] = -1;
            }
//             read(fd_hp[0], &c_oponente, 1);
             al_flip_display();
        }while(!((c == 'N' || c_oponente == 'N') && pieza_jugador.centro_pos[0] == -1 && pieza_oponente.centro_pos[0] == -1));
        
        descargar_lista(&h);
        al_destroy_event_queue(event_queue);
        al_destroy_timer(timer);
        for(i = 0; i < 9; i++)
        {
            al_destroy_bitmap(colores[i]);
        }
        al_destroy_display(display);
        }
}
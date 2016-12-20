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
    
    int campo[22][12], marca = 0, x, y, n = 1, i = 0, flag = 0, marca2 = 0;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_FONT *font = al_load_ttf_font("Font/ka1.ttf", 20, 0);
    int lineas_totales = 0, puntos = 0, nivel = 1, lineas;
    struct nodo *h = NULL, *l = NULL;
    struct datos pieza, pieza_next, asd;
    ALLEGRO_BITMAP *colores[9];
    colores[0] = al_load_bitmap("Graphics/Piezas/clear.png");
    colores[1] = al_load_bitmap("Graphics/Piezas/pieza_gris.png");
    colores[2] = al_load_bitmap("Graphics/Piezas/pieza_rojo.png");
    colores[3] = al_load_bitmap("Graphics/Piezas/pieza_naranja.png");
    colores[4] = al_load_bitmap("Graphics/Piezas/pieza_amarillo.png");
    colores[5] = al_load_bitmap("Graphics/Piezas/pieza_verde.png");
    colores[6] = al_load_bitmap("Graphics/Piezas/pieza_cyan.png");
    colores[7] = al_load_bitmap("Graphics/Piezas/pieza_azul.png");
    colores[8] = al_load_bitmap("Graphics/Piezas/pieza_violeta.png");
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    ALLEGRO_EVENT events;
    double velocidad = 0.5, auxiliar = 0.5;
    int fd_w, fd_r, a;
    char ip[20], nombre[20];
    mkfifo("FIFO_2", 0666);
    fd_r = open("FIFO_2", O_RDONLY);
    do
    {
        a = read(fd_r, (void *)nombre, 20);
    }while(a == 0);
    close(fd_r);
    mkfifo("FIFO", 0666);
    fd_w = open("FIFO", O_WRONLY);
    al_set_new_window_position(0, 0);
    display = al_create_display(550, 600);
    if(!font)
    {
        perror("ERROR");
        exit(EXIT_FAILURE);
    }
    cargar_piezas(&h);
    init_campo(campo);
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    srand(getpid());
    pieza = prandom(&h);
    pieza_next = prandom(&h);
    do
    {
        marca = 0;
        put_pieza_campo(&pieza, campo);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        print_campo(campo, colores);
        print_next(pieza_next, colores);
        al_draw_text(font, al_map_rgb(255, 255, 255), 380, 50, ALLEGRO_ALIGN_LEFT, "PROXIMO:");
        al_draw_textf(font, al_map_rgb(255, 255, 255), 380, 250, ALLEGRO_ALIGN_LEFT, "NIVEL: %d", nivel);
        al_draw_textf(font, al_map_rgb(255, 255, 255), 380, 300, ALLEGRO_ALIGN_LEFT, "LINEAS:%d", lineas_totales);
        al_draw_textf(font, al_map_rgb(255, 255, 255), 380, 350, ALLEGRO_ALIGN_LEFT, "PUNTOS:%d", puntos);
        al_draw_textf(font, al_map_rgb(255, 255, 255), 380, 0, ALLEGRO_ALIGN_LEFT, "%s", nombre);
        al_flip_display();
        lineas = 0;
        write(fd_w, (void *)campo, 1056);
        while(marca == 0)
        {
            timer = al_create_timer(velocidad);
            al_set_timer_count(timer, 0);
            al_start_timer(timer);
            
            while(al_get_timer_count(timer) < 1)
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
                    clear(&pieza, colores);
                    switch(events.keyboard.keycode)
                    {
                        case ALLEGRO_KEY_RIGHT: 
                            mover_derecha(&pieza, campo);
                            write(fd_w, (void *)campo, 1056);
                            break;
                            
                        case ALLEGRO_KEY_LEFT:
                            mover_izquierda(&pieza, campo);
                            write(fd_w, (void *)campo, 1056);
                            break;
                            
                        case ALLEGRO_KEY_UP:
                            rotar_pieza(&pieza, campo);
                            write(fd_w, (void *)campo, 1056);
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
                    print(&pieza, colores);
                    al_flip_display();
                }
            }
            al_stop_timer(timer);
                
            clear(&pieza, colores);
            marca = mover_abajo(&pieza, campo);
            if(marca == 1)
            {
                lineas = delete_line(campo);
            }
            print(&pieza, colores);
            al_flip_display();
            write(fd_w, (void *)campo, 1056);
        }
        lineas_totales = lineas_totales + lineas;
        puntos = puntos + (lineas*10*nivel);
        if((lineas_totales != 0) && (lineas_totales >= nivel*10) && (lineas != 0))
        {
            nivel = nivel + 1;
            velocidad = velocidad - 0.01;
        }
        pieza = pieza_next;
        pieza_next = prandom(&h);
        if(comprobar(pieza, campo) == -1)
        {
            flag = 1;
        }
    }while(flag == 0);
    for(y = 0; y < 22; y++)
    {
        for(x = 0; x < 12; x++)
        {
            campo[y][x] = 0;
        }
    }
    write(fd_w, (void *)campo, 1056);
    close(fd_w);
    system("rm FIFO");
    system("rm FIFO_2");
    descargar_lista(&h);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    for(i = 0; i < 9; i++)
    {
        al_destroy_bitmap(colores[i]);
    }
    al_destroy_display(display);
    
    exit(EXIT_SUCCESS);
}
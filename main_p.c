#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#define DIRECTORIO "Graphics/pieza_"
#define EXTENSION ".png"
#define UNIDAD 26

struct pieza
{
    ALLEGRO_BITMAP *bitmap;
    int centro_pos[2];
    int periferico_1_pos[2];
    int periferico_2_pos[2];
    int periferico_3_pos[2];
    char nombre;
    char color[10];
};

typedef struct pieza PIEZA;

int crear_pieza(PIEZA *);
void move_pieza(PIEZA *, double, int campo[22][12]);
void print_pieza(PIEZA *);
void rotar_pieza(PIEZA*,int campo[22][12]);
void cargar_matriz(PIEZA *, int campo[22][12]);
void detect_colision(int campo[22][12], int *, PIEZA *);
void clear_segmento(int, int);
void put_pieza_campo(PIEZA *, int campo[22][12]);

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
    
    int campo[22][12], i, j;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_BITMAP *limite_bitmap;
    
    limite_bitmap = al_load_bitmap("Graphics/pieza_limite.png");
    
    display = al_create_display(800, 600);
    
    PIEZA pieza_L;
    PIEZA asd;
    PIEZA palo;
    
    pieza_L.centro_pos[0] = 2;
    pieza_L.centro_pos[1] = 2;
    
    pieza_L.periferico_1_pos[0] = 2;
    pieza_L.periferico_1_pos[1] = 1;
    
    pieza_L.periferico_2_pos[0] = 2;
    pieza_L.periferico_2_pos[1] = 3;
    
    pieza_L.periferico_3_pos[0] = 3;
    pieza_L.periferico_3_pos[1] = 3;
    
    pieza_L.nombre = 'L';
    
    asd.centro_pos[0] = 4;
    asd.centro_pos[1] = 8;
    
    asd.periferico_1_pos[0] = 5;
    asd.periferico_1_pos[1] = 8;
    
    asd.periferico_2_pos[0] = 4;
    asd.periferico_2_pos[1] = 9;
    
    asd.periferico_3_pos[0] = 5;
    asd.periferico_3_pos[1] = 9;
    
    palo.centro_pos[0] = 6;
    palo.centro_pos[1] = 5;
    
    palo.periferico_1_pos[0] = 6;
    palo.periferico_1_pos[1] = 6;
    
    palo.periferico_2_pos[0] = 6;
    palo.periferico_2_pos[1] = 7;
    
    palo.periferico_3_pos[0] = 6;
    palo.periferico_3_pos[1] = 8;
    
    strcpy(pieza_L.color, "rojo");
    strcpy(asd.color, "azul");
    strcpy(palo.color, "azul");
    
    for(i = 0; i < 22; i++)
    {
        for(j = 0; j < 12; j++)
        {
            campo[i][j] = 3;
        }
    }
    for(i = 1; i < 21; i++)
    {
        for(j = 1; j < 11; j++)
        {
            campo[i][j] = 0;
        }
    }
    
    for(j = 0; j < 22; j++)
    {
        for(i = 0; i < 12; i++)
        {
            if(campo[j][i] == 3)
            al_draw_bitmap(limite_bitmap, i*UNIDAD, j*UNIDAD, 0);
        }
    }
    
    cargar_matriz(&pieza_L, campo);
    cargar_matriz(&asd, campo);
    cargar_matriz(&palo, campo);
    
    if(crear_pieza(&pieza_L) == 1)
    {
        exit(EXIT_FAILURE);
    }
    
    crear_pieza(&asd);
    
    crear_pieza(&palo);
    
    al_flip_display();
    
    move_pieza(&pieza_L, 1.0, campo);
    
    al_destroy_bitmap(pieza_L.bitmap);
    
    al_destroy_display(display);
    
    exit(EXIT_SUCCESS);
}

int crear_pieza(PIEZA *pieza)
{
    char directorio[30] = DIRECTORIO, extension[5] = EXTENSION;
    
    if(strcmp(pieza->color, "rojo") != 0 && strcmp(pieza->color, "naranja") != 0 && strcmp(pieza->color, "amarillo") != 0 && strcmp(pieza->color, "verde") != 0 && strcmp(pieza->color, "cyan") != 0 && strcmp(pieza->color, "azul") != 0 && strcmp(pieza->color, "violeta") != 0)
    {
        printf("ERROR: Debe ser un color valido (rojo, naranja, amarillo, verde, cyan, azul, violeta)\n");
        
        return 1;
    }
    else
    {
        strcat(directorio, pieza->color);
        strcat(directorio, extension);
        
        pieza->bitmap = al_load_bitmap(directorio);
        
        print_pieza(pieza);
    }
    
    return 0;
}

void move_pieza(PIEZA *pieza, double velocidad, int campo[22][12])
{
    int i = 0, j = 0, m, n, marca = 0, x, y;
    int v[4];
    ALLEGRO_TIMER *timer = al_create_timer(velocidad);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    ALLEGRO_EVENT events;
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    while(i <= 30 && i >= -10 && j <= 25)
    {
        al_set_timer_count(timer, 0);
        al_start_timer(timer);
        put_pieza_campo(pieza, campo);
        while(al_get_timer_count(timer) < 1)
        {
            al_get_next_event(event_queue, &events);
            if(events.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                if(events.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                {
                    detect_colision(campo, v, pieza);
                    if(v[2] == 0)
                    {
                        campo[pieza->centro_pos[1]][pieza->centro_pos[0]] = 0;
                        campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = 0;
                        campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = 0;
                        campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = 0;
                        clear_segmento(pieza->periferico_1_pos[1]*UNIDAD, pieza->periferico_1_pos[0]*UNIDAD);
                        clear_segmento(pieza->periferico_2_pos[1]*UNIDAD, pieza->periferico_2_pos[0]*UNIDAD);
                        clear_segmento(pieza->periferico_3_pos[1]*UNIDAD, pieza->periferico_3_pos[0]*UNIDAD);
                        clear_segmento(pieza->centro_pos[1]*UNIDAD, pieza->centro_pos[0]*UNIDAD);
                        pieza->centro_pos[0] += 1;
                        pieza->periferico_1_pos[0] += 1;
                        pieza->periferico_2_pos[0] += 1;
                        pieza->periferico_3_pos[0] += 1;
                        put_pieza_campo(pieza, campo);
                        i++;
                        print_pieza(pieza);
                        al_flip_display();
                        for(y = 0; y < 22; y++)
                        {
                            for(x = 0; x < 12; x++)
                            {
                                printf("%d", campo[y][x]);
                            }
                            printf("\n");
                            
                        }
                    }
                }
                if(events.keyboard.keycode == ALLEGRO_KEY_LEFT)
                {
                    detect_colision(campo, v, pieza);
                    if(v[0] == 0)
                    {
                        campo[pieza->centro_pos[1]][pieza->centro_pos[0]] = 0;
                        campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = 0;
                        campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = 0;
                        campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = 0;
                        clear_segmento(pieza->periferico_1_pos[1]*UNIDAD, pieza->periferico_1_pos[0]*UNIDAD);
                        clear_segmento(pieza->periferico_2_pos[1]*UNIDAD, pieza->periferico_2_pos[0]*UNIDAD);
                        clear_segmento(pieza->periferico_3_pos[1]*UNIDAD, pieza->periferico_3_pos[0]*UNIDAD);
                        clear_segmento(pieza->centro_pos[1]*UNIDAD, pieza->centro_pos[0]*UNIDAD);
                        pieza->centro_pos[0] -= 1;
                        pieza->periferico_1_pos[0] -= 1;
                        pieza->periferico_2_pos[0] -= 1;
                        pieza->periferico_3_pos[0] -= 1;
                        put_pieza_campo(pieza, campo);
                        i--;
                        print_pieza(pieza);
                        al_flip_display();
                        for(y = 0; y < 22; y++)
                        {
                            for(x = 0; x < 12; x++)
                            {
                                printf("%d", campo[y][x]);
                            }
                            printf("\n");
                        }
                    }
                }
                if(events.keyboard.keycode == ALLEGRO_KEY_UP)
                {
                     rotar_pieza(pieza,campo);
                     for(y = 0; y < 22; y++)
                     {
                         for(x = 0; x < 12; x++)
                         {
                             printf("%d", campo[y][x]);
                         }
                         printf("\n");
                     }
                 }
             }
         }
         al_stop_timer(timer);
        
        detect_colision(campo, v, pieza);
        if(v[1] == 0)
        {
        campo[pieza->centro_pos[1]][pieza->centro_pos[0]] = 0;
        campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = 0;
        campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = 0;
        campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = 0;
        clear_segmento(pieza->periferico_1_pos[1]*UNIDAD, pieza->periferico_1_pos[0]*UNIDAD);
        clear_segmento(pieza->periferico_2_pos[1]*UNIDAD, pieza->periferico_2_pos[0]*UNIDAD);
        clear_segmento(pieza->periferico_3_pos[1]*UNIDAD, pieza->periferico_3_pos[0]*UNIDAD);
        clear_segmento(pieza->centro_pos[1]*UNIDAD, pieza->centro_pos[0]*UNIDAD);
        pieza->centro_pos[1] += 1;
        pieza->periferico_1_pos[1] += 1;
        pieza->periferico_2_pos[1] += 1;
        pieza->periferico_3_pos[1] += 1;
        put_pieza_campo(pieza, campo);
        
        j++;
        print_pieza(pieza);
        al_flip_display();
        }
        else
        {
            campo[pieza->centro_pos[1]][pieza->centro_pos[0]] = 1;
            campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = 1;
            campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = 1;
            campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = 1;
        }
    }
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
}

void print_pieza(PIEZA *pieza)
{
    al_draw_bitmap(pieza->bitmap, pieza->centro_pos[0]*UNIDAD, pieza->centro_pos[1]*UNIDAD, 0);
    al_draw_bitmap(pieza->bitmap, pieza->periferico_1_pos[0]*UNIDAD, pieza->periferico_1_pos[1]*UNIDAD, 0);
    al_draw_bitmap(pieza->bitmap, pieza->periferico_2_pos[0]*UNIDAD, pieza->periferico_2_pos[1]*UNIDAD, 0);
    al_draw_bitmap(pieza->bitmap, pieza->periferico_3_pos[0]*UNIDAD, pieza->periferico_3_pos[1]*UNIDAD, 0);
                
    al_flip_display();
}

 void rotar_pieza(PIEZA *pieza, int campo[22][12])
 {
         int i,marca , j = 0, m = 0;
         int aux[8], v[8], aux2[3][2];
         if(pieza->nombre == 'L' || pieza->nombre == 'J' || pieza->nombre == 'S' || pieza->nombre == 'Z' || pieza->nombre == 'T')
         {
         clear_segmento(pieza->periferico_1_pos[1]*UNIDAD, pieza->periferico_1_pos[0]*UNIDAD);
         clear_segmento(pieza->periferico_2_pos[1]*UNIDAD, pieza->periferico_2_pos[0]*UNIDAD);
         clear_segmento(pieza->periferico_3_pos[1]*UNIDAD, pieza->periferico_3_pos[0]*UNIDAD);
         clear_segmento(pieza->centro_pos[1]*UNIDAD, pieza->centro_pos[0]*UNIDAD);
         
         v[0]=campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]-1];
         v[1]=campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]];
         v[2]=campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]+1];
         v[3]=campo[pieza->centro_pos[1]][pieza->centro_pos[0]+1];
         v[4]=campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]+1];
         v[5]=campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]];
         v[6]=campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]-1];
         v[7]=campo[pieza->centro_pos[1]][pieza->centro_pos[0]-1];
         
         for(i=0; i<8; i++)
         {
            if(v[i] == 2)
            {
            switch(i)
            {
                case 6:
                if(v[7] == 1 || v[0] == 1 || v[7] == 3 || v[0] == 3)
                {
                    marca = 0;
                    i = 8;
                }
                else
                {
                    marca = 1;
                }
                break;
                case 7:
                if(v[0] == 1 || v[1] == 1 || v[0] == 3 || v[1] == 3)
                {
                    marca = 0;
                    i = 8;
                }
                else
                {
                    marca = 1;
                }
                break;
                default:
                if(v[i+1] == 1 || v[i+2] == 1 || v[i+1] == 3 || v[i+2] == 3)
                {
                    marca = 0;
                    i = 8;
                }
                else
                {
                    marca = 1;
                }
                break;
            }
            }
         }
        
         if(marca == 1)//si marca es igual a 1 entonces puede rotar,si es igual a 0 no puede
         {
    
             printf("%d\n\n", m);
             
             if(v[0] != 1 && v[0] != 3)
                 aux[2] = v[0];
             else
                 aux[2] = 0;
             if(v[1] != 1 && v[1] != 3)
                 aux[3] = v[1];
             else
                 aux[3] = 0;
             if(v[2] != 1 && v[2] != 3)
                 aux[4] = v[2];
             else
                 aux[4] = 0;
             if(v[3] != 1 && v[3] != 3)
                 aux[5] = v[3];
             else
                 aux[5] = 0;
             if(v[4] != 1 && v[4] != 3)
                 aux[6] = v[4];
             else
                 aux[6] = 0;
             if(v[5] != 1 && v[5] != 3)
                 aux[7] = v[5];
             else
                 aux[7] = 0;
             if(v[6] != 1 && v[6] != 3)
                 aux[0] = v[6];
             else
                 aux[0] = 0;
             if(v[7] != 1 && v[7] != 3)
                 aux[1] = v[7];
             else
                 aux[1] = 0;
             
             for(i = 0; i < 8; i++)
             {
                 if(v[i] == 1)
                 {
                    aux[i] = 1;
                 }
                 else if(v[i] == 3)
                 {
                     aux[i] = 3;
                 }
             }
             
             campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]-1] = aux[0];
             if(aux[0] == 2)
             {
                 aux2[j][0] = pieza->centro_pos[0]-1;
                 aux2[j][1] = pieza->centro_pos[1]-1;
                 j++;
             }
             campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]] = aux[1];
             if(aux[1] == 2)
             {
                 aux2[j][0] = pieza->centro_pos[0];
                 aux2[j][1] = pieza->centro_pos[1]-1;
                 j++;
             }
             campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]+1] = aux[2];
             if(aux[2] == 2)
             {
                 aux2[j][0] = pieza->centro_pos[0]+1;
                 aux2[j][1] = pieza->centro_pos[1]-1;
                 j++;
             }
             campo[pieza->centro_pos[1]][pieza->centro_pos[0]+1] = aux[3];
             if(aux[3] == 2)
             {
                 aux2[j][0] = pieza->centro_pos[0]+1;
                 aux2[j][1] = pieza->centro_pos[1];
                 j++;
             }
             campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]+1] = aux[4];
             if(aux[4] == 2)
             {
                 aux2[j][0] = pieza->centro_pos[0]+1;
                 aux2[j][1] = pieza->centro_pos[1]+1;
                 j++;
             }
             campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]] = aux[5];
             if(aux[5] == 2)
             {
                 aux2[j][0] = pieza->centro_pos[0];
                 aux2[j][1] = pieza->centro_pos[1]+1;
                 j++;
             }
             campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]-1] = aux[6];
             if(aux[6] == 2)
             {
                 aux2[j][0] = pieza->centro_pos[0]-1;
                 aux2[j][1] = pieza->centro_pos[1]+1;
                 j++;
             }
             campo[pieza->centro_pos[1]][pieza->centro_pos[0]-1] = aux[7];
             if(aux[7] == 2)
             {
                 aux2[j][0] = pieza->centro_pos[0]-1;
                 aux2[j][1] = pieza->centro_pos[1];
                 j++;
             }
             
             pieza->periferico_1_pos[0] = aux2[0][0];
             pieza->periferico_1_pos[1] = aux2[0][1];
             pieza->periferico_2_pos[0] = aux2[1][0];
             pieza->periferico_2_pos[1] = aux2[1][1];
             pieza->periferico_3_pos[0] = aux2[2][0];
             pieza->periferico_3_pos[1] = aux2[2][1];
         }
         }
             
        print_pieza(pieza);
        al_flip_display();
 }
 
 void cargar_matriz(PIEZA *pieza, int campo[22][12])
 {
     campo[pieza->centro_pos[1]][pieza->centro_pos[0]] = 1;
     campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = 1;
     campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = 1;
     campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = 1;
 }
 
 void detect_colision(int campo[22][12], int *v, PIEZA *pieza)
 {     
     if(campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]-1] == 1 || campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]-1] == 1 || campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]-1] == 1 || campo[pieza->centro_pos[1]][pieza->centro_pos[0]-1] == 1 ||campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]-1] == 3 || campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]-1] == 3 || campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]-1] == 3 || campo[pieza->centro_pos[1]][pieza->centro_pos[0]-1] == 3)
     {
         v[0] = 1;
     }
     else
     {
         v[0] = 0;
     }
     
     if(campo[pieza->periferico_1_pos[1]+1][pieza->periferico_1_pos[0]] == 1 || campo[pieza->periferico_2_pos[1]+1][pieza->periferico_2_pos[0]] == 1 || campo[pieza->periferico_3_pos[1]+1][pieza->periferico_3_pos[0]] == 1 || campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]] == 1 || campo[pieza->periferico_1_pos[1]+1][pieza->periferico_1_pos[0]] == 3 || campo[pieza->periferico_2_pos[1]+1][pieza->periferico_2_pos[0]] == 3 || campo[pieza->periferico_3_pos[1]+1][pieza->periferico_3_pos[0]] == 3 || campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]] == 3)
     {
         v[1] = 1;
     }
     else
     {
         v[1] = 0;
     }
     
     if(campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]+1] == 1 || campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]+1] == 1 || campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]+1] == 1 || campo[pieza->centro_pos[1]][pieza->centro_pos[0]+1] == 1 || campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]+1] == 3 || campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]+1] == 3 || campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]+1] == 3 || campo[pieza->centro_pos[1]][pieza->centro_pos[0]+1] == 3)
     {
         v[2] = 1;
     }
     else
     {
         v[2] = 0;
     }
     
     if(campo[pieza->periferico_1_pos[1]-1][pieza->periferico_1_pos[0]] == 1 || campo[pieza->periferico_2_pos[1]-1][pieza->periferico_2_pos[0]] == 1 || campo[pieza->periferico_3_pos[1]-1][pieza->periferico_3_pos[0]] == 1 || campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]] == 1 || campo[pieza->periferico_1_pos[1]-1][pieza->periferico_1_pos[0]] == 3 || campo[pieza->periferico_2_pos[1]-1][pieza->periferico_2_pos[0]] == 3 || campo[pieza->periferico_3_pos[1]-1][pieza->periferico_3_pos[0]] == 3 || campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]] == 3)
     {
         v[3] = 1;
     }
     else
     {
         v[3] = 0;
     }
 }
 
 void clear_segmento(int y, int x)
{
    ALLEGRO_BITMAP *bitmap;
    bitmap = al_load_bitmap("Graphics/clear.png");
    al_draw_bitmap(bitmap, x, y, 0);
    al_convert_mask_to_alpha(bitmap, al_map_rgb(1,0,0));
    al_destroy_bitmap(bitmap);
}

void put_pieza_campo(PIEZA *pieza, int campo[22][12])
{
    campo[pieza->centro_pos[1]][pieza->centro_pos[0]] = 2;
    campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = 2;
    campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = 2;
    campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = 2;
}

/*void cargar_datos(void)
{
    FILE *fd;
    char buffer[20];
    
    fd = fopen("Data/Piezas","r");

    fread(buffer, )
    */
    
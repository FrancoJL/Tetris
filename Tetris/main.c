#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#define DIRECTORIO "Graphics/pieza_"
#define EXTENSION ".png"
#define UNIDAD 26

/* 0: Nada
 * 1: Marco
 * 2: Pieza color ROJO
 * 3: Pieza color NARANJA
 * 4: Pieza color AMARILLO
 * 5: Pieza color VERDE
 * 6: Pieza color CYAN
 * 7: Pieza color AZUL
 * 8: Pieza color VIOLETA
 */

struct datos
{
    int centro_pos[2];
    int periferico_1_pos[2];
    int periferico_2_pos[2];
    int periferico_3_pos[2];
    char nombre;
    char color[10];
};

struct nodo
{
    struct datos pieza;
    struct nodo *next;
};

int CtoI(char);
struct nodo *agregar_nodo(struct nodo **, struct nodo **);
void init_campo(int campo[22][12]);
void print_campo(int campo[22][12]);
int cargar_piezas(struct nodo **, struct nodo **);
void put_pieza_campo(struct datos *, int campo[22][12]);
void detect_colision(int campo[22][12], int *, struct datos *);
void move_pieza(struct datos *, double, int campo[22][12]);
void print(struct datos *);
void clear(struct datos *);

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
    FILE *fp;
    char buffer[20];
    int x, y;
    struct datos pieza_L;
    struct datos asd;
    struct datos palo;
    
    display = al_create_display(800, 600);
    
    init_campo(campo);
    
    pieza_L.centro_pos[0] = 5;
    pieza_L.centro_pos[1] = 2;
    
    pieza_L.periferico_1_pos[0] = 5;
    pieza_L.periferico_1_pos[1] = 1;
    
    pieza_L.periferico_2_pos[0] = 5;
    pieza_L.periferico_2_pos[1] = 3;
    
    pieza_L.periferico_3_pos[0] = 6;
    pieza_L.periferico_3_pos[1] = 3;
    
    pieza_L.nombre = 'L';
    
    campo[4][8] = -7;
    campo[5][8] = -7;
    campo[4][9] = -7;
    campo[5][9] = -7;
    campo[6][5] = -7;
    campo[6][6] = -7;
    campo[6][7] = -7;
    campo[6][8] = -7;
    
    strcpy(pieza_L.color, "rojo");
    strcpy(asd.color, "azul");
    strcpy(palo.color, "azul");
    
    put_pieza_campo(&pieza_L, campo);
    
    print_campo(campo);

    for(y = 0; y < 22; y++)
{
    for(x = 0; x < 12; x++)
    {
        printf("%d", campo[y][x]);
    }
    printf("\n");
                            
}
    
    al_flip_display();
    
    move_pieza(&pieza_L, 1.0, campo);
    
    al_rest(2.0);
    
    al_destroy_display(display);
    
    exit(EXIT_SUCCESS);
    
    /*fp = fopen("Data/Piezas", "r");
    
    if(fp == NULL)
    {
        return -1;
    }
    else
    {
        fscanf(fp, "%s", buffer);
        printf("nombre: %s\n", buffer);
        fscanf(fp, "%s", buffer);
        fscanf(fp, "%s", buffer);
        x = CtoI(buffer[1]);
        y = CtoI(buffer[3]);
        printf("(%d, %d)\n", x, y);
    }
    fclose(fp);*/
}

 void rotar_pieza(struct datos *pieza, int campo[22][12])
 {
         int i,marca , j = 0, m = 0;
         int aux[8], v[8], aux2[3][2];
         
         if(pieza->nombre != 'I')
         {
         v[0]=campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]-1];
         v[1]=campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]];
         v[2]=campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]+1];
         v[3]=campo[pieza->centro_pos[1]][pieza->centro_pos[0]+1];
         v[4]=campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]+1];
         v[5]=campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]];
         v[6]=campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]-1];
         v[7]=campo[pieza->centro_pos[1]][pieza->centro_pos[0]-1];
         
         for(i = 0; i < 8; i++)
         {
            if(v[i] > 1)
            {
            switch(i)
            {
                case 6:
                if(v[7] <= -2 || v[0] <= -2 || v[7] == 1 || v[0] == 1)
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
                if(v[0] <= -2 || v[1] <= -2 || v[0] == 1 || v[1] == 1)
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
                if(v[i+1] <= -2 || v[i+2] <= -2 || v[i+1] == 1 || v[i+2] == 1)
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
             if(v[0] > 1)
                 aux[2] = v[0];
             else
                 aux[2] = 0;
             if(v[1] > 1)
                 aux[3] = v[1];
             else
                 aux[3] = 0;
             if(v[2] > 1)
                 aux[4] = v[2];
             else
                 aux[4] = 0;
             if(v[3] > 1)
                 aux[5] = v[3];
             else
                 aux[5] = 0;
             if(v[4] > 1)
                 aux[6] = v[4];
             else
                 aux[6] = 0;
             if(v[5] > 1)
                 aux[7] = v[5];
             else
                 aux[7] = 0;
             if(v[6] > 1)
                 aux[0] = v[6];
             else
                 aux[0] = 0;
             if(v[7] > 1)
                 aux[1] = v[7];
             else
                 aux[1] = 0;
             
             for(i = 0; i < 8; i++)
             {
                 if(v[i] <= -2)
                 {
                    aux[i] = v[i];
                 }
                 else if(v[i] == 1)
                 {
                     aux[i] = 1;
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
        /* else if(pieza->nombre == 'I')
         {
                if(campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]] == 2)
                {
                    if(campo[pieza->centro_pos[1]-2][pieza->centro_pos[0]+1] != 1 || campo[pieza->centro_pos[1]-2][pieza->centro_pos[0]+2] != 1 || campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]+1] != 1 || campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]+2] != 1 || campo[pieza->centro_pos[1]][pieza->centro_pos[0]+1] != 1 || campo[pieza->centro_pos[1]][pieza->centro_pos[0]+2] != 1 || campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]-1] != 1 || campo[pieza->centro_pos[1]][pieza->centro_pos[0]-1] != 1 || campo[pieza->centro_pos[1]-2][pieza->centro_pos[0]+1] != 3 || campo[pieza->centro_pos[1]-2][pieza->centro_pos[0]+2] != 3 || campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]+1] != 3 || campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]+2] != 3 || campo[pieza->centro_pos[1]][pieza->centro_pos[0]+1] != 3 || campo[pieza->centro_pos[1]][pieza->centro_pos[0]+2] != 3 || campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]-1] != 3 || campo[pieza->centro_pos[1]][pieza->centro_pos[0]-1] != 3)
                    {
                        campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = 0;
                        campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = 0;
                        campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = 0;
                        
                        pieza->periferico_1_pos[0] = pieza->centro_pos[0]+1;
                        pieza->periferico_1_pos[1] = pieza->centro_pos[1];
                        
                        pieza->periferico_2_pos[0] = pieza->centro_pos[0]+2;
                        pieza->periferico_2_pos[1] = pieza->centro_pos[1];
                        
                        pieza->periferico_3_pos[0] = pieza->centro_pos[0]-1;
                        pieza->periferico_3_pos[1] = pieza->centro_pos[1];
                    }
    
             }
             else
             {
                campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = 0;
                campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = 0;
                campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = 0;
                
                pieza->periferico_1_pos[0] = pieza->centro_pos[0];
                pieza->periferico_1_pos[1] = pieza->centro_pos[1]-1;
                
                pieza->periferico_2_pos[0] = pieza->centro_pos[0];
                pieza->periferico_2_pos[1] = pieza->centro_pos[1]-2;
                
                pieza->periferico_3_pos[0] = pieza->centro_pos[0];
                pieza->periferico_3_pos[1] = pieza->centro_pos[1]+1;
                
             }
             campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = 2;
             campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = 2;
             campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = 2;
         }*/
 }

int CtoI(char a)
{
    switch(a)
    {
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case '0': return 0;
    }
}
        
struct nodo *agregar_nodo(struct nodo **h, struct nodo **l)
{
    struct nodo *aux;
    
    aux = (struct nodo *)malloc(sizeof(struct nodo));
 
    if(aux = NULL)
    {
        return NULL;
    }
    
    if(*h == NULL)
    {
        *h = aux;
        *l = aux;
        aux->next = NULL;
    }
    else
    {
        (*l)->next = aux;
        *l = aux;
        aux->next = NULL;
    }
    
    return aux;
}

void init_campo(int campo[22][12])
{
    int i, j;
    
    for(j = 0; j < 22; j++)
    {
        for(i = 0; i < 12; i++)
        {
            campo[j][i] = 1;
        }
    }
    
    for(j = 1; j < 21; j++)
    {
        for(i = 1; i < 11; i++)
        {
            campo[j][i] = 0;
        }
    }
}

void print_campo(int campo[22][12])
{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_BITMAP *bitmap;
    int i, j;
    
    for(j = 0; j < 22; j++)
    {
        for(i = 0; i < 12; i++)
        {
            switch(campo[j][i])
            {
                case 1: bitmap = al_load_bitmap("Graphics/pieza_limite.png");
                        al_draw_bitmap(bitmap, i*26, j*26, 0);
                        break;
                        
                case 2: bitmap = al_load_bitmap("Graphics/pieza_rojo.png");
                        al_draw_bitmap(bitmap, i*26, j*26, 0);
                        break;
                    
                case 3: bitmap = al_load_bitmap("Graphics/pieza_naranja.png");
                        al_draw_bitmap(bitmap, i*26, j*26, 0);
                        break;
                        
                case 4: bitmap = al_load_bitmap("Graphics/pieza_amarillo.png");
                        al_draw_bitmap(bitmap, i*26, j*26, 0);
                        break;
                        
                case 5: bitmap = al_load_bitmap("Graphics/pieza_verde.png");
                        al_draw_bitmap(bitmap, i*26, j*26, 0);
                        break;
                        
                case 6: bitmap = al_load_bitmap("Graphics/pieza_cyan.png");
                        al_draw_bitmap(bitmap, i*26, j*26, 0);
                        break;
                        
                case 7: bitmap = al_load_bitmap("Graphics/pieza_azul.png");
                        al_draw_bitmap(bitmap, i*26, j*26, 0);
                        break;
                        
                case 8: bitmap = al_load_bitmap("Graphics/pieza_violeta.png");
                        al_draw_bitmap(bitmap, i*26, j*26, 0);
                        break;
                        
                case -2: bitmap = al_load_bitmap("Graphics/pieza_rojo.png");
                        al_draw_bitmap(bitmap, i*26, j*26, 0);
                        break;
                    
                case -3: bitmap = al_load_bitmap("Graphics/pieza_naranja.png");
                        al_draw_bitmap(bitmap, i*26, j*26, 0);
                        break;
                        
                case -4: bitmap = al_load_bitmap("Graphics/pieza_amarillo.png");
                        al_draw_bitmap(bitmap, i*26, j*26, 0);
                        break;
                        
                case -5: bitmap = al_load_bitmap("Graphics/pieza_verde.png");
                        al_draw_bitmap(bitmap, i*26, j*26, 0);
                        break;
                        
                case -6: bitmap = al_load_bitmap("Graphics/pieza_cyan.png");
                        al_draw_bitmap(bitmap, i*26, j*26, 0);
                        break;
                        
                case -7: bitmap = al_load_bitmap("Graphics/pieza_azul.png");
                        al_draw_bitmap(bitmap, i*26, j*26, 0);
                        break;
                        
                case -8: bitmap = al_load_bitmap("Graphics/pieza_violeta.png");
                        al_draw_bitmap(bitmap, i*26, j*26, 0);
                        break;
            }
        }
    }
    al_flip_display();
    al_destroy_bitmap(bitmap);
}

int cargar_piezas(struct nodo **h, struct nodo **l)
{
    FILE *fp;
    struct nodo *aux;
    char buffer[20];
    
    fp = fopen("Data/Piezas", "r");
    
    if(fp == NULL)
    {
        return -1;
    }
    else
    {
        aux = agregar_nodo(h, l);
        fscanf(fp, "%c", &(aux->pieza.nombre));
        fscanf(fp, "%s", buffer);
        fscanf(fp, "%s", buffer);
        aux->pieza.centro_pos[0] = CtoI(buffer[1]);
        aux->pieza.centro_pos[1] = CtoI(buffer[3]);
        fscanf(fp, "%s", buffer);
        fscanf(fp, "%s", buffer);
        aux->pieza.periferico_1_pos[0] = CtoI(buffer[1]);
        aux->pieza.periferico_1_pos[1] = CtoI(buffer[3]);
        fscanf(fp, "%s", buffer);
        fscanf(fp, "%s", buffer);
        aux->pieza.periferico_2_pos[0] = CtoI(buffer[1]);
        aux->pieza.periferico_2_pos[1] = CtoI(buffer[3]);
        fscanf(fp, "%s", buffer);
        fscanf(fp, "%s", buffer);
        aux->pieza.periferico_3_pos[0] = CtoI(buffer[1]);
        aux->pieza.periferico_3_pos[1] = CtoI(buffer[3]);
        fscanf(fp, "%s", buffer);
        fscanf(fp, "%s", aux->pieza.color);
        fscanf(fp, "%s", buffer);
        
        while(!feof(fp))
        {
            aux = agregar_nodo(h, l);
            fscanf(fp, "%c", &(aux->pieza.nombre));
            fscanf(fp, "%s", buffer);
            fscanf(fp, "%s", buffer);
            aux->pieza.centro_pos[0] = CtoI(buffer[1]);
            aux->pieza.centro_pos[1] = CtoI(buffer[3]);
            fscanf(fp, "%s", buffer);
            fscanf(fp, "%s", buffer);
            aux->pieza.periferico_1_pos[0] = CtoI(buffer[1]);
            aux->pieza.periferico_1_pos[1] = CtoI(buffer[3]);
            fscanf(fp, "%s", buffer);
            fscanf(fp, "%s", buffer);
            aux->pieza.periferico_2_pos[0] = CtoI(buffer[1]);
            aux->pieza.periferico_2_pos[1] = CtoI(buffer[3]);
            fscanf(fp, "%s", buffer);
            fscanf(fp, "%s", buffer);
            aux->pieza.periferico_3_pos[0] = CtoI(buffer[1]);
            aux->pieza.periferico_3_pos[1] = CtoI(buffer[3]);
            fscanf(fp, "%s", buffer);
            fscanf(fp, "%s", aux->pieza.color);
            fscanf(fp, "%s", buffer);
        }
    }
    return 1;
}

void move_pieza(struct datos *pieza, double velocidad, int campo[22][12])
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
                        clear(pieza);
                        pieza->centro_pos[0] += 1;
                        pieza->periferico_1_pos[0] += 1;
                        pieza->periferico_2_pos[0] += 1;
                        pieza->periferico_3_pos[0] += 1;
//                         al_clear_to_color(al_map_rgb(0, 0, 0));
                        put_pieza_campo(pieza, campo);
                        print(pieza);
//                         print_campo(campo);
                        al_flip_display();
                        i++;
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
                        clear(pieza);
                        pieza->centro_pos[0] -= 1;
                        pieza->periferico_1_pos[0] -= 1;
                        pieza->periferico_2_pos[0] -= 1;
                        pieza->periferico_3_pos[0] -= 1;
//                         al_clear_to_color(al_map_rgb(0, 0, 0));
                        put_pieza_campo(pieza, campo);
                        print(pieza);
//                         print_campo(campo);
                        al_flip_display();
                        i--;
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
                    clear(pieza);
                    rotar_pieza(pieza,campo);
//                     al_clear_to_color(al_map_rgb(0, 0, 0));
                    put_pieza_campo(pieza, campo);
                    print(pieza);
//                     print_campo(campo);
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
         }
         al_stop_timer(timer);
        
        detect_colision(campo, v, pieza);
        if(v[1] == 0)
        {
        campo[pieza->centro_pos[1]][pieza->centro_pos[0]] = 0;
        campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = 0;
        campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = 0;
        campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = 0;
        clear(pieza);
        pieza->centro_pos[1] += 1;
        pieza->periferico_1_pos[1] += 1;
        pieza->periferico_2_pos[1] += 1;
        pieza->periferico_3_pos[1] += 1;
        put_pieza_campo(pieza, campo);
//         al_clear_to_color(al_map_rgb(0, 0, 0));
        print(pieza);
//         print_campo(campo);
        al_flip_display();
        j++;
        for(y = 0; y < 22; y++)
        {
            for(x = 0; x < 12; x++)
            {
                printf("%d", campo[y][x]);
            }
            printf("\n");
        }
        }
        else
        {
            /*campo[pieza->centro_pos[1]][pieza->centro_pos[0]] = campo[pieza->centro_pos[1]][pieza->centro_pos[0]]*(-1);
            campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]]*(-1);
            campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]]*(-1);
            campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]]*(-1);*/
        }
    }
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
}

void detect_colision(int campo[22][12], int *v, struct datos *pieza)
 {     
     if(campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]-1] <= -2 || campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]-1] <= -2 || campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]-1] <= -2 || campo[pieza->centro_pos[1]][pieza->centro_pos[0]-1] <= -2 ||campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]-1] == 1 || campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]-1] == 1 || campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]-1] == 1 || campo[pieza->centro_pos[1]][pieza->centro_pos[0]-1] == 1)
     {
         v[0] = 1;
     }
     else
     {
         v[0] = 0;
     }
     
     if(campo[pieza->periferico_1_pos[1]+1][pieza->periferico_1_pos[0]] <= -2 || campo[pieza->periferico_2_pos[1]+1][pieza->periferico_2_pos[0]] <= -2 || campo[pieza->periferico_3_pos[1]+1][pieza->periferico_3_pos[0]] <= -2 || campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]] <= -2 || campo[pieza->periferico_1_pos[1]+1][pieza->periferico_1_pos[0]] == 1 || campo[pieza->periferico_2_pos[1]+1][pieza->periferico_2_pos[0]] == 1 || campo[pieza->periferico_3_pos[1]+1][pieza->periferico_3_pos[0]] == 1 || campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]] == 1)
     {
         v[1] = 1;
     }
     else
     {
         v[1] = 0;
     }
     
     if(campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]+1] <= -2 || campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]+1] <= -2 || campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]+1] <= -2 || campo[pieza->centro_pos[1]][pieza->centro_pos[0]+1] <= -2 || campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]+1] == 1 || campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]+1] == 1 || campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]+1] == 1 || campo[pieza->centro_pos[1]][pieza->centro_pos[0]+1] == 1)
     {
         v[2] = 1;
     }
     else
     {
         v[2] = 0;
     }
     
     if(campo[pieza->periferico_1_pos[1]-1][pieza->periferico_1_pos[0]] <= -2 || campo[pieza->periferico_2_pos[1]-1][pieza->periferico_2_pos[0]] <= -2 || campo[pieza->periferico_3_pos[1]-1][pieza->periferico_3_pos[0]] <= -2 || campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]] <= -2 || campo[pieza->periferico_1_pos[1]-1][pieza->periferico_1_pos[0]] == 3 || campo[pieza->periferico_2_pos[1]-1][pieza->periferico_2_pos[0]] == 3 || campo[pieza->periferico_3_pos[1]-1][pieza->periferico_3_pos[0]] == 3 || campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]] == 3)
     {
         v[3] = 1;
     }
     else
     {
         v[3] = 0;
     }
 }
 
void put_pieza_campo(struct datos *pieza, int campo[22][12])
{
    int i;
    
    if(strcmp(pieza->color, "rojo") == 0)
        i = 2;
    else if(strcmp(pieza->color, "naranja") == 0)
        i = 3;
    else if(strcmp(pieza->color, "amarillo") == 0)
        i = 4;
    else if(strcmp(pieza->color, "verde") == 0)
        i = 5;
    else if(strcmp(pieza->color, "cyan") == 0)
        i = 6;
    else if(strcmp(pieza->color, "azul") == 0)
        i = 7;
    else if(strcmp(pieza->color, "violeta") == 0)
        i = 8;
    
    campo[pieza->centro_pos[1]][pieza->centro_pos[0]] = i;
    campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = i;
    campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = i;
    campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = i;
}

void clear(struct datos *pieza)
{
    ALLEGRO_BITMAP *bitmap;
    
    bitmap = al_load_bitmap("Graphics/clear.png");
    
    al_draw_bitmap(bitmap, pieza->centro_pos[0]*26, pieza->centro_pos[1]*26, 0);
    al_draw_bitmap(bitmap, pieza->periferico_1_pos[0]*26, pieza->periferico_1_pos[1]*26, 0);
    al_draw_bitmap(bitmap, pieza->periferico_2_pos[0]*26, pieza->periferico_2_pos[1]*26, 0);
    al_draw_bitmap(bitmap, pieza->periferico_3_pos[0]*26, pieza->periferico_3_pos[1]*26, 0);
    
    al_destroy_bitmap(bitmap);
}

void print(struct datos *pieza)
{
    ALLEGRO_BITMAP *bitmap;
    
    if(strcmp(pieza->color, "rojo") == 0)
        bitmap = al_load_bitmap("Graphics/pieza_rojo.png");
    if(strcmp(pieza->color, "naranja") == 0)
        bitmap = al_load_bitmap("Graphics/pieza_naranja.png");
    if(strcmp(pieza->color, "amarillo") == 0)
        bitmap = al_load_bitmap("Graphics/pieza_amarillo.png");
    if(strcmp(pieza->color, "verde") == 0)
        bitmap = al_load_bitmap("Graphics/pieza_verde.png");
    if(strcmp(pieza->color, "cyan") == 0)
        bitmap = al_load_bitmap("Graphics/pieza_cyan.png");
    if(strcmp(pieza->color, "azul") == 0)
        bitmap = al_load_bitmap("Graphics/pieza_azul.png");
    if(strcmp(pieza->color, "violeta") == 0)
        bitmap = al_load_bitmap("Graphics/pieza_violeta.png");
    
    al_draw_bitmap(bitmap, pieza->centro_pos[0]*26, pieza->centro_pos[1]*26, 0);
    al_draw_bitmap(bitmap, pieza->periferico_1_pos[0]*26, pieza->periferico_1_pos[1]*26, 0);
    al_draw_bitmap(bitmap, pieza->periferico_2_pos[0]*26, pieza->periferico_2_pos[1]*26, 0);
    al_draw_bitmap(bitmap, pieza->periferico_3_pos[0]*26, pieza->periferico_3_pos[1]*26, 0);
 
    al_destroy_bitmap(bitmap);
}
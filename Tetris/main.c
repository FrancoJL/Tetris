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
 * Numeros negativos: Basura
 */

struct datos
{
    int centro_pos[2];
    int periferico_1_pos[2];
    int periferico_2_pos[2];
    int periferico_3_pos[2];
    char nombre;
    char color[10];
    int sign;
};

struct nodo
{
    struct datos pieza;
    struct nodo *next;
};

int CtoI(char);
void agregar_nodo(struct nodo **h,struct nodo *aux);
void init_campo(int campo[22][12]);
void print_campo(int campo[22][12]);
int cargar_piezas(struct nodo **);
void put_pieza_campo(struct datos *, int campo[22][12]);
void detect_colision(int campo[22][12], int *, struct datos *);
void move_pieza(struct datos *, double, int campo[22][12]);
void print(struct datos *);
void clear(struct datos *);
struct datos prandom(struct nodo **);
int delete_line(int campo[22][12]);
int comprobar(struct datos, int campo[22][12]);
void print_next(struct datos);

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
    
    int campo[22][12], marca = 1;
    ALLEGRO_DISPLAY *display;
    struct nodo *h = NULL, *l = NULL;
    struct datos pieza, pieza_next;
    
    display = al_create_display(800, 600);
    
    cargar_piezas(&h);
    init_campo(campo);
    
    srand(getpid());
    
    pieza = prandom(&h);
    pieza_next = prandom(&h);
    print_campo(campo);
    
    do
    {
        if(comprobar(pieza, campo) == -1)
        {
            marca = 0;
        }
        put_pieza_campo(&pieza, campo);
        print_campo(campo);
        print_next(pieza_next);
        print_next(pieza_next);
        print_next(pieza_next);
        print_next(pieza_next);
        al_flip_display();
        move_pieza(&pieza, 0.25, campo);
        pieza = pieza_next;
        pieza_next = prandom(&h);
    }while(marca == 1);
    
    al_destroy_display(display);
    
    exit(EXIT_SUCCESS);
}

 void rotar_pieza(struct datos *pieza, int campo[22][12])
 {
     int i,marca , j = 0, m = 0;
     int aux[8], v[8], aux2[3][2];
         
     if(pieza->nombre != 'I' && pieza->nombre != 'O')
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
             if(aux[0] >= 2)
             {
                 aux2[j][0] = pieza->centro_pos[0]-1;
                 aux2[j][1] = pieza->centro_pos[1]-1;
                 j++;
             }
             campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]] = aux[1];
             if(aux[1] >= 2)
             {
                 aux2[j][0] = pieza->centro_pos[0];
                 aux2[j][1] = pieza->centro_pos[1]-1;
                 j++;
             }
             campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]+1] = aux[2];
             if(aux[2] >= 2)
             {
                 aux2[j][0] = pieza->centro_pos[0]+1;
                 aux2[j][1] = pieza->centro_pos[1]-1;
                 j++;
             }
             campo[pieza->centro_pos[1]][pieza->centro_pos[0]+1] = aux[3];
             if(aux[3] >= 2)
             {
                 aux2[j][0] = pieza->centro_pos[0]+1;
                 aux2[j][1] = pieza->centro_pos[1];
                 j++;
             }
             campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]+1] = aux[4];
             if(aux[4] >= 2)
             {
                 aux2[j][0] = pieza->centro_pos[0]+1;
                 aux2[j][1] = pieza->centro_pos[1]+1;
                 j++;
             }
             campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]] = aux[5];
             if(aux[5] >= 2)
             {
                 aux2[j][0] = pieza->centro_pos[0];
                 aux2[j][1] = pieza->centro_pos[1]+1;
                 j++;
             }
             campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]-1] = aux[6];
             if(aux[6] >= 2)
             {
                 aux2[j][0] = pieza->centro_pos[0]-1;
                 aux2[j][1] = pieza->centro_pos[1]+1;
                 j++;
             }
             campo[pieza->centro_pos[1]][pieza->centro_pos[0]-1] = aux[7];
             if(aux[7] >= 2)
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
    else
    {
        if(pieza->nombre == 'I')
        {
            if(pieza->sign == 0)
            {
                if(campo[pieza->centro_pos[1]-1][pieza->centro_pos[0]] == 0 && campo[pieza->centro_pos[1]+1][pieza->centro_pos[0]] == 0 && campo[pieza->centro_pos[1]+2][pieza->centro_pos[0]] == 0)
                {
                    i = campo[pieza->centro_pos[1]][pieza->centro_pos[0]];
                    campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = 0;
                    campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = 0;
                    campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = 0;
                    pieza->periferico_1_pos[0] = pieza->periferico_1_pos[0] + 1;
                    pieza->periferico_1_pos[1] = pieza->periferico_1_pos[1] - 1;
                    pieza->periferico_2_pos[0] = pieza->periferico_2_pos[0] - 1;
                    pieza->periferico_2_pos[1] = pieza->periferico_2_pos[1] + 1;
                    pieza->periferico_3_pos[0] = pieza->periferico_3_pos[0] - 2;
                    pieza->periferico_3_pos[1] = pieza->periferico_3_pos[1] + 2;
                    campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = i;
                    campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = i;
                    campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = i;
                    pieza->sign = 1;
                }
            }
            else
            {
                if(campo[pieza->centro_pos[1]][pieza->centro_pos[0]-1] == 0 && campo[pieza->centro_pos[1]][pieza->centro_pos[0]+1] == 0 && campo[pieza->centro_pos[1]][pieza->centro_pos[0]+2] == 0)
                {
                    i = campo[pieza->centro_pos[1]][pieza->centro_pos[0]];
                    campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = 0;
                    campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = 0;
                    campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = 0;
                    pieza->periferico_1_pos[0] = pieza->periferico_1_pos[0] - 1;
                    pieza->periferico_1_pos[1] = pieza->periferico_1_pos[1] + 1;
                    pieza->periferico_2_pos[0] = pieza->periferico_2_pos[0] + 1;
                    pieza->periferico_2_pos[1] = pieza->periferico_2_pos[1] - 1;
                    pieza->periferico_3_pos[0] = pieza->periferico_3_pos[0] + 2;
                    pieza->periferico_3_pos[1] = pieza->periferico_3_pos[1] - 2;
                    campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = i;
                    campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = i;
                    campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = i;
                    pieza->sign = 0;
                }
            }
        }
    }
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
        
void agregar_nodo(struct nodo **h,struct nodo *aux)
{
    struct nodo *l;
    if((*h)==NULL)
    {
        (*h)=aux;
        return;
    }
    else
    {
        l=(*h);
        while(l->next!=NULL)
        {
            l=l->next;
        }
        l->next=aux;
    }
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

int cargar_piezas(struct nodo **h)
{
    FILE *fp;
    struct nodo *aux;
    char buffer[20];
    char a,b;
    fp = fopen("Data/Piezas", "r");
    if(fp == NULL)
    {
        printf("ERROR AL CARGAR ARCHIVO\n");
        return -1;
    }
    else
    {
        while(!feof(fp))
        {
            aux=(struct nodo*)malloc(sizeof(struct nodo));
            fscanf(fp, "%c\n", &(aux->pieza.nombre));
            fscanf(fp, "%s ", buffer);
            fscanf(fp, "%c %c\n",&a,&b);
            aux->pieza.centro_pos[0] = CtoI(a);
            aux->pieza.centro_pos[1] = CtoI(b);
            fscanf(fp, "%s ", buffer);
            fscanf(fp, "%c %c\n",&a,&b);
            aux->pieza.periferico_1_pos[0] = CtoI(a);
            aux->pieza.periferico_1_pos[1] = CtoI(b);
            fscanf(fp, "%s ", buffer);
            fscanf(fp, "%c %c\n", &a,&b);
            aux->pieza.periferico_2_pos[0] = CtoI(a);
            aux->pieza.periferico_2_pos[1] = CtoI(b);
            fscanf(fp, "%s ", buffer);
            fscanf(fp, "%c %c\n",&a,&b);
            aux->pieza.periferico_3_pos[0] = CtoI(a);
            aux->pieza.periferico_3_pos[1] = CtoI(b);
            fscanf(fp, "%s ", buffer);
            fscanf(fp, "%s\n", aux->pieza.color);
            fscanf(fp, "%s\n", buffer);
            aux->pieza.sign = 0;
            aux->next=NULL;
            agregar_nodo(h,aux);
        }
    }
    fclose(fp);
    return 1;
}

void move_pieza(struct datos *pieza, double velocidad, int campo[22][12])
{
    int marca = 0, v[4], x, y, n = 1;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    ALLEGRO_EVENT events;
    ALLEGRO_KEYBOARD_STATE state;
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    while(marca == 0)
    {
        timer = al_create_timer(velocidad);
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
                        put_pieza_campo(pieza, campo);
                        print(pieza);
                        al_flip_display();
//                         for(y = 0; y < 22; y++)
//                         {
//                             for(x = 0; x < 12; x++)
//                             {
//                                 printf("%d", campo[y][x]);
//                             }
//                             printf("\n");
//                         }
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
                        put_pieza_campo(pieza, campo);
                        print(pieza);
                        al_flip_display();
//                         for(y = 0; y < 22; y++)
//                         {
//                             for(x = 0; x < 12; x++)
//                             {
//                                 printf("%d", campo[y][x]);
//                             }
//                             printf("\n");
//                                                     
//                         }
                    }
                }
                if(events.keyboard.keycode == ALLEGRO_KEY_UP)
                {
                    clear(pieza);
                    rotar_pieza(pieza,campo);
//                     for(y = 0; y < 22; y++)
//                     {
//                         for(x = 0; x < 12; x++)
//                         {
//                             printf("%d", campo[y][x]);
//                         }
//                         printf("\n");
//                     }
                    put_pieza_campo(pieza, campo);
                    print(pieza);
                    al_flip_display();
                }
                if(events.keyboard.keycode == ALLEGRO_KEY_DOWN)
                {
                    do
                    {
                        al_get_keyboard_state(&state);
                        if(al_key_down(&state, ALLEGRO_KEY_DOWN) == true)
                        {
                            n = 0;
                            velocidad = 0.03;
                        }
                        else
                        {
                            n = 1;
                        }
                    }while(n == 1);
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
        print(pieza);
        al_flip_display();
//         for(y = 0; y < 22; y++)
//         {
//             for(x = 0; x < 12; x++)
//             {
//                 printf("%d", campo[y][x]);
//             }
//             printf("\n");
//         }
        }
        else
        {
            marca = 1;
            campo[pieza->centro_pos[1]][pieza->centro_pos[0]] = -(campo[pieza->centro_pos[1]][pieza->centro_pos[0]]);
            campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = -(campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]]);
            campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = -(campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]]);
            campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = -(campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]]);
//             for(y = 0; y < 22; y++)
//             {
//                 for(x = 0; x < 12; x++)
//                 {
//                     printf("%d", campo[y][x]);
//                 }
//                 printf("\n");
//             }
            delete_line(campo);
            al_clear_to_color(al_map_rgb(0, 0, 0));
            print_campo(campo);
            al_flip_display();
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
 
int comprobar(struct datos pieza, int campo[22][12])
{
    switch(pieza.nombre)
    {
        case 'O':
            if(campo[1][6] < 0 || campo[2][6] < 0 || campo[2][5] < 0 || campo[1][5] < 0)
                return -1;
            
        case 'L':
            if(campo[1][5] < 0 || campo[2][5] < 0 || campo[3][5] < 0 || campo[3][6] < 0)
                return -1;
            
        case 'J':
            if(campo[1][6] < 0 || campo[2][6] < 0 || campo[3][6] < 0 || campo[3][5] < 0)
                return -1;
        
        case 'S':
            if(campo[1][5] < 0 || campo[2][5] < 0 || campo[1][6] < 0 || campo[2][4] < 0)
                return -1;
            
        case 'Z':
            if(campo[1][5] < 0 || campo[2][5] < 0 || campo[1][4] < 0 || campo[2][6] < 0)
                return -1;
            
        case 'I':
            if(campo[1][4] < 0 || campo[1][5] < 0 || campo[1][6] < 0 || campo[1][7] < 0)
                return -1;
            
        case 'T':
            if(campo[1][6] < 0 || campo[2][6] < 0 || campo[1][5] < 0 || campo[1][7] < 0)
                return -1;
    }
    return 0;
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

void print_next(struct datos pieza)
{
    ALLEGRO_BITMAP *bitmap;
    
    if(strcmp(pieza.color, "rojo") == 0)
        bitmap = al_load_bitmap("Graphics/pieza_rojo.png");
    if(strcmp(pieza.color, "naranja") == 0)
        bitmap = al_load_bitmap("Graphics/pieza_naranja.png");
    if(strcmp(pieza.color, "amarillo") == 0)
        bitmap = al_load_bitmap("Graphics/pieza_amarillo.png");
    if(strcmp(pieza.color, "verde") == 0)
        bitmap = al_load_bitmap("Graphics/pieza_verde.png");
    if(strcmp(pieza.color, "cyan") == 0)
        bitmap = al_load_bitmap("Graphics/pieza_cyan.png");
    if(strcmp(pieza.color, "azul") == 0)
        bitmap = al_load_bitmap("Graphics/pieza_azul.png");
    if(strcmp(pieza.color, "violeta") == 0)
        bitmap = al_load_bitmap("Graphics/pieza_violeta.png");
    
    al_draw_bitmap(bitmap, (pieza.centro_pos[0]*26)+(26*10), pieza.centro_pos[1]*26+(26*3), 0);
    al_draw_bitmap(bitmap, (pieza.periferico_1_pos[0]*26)+(26*10), pieza.periferico_1_pos[1]*26+(26*3), 0);
    al_draw_bitmap(bitmap, (pieza.periferico_2_pos[0]*26)+(26*10), pieza.periferico_2_pos[1]*26+(26*3), 0);
    al_draw_bitmap(bitmap, (pieza.periferico_3_pos[0]*26)+(26*10), pieza.periferico_3_pos[1]*26+(26*3), 0);
 
    al_destroy_bitmap(bitmap);
}

struct datos prandom(struct nodo **h)
{
    int m, n;
    struct nodo *aux;
    
    m = rand() % 7;
    
    for(aux = *h, n = 0; n < m; n++, aux = aux->next);
    
    return aux->pieza;
}

int delete_line(int campo[22][12])
{
    int i, j, k, marca, lineas = 0;
    for(i = 1; i < 21; i++)         //desde linea de arriba
    {
        marca = 0;
        for(j = 1; j < 11; j++)
        {
            if(campo[i][j] < 0)     //solo si hay basura
                marca++;
            else                    //si no hay basura, se sale pasa a la otra linea
                j = 20;             //asigne j=20 para que salga del for
        }
        if(marca == 10)
        {
            for(k = i; k > 0; k--)
            {
                if(k != 1)
                {
                    for(j = 1; j < 11; j++)//no estoy contemplando si fuera la primera linea
                    campo[k][j] = campo[k-1][j];
                }
            }
            lineas++;
        }
    }
    return lineas;
}
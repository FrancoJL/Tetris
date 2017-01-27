// menu server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
struct letras
{
    char nombre;
    int pos01[2];
    int pos02[2];
    int pos03[2];
    int pos04[2];
    int pos05[2];
    int pos06[2];
    int pos07[2];
    int pos08[2];
    int pos09[2];
    int pos10[2];
    int pos11[2];
};
typedef struct nodo_l
{
    struct letras caracter;
    struct nodo_l *next;
}NODO_L;

void init_campo_2(int campo_2[16][25]);
void print_campo(int campo_2[16][25], ALLEGRO_BITMAP *colores[8]);
void cargar_letras(NODO_L **h);
void save_pos(char buffer[20],int a,int b,NODO_L *aux);
void agregar_nodo_l(NODO_L **h,NODO_L *aux);
void descargar_lista_l(NODO_L **h);
void put_pieza_campo_2(struct letras *caracter, int campo_2[16][25]);
void move_letra(int campo_2[16][25],int a);
void move_letras(int campo_2[16][25],ALLEGRO_BITMAP *colores[9]);
void borde(int campo_2[16][25],int n);
void opciones(float);
int opcion_menu(int j);
int menu(ALLEGRO_DISPLAY *display,ALLEGRO_BITMAP *colores[9]);
int main()
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
    ALLEGRO_DISPLAY *display;
    al_set_new_window_position(0, 0);
    display = al_create_display(960, 600);
    ALLEGRO_BITMAP *colores[9];
    int i;
    colores[0] = al_load_bitmap("Graphics/Piezas/clear.png");
    colores[1] = al_load_bitmap("Graphics/Piezas/pieza_gris.png");
    colores[2] = al_load_bitmap("Graphics/Piezas/pieza_rojo.png");
    colores[3] = al_load_bitmap("Graphics/Piezas/pieza_naranja.png");
    colores[4] = al_load_bitmap("Graphics/Piezas/pieza_amarillo.png");
    colores[5] = al_load_bitmap("Graphics/Piezas/pieza_verde.png");
    colores[6] = al_load_bitmap("Graphics/Piezas/pieza_cyan.png");
    colores[7] = al_load_bitmap("Graphics/Piezas/pieza_azul.png");
    colores[8] = al_load_bitmap("Graphics/Piezas/pieza_violeta.png");
    i=menu(display,colores);
    for(i = 0; i < 9; i++)
    {
        al_destroy_bitmap(colores[i]);
    }
    al_destroy_display(display);
    exit(EXIT_SUCCESS);
}
int menu(ALLEGRO_DISPLAY *display,ALLEGRO_BITMAP *colores[9])
{
    ALLEGRO_COLOR color_white = al_map_rgb(255,255,255),color_black = al_map_rgb(0,0,0);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    ALLEGRO_EVENT events;
    ALLEGRO_TIMER *timer;
    int campo_2 [16][25],i=0,j=0,salida=0,marca[4]={0,0,0,0};
    NODO_L *h = NULL,*aux =NULL;
    init_campo_2(campo_2);
    cargar_letras(&h);
    for(aux=h;aux!=NULL;aux=aux->next)
        put_pieza_campo_2(&(aux->caracter),campo_2);
    print_campo(campo_2,colores);
    al_flip_display();
    move_letras(campo_2,colores);
    opciones(0.2);
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    while(salida >= 0)
    {
        timer = al_create_timer(0.1);
        al_set_timer_count(timer, 0);
        al_start_timer(timer);
        al_get_next_event(event_queue, &events);
        if(i>8)
            i=0;
        borde(campo_2,i);
        i++;
        print_campo(campo_2,colores);
        al_flip_display();
        while(al_get_timer_count(timer) < 0.5 && salida >= 0)
        {
                if(events.type == ALLEGRO_EVENT_KEY_DOWN)
                {
                    if(events.keyboard.keycode == ALLEGRO_KEY_DOWN)
                        marca[0] = 0;
                    else if(events.keyboard.keycode == ALLEGRO_KEY_UP)
                        marca[1] = 0;
                    else if(events.keyboard.keycode == ALLEGRO_KEY_ENTER)
                        marca[2] = 0;
                    else if(events.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                        marca[3] = 0;
                }
                if(events.type == ALLEGRO_EVENT_KEY_UP)
                {
                    switch(events.keyboard.keycode)
                    {
                        case ALLEGRO_KEY_UP:
                            if(j>0 && marca[1] == 0 && salida == 0)
                            {
                                if(j==1)
                                {
                                    al_draw_rectangle(410,395,550,430,color_white,2);
                                    al_draw_rectangle(310,445,650,480,color_black,2);
                                    marca[1] = 1;
                                    al_flip_display();
                                }
                                else if(j==2)
                                {
                                    al_draw_rectangle(310,445,650,480,color_white,2);
                                    al_draw_rectangle(410,495,550,530,color_black,2);
                                    marca[1] = 1;
                                    al_flip_display();
                                }
                                j--;
                            }
                            else if(j==1 && marca[1] == 0 && salida == 2)
                            {
                                al_draw_rectangle(410,395,550,430,color_white,2);
                                al_draw_rectangle(410,445,550,480,color_black,2);
                                marca[1] = 1;
                                al_flip_display();
                                j--;
                            }
                            break;
                                    
                        case ALLEGRO_KEY_DOWN:
                            if(j<2 && marca[0] == 0 && salida == 0)
                            {
                                if(j==0)
                                {
                                    al_draw_rectangle(310,445,650,480,color_white,2);
                                    al_draw_rectangle(410,395,550,430,color_black,2);
                                    marca[0] = 1;
                                    al_flip_display();
                                }
                                else if(j==1)
                                {
                                    al_draw_rectangle(410,495,550,530,color_white,2);
                                    al_draw_rectangle(310,445,650,480,color_black,2);
                                    marca[0] = 1;
                                    al_flip_display();
                                }
                                j++;
                            }
                            else if(j==0 && marca[0] == 0 && salida == 2)
                            {
                                al_draw_rectangle(410,395,550,430,color_black,2);
                                al_draw_rectangle(410,445,550,480,color_white,2);
                                marca[0] = 1;
                                al_flip_display();
                                j++;
                            }
                            break;
                        case ALLEGRO_KEY_ENTER:
                            if(salida == 0 && marca[2] == 0)
                            {
                                salida=opcion_menu(j);
                                marca[2]=1;
                            }
                            break;
                        case ALLEGRO_KEY_ESCAPE:
                            if(salida > 0 && marca[3] == 0)
                            {
                                al_draw_filled_rectangle(290,370,680,590,color_black);
                                opciones(0);
                                j=0;
                                salida=0;
                                marca[3]=1;
                            }
                            break;
                            default: break;
                    }
                }
        }
    }
    al_destroy_event_queue(event_queue);
    descargar_lista_l(&h);
    return salida;
}
int opcion_menu(int j)
{
    ALLEGRO_FONT *font = al_load_ttf_font("Font/ka1.ttf", 20, 0);
    if(!font)
    {
        perror("ERROR");
        exit(EXIT_FAILURE);
    }
    ALLEGRO_COLOR color_black = al_map_rgb(0,0,0);
    ALLEGRO_COLOR color_white = al_map_rgb(255,255,255);
    al_draw_filled_rectangle(290,370,680,590,color_black);
    al_flip_display();
    if(j==0)//server o cliente
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), 480, 400, ALLEGRO_ALIGN_CENTRE, "SERVIDOR");
        al_draw_text(font, al_map_rgb(255, 255, 255), 480, 450, ALLEGRO_ALIGN_CENTRE, "CLIENTE");
        al_draw_rectangle(410,395,550,430,color_white,2);
        al_flip_display();
        return 2;
    }
    else if(j==1)//maximas PUNTUACIONES
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), 480, 400, ALLEGRO_ALIGN_CENTRE, "DIEGO.....15000");
        al_draw_text(font, al_map_rgb(255, 255, 255), 480, 450, ALLEGRO_ALIGN_CENTRE, "FRANCO....12054");
        al_flip_display();
    }
    else if(j==2)
        return -1;
    return 1;
}
void opciones(float i)
{
    ALLEGRO_FONT *font = al_load_ttf_font("Font/ka1.ttf", 20, 0);
    if(!font)
    {
        perror("ERROR");
        exit(EXIT_FAILURE);
    }
    ALLEGRO_COLOR color_white = al_map_rgb(255,255,255);
    ALLEGRO_COLOR color_black = al_map_rgb(0,0,0);
    al_draw_filled_rectangle(290,370,680,590,color_black);
    al_draw_text(font, al_map_rgb(255, 255, 255), 480, 400, ALLEGRO_ALIGN_CENTRE, "INICIAR");
    al_rest(i);
    al_flip_display();
    al_draw_text(font, al_map_rgb(255, 255, 255), 480, 450, ALLEGRO_ALIGN_CENTRE, "MAXIMAS PUNTUACIONES");
    al_rest(i);
    al_flip_display();
    al_draw_text(font, al_map_rgb(255, 255, 255), 480, 500, ALLEGRO_ALIGN_CENTRE, "SALIR");
    al_rest(i);
    al_draw_rectangle(410,395,550,430,color_white,2);
    al_flip_display();
}
void borde(int campo_2[16][25],int n)
{
    int i,j,k=n;
    for(i=0;i<25;i++,k++)
    {
        if(k>8)
            k=0;
        campo_2[7][i]=k;
    }
    for(j=8;j<15;j++,k++)
    {
        if(k>8)
            k=0;
        campo_2[j][24]=k;
    }
    for(i=24;i>=0;i--,k++)
    {
        if(k>8)
            k=0;
        campo_2[15][i]=k;
    }
    for(j=14;j>0;j--,k++)
    {
        if(k>8)
            k=0;
        campo_2[j][0]=k;
    }
}
void move_letras(int campo_2[16][25],ALLEGRO_BITMAP *colores[9])
{
    int aux=0;
    do{
        move_letra(campo_2,7);//T
        if(aux > 5)
            move_letra(campo_2,6);//R
        if(aux > 10)
            move_letra(campo_2,5);//t
        if(aux > 15)
            move_letra(campo_2,8);//S
        if(aux > 20)
            move_letra(campo_2,4);//E
        if(aux > 25)
            move_letra(campo_2,2);//I
        print_campo(campo_2,colores);
        al_flip_display();
        al_rest(0.2);
        aux++;
    }while(aux < 34);
}
void move_letra(int campo_2[16][25],int a)
{
    int i,j,k;
    for(j=13;j>0;j--)
    {
        for(i=1;i<25;i++)
        {
            if(campo_2[j][i] == a)
            {
                if(j!=13)
                {
                    k=j;
                    k++;
                    campo_2[k][i]=campo_2[j][i];
                    campo_2[j][i]=0;
                }
                else
                    return;
            }
        }
    }
}
void cargar_letras(NODO_L **h)
{
    FILE *fp;
    NODO_L *aux;
    char buffer[20];
    int a,b,i;
    fp = fopen("Data/Letras", "r");
    if(fp == NULL)
    {
        printf("ERROR AL CARGAR ARCHIVO\n");
        return;
    }
    else
    {
        while(!feof(fp))
        {
            for(i=0;i<6;i++)
            {
                aux=(NODO_L*)malloc(sizeof(NODO_L));
                fscanf(fp, "%c\n", &(aux->caracter.nombre));
                fscanf(fp, "%s \n", buffer);
                do
                {
                    fscanf(fp, "%d %d\n",&a,&b);
                    save_pos(buffer,a,b,aux);
                    fscanf(fp, "%s \n",buffer);
                }while(strcmp(buffer,"-------------")!= 0);
                aux->next=NULL;
                agregar_nodo_l(h,aux);
            }
        }
    }
    fclose(fp);
}
void save_pos(char buffer[20],int a,int b,NODO_L *aux)
{
    if(strcmp(buffer,"POS01")==0)
    {
        aux->caracter.pos01[0]=a;
        aux->caracter.pos01[1]=b;
    }
    else if(strcmp(buffer,"POS02")==0)
    {
        aux->caracter.pos02[0]=a;
        aux->caracter.pos02[1]=b;
    }
    else if(strcmp(buffer,"POS03")==0)
    {
        aux->caracter.pos03[0]=a;
        aux->caracter.pos03[1]=b;
    }
    else if(strcmp(buffer,"POS04")==0)
    {
        aux->caracter.pos04[0]=a;
        aux->caracter.pos04[1]=b;
    }
    else if(strcmp(buffer,"POS05")==0)
    {
        aux->caracter.pos05[0]=a;
        aux->caracter.pos05[1]=b;
    }
    else if(strcmp(buffer,"POS06")==0)
    {
        aux->caracter.pos06[0]=a;
        aux->caracter.pos06[1]=b;
    }
    else if(strcmp(buffer,"POS07")==0)
    {
        aux->caracter.pos07[0]=a;
        aux->caracter.pos07[1]=b;
    }
    else if(strcmp(buffer,"POS08")==0)
    {
        aux->caracter.pos08[0]=a;
        aux->caracter.pos08[1]=b;
    }
    else if(strcmp(buffer,"POS09")==0)
    {
        aux->caracter.pos09[0]=a;
        aux->caracter.pos09[1]=b;
    }
    else if(strcmp(buffer,"POS10")==0)
    {
        aux->caracter.pos10[0]=a;
        aux->caracter.pos10[1]=b;
    }
    else if(strcmp(buffer,"POS11")==0)
    {
        aux->caracter.pos11[0]=a;
        aux->caracter.pos11[1]=b;
    }
    
}
void agregar_nodo_l(NODO_L **h,NODO_L *aux)
{
    NODO_L *l;
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
void descargar_lista_l(NODO_L **h)
{
    NODO_L *aux, *aux2;
    
    for(aux = *h, aux2 = aux->next; aux->next != NULL; aux2 = aux2->next)
    {
        free(aux);
        aux = aux2;
    }
    free(aux);
}
void init_campo_2(int campo_2[16][25])
{
    int i,j;
    for(j = 0; j < 16; j++)
    {
        for(i = 0; i < 25; i++)
            campo_2[j][i] = 0;
    }
}
void print_campo(int campo_2[16][25], ALLEGRO_BITMAP *colores[9])
{
    int i, j,k,m=150;
    
    for(j = 7,k=1; j < 16; j++,k++)
    {
        for(i = 0; i < 25; i++)
        {
            switch(campo_2[j][i])
            {
                case 1: 
                    al_draw_bitmap(colores[1], i*26+m, k*26, 0);
                    break;
                        
                case 2: 
                    al_draw_bitmap(colores[2], i*26+m, k*26, 0);
                    break;
                    
                case 3:
                    al_draw_bitmap(colores[3], i*26+m, k*26, 0);
                    break;
                        
                case 4:
                    al_draw_bitmap(colores[4], i*26+m, k*26, 0);
                    break;
                        
                case 5:
                    al_draw_bitmap(colores[5], i*26+m, k*26, 0);
                    break;
                        
                case 6:
                    al_draw_bitmap(colores[6], i*26+m, k*26, 0);
                    break;
                        
                case 7:
                    al_draw_bitmap(colores[7], i*26+m, k*26, 0);
                    break;
                        
                case 8:
                    al_draw_bitmap(colores[8], i*26+m, k*26, 0);
                    break;
                case 0:
                    al_draw_bitmap(colores[0], i*26+m, k*26, 0);
                    break;
                default: break;
            }
        }
    }
}
void put_pieza_campo_2(struct letras *caracter, int campo_2[11][25])
{
    int i;
    if(caracter->nombre == 'T')
        i=7;
    else if(caracter->nombre == 'E')
        i=4;
    else if(caracter->nombre == 't')
        i=5;
    else if(caracter->nombre == 'R')
        i=6;
    else if(caracter->nombre == 'I')
        i=2;
    else if(caracter->nombre == 'S')
        i=8;
    campo_2[caracter->pos01[1]][caracter->pos01[0]] = i;
    campo_2[caracter->pos02[1]][caracter->pos02[0]] = i;
    campo_2[caracter->pos03[1]][caracter->pos03[0]] = i;
    campo_2[caracter->pos04[1]][caracter->pos04[0]] = i;
    if(caracter->pos05[0] != 0)
        campo_2[caracter->pos05[1]][caracter->pos05[0]] = i;
    if(caracter->pos06[0] != 0)
        campo_2[caracter->pos06[1]][caracter->pos06[0]] = i;
    if(caracter->pos07[0] != 0)
        campo_2[caracter->pos07[1]][caracter->pos07[0]] = i;
    if(caracter->pos08[0] != 0)
        campo_2[caracter->pos08[1]][caracter->pos08[0]] = i;
    if(caracter->pos09[0] != 0)
        campo_2[caracter->pos09[1]][caracter->pos09[0]] = i;
    if(caracter->pos10[0] != 0)
        campo_2[caracter->pos10[1]][caracter->pos10[0]] = i;
    if(caracter->pos11[0] != 0)
        campo_2[caracter->pos11[1]][caracter->pos11[0]] = i;
}
/*******************************************************************************************************************************//**
 *
 * @file		headers.h
 * @brief		Contiene includes, structs y protitopos
 * @date		18/12/2016
 * @author		Franco Jatib, Diego Quispe, Emmanuel Carcomo
 *
 **********************************************************************************************************************************/
 /***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
 
 #ifndef HEADERS_h_
 #define HEADERS_h_

 /***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ifaddrs.h>

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

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

struct paquete
{
    int campo[22][12];
    int lineas;
    int puntos;
    int nivel;
};
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

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/

int CtoI(char);
void agregar_nodo(struct nodo **h,struct nodo *aux);
void init_campo(int campo[22][12]);
void print_campo(int campo[22][12], ALLEGRO_BITMAP *colores[], int, int);
int cargar_piezas(struct nodo **);
void put_pieza_campo(struct datos *, int campo[22][12]);
void detect_colision(int campo[22][12], int *, struct datos *);
void mover_derecha(struct datos *, int campo[22][12]);
void mover_izquierda(struct datos *, int campo[22][12]);
int mover_abajo(struct datos *, int campo[22][12]);
void rotar_pieza(struct datos *, int campo[22][12]);
void print(struct datos *, ALLEGRO_BITMAP *colores[], int);
void clear(struct datos *, ALLEGRO_BITMAP *colores[], int);
struct datos prandom(struct nodo **);
int delete_line(int campo[22][12]);
int comprobar(struct datos, int campo[22][12]);
void print_next(struct datos, ALLEGRO_BITMAP *colores[], int, int);
void descargar_lista(struct nodo **);
int campocmp(int campo1[22][12],int campo2 [22][12]);
void init_campo_2(int campo_2[16][25]);
void print_campo_2(int campo_2[16][25], ALLEGRO_BITMAP *colores_m[8]);
void cargar_letras(NODO_L **h);
void save_pos(char buffer[20],int a,int b,NODO_L *aux);
void agregar_nodo_l(NODO_L **h,NODO_L *aux);
void descargar_lista_l(NODO_L **h);
void put_pieza_campo_2(struct letras *caracter, int campo_2[16][25]);
void move_letra(int campo_2[16][25],int a);
void move_letras(int campo_2[16][25],ALLEGRO_BITMAP *colores_m[9]);
void borde(int campo_2[16][25],int n);
void opciones(float,ALLEGRO_FONT *font);
int opcion_menu(int j,ALLEGRO_FONT *font);
int menu(int campo_2[16][25],ALLEGRO_DISPLAY *display,ALLEGRO_BITMAP *colores_m[9],char nombre[6],char IP[20]);
void caer(struct datos *, int campo[22][12]);
void alias(char y,int k,ALLEGRO_FONT *font);
void ip_f(char *IP,char*ip);

#endif

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
#define PUERTO 2020

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

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/

int CtoI(char);
void agregar_nodo(struct nodo **h,struct nodo *aux);
void init_campo(int campo[22][12]);
void print_campo(int campo[22][12], ALLEGRO_BITMAP *colores[]);
int cargar_piezas(struct nodo **);
void put_pieza_campo(struct datos *, int campo[22][12]);
void detect_colision(int campo[22][12], int *, struct datos *);
void mover_derecha(struct datos *, int campo[22][12]);
void mover_izquierda(struct datos *, int campo[22][12]);
int mover_abajo(struct datos *, int campo[22][12]);
void rotar_pieza(struct datos *, int campo[22][12]);
void print(struct datos *, ALLEGRO_BITMAP *colores[]);
void clear(struct datos *, ALLEGRO_BITMAP *colores[]);
struct datos prandom(struct nodo **);
int delete_line(int campo[22][12]);
int comprobar(struct datos, int campo[22][12]);
void print_next(struct datos, ALLEGRO_BITMAP *colores[]);
void descargar_lista(struct nodo **);



#endif
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
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
int cargar_piezas(struct nodo **);
void agregar_nodo(struct nodo **,struct nodo *);
int CtoI(char);
void print_lista(struct nodo *);
void liberar_lista(struct nodo **);
int main(void)
{
    struct nodo *lista;
    lista=NULL;
    int i;
    i=cargar_piezas(&lista);
    if(i==(-1))
    {
        printf("ERROR\n");
    }
    print_lista(lista);
    liberar_lista(&lista);
    exit(EXIT_SUCCESS);
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
            aux->next=NULL;
            agregar_nodo(h,aux);
        }
    }
    fclose(fp);
    return 1;
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
void print_lista(struct nodo *lista)
{
    struct nodo *aux;
    aux=lista;
    while(aux!=NULL)
    {
        printf("Nombre:%c\n",aux->pieza.nombre);
        printf("centro_pos:(%d,%d)\n",aux->pieza.centro_pos[0],aux->pieza.centro_pos[1]);
        printf("periferico_1_pos:(%d,%d)\n",aux->pieza.periferico_1_pos[0],aux->pieza.periferico_1_pos[1]);
        printf("periferico_2_pos:(%d,%d)\n",aux->pieza.periferico_2_pos[0],aux->pieza.periferico_2_pos[1]);
        printf("periferico_3_pos:(%d,%d)\n",aux->pieza.periferico_3_pos[0],aux->pieza.periferico_3_pos[1]);
        printf("Color:%s\n",aux->pieza.color);
        aux=aux->next;
    }
}
void liberar_lista(struct nodo **lista)
{
    struct nodo *i,*aux;
    aux=(*lista);
    while(aux!=NULL)
    {
        i=aux;
        aux=aux->next;
        free(i);
    }
}
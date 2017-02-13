/*******************************************************************************************************************************//**
 * @details             Proyecto: Tetris
 * @file		funciones.c
 * @brief		Funciones utilizadas en el programa
 * @date		18/12/2016
 * @author		Franco Jatib, Diego Quispe, Emmanuel Carcomo
 *
 **********************************************************************************************************************************/
/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "headers.h"
/**
	@fn  		void rotar_pieza(struct datos *pieza,int campo[22][12]) 
	@brief 		Rota la pieza 
 	@author 	Franco Jatib, Diego Quispe, Emmanuel Carcomo
 	@date 		18-12-16
 	@param [in] pieza:  direccion del header de la pieza
 	@param [in] campo:  direccion de la matriz
	@return         no retorna
*/

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
    put_pieza_campo(pieza, campo);
}

/**
	@fn  		int CtoI(char a) 
	@brief 		Pasa de caracter a entero
 	@author 	Franco Jatib, Diego Quispe, Emmanuel Carcomo
 	@date 		18-12-16
 	@param [in] a:  caracter (char)
	@return         entero (int)
*/

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

/**
	@fn  		void agregar_nodo(struct nodo **h,struct nodo *aux) 
	@brief 		agrega nodo al final
 	@author 	Franco Jatib, Diego Quispe, Emmanuel Carcomo
 	@date 		18-12-16
 	@param [in] h:  direccion del header
 	@param [in] aux:  direccion del dato
	@return         no retorna
*/

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

/**
	@fn  		void descargar_lista(struct nodo **h) 
	@brief 		libera lista
 	@author 	Franco Jatib, Diego Quispe, Emmanuel Carcomo
 	@date 		18-12-16
 	@param [in] h:  direccion del header
	@return         no retorna
*/

void descargar_lista(struct nodo **h)
{
    struct nodo *aux, *aux2;
    
    for(aux = *h, aux2 = aux->next; aux->next != NULL; aux2 = aux2->next)
    {
        free(aux);
        aux = aux2;
    }
    free(aux);
}

/**
	@fn  		void init_campo(int campo[22][12]) 
	@brief 		inicializa la matriz
 	@author 	Franco Jatib, Diego Quispe, Emmanuel Carcomo
 	@date 		18-12-16
 	@param [in] campo:  direccion de la matriz
	@return         no retorna
*/

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

/**
	@fn  		void print_campo(int campo[22][12], ALLEGRO_BITMAP *colores[8]) 
	@brief 		imprime la matriz en la pantalla
 	@author 	Franco Jatib, Diego Quispe, Emmanuel Carcomo
 	@date 		18-12-16
 	@param [in] campo:  direccion de la matriz
 	@param [in] colores:  direccion del vector de los colores
	@return         no retorna
*/

void print_campo(int campo[22][12], ALLEGRO_BITMAP *colores[8], int x, int y)
{
    int i, j;
    
    for(j = 1; j < 21; j++)
    {
        for(i = 1; i < 11; i++)
        {
            switch(campo[j][i])
            {
                case 1: 
                    al_draw_bitmap(colores[1], i*21 -21 + x, j*21 -21 + y, 0);
                    break;
                        
                case 2: 
                    al_draw_bitmap(colores[2], i*21 -21 + x, j*21 -21 + y, 0);
                    break;
                    
                case 3:
                    al_draw_bitmap(colores[3], i*21 -21 + x, j*21 -21 + y, 0);
                    break;
                        
                case 4:
                    al_draw_bitmap(colores[4], i*21 -21 + x, j*21 -21 + y, 0);
                    break;
                        
                case 5:
                    al_draw_bitmap(colores[5], i*21 -21 + x, j*21 -21 + y, 0);
                    break;
                        
                case 6:
                    al_draw_bitmap(colores[6], i*21 -21 + x, j*21 -21 + y, 0);
                    break;
                        
                case 7:
                    al_draw_bitmap(colores[7], i*21 -21 + x, j*21 -21 + y, 0);
                    break;
                        
                case 8:
                    al_draw_bitmap(colores[8], i*21 -21 + x, j*21 -21 + y, 0);
                    break;
                        
                case -2:
                    al_draw_bitmap(colores[2], i*21 -21 + x, j*21 -21 + y, 0);
                    break;
                    
                case -3:
                    al_draw_bitmap(colores[3], i*21 -21 + x, j*21 -21 + y, 0);
                    break;
                        
                case -4:
                    al_draw_bitmap(colores[4], i*21 -21 + x, j*21 -21 + y, 0);
                    break;
                        
                case -5:
                    al_draw_bitmap(colores[5], i*21 -21 + x, j*21 -21 + y, 0);
                    break;
                        
                case -6:
                    al_draw_bitmap(colores[6], i*21 -21 + x, j*21 -21 + y, 0);
                    break;
                    
                case -7:
                    al_draw_bitmap(colores[7], i*21 -21 + x, j*21 -21 + y, 0);
                    break;
                        
                case -8:
                    al_draw_bitmap(colores[8], i*21 -21 + x, j*21 -21 + y, 0);
                    break;
                        
                default: break;
            }
        }
    }
}

/**
	@fn  		int cargar_piezas(struct nodo **h) 
	@brief 		carga las piezas del archivo a la lista
 	@author 	Franco Jatib, Diego Quispe, Emmanuel Carcomo
 	@date 		18-12-16
 	@param [in] h:  direccion del header
	@return         -1 por error y 1 por exito
*/

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

/**
	@fn  		void mover_derecha(struct datos *pieza, int campo[22][12]) 
	@brief 		mueve pieza a la derecha
 	@author 	Franco Jatib, Diego Quispe, Emmanuel Carcomo
 	@date 		18-12-16
 	@param [in] pieza:  direccion del header de la pieza
 	@param [in] campo:  direccion de la matriz
	@return         no retorna
*/

void mover_derecha(struct datos *pieza, int campo[22][12])
{
    int v[4];
    
    detect_colision(campo, v, pieza);
    if(v[2] == 0)
    {
        campo[pieza->centro_pos[1]][pieza->centro_pos[0]] = 0;
        campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = 0;
        campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = 0;
        campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = 0;
        pieza->centro_pos[0] += 1;
        pieza->periferico_1_pos[0] += 1;
        pieza->periferico_2_pos[0] += 1;
        pieza->periferico_3_pos[0] += 1;
        put_pieza_campo(pieza, campo);
    }
}

/**
	@fn  		void mover_izquierda(struct datos *pieza, int campo[22][12]) 
	@brief 		mueve pieza a la izquierda
 	@author 	Franco Jatib, Diego Quispe, Emmanuel Carcomo
 	@date 		18-12-16
 	@param [in] pieza:  direccion del header de la pieza
 	@param [in] campo:  direccion de la matriz
	@return         no retorna
*/

void mover_izquierda(struct datos *pieza, int campo[22][12])
{
    int v[4];
    
    detect_colision(campo, v, pieza);
    if(v[0] == 0)
    {
        campo[pieza->centro_pos[1]][pieza->centro_pos[0]] = 0;
        campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = 0;
        campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = 0;
        campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = 0;
        pieza->centro_pos[0] -= 1;
        pieza->periferico_1_pos[0] -= 1;
        pieza->periferico_2_pos[0] -= 1;
        pieza->periferico_3_pos[0] -= 1;
        put_pieza_campo(pieza, campo);
    }
}

/**
	@fn  		void mover_abajo(struct datos *pieza, int campo[22][12]) 
	@brief 		mueve pieza abajo
 	@author 	Franco Jatib, Diego Quispe, Emmanuel Carcomo
 	@date 		18-12-16
 	@param [in] pieza:  direccion del header de la pieza
 	@param [in] campo:  direccion de la matriz
	@return   0 si se movio hacia abajo y 1 si no se movio hacia abajo      
*/

int mover_abajo(struct datos *pieza, int campo[22][12])
{
    int v[4], i;
    
    detect_colision(campo, v, pieza);
        
    if(v[1] == 0)
    {
        i = 0;
        campo[pieza->centro_pos[1]][pieza->centro_pos[0]] = 0;
        campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = 0;
        campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = 0;
        campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = 0;
        pieza->centro_pos[1] += 1;
        pieza->periferico_1_pos[1] += 1;
        pieza->periferico_2_pos[1] += 1;
        pieza->periferico_3_pos[1] += 1;
        put_pieza_campo(pieza, campo);
    }
    else
    {
        i = 1;
        campo[pieza->centro_pos[1]][pieza->centro_pos[0]] = -(campo[pieza->centro_pos[1]][pieza->centro_pos[0]]);
        campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = -(campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]]);
        campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = -(campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]]);
        campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = -(campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]]);
    }
    return i;
}

/**
	@fn  		void detect_colision(int campo[22][12], int *v, struct datos *pieza) 
	@brief 		detecta colisiones hacia derecha, izquierda, arriba y abajo de la pieza
 	@author 	Franco Jatib, Diego Quispe, Emmanuel Carcomo
 	@date 		18-12-16
 	@param [in] campo:  direccion de la matriz
 	@param [in] v:  direccion del vector
        @param [in] pieza:  direccion del header de la pieza
	@return         no retorna
*/

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

 /**
	@fn  		int comprobar(struct datos pieza, int campo[22][12]) 
	@brief 		comprueba que no haya basura donde se va a poner la nueva pieza
 	@author 	Franco Jatib, Diego Quispe, Emmanuel Carcomo
 	@date 		18-12-16
 	@param [in] pieza:  struct de la pieza
 	@param [in] campo:  direccion de la matriz
	@return         -1 si hay basura y 0 si no hay basura
*/
 
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

/**
	@fn  		void put_pieza_campo(struct datos *pieza, int campo[22][12]) 
	@brief 		pone la pieza en al matriz con su respectivo color
 	@author 	Franco Jatib, Diego Quispe, Emmanuel Carcomo
 	@date 		18-12-16
 	@param [in] pieza:  direccion del header de la pieza
 	@param [in] campo:  direccion de la matriz
	@return         no retorna
*/

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

/**
	@fn  		void clear(struct datos *pieza, ALLEGRO_BITMAP *colores[8]) 
	@brief 		pone la pantalla en negro en las coordenadas de la pieza
 	@author 	Franco Jatib, Diego Quispe, Emmanuel Carcomo
 	@date 		18-12-16
 	@param [in] pieza:  direccion del header de la pieza
 	@param [in] colores:  direccion del vector de los colores
	@return         no retorna
*/

void clear(struct datos *pieza, ALLEGRO_BITMAP *colores[8], int x, int y)
{
    al_draw_bitmap(colores[0], pieza->centro_pos[0]*21-21+x, pieza->centro_pos[1]*21-21+y, 0);
    al_draw_bitmap(colores[0], pieza->periferico_1_pos[0]*21-21+x, pieza->periferico_1_pos[1]*21-21+y, 0);
    al_draw_bitmap(colores[0], pieza->periferico_2_pos[0]*21-21+x, pieza->periferico_2_pos[1]*21-21+y, 0);
    al_draw_bitmap(colores[0], pieza->periferico_3_pos[0]*21-21+x, pieza->periferico_3_pos[1]*21-21+y, 0);
}

/**
	@fn  		void print(struct datos *pieza, ALLEGRO_BITMAP *colores[8]) 
	@brief 		imprime la pieza en la pantalla con su respectivo color
 	@author 	Franco Jatib, Diego Quispe, Emmanuel Carcomo
 	@date 		18-12-16
 	@param [in] pieza:  direccion del header de la pieza
 	@param [in] colores:  direccion del vector de los colores
	@return         no retorna
*/

void print(struct datos *pieza, ALLEGRO_BITMAP *colores[8], int x, int y)
{
    int i;
    
    if(strcmp(pieza->color, "rojo") == 0)
        i = 2;
    if(strcmp(pieza->color, "naranja") == 0)
        i = 3;
    if(strcmp(pieza->color, "amarillo") == 0)
        i = 4;
    if(strcmp(pieza->color, "verde") == 0)
        i = 5;
    if(strcmp(pieza->color, "cyan") == 0)
        i = 6;
    if(strcmp(pieza->color, "azul") == 0)
        i = 7;
    if(strcmp(pieza->color, "violeta") == 0)
        i = 8;
    
    al_draw_bitmap(colores[i], pieza->centro_pos[0]*21-21+x, pieza->centro_pos[1]*21-21+y, 0);
    al_draw_bitmap(colores[i], pieza->periferico_1_pos[0]*21-21+x, pieza->periferico_1_pos[1]*21-21+y, 0);
    al_draw_bitmap(colores[i], pieza->periferico_2_pos[0]*21-21+x, pieza->periferico_2_pos[1]*21-21+y, 0);
    al_draw_bitmap(colores[i], pieza->periferico_3_pos[0]*21-21+x, pieza->periferico_3_pos[1]*21-21+y, 0);
}

/**
	@fn  		void print_next(struct datos pieza, ALLEGRO_BITMAP *colores[8]) 
	@brief 		imprime la pieza ,dependiendo del tipo de pieza ,con su respectivo color
 	@author 	Franco Jatib, Diego Quispe, Emmanuel Carcomo
 	@date 		18-12-16
 	@param [in] pieza:  struct de la pieza
 	@param [in] colores:  direccion del vector de los colores
	@return         no retorna
*/

void print_next(struct datos pieza, ALLEGRO_BITMAP *colores[8], int x, int y)
{
    int i;
    
    if(strcmp(pieza.color, "rojo") == 0)
        i = 2;
    if(strcmp(pieza.color, "naranja") == 0)
        i = 3;
    if(strcmp(pieza.color, "amarillo") == 0)
        i = 4;
    if(strcmp(pieza.color, "verde") == 0)
        i = 5;
    if(strcmp(pieza.color, "cyan") == 0)
        i = 6;
    if(strcmp(pieza.color, "azul") == 0)
        i = 7;
    if(strcmp(pieza.color, "violeta") == 0)
        i = 8;
    
    al_draw_bitmap(colores[i], pieza.centro_pos[0]*21-21+x, pieza.centro_pos[1]*21-21+y, 0);
    al_draw_bitmap(colores[i], pieza.periferico_1_pos[0]*21-21+x, pieza.periferico_1_pos[1]*21-21+y, 0);
    al_draw_bitmap(colores[i], pieza.periferico_2_pos[0]*21-21+x, pieza.periferico_2_pos[1]*21-21+y, 0);
    al_draw_bitmap(colores[i], pieza.periferico_3_pos[0]*21-21+x, pieza.periferico_3_pos[1]*21-21+y, 0);

}

/**
	@fn  		struct datos prandom(struct nodo **h) 
	@brief 		elije una pieza aleatoria de la lista de las piezas
 	@author 	Franco Jatib, Diego Quispe, Emmanuel Carcomo
 	@date 		18-12-16
 	@param [in] pieza:  direccion del header de las piezas
	@return         struct con los datos de la pieza elegida
*/

struct datos prandom(struct nodo **h)
{
    int m, n;
    struct nodo *aux;
    
    m = rand() % 7;
    
    for(aux = *h, n = 0; n < m; n++, aux = aux->next);
    
    return aux->pieza;
}

/**
	@fn  		int delete_line(int campo[22][12]) 
	@brief 		elimina linea de la basura si esta esta completa
 	@author 	Franco Jatib, Diego Quispe, Emmanuel Carcomo
 	@date 		18-12-16
 	@param [in] campo:  direccion de la matriz
	@return         cantidad de lineas eliminadas
*/

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

int piezacmp(struct datos pieza_a, struct datos pieza_b)
{
    if(pieza_a.centro_pos[0] != pieza_b.centro_pos[0] && pieza_a.centro_pos[1] != pieza_b.centro_pos[1] && pieza_a.periferico_1_pos[0] != pieza_b.periferico_1_pos[0] && pieza_a.periferico_1_pos[1] != pieza_b.periferico_1_pos[1] && pieza_a.periferico_2_pos[0] != pieza_b.periferico_2_pos[0] && pieza_a.periferico_2_pos[1] != pieza_b.periferico_2_pos[1] && pieza_a.periferico_3_pos[0] != pieza_b.periferico_3_pos[0] && pieza_a.periferico_3_pos[1] != pieza_b.periferico_3_pos[1])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int campocmp(int campo1[22][12], int campo2[22][12])
{
    int x, y, xx, yy;
    
    for(y = 1; y < 21; y++)
    {
        for(x = 1; x < 11; x++)
        {
            if(campo1[y][x] != campo2[y][x])
            {
                return 0;
            }
        }
    }
    return 1;
}
int menu(int campo_2[16][25],ALLEGRO_DISPLAY *display,ALLEGRO_BITMAP *colores_m[9],char nombre[6],char IP[15])
{
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    ALLEGRO_EVENT events;
    ALLEGRO_TIMER *timer;
    ALLEGRO_FONT *font = al_load_ttf_font("Font/ka1.ttf", 20, 0);
    if(!font)
    {
        perror("ERROR");
        exit(EXIT_FAILURE);
    }
    int i=0,j=0,k=0,y=0,salida=0,marca[5]={0,0,0,0,0},opcion=0;
    char car[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    char num[10]={'0','1','2','3','4','5','6','7','8','9'};
    NODO_L *h = NULL,*aux =NULL;
    init_campo_2(campo_2);
    cargar_letras(&h);
    for(aux=h;aux!=NULL;aux=aux->next)
        put_pieza_campo_2(&(aux->caracter),campo_2);
    print_campo_2(campo_2,colores_m);
    al_flip_display();
//     move_letras(campo_2,colores_m);
    opciones(0.2,font);
     
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    while(salida >= 0)
    {
        timer = al_create_timer(0.1);
        al_set_timer_count(timer, 0);
        al_start_timer(timer);
        
        if(i>8)
            i=0;
        borde(campo_2,i);
        i++;
        print_campo_2(campo_2,colores_m);
        al_flip_display();
    
        while(al_get_timer_count(timer) < 0.2)
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
                else if(events.keyboard.keycode == ALLEGRO_KEY_LEFT)
                    marca[4] = 0;
                else if(events.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                    marca[5] = 0;
            }
            al_get_next_event(event_queue, &events);
            if(events.type == ALLEGRO_EVENT_KEY_UP)
            {
                switch(events.keyboard.keycode)
                {
                    case ALLEGRO_KEY_UP:
                        if(j>0 && marca[1] == 0 && salida == 0)
                        {
                            if(j==1)
                            {
                                al_draw_rectangle(410,395,550,430,al_map_rgb(255,255,255),2);
                                al_draw_rectangle(310,445,650,480,al_map_rgb(0,0,0),2);
                                marca[1] = 1;
                                al_flip_display();
                            }
                            else if(j==2)
                            {
                                al_draw_rectangle(310,445,650,480,al_map_rgb(255,255,255),2);
                                al_draw_rectangle(410,495,550,530,al_map_rgb(0,0,0),2);
                                marca[1] = 1;
                                al_flip_display();
                            }
                            j--;
                        }
                        else if(j==1 && marca[1] == 0 && salida == 2)
                        {
                            al_draw_rectangle(410,395,550,430,al_map_rgb(255,255,255),2);
                            al_draw_rectangle(410,445,550,480,al_map_rgb(0,0,0),2);
                            marca[1] = 1;
                            al_flip_display();
                            j--;
                        }
                        else if(salida == 3 && marca[1] == 0)
                        {
                            if(y==25)
                                y=0;
                            else
                                y++;
                            nombre[k]=car[y];
                            alias(car[y],k,font);
                            marca[1] = 1;
                        }
                        else if(salida == 4 && marca[1] == 0)
                        {
                            if(y==9)
                                y=0;
                            else
                                y++;
                            IP[k]=num[y];
                            alias(num[y],k,font);
                            marca[1] = 1;
                        }
                        break;
                                
                    case ALLEGRO_KEY_DOWN:
                        if(j<2 && marca[0] == 0 && salida == 0)
                        {
                            if(j==0)
                            {
                                al_draw_rectangle(310,445,650,480,al_map_rgb(255,255,255),2);
                                al_draw_rectangle(410,395,550,430,al_map_rgb(0,0,0),2);
                                marca[0] = 1;
                                al_flip_display();
                            }
                            else if(j==1)
                            {
                                al_draw_rectangle(410,495,550,530,al_map_rgb(255,255,255),2);
                                al_draw_rectangle(310,445,650,480,al_map_rgb(0,0,0),2);
                                marca[0] = 1;
                                al_flip_display();
                            }
                            j++;
                        }
                        else if(j==0 && marca[0] == 0 && salida == 2)
                        {
                            al_draw_rectangle(410,395,550,430,al_map_rgb(0,0,0),2);
                            al_draw_rectangle(410,445,550,480,al_map_rgb(255,255,255),2);
                            marca[0] = 1;
                            al_flip_display();
                            j++;
                        }
                        else if(salida == 3 && marca[0] == 0)
                        {
                            if(y==0)
                                y=25;
                            else
                                y--;
                            nombre[k]=car[y];
                            alias(car[y],k,font);
                            marca[0] = 1;
                        }
                        else if(salida == 4 && marca[0] == 0)
                        {
                            if(y==0)
                                y=9;
                            else
                                y--;
                            IP[k]=num[y];
                            alias(num[y],k,font);
                            marca[0] = 1;
                        }
                        break;
                    case ALLEGRO_KEY_ENTER:
                        if(salida == 0 && marca[2] == 0 && j!=0)
                        {
                            salida=opcion_menu(j,font);
                            marca[2]=1;
                        }
                        else if(j==0 && marca[2] == 0 && salida == 2)
                        {
                            salida=opcion_menu(3,font);
                            opcion=1;
                            salida=-1;
                            marca[2]=1;
                        }
                        else if(j==1 && marca[2] == 0 && salida == 2)
                        {
                            salida=opcion_menu(4,font);
                            opcion=2;
                            k=0;
                            y=0;
                            marca[2]=1;
                        }
                        else if(marca[2] == 0 && salida == 0 && j==0)
                        {
                            salida=opcion_menu(5,font);
                            marca[2]=1;
                        }
                        else if(marca[2] == 0 && salida == 3)
                        {
                            salida=opcion_menu(0,font);
                            marca[2]=1;
                        }
                        else if(marca[2] == 0 && salida == 4)
                        {
                            salida=-1;
                            marca[2]=1;
                        }
                        break;
                    case ALLEGRO_KEY_ESCAPE:
                        if(salida > 0 && marca[3] == 0)
                        {
                            al_draw_filled_rectangle(290,370,950,590,al_map_rgb(0,0,0));
                            opciones(0,font);
                            j=0;
                            opcion=0;
                            salida=0;
                            marca[3]=1;
                        }
                        break;
                    case ALLEGRO_KEY_LEFT:
                        if(salida == 3 && marca[4] == 0 && k>0)
                        {
                            al_draw_rectangle(488+k*25,400,512+k*25,425,al_map_rgb(0,0,0),1);
                            k--;
                            y=0;
                            al_draw_rectangle(488+k*25,400,512+k*25,425,al_map_rgb(255,255,255),1);
                            marca[4]=1;
                        }
                        else if(salida == 4 && marca[4] == 0 && k>0)
                        {
                            if(k == 4 || k == 8 || k == 12)
                            {
                                al_draw_rectangle(488+k*25,400,512+k*25,425,al_map_rgb(0,0,0),1);
                                k--;
                            }
                            al_draw_rectangle(488+k*25,400,512+k*25,425,al_map_rgb(0,0,0),1);
                            k--;
                            y=0;
                            al_draw_rectangle(488+k*25,400,512+k*25,425,al_map_rgb(255,255,255),1);
                            marca[4]=1;
                            
                        }
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        if(salida == 3 && marca[5]== 0 && k<4)
                        {
                            al_draw_rectangle(488+k*25,400,512+k*25,425,al_map_rgb(0,0,0),1);
                            k++;
                            y=0;
                            al_draw_rectangle(488+k*25,400,512+k*25,425,al_map_rgb(255,255,255),1);
                            marca[5]=1;
                        }
                        else if(salida == 4 && marca[5] == 0 && k< 14)
                        {
                            if(k == 2 || k == 6 || k == 10)
                            {
                                al_draw_rectangle(488+k*25,400,512+k*25,425,al_map_rgb(0,0,0),1);
                                k++;
                            }
                            al_draw_rectangle(488+k*25,400,512+k*25,425,al_map_rgb(0,0,0),1);
                            k++;
                            y=0;
                            al_draw_rectangle(488+k*25,400,512+k*25,425,al_map_rgb(255,255,255),1);
                            marca[5]=1;
                        }
                        break;
                        default: break;
                }
            }
        }
    }
    nombre[5]='\0';
    al_destroy_event_queue(event_queue);
    descargar_lista_l(&h);
    return opcion;
}
int opcion_menu(int j,ALLEGRO_FONT *font)
{
    al_draw_filled_rectangle(290,370,680,590,al_map_rgb(0,0,0));
    al_flip_display();
    if(j==0)//server o cliente
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), 480, 400, ALLEGRO_ALIGN_CENTRE, "SERVIDOR");
        al_draw_text(font, al_map_rgb(255, 255, 255), 480, 450, ALLEGRO_ALIGN_CENTRE, "CLIENTE");
        al_draw_rectangle(410,395,550,430,al_map_rgb(255,255,255),2);
        al_flip_display();
        return 2;
    }
    else if(j==1)//maximas PUNTUACIONES
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), 480, 400, ALLEGRO_ALIGN_CENTRE, "DIEGO.....15000");
        al_draw_text(font, al_map_rgb(255, 255, 255), 480, 450, ALLEGRO_ALIGN_CENTRE, "FRANCO....12054");
        al_flip_display();
    }
    else if(j==3)//SERVER
    {
        al_draw_filled_rectangle(290,370,680,590,al_map_rgb(0,0,0));
        al_draw_text(font, al_map_rgb(255, 255, 255), 480, 450, ALLEGRO_ALIGN_CENTRE, "ESPERANDO OPONENTE...");
        al_flip_display();
    }
    else if(j==4)//cliente
    {
        al_draw_filled_rectangle(290,370,680,590,al_map_rgb(0,0,0));
        al_draw_text(font, al_map_rgb(255, 255, 255), 480, 400, ALLEGRO_ALIGN_RIGHT, "INGRESE IP:");
        al_draw_text(font, al_map_rgb(255, 255, 255), 490, 400, ALLEGRO_ALIGN_LEFT, "0");
        al_draw_text(font, al_map_rgb(255, 255, 255), 515, 400, ALLEGRO_ALIGN_LEFT, "0");
        al_draw_text(font, al_map_rgb(255, 255, 255), 540, 400, ALLEGRO_ALIGN_LEFT, "0");
        al_draw_text(font, al_map_rgb(255, 255, 255), 565, 400, ALLEGRO_ALIGN_LEFT, ".");
        al_draw_text(font, al_map_rgb(255, 255, 255), 590, 400, ALLEGRO_ALIGN_LEFT, "0");
        al_draw_text(font, al_map_rgb(255, 255, 255), 615, 400, ALLEGRO_ALIGN_LEFT, "0");
        al_draw_text(font, al_map_rgb(255, 255, 255), 640, 400, ALLEGRO_ALIGN_LEFT, "0");
        al_draw_text(font, al_map_rgb(255, 255, 255), 665, 400, ALLEGRO_ALIGN_LEFT, ".");
        al_draw_text(font, al_map_rgb(255, 255, 255), 690, 400, ALLEGRO_ALIGN_LEFT, "0");
        al_draw_text(font, al_map_rgb(255, 255, 255), 715, 400, ALLEGRO_ALIGN_LEFT, "0");
        al_draw_text(font, al_map_rgb(255, 255, 255), 740, 400, ALLEGRO_ALIGN_LEFT, "0");
        al_draw_text(font, al_map_rgb(255, 255, 255), 765, 400, ALLEGRO_ALIGN_LEFT, ".");
        al_draw_text(font, al_map_rgb(255, 255, 255), 790, 400, ALLEGRO_ALIGN_LEFT, "0");
        al_draw_text(font, al_map_rgb(255, 255, 255), 815, 400, ALLEGRO_ALIGN_LEFT, "0");
        al_draw_text(font, al_map_rgb(255, 255, 255), 840, 400, ALLEGRO_ALIGN_LEFT, "0");
        al_flip_display();
        return 4;
    }
    else if(j==5)
    {
        al_draw_filled_rectangle(290,370,680,590,al_map_rgb(0,0,0));
        al_draw_text(font, al_map_rgb(255, 255, 255), 470, 400, ALLEGRO_ALIGN_RIGHT, "ALIAS:");
        al_draw_text(font, al_map_rgb(255, 255, 255), 490, 400, ALLEGRO_ALIGN_LEFT, "A");
        al_draw_text(font, al_map_rgb(255, 255, 255), 515, 400, ALLEGRO_ALIGN_LEFT, "A");
        al_draw_text(font, al_map_rgb(255, 255, 255), 540, 400, ALLEGRO_ALIGN_LEFT, "A");
        al_draw_text(font, al_map_rgb(255, 255, 255), 565, 400, ALLEGRO_ALIGN_LEFT, "A");
        al_draw_text(font, al_map_rgb(255, 255, 255), 590, 400, ALLEGRO_ALIGN_LEFT, "A");
        al_draw_rectangle(488,400,512,425,al_map_rgb(255,255,255),1);
        al_flip_display();
        return 3;
    }
    else if(j==2)
        return -1;
    return 1;
}
void alias(char car,int k,ALLEGRO_FONT *font)
{
    al_draw_filled_rectangle(485+k*25,395,515+k*25,430,al_map_rgb(0,0,0));
    al_draw_textf(font, al_map_rgb(255, 255, 255), 490+k*25, 400, ALLEGRO_ALIGN_LEFT, "%c",car);
    al_draw_rectangle(488+k*25,400,512+k*25,425,al_map_rgb(255,255,255),1);
    al_flip_display();
}
void opciones(float i,ALLEGRO_FONT *font)
{
    al_draw_filled_rectangle(290,370,680,590,al_map_rgb(0,0,0));
    al_draw_text(font, al_map_rgb(255, 255, 255), 480, 400, ALLEGRO_ALIGN_CENTRE, "INICIAR");
    al_rest(i);
    al_flip_display();
    al_draw_text(font, al_map_rgb(255, 255, 255), 480, 450, ALLEGRO_ALIGN_CENTRE, "MAXIMAS PUNTUACIONES");
    al_rest(i);
    al_flip_display();
    al_draw_text(font, al_map_rgb(255, 255, 255), 480, 500, ALLEGRO_ALIGN_CENTRE, "SALIR");
    al_rest(i);
    al_draw_rectangle(410,395,550,430,al_map_rgb(255,255,255),2);
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
void move_letras(int campo_2[16][25],ALLEGRO_BITMAP *colores_m[9])
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
        print_campo_2(campo_2,colores_m);
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
void print_campo_2(int campo_2[16][25], ALLEGRO_BITMAP *colores[9])
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

void caer(struct datos *pieza, int campo[22][12])
{
    int v[4], color;
    
    detect_colision(campo, v, pieza);
    
    while(v[1] == 0)
    {
        color = campo[pieza->centro_pos[1]][pieza->centro_pos[0]];
        
        campo[pieza->centro_pos[1]][pieza->centro_pos[0]] = 0;
        campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = 0;
        campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = 0;
        campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = 0;
        
        pieza->centro_pos[1] = pieza->centro_pos[1] + 1;
        pieza->periferico_1_pos[1] = pieza->periferico_1_pos[1] + 1;
        pieza->periferico_2_pos[1] = pieza->periferico_2_pos[1] + 1;
        pieza->periferico_3_pos[1] = pieza->periferico_3_pos[1] + 1;
        
        campo[pieza->centro_pos[1]][pieza->centro_pos[0]] = color;
        campo[pieza->periferico_1_pos[1]][pieza->periferico_1_pos[0]] = color;
        campo[pieza->periferico_2_pos[1]][pieza->periferico_2_pos[0]] = color;
        campo[pieza->periferico_3_pos[1]][pieza->periferico_3_pos[0]] = color;
        
        detect_colision(campo, v, pieza);
    }
}
void ip_f(char *IP,char*ip)
{
    int i,j=1,k=0;
    for(i=0;IP[i]!='\0';i++)
    {
        if(IP[i]=='.')
        {
            j=0;
            ip[k]=IP[i];
            k++;
        }
        else if(IP[i]!='.')
        {
            if(IP[i]=='0')
            {
                if(j==1 || j==(-2))
                {
                    ip[k]=IP[i];
                    k++;
                }
                else
                    j--;
            }
            else if(IP[i]!='0')
            {
                ip[k]=IP[i];
                j++;
                k++;
            }
        }
    }
    ip[k]='\0';
    printf("%s\n%s\n",IP,ip);
}
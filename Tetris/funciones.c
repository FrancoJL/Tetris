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

void print_campo(int campo[22][12], ALLEGRO_BITMAP *colores[8])
{
    int i, j;
    
    for(j = 0; j < 22; j++)
    {
        for(i = 0; i < 12; i++)
        {
            switch(campo[j][i])
            {
                case 1: 
                    al_draw_bitmap(colores[1], i*26, j*26, 0);
                    break;
                        
                case 2: 
                    al_draw_bitmap(colores[2], i*26, j*26, 0);
                    break;
                    
                case 3:
                    al_draw_bitmap(colores[3], i*26, j*26, 0);
                    break;
                        
                case 4:
                    al_draw_bitmap(colores[4], i*26, j*26, 0);
                    break;
                        
                case 5:
                    al_draw_bitmap(colores[5], i*26, j*26, 0);
                    break;
                        
                case 6:
                    al_draw_bitmap(colores[6], i*26, j*26, 0);
                    break;
                        
                case 7:
                    al_draw_bitmap(colores[7], i*26, j*26, 0);
                    break;
                        
                case 8:
                    al_draw_bitmap(colores[8], i*26, j*26, 0);
                    break;
                        
                case -2:
                    al_draw_bitmap(colores[2], i*26, j*26, 0);
                    break;
                    
                case -3:
                    al_draw_bitmap(colores[3], i*26, j*26, 0);
                    break;
                        
                case -4:
                    al_draw_bitmap(colores[4], i*26, j*26, 0);
                    break;
                        
                case -5:
                    al_draw_bitmap(colores[5], i*26, j*26, 0);
                    break;
                        
                case -6:
                    al_draw_bitmap(colores[6], i*26, j*26, 0);
                    break;
                    
                case -7:
                    al_draw_bitmap(colores[7], i*26, j*26, 0);
                    break;
                        
                case -8:
                    al_draw_bitmap(colores[8], i*26, j*26, 0);
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

void clear(struct datos *pieza, ALLEGRO_BITMAP *colores[8])
{
    al_draw_bitmap(colores[0], pieza->centro_pos[0]*26, pieza->centro_pos[1]*26, 0);
    al_draw_bitmap(colores[0], pieza->periferico_1_pos[0]*26, pieza->periferico_1_pos[1]*26, 0);
    al_draw_bitmap(colores[0], pieza->periferico_2_pos[0]*26, pieza->periferico_2_pos[1]*26, 0);
    al_draw_bitmap(colores[0], pieza->periferico_3_pos[0]*26, pieza->periferico_3_pos[1]*26, 0);
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

void print(struct datos *pieza, ALLEGRO_BITMAP *colores[8])
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
    
    al_draw_bitmap(colores[i], pieza->centro_pos[0]*26, pieza->centro_pos[1]*26, 0);
    al_draw_bitmap(colores[i], pieza->periferico_1_pos[0]*26, pieza->periferico_1_pos[1]*26, 0);
    al_draw_bitmap(colores[i], pieza->periferico_2_pos[0]*26, pieza->periferico_2_pos[1]*26, 0);
    al_draw_bitmap(colores[i], pieza->periferico_3_pos[0]*26, pieza->periferico_3_pos[1]*26, 0);
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

void print_next(struct datos pieza, ALLEGRO_BITMAP *colores[8])
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
    
    switch(pieza.nombre)
    {
        case 'O':
            al_draw_bitmap(colores[i], (pieza.centro_pos[0]*26)+270, pieza.centro_pos[1]*26+130, 0);
            al_draw_bitmap(colores[i], (pieza.periferico_1_pos[0]*26)+270, pieza.periferico_1_pos[1]*26+130, 0);
            al_draw_bitmap(colores[i], (pieza.periferico_2_pos[0]*26)+270, pieza.periferico_2_pos[1]*26+130, 0);
            al_draw_bitmap(colores[i], (pieza.periferico_3_pos[0]*26)+270, pieza.periferico_3_pos[1]*26+130, 0);
            break;
            
        case 'L':
            al_draw_bitmap(colores[i], (pieza.centro_pos[0]*26)+(26*10), pieza.centro_pos[1]*26+(26*3), 0);
            al_draw_bitmap(colores[i], (pieza.periferico_1_pos[0]*26)+(26*10), pieza.periferico_1_pos[1]*26+(26*3), 0);
            al_draw_bitmap(colores[i], (pieza.periferico_2_pos[0]*26)+(26*10), pieza.periferico_2_pos[1]*26+(26*3), 0);
            al_draw_bitmap(colores[i], (pieza.periferico_3_pos[0]*26)+(26*10), pieza.periferico_3_pos[1]*26+(26*3), 0);
            break;
            
        case 'J':
            al_draw_bitmap(colores[i], (pieza.centro_pos[0]*26)+(26*10), pieza.centro_pos[1]*26+(26*3), 0);
            al_draw_bitmap(colores[i], (pieza.periferico_1_pos[0]*26)+(26*10), pieza.periferico_1_pos[1]*26+(26*3), 0);
            al_draw_bitmap(colores[i], (pieza.periferico_2_pos[0]*26)+(26*10), pieza.periferico_2_pos[1]*26+(26*3), 0);
            al_draw_bitmap(colores[i], (pieza.periferico_3_pos[0]*26)+(26*10), pieza.periferico_3_pos[1]*26+(26*3), 0);
            break;
            
        case 'S':
            al_draw_bitmap(colores[i], (pieza.centro_pos[0]*26)+(26*10), pieza.centro_pos[1]*26+(26*3), 0);
            al_draw_bitmap(colores[i], (pieza.periferico_1_pos[0]*26)+(26*10), pieza.periferico_1_pos[1]*26+(26*3), 0);
            al_draw_bitmap(colores[i], (pieza.periferico_2_pos[0]*26)+(26*10), pieza.periferico_2_pos[1]*26+(26*3), 0);
            al_draw_bitmap(colores[i], (pieza.periferico_3_pos[0]*26)+(26*10), pieza.periferico_3_pos[1]*26+(26*3), 0);
            break;
            
        case 'Z':
            al_draw_bitmap(colores[i], (pieza.centro_pos[0]*26)+(26*10), pieza.centro_pos[1]*26+(26*3), 0);
            al_draw_bitmap(colores[i], (pieza.periferico_1_pos[0]*26)+(26*10), pieza.periferico_1_pos[1]*26+(26*3), 0);
            al_draw_bitmap(colores[i], (pieza.periferico_2_pos[0]*26)+(26*10), pieza.periferico_2_pos[1]*26+(26*3), 0);
            al_draw_bitmap(colores[i], (pieza.periferico_3_pos[0]*26)+(26*10), pieza.periferico_3_pos[1]*26+(26*3), 0);
            break;
            
        case 'I':
            al_draw_bitmap(colores[i], (pieza.centro_pos[0]*26)+(26*10), pieza.centro_pos[1]*26+(26*4), 0);
            al_draw_bitmap(colores[i], (pieza.periferico_1_pos[0]*26)+(26*10), pieza.periferico_1_pos[1]*26+(26*4), 0);
            al_draw_bitmap(colores[i], (pieza.periferico_2_pos[0]*26)+(26*10), pieza.periferico_2_pos[1]*26+(26*4), 0);
            al_draw_bitmap(colores[i], (pieza.periferico_3_pos[0]*26)+(26*10), pieza.periferico_3_pos[1]*26+(26*4), 0);
            break;
            
        case 'T':
            al_draw_bitmap(colores[i], (pieza.centro_pos[0]*26)+(26*10), pieza.centro_pos[1]*26+(26*3), 0);
            al_draw_bitmap(colores[i], (pieza.periferico_1_pos[0]*26)+(26*10), pieza.periferico_1_pos[1]*26+(26*3), 0);
            al_draw_bitmap(colores[i], (pieza.periferico_2_pos[0]*26)+(26*10), pieza.periferico_2_pos[1]*26+(26*3), 0);
            al_draw_bitmap(colores[i], (pieza.periferico_3_pos[0]*26)+(26*10), pieza.periferico_3_pos[1]*26+(26*3), 0);
            break;
    }
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
/*******************************************************************************************************************************//**
 * @details             Proyecto: Tetris
 * @file		server.c
 * @brief		Servidor del programa
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
    int sock_server;
    int campo_A[22][12], campo_B[22][12], marca1 = 0, marca2 = 0, marca_A = 0, marca_B = 0;
    struct sockaddr_in my_addr; 
    struct sockaddr src_addr_A, src_addr_B;
    char ip[20], str_A[20], str_B[20];
    socklen_t len;
    
    printf("IP: ");
    scanf("%s", ip);
    
    sock_server = socket(AF_INET, SOCK_DGRAM, 0);
    
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(8081);
    inet_aton(ip, &(my_addr.sin_addr));
    memset(&(my_addr.sin_zero), '\0', 8);
    
    if(bind(sock_server, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("ERROR1: ");
        exit(EXIT_FAILURE);
    }


    len = sizeof(struct sockaddr);

        
        if(recvfrom(sock_server, str_A, 20, 0, &src_addr_A, &len) == -1)
        {
            perror("ERROR4: ");
            exit(EXIT_FAILURE);
        }
        
        if(recvfrom(sock_server, str_B, 20, 0, &src_addr_B, &len) == -1)
        {
            perror("ERROR4: ");
            exit(EXIT_FAILURE);
        }
        
        if(sendto(sock_server, (void *) str_B, 20, 0, (struct sockaddr *) &src_addr_A, sizeof(struct sockaddr_in)) == -1)
        {
            perror("ERROR6: ");
            exit(EXIT_FAILURE);
        }
                
        if(sendto(sock_server, (void *) str_A, 20, 0, (struct sockaddr *) &src_addr_B, sizeof(struct sockaddr_in)) == -1)
        {
            perror("ERROR6: ");
            exit(EXIT_FAILURE);
        }
    
    do
    {
        if(recvfrom(sock_server, campo_A, 1056, 0, &src_addr_A, &len) == -1)
        {
            perror("ERROR4: ");
            exit(EXIT_FAILURE);
        }
        else
        {
            marca1 = 1;
        }
        
        if(recvfrom(sock_server, campo_B, 1056, 0, (struct sockaddr *) &src_addr_B, &len) == -1)
        {
            perror("ERROR5: ");
            exit(EXIT_FAILURE);
        }
        else
        {
            marca2 = 1;
        }
    
        if(marca1 == 1 || marca2 == 1)
        {
            if(sendto(sock_server, (void *) campo_B, 1056, 0, (struct sockaddr *) &src_addr_A, sizeof(struct sockaddr_in)) == -1)
            {
                perror("ERROR6: ");
                exit(EXIT_FAILURE);
            }
            
            if(sendto(sock_server, (void *) campo_A, 1056, 0, (struct sockaddr *) &src_addr_B, sizeof(struct sockaddr_in)) == -1)
            {
                perror("ERROR7: ");
                exit(EXIT_FAILURE);
            }
        }
    }while(1);

exit(EXIT_SUCCESS);
}
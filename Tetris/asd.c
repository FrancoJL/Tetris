#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>   /* gethostbyname() necesita esta cabecera */


int main(int argc, char **argv)
{
    int sock_cliente;
    struct sockaddr_in server_addr;
    char ip[40];
    char str[20], str2[20];
    int asd, marca = 0;
    
    scanf("%s", ip);
    
    sock_cliente = socket(AF_INET, SOCK_DGRAM, 0);
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8081);
    inet_aton(ip, &(server_addr.sin_addr));
    memset(&(server_addr.sin_zero), '\0', 8);
    
        scanf("%s", str);
        
        if(sendto(sock_cliente, (void *)str, 20, 0, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_in))  == -1)
        {
            perror("ERROR2: ");
            exit(EXIT_FAILURE);
        }
        
        asd = sizeof(struct sockaddr_in);
        
        do
        {
            if(recvfrom(sock_cliente, str2, 20, 0, (struct sockaddr *) &server_addr, &asd) == -1)
            {
                perror("ERROR5: ");
                exit(EXIT_FAILURE);
            }
            else
            {
                marca = 1;
                printf("%s\n", str2);
            }
        }while(marca == 0);
    
    
    exit(EXIT_SUCCESS);
}
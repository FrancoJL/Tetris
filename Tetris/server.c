#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>   /* gethostbyname() necesita esta cabecera */
#include <string.h>

int main(void)
{
    int sock_server;
    int campo_A[22][12], campo_B[22][12], marca1 = 0, marca2 = 0;
    struct sockaddr_in my_addr; 
    struct sockaddr src_addr_A, src_addr_B;
    char *ip;
    socklen_t len;
    
    sock_server = socket(AF_INET, SOCK_DGRAM, 0);
    
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(8081);
    inet_aton("127.0.0.1", &(my_addr.sin_addr));
    memset(&(my_addr.sin_zero), '\0', 8);
    
    ip = inet_ntoa(my_addr.sin_addr);
    
    printf("%s\n", ip);
    
    if(bind(sock_server, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("ERROR1: ");
        exit(EXIT_FAILURE);
    }


    len = sizeof(struct sockaddr);
    
    do
    {
        if(recvfrom(sock_server, campo_A, 20, 0, &src_addr_A, &len) == -1)
        {
            perror("ERROR4: ");
            exit(EXIT_FAILURE);
        }
        else
        {
            marca1 = 1;
        }
        
        if(recvfrom(sock_server, campo_B, 20, 0, (struct sockaddr *) &src_addr_B, &len) == -1)
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

return 0;
}

// int inicia_socket()
// {
// int s= socket(PF_INET,SOCK_STREAM,0);  /* PF_INET para conexiones fuera de la misma pc, SOCK_STREAM decis que los flujos de datos se van a enviar por la red.*/
// if(s==-1) perror("Error al iniciar socket..\n");
// return s;
// }
// 
// void bind_puerto(int sock,int port)
//  {
//   struct sockaddr_in name;
//   name.sin_family     =PF_INET;
//   name.sin_port       =(in_port_t)htons(port);
//   name.sin_addr.s_addr=htonl(INADDR_ANY);
//   /*Para poder reusar el puerto x si ya se uso*/
//   int reuse=1;
//   if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char*)&reuse,sizeof(int))== -1)
//     {
//      perror("ERROR: "); 
//     }
//   int c= bind(sock,(struct sockaddr*)&name,sizeof(name));
// 
//   if(c== -1) perror("ERROR: ");
//  }
// 
// /*
// void send_campo(int campo [22][12])
//  {
//   int j;
//         
//   send(connect,(void *) campo,264,0);
// 
//  }*/
// 
// 
// int connect_cliente(int sock)
//  {
//   struct sockaddr_storage client;
//   unsigned int addres_size = sizeof(client);
//   printf("Esperando al cliente..\n");
//   int connect = accept(sock,(struct sockaddr*) &client,&addres_size);
//   if(connect == -1)
//   {
//    printf("No se puede conectar socket secundario\n");
//   }
//   printf("Atendiendo al cliente\n");
//   return connect;
//  }
/*******************************************************************************************************************************//**
 * @details             Proyecto: Tetris
 * @file		main_multijugador.c
 * @brief		Main para el multijugador
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
    
    int fd_r, fd_w, sock_cliente, len, marca = 0, campo[22][12], campo_opp[22][12], bytes, bytes2, a,i,b=1;
    struct sockaddr_in server_addr;
    char ip[20], str[3] = "OK", str2[3], nombre[20], nombre2[20], string[20];
    ALLEGRO_DISPLAY *display;
    ALLEGRO_BITMAP *colores[9];
    ALLEGRO_FONT *font = al_load_ttf_font("Font/ka1.ttf", 20, 0);
    colores[0] = al_load_bitmap("Graphics/Piezas/clear.png");
    colores[1] = al_load_bitmap("Graphics/Piezas/pieza_gris.png");
    colores[2] = al_load_bitmap("Graphics/Piezas/pieza_rojo.png");
    colores[3] = al_load_bitmap("Graphics/Piezas/pieza_naranja.png");
    colores[4] = al_load_bitmap("Graphics/Piezas/pieza_amarillo.png");
    colores[5] = al_load_bitmap("Graphics/Piezas/pieza_verde.png");
    colores[6] = al_load_bitmap("Graphics/Piezas/pieza_cyan.png");
    colores[7] = al_load_bitmap("Graphics/Piezas/pieza_azul.png");
    colores[8] = al_load_bitmap("Graphics/Piezas/pieza_violeta.png");
    
    printf("Ingrese IP: ");
    scanf("%s", ip);
    
    printf("Nombre: ");
    scanf("%s", nombre);
    
    sock_cliente = socket(AF_INET, SOCK_DGRAM, 0);
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8081);
    inet_aton(ip, &(server_addr.sin_addr));
    memset(&(server_addr.sin_zero), '\0', 8);
    
    printf("Esperando oponente...\n");
    
    do
    {
        if(sendto(sock_cliente, (void *)nombre, 20, 0, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_in))  == -1)
        {
            perror("ERROR2: ");
            exit(EXIT_FAILURE);
        }
        
        len = sizeof(struct sockaddr_in);
        
        a = recvfrom(sock_cliente, nombre2, 20, 0, (struct sockaddr *) &server_addr, &len);
        
        if(a == -1)
        {
            perror("ERROR5: ");
            exit(EXIT_FAILURE);
        }
    }while(a == 0);
    printf("%s\n", nombre2);
    printf("Oponente encontrado!\n");
    
    mkfifo("FIFO_2", 0666);
    fd_w = open("FIFO_2", O_WRONLY);
    write(fd_w, (void *)nombre, 20);
    
    close(fd_w);
    
    mkfifo("FIFO", 0666);
    fd_r = open("FIFO", O_RDONLY);
    
    al_set_new_window_position(550, 0);
    display = al_create_display(550, 600);
    
    do
    {
        read(fd_r, (void *)campo, 1056);
        
        if(sendto(sock_cliente, (void *)campo, 1056, 0, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_in))  == -1)
        {
            perror("ERROR2: ");
            exit(EXIT_FAILURE);
        }
        
        len = sizeof(struct sockaddr_in);
        
        bytes = recvfrom(sock_cliente, campo_opp, 1056, 0, (struct sockaddr *) &server_addr, &len);
        
        if(bytes == -1)
        {
            perror("ERROR5: ");
            exit(EXIT_FAILURE);
        }
        
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_textf(font, al_map_rgb(255, 255, 255), 380, 0, ALLEGRO_ALIGN_LEFT, "%s", nombre2);
        print_campo(campo_opp, colores);
        al_flip_display();
        if(campo_opp[0][0] == 0)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 200, 250, ALLEGRO_ALIGN_LEFT, "EL OPONENTE PERDIO");
            al_flip_display();
            do
            {
                bytes2 = read(fd_r, (void *)campo, 1056);
            }while(bytes2 != 0);
            close(fd_r);
            b=0;
        }
        if(campo[0][0] == 0)
        {
            close(fd_r);
            b=0;
        }
    }while(b == 1);
    al_destroy_display(display);
    for(i=0;i<9;i++)
    {
        al_destroy_bitmap(colores[i]);
    }
    exit(EXIT_SUCCESS);
}
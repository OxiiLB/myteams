/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** init_fd_struct
*/

#include "myteams_server.h"

static void init_fd_struct(fd_t *fd, int *my_socket)
{
    FD_ZERO(&fd->input);
    FD_SET(*my_socket, &fd->input);
    FD_ZERO(&fd->save_input);
    FD_SET(*my_socket, &fd->save_input);
    FD_ZERO(&fd->ouput);
    FD_SET(*my_socket, &fd->ouput);
}

int init_server(my_teams_server_struct_t *my_teams_server_struct, int port)
{
    if (my_teams_server_struct == NULL)
        return ERROR;
    my_teams_server_struct->my_socket = setup_server(port, 42);
    if (my_teams_server_struct->my_socket == -1){
        printf("open server port\n");
        return KO;
    }
    init_fd_struct(&my_teams_server_struct->fd,
        &my_teams_server_struct->my_socket);
    for (int i = 0; i < FD_SETSIZE; i += 1) {
        my_teams_server_struct->clients[i].is_logged = false;
        my_teams_server_struct->clients[i].is_connected = false;
    }
    return 0;
}

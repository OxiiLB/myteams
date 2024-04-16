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

void init_list(teams_server_t *teams_server)
{
    LIST_INIT(&teams_server->all_user);
    teams_server->all_user.lh_first = NULL;
    LIST_INIT(&teams_server->all_teams);
    teams_server->all_teams.lh_first = NULL;
}

int init_server(teams_server_t *teams_server, int port)
{
    if (teams_server == NULL)
        return ERROR;
    teams_server->my_socket = setup_server(port, 42);
    if (teams_server->my_socket == -1){
        printf("can't open server port\n");
        return KO;
    }
    init_fd_struct(&teams_server->fd,
        &teams_server->my_socket);
    init_list(teams_server);
    for (int i = 0; i < FD_SETSIZE; i += 1) {
        teams_server->clients[i].is_logged = false;
    }
    return 0;
}

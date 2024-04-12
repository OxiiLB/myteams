/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** scan_fd
*/

#include "myteams_server.h"

static int check_connection(my_teams_server_struct_t *my_teams_server_struct)
{
    int client_fd = 0;

    if (my_teams_server_struct->actual_sockfd == my_teams_server_struct->
        my_socket) {
        client_fd = accept_new_connection(my_teams_server_struct->my_socket);
        if (client_fd == ERROR) {
            return ERROR;
        }
        dprintf(client_fd, "220 Service ready for new user.\n");
        FD_SET(client_fd, &my_teams_server_struct->fd.save_input);
    } else {
        handle_client(my_teams_server_struct);
    }
    return OK;
}

static int fd_is_set(my_teams_server_struct_t *my_teams_server_struct)
{
    if (FD_ISSET(my_teams_server_struct->actual_sockfd,
        &my_teams_server_struct->fd.input)) {
        if (check_connection(my_teams_server_struct) == ERROR)
            return ERROR;
        return 0;
    }
    return 0;
}

int scan_fd(my_teams_server_struct_t *my_teams_server_struct)
{
    for (my_teams_server_struct->actual_sockfd = 0; my_teams_server_struct->
        actual_sockfd < __FD_SETSIZE; my_teams_server_struct->actual_sockfd
        += 1) {
        if (fd_is_set(my_teams_server_struct) == ERROR)
            return ERROR;
    }
    return 0;
}

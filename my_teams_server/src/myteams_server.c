/*
** EPITECH PROJECT, 2023
** new_project_folder_file
** File description:
** my_project
*/

#include "myteams_server.h"
#include "../../include/my_macro.h"
#include <stdio.h>

int init_clients(ftp_struct_t *ftp_struct)
{
    for (int i = 0; i < __FD_SETSIZE; i++) {
        ftp_struct->clients[i].current_path = realpath(ftp_struct->home, NULL);
        ftp_struct->clients[i].is_logged = false;
        ftp_struct->clients[i].is_connected = false;
        ftp_struct->clients[i].username_entered = false;
    }
    return 0;
}

int accept_new_connection(ftp_struct_t *ftp_struct)
{
    ftp_struct->client_sockfd = accept(ftp_struct->sockfd, NULL, NULL);
    if (ftp_struct->client_sockfd == -1)
        return ERROR;
    return init_clients(ftp_struct);
}

int check_new_connection(ftp_struct_t *ftp_struct, int i)
{
    if (i == ftp_struct->sockfd) {
        if (accept_new_connection(ftp_struct) == ERROR)
            return ERROR;
        FD_SET(ftp_struct->client_sockfd, &ftp_struct->current_sockets);
        if (dprintf(ftp_struct->client_sockfd, "220\r\n") == -1)
            return ERROR;
    } else {
        if (read_from_client(ftp_struct) == ERROR)
            return ERROR;
    }
    return 0;
}

int init_server(char const *const *argv)
{
    ftp_struct_t *ftp_struct = malloc(sizeof(ftp_struct_t));

    if (ftp_struct == NULL ||
    setup_server(ftp_struct, 10, argv) == ERROR)
        return ERROR;
    set_fds(ftp_struct);
    while (1) {
        ftp_struct->ready_sockets = ftp_struct->current_sockets;
        if (select(__FD_SETSIZE,
        &ftp_struct->ready_sockets, &ftp_struct->writefds,
        &ftp_struct->exceptfds, NULL) == -1)
            return ERROR;
        if (scan_fd(ftp_struct) == ERROR)
            return ERROR;
    }
    free(ftp_struct);
    close((*ftp_struct).sockfd);
    return 0;
}

int myteams_server(int __attribute__((unused))argc, char const
    __attribute__((unused)) *const *argv)
{
    return init_server(argv);
}

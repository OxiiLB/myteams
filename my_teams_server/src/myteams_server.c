/*
** EPITECH PROJECT, 2023
** new_project_folder_file
** File description:
** my_project
*/

#include "myteams_server.h"
#include "../../include/my_macro.h"
#include <stdio.h>
#include <signal.h>

bool loopRunning;

void signal_handler(int signal)
{
    if (signal == SIGINT) {
        loopRunning = false;
    }
}

int init_clients(my_teams_server_struct_t *my_teams_server_struct)
{
    for (int i = 0; i < __FD_SETSIZE; i++) {
        my_teams_server_struct->clients[i].is_logged = false;
        my_teams_server_struct->clients[i].is_connected = false;
    }
    return 0;
}

int accept_new_connection(int my_socket)
{
    int client_sockfd = accept(my_socket, NULL, NULL);

    if (client_sockfd == -1)
        return ERROR;
    return client_sockfd;
}

int check_connection(my_teams_server_struct_t *my_teams_server_struct,
    int i)
{
    int client_fd = 0;

    if (i == my_teams_server_struct->my_socket) {
        client_fd = accept_new_connection(my_teams_server_struct->my_socket);
        if (client_fd == ERROR) {
            return ERROR;
        }
        dprintf(client_fd, "220 Service ready for new user.\n");
        FD_SET(client_fd, &my_teams_server_struct->fd.save_input);
    } else {
        handle_client(my_teams_server_struct, i);
    }
    return OK;
}

int myteams_server(int port)
{
    my_teams_server_struct_t my_teams_server_struct;

    loopRunning = true;
    signal(SIGINT, signal_handler);
    init_server(&my_teams_server_struct, port);
    while (loopRunning) {
        my_teams_server_struct.fd.input = my_teams_server_struct.fd.save_input;
        if (select(FD_SETSIZE, &my_teams_server_struct.fd.input,
            &my_teams_server_struct.fd.ouput, NULL, NULL) == -1)
            return ERROR;
        if (scan_fd(&my_teams_server_struct) == ERROR)
            return ERROR;
    }
    close(my_teams_server_struct.my_socket);
    return 0;
}

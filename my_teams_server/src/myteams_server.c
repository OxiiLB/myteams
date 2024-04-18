/*
** EPITECH PROJECT, 2023
** new_project_folder_file
** File description:
** my_project
*/

#include "myteams_server.h"
#include <stdio.h>
#include <signal.h>

static bool loopRunning = true;

void signal_handler(int signal)
{
    if (signal == SIGINT)
        loopRunning = false;
}

int close_server(teams_server_t *teams_server)
{
    save_info_to_file(teams_server);
    close(teams_server->my_socket);
    free_users(&(teams_server->all_user));
    free(teams_server);
    return OK;
}

int myteams_server(int port)
{
    teams_server_t *teams_server = calloc(sizeof(teams_server_t), 1);


    signal(SIGINT, signal_handler);
    if (init_server(teams_server, port) == KO) {
        free(teams_server);
        return ERROR;
    }
    read_info_from_save_file(teams_server);
    users_command(teams_server, "");
    while (loopRunning) {
        teams_server->fd.input = teams_server->fd.save_input;
        if (select(FD_SETSIZE, &(teams_server->fd.input),
            &(teams_server->fd.ouput), NULL, NULL) == KO && loopRunning)
            return ERROR;
        if (loopRunning && scan_fd(teams_server) == ERROR)
            return ERROR;
    }
    close_server(teams_server);
    return OK;
}

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
    if (signal == SIGINT)
        loopRunning = false;
}

int myteams_server(int port)
{
    teams_server_t teams_server;

    loopRunning = true;
    signal(SIGINT, signal_handler);
    if (init_server(&teams_server, port) == KO)
        return ERROR;
    read_info_from_save_file(&teams_server);
    while (loopRunning) {
        teams_server.fd.input = teams_server.fd.save_input;
        if (select(FD_SETSIZE, &teams_server.fd.input,
            &teams_server.fd.ouput, NULL, NULL) == KO && loopRunning)
            return ERROR;
        if (loopRunning && scan_fd(&teams_server) == ERROR)
            return ERROR;
    }
    save_info_to_file(&teams_server);
    close(teams_server.my_socket);
    free_users(&teams_server.all_user);
    return OK;
}

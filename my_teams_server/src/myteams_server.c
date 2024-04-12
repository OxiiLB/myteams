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

int myteams_server(int port)
{
    my_teams_server_struct_t my_teams_server_struct;

    loopRunning = true;
    signal(SIGINT, signal_handler);
    if (init_server(&my_teams_server_struct, port) == KO)
        return ERROR;
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

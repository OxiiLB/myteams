/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** use_command
*/


#include "myteams_server.h"

int handle_errors(teams_server_t *teams_server, char *command)
{
    if (teams_server->clients[teams_server->actual_sockfd].is_logged ==
        false) {
        dprintf(teams_server->actual_sockfd, "500|not logged in\n");
        dprintf(teams_server->actual_sockfd, SPLITTER_STR);
        return 1;
    }
    if (strlen(command) != MAX_UUID_LENGTH + 1) {
        dprintf(teams_server->actual_sockfd, "500|Invalid UUID\n");
        dprintf(teams_server->actual_sockfd, SPLITTER_STR);
        return 1;
    }
    return 0;
}

int get_array_len(char **array)
{
    int i = 0;

    for (; array[i] != NULL; i++);
    return i;
}

void use_command(teams_server_t *teams_server, char *command)
{
    char **split_command = my_strtok(command, " ");

    if (get_array_len(split_command) == 1) {
        strcpy(teams_server->clients[teams_server->actual_sockfd].user->context,
            ROOT_CONEXT);
    }
    if (handle_errors(teams_server, command) == 1)
        return;
    strcpy(teams_server->clients[teams_server->actual_sockfd].user->context,
        split_command[1]);
    teams_server->clients[teams_server->actual_sockfd].user->valid_context =
        true;
    dprintf(teams_server->actual_sockfd, "200|");
    dprintf(teams_server->actual_sockfd, SPLITTER_STR);
}

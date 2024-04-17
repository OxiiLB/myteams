/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** use_command
*/


#include "myteams_server.h"

void use_command(teams_server_t *teams_server, char *command)
{
    if (teams_server->clients[teams_server->actual_sockfd].is_logged ==
        false) {
        dprintf(teams_server->actual_sockfd, "500|not logged in\n");
        dprintf(teams_server->actual_sockfd, SPLITTER_STR);
        return;
    }
    if (strlen(command) != MAX_UUID_LENGTH + 1) {
        dprintf(teams_server->actual_sockfd, "500|Invalid UUID\n");
        dprintf(teams_server->actual_sockfd, SPLITTER_STR);
        return;
    }
    strcpy(teams_server->clients[teams_server->actual_sockfd].user->context,
        command);
    teams_server->clients[teams_server->actual_sockfd].user->valid_context =
        true;
    dprintf(teams_server->actual_sockfd, "200|");
    dprintf(teams_server->actual_sockfd, SPLITTER_STR);
}

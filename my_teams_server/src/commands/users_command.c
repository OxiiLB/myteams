/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** users_command
*/


#include "myteams_server.h"

void users_command(teams_server_t *teams_server, char *command)
{
    user_t *user = NULL;

    if (!command)
        return;
    if (strlen(command) != 0) {
        dprintf(teams_server->actual_sockfd, "500|Internal Server Error\n");
        dprintf(teams_server->actual_sockfd, SPLITTER_STR);
        return;
    }
    dprintf(teams_server->actual_sockfd, "200|");
    if (teams_server->clients[teams_server->actual_sockfd].is_logged > 0)
        dprintf(teams_server->actual_sockfd, "1\n");
    else
        dprintf(teams_server->actual_sockfd, "0\n");
    LIST_FOREACH(user, &teams_server->all_user, next)
    {
        dprintf(teams_server->actual_sockfd, "%s\b%s\n",
            user->uuid, user->username);
    }
    dprintf(teams_server->actual_sockfd, SPLITTER_STR);
}

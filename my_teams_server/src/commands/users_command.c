/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** users_command
*/


#include "myteams_server.h"

int check_errors(teams_server_t *teams_server, char *command)
{
    if (!command)
        return 1;
    if (teams_server->clients[teams_server->actual_sockfd].user == NULL) {
        dprintf(teams_server->actual_sockfd, "502|Unauthorized action\n%s",
            SPLITTER_STR);
        return 1;
    }
    if (strlen(command) != 0) {
        dprintf(teams_server->actual_sockfd, "500|Internal Server Error\n%s",
            SPLITTER_STR);
        return 1;
    }
    return 0;
}

void users_command(teams_server_t *teams_server, char *command)
{
    user_t *user = NULL;

    if (check_errors(teams_server, command) == 1)
        return;
    dprintf(teams_server->actual_sockfd, "200|/users\n");
    TAILQ_FOREACH(user, &teams_server->all_user, next) {
        dprintf(teams_server->actual_sockfd, "%s\b%s\b",
            user->uuid, user->username);
        if (user->nb_clients > 0)
            dprintf(teams_server->actual_sockfd, "1\n");
        else
            dprintf(teams_server->actual_sockfd, "0\n");
    }
    dprintf(teams_server->actual_sockfd, SPLITTER_STR);
}

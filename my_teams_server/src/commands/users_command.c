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
        dprintf(teams_server->actual_sockfd, "502|Unauthorized action%s%s",
            END_LINE, END_STR);
        return 1;
    }
    if (strlen(command) != 0) {
        dprintf(teams_server->actual_sockfd, "500|Internal Server Error%s%s",
            END_LINE, END_STR);
        return 1;
    }
    return 0;
}

void users_command(teams_server_t *teams_server, char *command)
{
    user_t *user = NULL;

    if (check_errors(teams_server, command) == 1)
        return;
    dprintf(teams_server->actual_sockfd, "200|/users%s", END_LINE);
    TAILQ_FOREACH(user, &teams_server->all_user, next) {
        if (user->nb_clients > 0)
            dprintf(teams_server->actual_sockfd, "1%s", SPLIT_LINE);
        else
            dprintf(teams_server->actual_sockfd, "0%s", SPLIT_LINE);
        dprintf(teams_server->actual_sockfd, "%s%s%s%s",
            user->uuid, SPLIT_LINE, user->username, END_LINE);
    }
    dprintf(teams_server->actual_sockfd, END_STR);
}

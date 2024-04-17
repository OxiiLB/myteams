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

    printf("users_command\n");
    LIST_FOREACH(user, &teams_server->all_user, next)
    {
        dprintf(teams_server->actual_sockfd, "username: %s\n",
            user->username);
    }
    dprintf(teams_server->actual_sockfd, SPLITTER_STR);
}

/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** users_command
*/


#include "myteams_server.h"

void users_command(teams_server_t *teams_server,
    char __attribute__((unused)) * command)
{
    user_t *user;

    LIST_FOREACH(user, &teams_server->all_user, next)
    {
        dprintf(teams_server->actual_sockfd, "username: %s\n",
            user->username);
    }
    dprintf(teams_server->actual_sockfd, SPLITTER_STR);
}

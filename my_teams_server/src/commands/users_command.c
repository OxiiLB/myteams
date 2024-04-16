/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** users_command
*/


#include "myteams_server.h"

char *get_users(teams_server_t *teams_server)
{
    user_t *user;
    char *result = NULL;
    int len = 0;

    LIST_FOREACH(user, &teams_server->all_user, next)
        len += strlen(user->username) + 1;
    result = malloc(sizeof(char) * (len + 2));
    if (!result)
        return NULL;
    if (teams_server->clients[teams_server->actual_sockfd].is_logged == false)
        strcat(result, "0");
    else
        strcat(result, "1");
    LIST_FOREACH(user, &teams_server->all_user, next)
    {
        strcat(result, user->username);
        strcat(result, "\n");
    }
    strcat(result, SPLITTER_STR);
    return result;
}

void pusers_command(teams_server_t *teams_server,
    char __attribute__((unused)) * command)
{
    char *result = get_users(teams_server);

    if (!result)
        return;
    dprintf(teams_server->actual_sockfd, result);
    free(result);
}

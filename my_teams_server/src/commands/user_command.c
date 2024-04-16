/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** user_command
*/


#include "myteams_server.h"

char *get_user_info(teams_server_t *teams_server, user_t *user)
{
    char *result = NULL;
    int len = 0;

    len = strlen(user->username) + strlen(user->uuid) + 1;
    result = malloc(sizeof(char) * (len + 3));
    if (!result)
        return NULL;
    if (result, teams_server->clients[teams_server->actual_sockfd].is_logged)
        strcat(result, "1");
    else
        strcat(result, "0");
    strcat(result, user->username);
    strcat(result, "\n");
    strcat(result, user->uuid);
    strcat(result, SPLITTER_STR);
    strcat(result, "\0");
}

void user_command(teams_server_t *teams_server,
    char __attribute__((unused)) * command)
{
    char *result = NULL;
    char **parsed_command = splitter(command, " ");
    user_t *user = NULL;

    if (!parsed_command || !parsed_command[1])
        return;
    LIST_FOREACH(user, &teams_server->all_user, next)
    {
        if (strcmp(user->uuid, parsed_command[1]) == 0) {
            result = get_user_info(teams_server, user);
            dprintf(teams_server->actual_sockfd, result);
            free_array(parsed_command);
            free(result);
            return;
        }
    }
    dprintf(teams_server->actual_sockfd, "user not found\n");
    dprintf(teams_server->actual_sockfd, SPLITTER_STR);
}

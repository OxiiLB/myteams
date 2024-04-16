/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** user_command
*/


#include "myteams_server.h"

void user_command(teams_server_t *teams_server,
    char __attribute__((unused)) * command)
{
    char **parsed_command = splitter(command, " ");
    user_t *user = NULL;

    if (!parsed_command || !parsed_command[1])
        return;
    LIST_FOREACH(user, &teams_server->all_user, next)
    {
        if (strcmp(user->uuid, parsed_command[1]) == 0) {
            dprintf(teams_server->actual_sockfd, "user %s\n%s\n",
                user->username, user->uuid);
            dprintf(teams_server->actual_sockfd, SPLITTER_STR);
            free_array(parsed_command);
            return;
        }
    }
    dprintf(teams_server->actual_sockfd, "user not found\n");
    dprintf(teams_server->actual_sockfd, SPLITTER_STR);
}

/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** user_command
*/


#include "myteams_server.h"

int print_user(teams_server_t *teams_server, user_t *user)
{
    dprintf(teams_server->actual_sockfd, "200|/user%s%s%s%s%s",
        END_LINE, user->uuid, SPLIT_LINE, user->username, SPLIT_LINE);
    if (teams_server->clients[teams_server->actual_sockfd].user)
        dprintf(teams_server->actual_sockfd, "1%s", END_LINE);
    else
        dprintf(teams_server->actual_sockfd, "0%s", END_LINE);
    dprintf(teams_server->actual_sockfd, END_STR);
    return 0;
}

void user_command(teams_server_t *teams_server,
    char __attribute__((unused)) * command)
{
    char **parsed_command = splitter(command, " ");
    user_t *user = NULL;

    if (!parsed_command || !parsed_command[1]) {
        dprintf(teams_server->actual_sockfd, "500|Internal Server Error%s%s",
            END_LINE, END_STR);
        return;
    }
    TAILQ_FOREACH(user, &teams_server->all_user, next) {
        if (strcmp(user->uuid, parsed_command[1]) == 0) {
            print_user(teams_server, user);
            dprintf(teams_server->actual_sockfd, END_STR);
            free_array(parsed_command);
            return;
        }
    }
    dprintf(teams_server->actual_sockfd, "500|User not found\n");
    dprintf(teams_server->actual_sockfd, END_STR);
}

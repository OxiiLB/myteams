/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** user_command
*/


#include "myteams_server.h"

int print_user(teams_server_t *teams_server, user_t *user)
{
    int status = 0;

    if (teams_server->clients[teams_server->actual_sockfd].user)
        status = 1;
    else
        status = 0;
    dprintf(teams_server->actual_sockfd, "200|/user%s%d%s%s%s%s%s",
        END_LINE, status, SPLIT_LINE, user->uuid, SPLIT_LINE,
        user->username, END_LINE);
    return 0;
}

void user_command(teams_server_t *teams_server,
    char __attribute__((unused)) * command)
{
    user_t *user = NULL;

    if (strlen(command) == 0) {
        dprintf(teams_server->actual_sockfd, "500|Internal Server Error%s%s",
            END_LINE, END_STR);
        return;
    }
    command = &command[2];
    command[strlen(command) - 1] = '\0';
    TAILQ_FOREACH(user, &teams_server->all_user, next) {
        printf("user->uuid = %s\n", user->uuid);
        printf("command = %s\n", command);
        if (strcmp(user->uuid, command) == 0) {
            print_user(teams_server, user);
            dprintf(teams_server->actual_sockfd, END_STR);
            return;
        }
    }
    dprintf(teams_server->actual_sockfd, "500|User not found\n");
    dprintf(teams_server->actual_sockfd, END_STR);
}

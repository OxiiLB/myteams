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
            END_STR);
        return 1;
    }
    if (strlen(command) != 0) {
        dprintf(teams_server->actual_sockfd, "500|Internal Server Error\n%s",
            END_STR);
        return 1;
    }
    return 0;
}

void users_command(teams_server_t *teams_server, char *command)
{
    user_t *user = NULL;

    // if (check_errors(teams_server, command) == 1)
    //     return;
    printf("200|/users%s", END_LINE);
    TAILQ_FOREACH(user, &teams_server->all_user, next) {
        printf("%s%s%s%s",
            user->uuid, SPLIT_LINE, user->username, SPLIT_LINE);
        if (user->nb_clients > 0)
            printf("1%s", END_LINE);
        else
            printf("0%s", END_LINE);
    }
    printf(END_STR);
}

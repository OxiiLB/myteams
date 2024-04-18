/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logout_command
*/


#include "myteams_server.h"

void logout_command(teams_server_t *teams_server, char *command)
{
    if (strlen(command) != 0) {
        dprintf(teams_server->actual_sockfd, "500|Invalid command\n%s",
            END_STR);
        return;
    }
    if (teams_server->clients[teams_server->actual_sockfd].user == NULL) {
        dprintf(teams_server->actual_sockfd, "502|Unauthorized action\n%s",
            END_STR);
        return;
    }
    dprintf(teams_server->actual_sockfd, "200|/logout%s%s%s%s%s",
        END_LINE, teams_server->clients[teams_server->actual_sockfd].
        user->uuid, SPLIT_LINE, teams_server->clients
        [teams_server->actual_sockfd].user->username, END_LINE);
    dprintf(teams_server->actual_sockfd, END_STR);
    server_event_user_logged_out(teams_server->clients[teams_server->
        actual_sockfd].user->uuid);
    teams_server->clients[teams_server->actual_sockfd].user = NULL;
    close(teams_server->actual_sockfd);
    FD_CLR(teams_server->actual_sockfd, &teams_server->fd.save_input);
}

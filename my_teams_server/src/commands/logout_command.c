/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logout_command
*/


#include "myteams_server.h"

void logout_command(teams_server_t *teams_server, char *command)
{
    if (teams_server->clients[teams_server->actual_sockfd].is_logged ==
        false) {
        dprintf(teams_server->actual_sockfd, "Not logged in\n");
        dprintf(teams_server->actual_sockfd, SPLITTER_STR);
        return;
    }
    dprintf(teams_server->actual_sockfd, teams_server->clients
        [teams_server->actual_sockfd].user->uuid);
    dprintf(teams_server->actual_sockfd, "\n");
    dprintf(teams_server->actual_sockfd, teams_server->clients
        [teams_server->actual_sockfd].user->username);
    dprintf(teams_server->actual_sockfd, SPLITTER_STR);
    server_event_user_logged_out(teams_server->clients[teams_server->
        actual_sockfd].user->uuid);
    teams_server->clients[teams_server->actual_sockfd].is_logged = false;
    teams_server->clients[teams_server->actual_sockfd].user = NULL;
    close(teams_server->actual_sockfd);
    FD_CLR(teams_server->actual_sockfd, &teams_server->fd.save_input);
}

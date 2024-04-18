/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logout_command
*/


#include "myteams_server.h"

void logout_command(teams_server_t *teams_server, char *command)
{
    if (teams_server->clients[teams_server->actual_sockfd].user == NULL) {
        dprintf(teams_server->actual_sockfd, "500|Not logged in");
        dprintf(teams_server->actual_sockfd, SPLITTER_STR);
        return;
    }
    dprintf(teams_server->actual_sockfd, "200|/logout\n%s\n%s\n",
        teams_server->clients[teams_server->actual_sockfd].user->uuid,
        teams_server->clients[teams_server->actual_sockfd].user->username);
    dprintf(teams_server->actual_sockfd, SPLITTER_STR);
    server_event_user_logged_out(teams_server->clients[teams_server->
        actual_sockfd].user->uuid);
    teams_server->clients[teams_server->actual_sockfd].user = NULL;
    close(teams_server->actual_sockfd);
    FD_CLR(teams_server->actual_sockfd, &teams_server->fd.save_input);
}

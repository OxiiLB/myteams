/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logout_command
*/


#include "myteams_server.h"

void logout_command(teams_server_t *teams_server,
    char __attribute__((unused)) * command)
{
    server_event_user_logged_out(teams_server->clients
    [teams_server->actual_sockfd].user->uuid);
    teams_server->clients[teams_server->
    actual_sockfd].is_logged = false;
    teams_server->clients[teams_server->
    actual_sockfd].user = NULL;
    close(teams_server->actual_sockfd);
    FD_CLR(teams_server->actual_sockfd,
    &teams_server->fd.save_input);
}

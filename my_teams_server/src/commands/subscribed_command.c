/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** subscribed_command
*/


#include "myteams_server.h"

void subscribed_command(teams_server_t *teams_server,
    char __attribute__((unused)) * command)
{
    if (teams_server->clients[teams_server->actual_sockfd].user == NULL) {
        dprintf(teams_server->actual_sockfd, "502|Unauthorized action%s%s",
            END_LINE, END_STR);
        return;
    }
    dprintf(teams_server->actual_sockfd, "200|/subscribed%s%s",
            END_LINE, END_STR);
}

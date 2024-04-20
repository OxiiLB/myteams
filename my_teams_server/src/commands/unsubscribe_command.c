/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** unsubscribe_command
*/


#include "myteams_server.h"

void unsubscribe_command(teams_server_t *teams_server,
    char __attribute__((unused)) * command)
{
    subscribed_teams_t *team = NULL;

    if (teams_server->clients[teams_server->actual_sockfd].user == NULL) {
        dprintf(teams_server->actual_sockfd, "502|Unauthorized action%s%s",
            END_LINE, END_STR);
        return;
    }
    if (command == NULL || strlen(command) < 2) {
        dprintf(teams_server->actual_sockfd, "500|Internal Server Error\n");
        dprintf(teams_server->actual_sockfd, END_STR);
        return;
    }
    command = &command[2];
    command[strlen(command) - 1] = '\0';
    TAILQ_FOREACH(team, &teams_server->
        clients[teams_server->actual_sockfd].user->subscribed_teams, next) {
        if (strcmp(team->team_uuid, command) == 0) {
            TAILQ_REMOVE(&teams_server->clients[teams_server->actual_sockfd]
                .user->subscribed_teams, team, next);
            server_event_user_unsubscribed(team->team_uuid, teams_server->
                clients[teams_server->actual_sockfd].user->uuid);
            return;
        }
    }
}

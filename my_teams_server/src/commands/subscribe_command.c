/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** subscribe_command
*/


#include "myteams_server.h"

bool is_team_exist(teams_server_t *teams_server, char *team_uuid)
{
    team_t *team = NULL;

    TAILQ_FOREACH(team, &teams_server->all_teams, next) {
        if (strcmp(team->team_uuid, team_uuid) == 0)
            return true;
    }
    return false;
}

static int handle_error(teams_server_t *teams_server, char *command)
{
    if (teams_server->clients[teams_server->actual_sockfd].user == NULL) {
        dprintf(teams_server->actual_sockfd, "502|Unauthorized action%s%s",
            END_LINE, END_STR);
        return KO;
    }
    if (strlen(command) < 2) {
        dprintf(teams_server->actual_sockfd, "500|Internal Server Error\n");
        dprintf(teams_server->actual_sockfd, END_STR);
        return KO;
    }
    return OK;
}

void subscribe_command(teams_server_t *teams_server, char *command)
{
    subscribed_teams_t *team = NULL;

    if (handle_error(teams_server, command) == KO)
        return;
    command = &command[2];
    command[strlen(command) - 1] = '\0';
    if (!is_team_exist(teams_server, command)) {
        dprintf(teams_server->actual_sockfd, "404|Team not found\n");
        dprintf(teams_server->actual_sockfd, END_STR);
        return;
    }
    team = calloc(sizeof(subscribed_teams_t), 1);
    strcpy(team->team_uuid, command);
    strcpy(team->user_uuid, teams_server->clients[teams_server->actual_sockfd]
        .user->uuid);
    TAILQ_INSERT_TAIL(&(teams_server->clients[teams_server->actual_sockfd]
        .user->subscribed_teams), team, next);
    server_event_user_subscribed(team->team_uuid, teams_server->
        clients[teams_server->actual_sockfd].user->uuid);
}

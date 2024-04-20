/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** subscribed_command
*/


#include "myteams_server.h"

team_t *get_team_by_uuid(struct teamhead* teams_head, char *uuid)
{
    team_t *team = NULL;

    TAILQ_FOREACH(team, teams_head, next) {
        if (strcmp(team->team_uuid, uuid) == 0)
            return team;
    }
    return NULL;
}

int list_subscribed_teams(teams_server_t *teams_server)
{
    team_t *team = NULL;
    subscribed_t *subscribed_team = NULL;

    dprintf(teams_server->actual_sockfd, "200|/subscribed%steams%s", END_LINE,
        END_LINE);
    TAILQ_FOREACH(subscribed_team, &teams_server->clients
        [teams_server->actual_sockfd].user->subscribed_teams, next) {
        team = get_team_by_uuid(&teams_server->all_teams,
            subscribed_team->team_uuid);
        if (team) {
            dprintf(teams_server->actual_sockfd, "%s%s%s%s%s%s",
            team->team_uuid, SPLIT_LINE,
            team->name, SPLIT_LINE,
            team->desc, END_LINE);
        }
    }
    dprintf(teams_server->actual_sockfd, END_STR);
    return 0;
}

void subscribed_command(teams_server_t *teams_server,
    char __attribute__((unused)) * command)
{
    char **splitted_command = splitter(command, "\"");

    if (teams_server->clients[teams_server->actual_sockfd].user == NULL) {
        dprintf(teams_server->actual_sockfd, "502|Unauthorized action%s%s",
            END_LINE, END_STR);
        free_array(splitted_command);
        return;
    }
    if (splitted_command[1] == NULL) {
        list_subscribed_teams(teams_server);
    } else {
        dprintf(teams_server->actual_sockfd, "200|/subscribed%s", END_LINE);
        dprintf(teams_server->actual_sockfd, END_STR);
    }
    free_array(splitted_command);
}

/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** help_command
*/

#include "myteams_server.h"

void help_command(teams_server_t *teams_server,
    char __attribute__((unused)) * command)
{
    if (teams_server->clients[teams_server->actual_sockfd].user == NULL) {
        dprintf(teams_server->actual_sockfd, "502|Unauthorized action%s%s",
            END_LINE, END_STR);
        return;
    }
    if (strlen(command) != 0) {
        dprintf(teams_server->actual_sockfd, "500|Invalid command\n");
        dprintf(teams_server->actual_sockfd, END_STR);
        return;
    }
    dprintf(teams_server->actual_sockfd, "214|/help%s", END_LINE);
    dprintf(teams_server->actual_sockfd, "COMMANDS:\n/help\n/login [\"userna");
    dprintf(teams_server->actual_sockfd, "me\"]\n/logout\n/users\n/user [\"u");
    dprintf(teams_server->actual_sockfd, "ser_uuid\"]\n/send [\"user_uuid\"]");
    dprintf(teams_server->actual_sockfd, " [\"message_body\"]\n/messages[\"u");
    dprintf(teams_server->actual_sockfd, "ser_uuid\"]\n/subscribe [\"team_uu");
    dprintf(teams_server->actual_sockfd, "id\"]\n/subscribed\n/unsubscribe [");
    dprintf(teams_server->actual_sockfd, "\"team_uuid\"]\n/use [\"team_uuid");
    dprintf(teams_server->actual_sockfd, "\"]\n/create [\"team_name\"] [\"te");
    dprintf(teams_server->actual_sockfd, "am_description\"]\n/list\n/info [");
    dprintf(teams_server->actual_sockfd, "\"team_uuid\"]\n");
    dprintf(teams_server->actual_sockfd, END_STR);
}

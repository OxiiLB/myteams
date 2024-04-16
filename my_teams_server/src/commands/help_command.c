/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** help_command
*/

#include "myteams_server.h"

void help_command(my_teams_server_struct_t *my_teams_server_struct,
    char __attribute__((unused)) * command)
{
    char *test = "100 HELP:\n\
    COMMANDS: /help\n/login [\"username\"]\n/logout\n/users\n\
    /user [\"user_uuid\"]\n/send [\"user_uuid\"] [\"message_body\"]\n/messages\
    [\"user_uuid\"]\n/subscribe [\"team_uuid\"]\n/subscribed\n/unsubscribe \
    [\"team_uuid\"]\n/use [\"team_uuid\"]\n/create [\"team_name\"] \
    [\"team_description\"]\n/list\n/info [\"team_uuid\"]\n";

    dprintf(my_teams_server_struct->actual_sockfd, test);
    dprintf(my_teams_server_struct->actual_sockfd, SPLITTER_STR);
}

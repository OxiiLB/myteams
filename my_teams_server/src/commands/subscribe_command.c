/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** subscribe_command
*/


#include "myteams_server.h"

void subscribe_command(teams_server_t *teams_server,
    char __attribute__((unused)) * command)
{
    char *test = "zaerzrzerzer";

    write(teams_server->actual_sockfd, test, strlen(test));
}

/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** unsubscribe_command
*/


#include "myteams_server.h"

void unsubscribe_command(my_teams_server_struct_t *my_teams_server_struct,
    char __attribute__((unused)) * command)
{
    char *test = "zaerzrzerzer";

    write(my_teams_server_struct->actual_sockfd, test, strlen(test));
}

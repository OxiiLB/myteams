/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** help_command
*/

#include "myteams_server.h"

void help_command(my_teams_server_struct_t *my_teams_server_struct,
    char *command)
{
    char *test = "zaerzrzerzer";

    write(my_teams_server_struct->actual_sockfd, test, strlen(test));
}

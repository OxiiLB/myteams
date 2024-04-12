/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** login_command
*/

#include "my_teams_server.h"

void login_command(my_teams_server_struct_t *my_teams_server_struct,
    char *command)
{
    char *test = "zaerzrzerzer";
    char *uuid;

    uuid = generate_random_uuid();
    write(my_teams_server_struct->actual_sockfd, uuid, strlen(test));
}

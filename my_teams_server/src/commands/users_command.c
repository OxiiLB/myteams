/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** users_command
*/


#include "myteams_server.h"

void users_command(my_teams_server_struct_t *my_teams_server_struct,
    char __attribute__((unused)) * command)
{
    user_t *user;

    LIST_FOREACH(user, &my_teams_server_struct->all_user, next)
    {
        dprintf(my_teams_server_struct->actual_sockfd, "username: %s\n",
            user->username);
    }
    dprintf(my_teams_server_struct->actual_sockfd, "\v");
}

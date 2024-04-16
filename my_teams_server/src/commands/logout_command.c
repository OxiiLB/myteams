/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logout_command
*/


#include "myteams_server.h"

void logout_command(my_teams_server_struct_t *my_teams_server_struct,
    char __attribute__((unused)) * command)
{
    my_teams_server_struct->clients[my_teams_server_struct->actual_sockfd].is_connected = false;
    server_event_user_logged_out(my_teams_server_struct->clients[my_teams_server_struct->actual_sockfd].user.uuid);
}

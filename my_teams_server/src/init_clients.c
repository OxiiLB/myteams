/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** init_clients
*/

#include "myteams_server.h"

int init_clients(my_teams_server_struct_t *my_teams_server_struct)
{
    for (int i = 0; i < __FD_SETSIZE; i++) {
        my_teams_server_struct->clients[i].is_logged = false;
        my_teams_server_struct->clients[i].is_connected = false;
    }
    return 0;
}

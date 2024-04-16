/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** init_clients
*/

#include "myteams_server.h"

int init_clients(teams_server_t *teams_server)
{
    for (int i = 0; i < __FD_SETSIZE; i++) {
        teams_server->clients[i].is_logged = false;
    }
    return 0;
}

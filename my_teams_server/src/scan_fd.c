/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** scan_fd
*/

#include "myteams_server.h"

static int fd_is_set(my_teams_server_struct_t *my_teams_server_struct, int i)
{
    if (FD_ISSET(i, &my_teams_server_struct->fd.input)) {
        if (check_connection(my_teams_server_struct, i) == ERROR)
            return ERROR;
        return 0;
    }
    return 0;
}

int scan_fd(my_teams_server_struct_t *my_teams_server_struct)
{
    for (int i = 0; i < __FD_SETSIZE; i++) {
        if (fd_is_set(my_teams_server_struct, i) == ERROR)
            return ERROR;
    }
    return 0;
}

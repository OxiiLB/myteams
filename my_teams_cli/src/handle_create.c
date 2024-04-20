/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_create
*/

#include "myteams_cli.h"

    // {"channel", &create_channel},
    // {"thread", &create_thread},
    // {"reply", &create_reply},

const struct create_s CREATE_FUNCS[] = {
    {"team", &create_team},
    {"NULL", NULL}
};

void create_team(char **info)
{
   //
}

void handle_create(char **info, int socketfd)
{
    (void)socketfd;
    
}

/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_list
*/

#include "myteams_cli.h"

const struct list_s LIST_FUNCS[] = {
    //{"user", &list_users},
    //{"team", &list_teams},
    //{"channel", &list_channels},
    //{"thread", &list_threads},
    {"NULL", NULL}
};

void handle_list(char **info, int socketfd)
{
    (void)socketfd;
    for (int i = 0; LIST_FUNCS[i].func != NULL; i++) {
        if (strcmp(info[1], LIST_FUNCS[i].context) == 0) {
            LIST_FUNCS[i].func(info);
            return;
        }
    }
}

/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_list
*/

#include "myteams_cli.h"

const struct list_s LIST_FUNCS[] = {
    {"team", &list_teams},
    {"channel", &list_channels},
    {"thread", &list_threads},
    {"reply", &list_replies},
    {"NULL", NULL}
};

void handle_list(char **info, int __attribute__((unused)) socketfd)
{
    int add = 0;

    for (int i = 0; LIST_FUNCS[i].func != NULL; i++) {
        if (strcmp(info[1], LIST_FUNCS[i].context) == 0) {
            LIST_FUNCS[i].func(info, add);
            return;
        }
    }
}

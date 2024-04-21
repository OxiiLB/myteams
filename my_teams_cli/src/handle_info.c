/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_info
*/

#include "myteams_cli.h"

const struct info_s INFO_FUNCS[] = {
    {"user", &info_user},
    {"team", &info_team},
    {"channel", &info_channel},
    {"thread", &info_thread},
    {"NULL", NULL}
};

void handle_info(char **info, int __attribute__((unused)) socketfd)
{
    for (int i = 0; INFO_FUNCS[i].func != NULL; i++) {
        if (strcmp(info[1], INFO_FUNCS[i].context) == 0) {
            INFO_FUNCS[i].func(info);
            return;
        }
    }
}

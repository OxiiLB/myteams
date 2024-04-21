/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_create
*/

#include "myteams_cli.h"


const struct create_s CREATE_FUNCS[] = {
    {"team", &create_team},
    {"channel", &create_channel},
    {"thread", &create_thread},
    {"reply", &create_reply},
    {"NULL", NULL}
};

// printf("\n"); ////////////////////////////////////////
// print_2d_array(info, 0); ///////////////////////////////
// printf("\n\n"); ////////////////////////////////////////
void handle_create(char **info, int socketfd)
{
    (void)socketfd;
    for (int i = 0; CREATE_FUNCS[i].func != NULL; i++) {
        if (strcmp(info[1], CREATE_FUNCS[i].context) == 0) {
            CREATE_FUNCS[i].func(info);
            return;
        }
    }
}

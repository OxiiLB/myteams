/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** tools
*/

#include "myteams_cli.h"

char *get_msg_after_status(char *server_msg)
{
    int len = strlen(server_msg);
    for (int i = 0; i < len - 1; i++) {
        server_msg[i] = server_msg[i + 1];
    }
    server_msg[len - 1] = '\0';
    return server_msg;
}

void do_multiple_frees(char *one, char *two, char *three, char *four)
{
    if (one != NULL)
        free(one);
    if (two != NULL)
        free(two);
    if (three != NULL)
        free(three);
    if (four != NULL)
        free(four);
}

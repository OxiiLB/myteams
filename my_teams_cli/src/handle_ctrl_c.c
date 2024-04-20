/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_ctrl_c
*/

#include "myteams_cli.h"

void handle_ctrl_c(int socketfd)
{
    int ret = 0;

    char buf[MAX_COMMAND_LENGTH] = "/logout\v";
    if (write(socketfd, buf, strlen(buf) + 1) == -1)
        exit(84);
}

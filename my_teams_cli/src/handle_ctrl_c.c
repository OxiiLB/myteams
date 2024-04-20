/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_ctrl_c
*/

#include "myteams_cli.h"

void handle_ctrl_c(int socketfd)
{
    char buf[MAX_COMMAND_LENGTH] = "/logout\v";

    if (write(socketfd, buf, strlen(buf) + 1) == -1)
        exit(84);
    read_server_message(NULL, socketfd);
}

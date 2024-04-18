/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_cmds_2
*/

#include "myteams_cli.h"

void handle_send(char **info)
{
    client_event_private_message_received(info[1], info[2]);
}

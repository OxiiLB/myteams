/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_cmds_2
*/

#include "myteams_cli.h"

void handle_send(char **info, int socketfd)
{
    char *user_uuid = get_msg_up_to_char(info[1], '\a', 0);
    char *user_name = get_msg_after_nb(info[1], (int)strlen(user_uuid));

    client_event_private_message_received(user_uuid, user_name);
    do_multiple_frees(user_uuid, user_name, NULL, NULL);
}

void handle_messages(char **info, int socketfd)
{
    int i = 0;
    char *sender_uuid = NULL;
    char *message_timestamp = NULL;
    char *message_body = NULL;

    for (i = 1; info[i] != NULL; i++) {
        sender_uuid = get_msg_up_to_char(info[i], '\a', 0);
        message_timestamp = get_msg_up_to_char(info[i], '\a',
        (int)strlen(sender_uuid) + 1);
        message_body = get_msg_after_nb(info[i],
        (int)strlen(sender_uuid) + (int)strlen(message_timestamp) + 2);
        client_private_message_print_messages(sender_uuid,
        (time_t)message_timestamp, message_body);
        do_multiple_frees(sender_uuid, message_timestamp, message_body, NULL);
    }
    printf("\n");
}

/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** send_command
*/


#include "myteams_server.h"

void send_command(teams_server_t *teams_server,
    char __attribute__((unused)) * command)
{
    char **parsed_command = splitter(command, " ");
    user_t *user = NULL;
    message_t *message = NULL;

    if (!parsed_command || !parsed_command[1] || !parsed_command[2])
        return;
    LIST_FOREACH(user, &teams_server->all_user, next) {
        if (strcmp(user->uuid, parsed_command[1]) != 0)
            continue;
        generate_random_uuid(message->message_uuid);
        strcpy(message->text, parsed_command[2]);
        strcpy(message->sender_uuid, teams_server->clients[teams_server->
        actual_sockfd].user->uuid);
        LIST_INSERT_AFTER(teams_server->private_messages, message, next);
        server_event_private_message_sended(
            teams_server->clients[teams_server->
            actual_sockfd].user->uuid, user->uuid, parsed_command[2]);
    }
    dprintf(teams_server->actual_sockfd, "message not found\n");
    dprintf(teams_server->actual_sockfd, SPLITTER_STR);
}

/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** send_command
*/


#include "myteams_server.h"

message_t *create_message(char *sender_uuid, char *receiver_uuid, char *text)
{
    message_t *message = malloc(sizeof(message_t));

    if (!message)
        return NULL;
    strcpy(message->sender_uuid, sender_uuid);
    strcpy(message->receiver_uuid, receiver_uuid);
    strcpy(message->text, text);
    generate_random_uuid(message->message_uuid);
    return message;
}

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
        message = create_message(teams_server->clients[teams_server->
            actual_sockfd].user->uuid, user->uuid, parsed_command[2]);
        LIST_INSERT_AFTER(teams_server->private_messages, message, next);
        server_event_private_message_sended(
            teams_server->clients[teams_server->
            actual_sockfd].user->uuid, user->uuid, parsed_command[2]);
        return;
    }
    dprintf(teams_server->actual_sockfd, "user not found\n");
    dprintf(teams_server->actual_sockfd, SPLITTER_STR);
}

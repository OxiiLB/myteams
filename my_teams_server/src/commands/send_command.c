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
    message->timestamp = get_actual_time();
    generate_random_uuid(message->message_uuid);
    return message;
}

static int loop_user(teams_server_t *teams_server, char **parsed_command)
{
    user_t *user = NULL;
    message_t *message = NULL;

    TAILQ_FOREACH(user, &teams_server->all_user, next) {
        if (strcmp(user->uuid, parsed_command[1]) != 0)
            continue;
        message = create_message(teams_server->clients[teams_server->
            actual_sockfd].user->uuid, user->uuid, parsed_command[2]);
        TAILQ_INSERT_HEAD(&(teams_server->private_messages), message, next);
        server_event_private_message_sended(
            teams_server->clients[teams_server->
            actual_sockfd].user->uuid, user->uuid, parsed_command[2]);
        return KO;
    }
    return OK;
}

char **parse_command(char *command)
{
    char **parsed_command = splitter(command, "\"");

    if (get_len_char_tab(parsed_command) != 3)
        return NULL;
    return parsed_command;
}

void send_command(teams_server_t *teams_server, char *command)
{
    char **parsed_command = parse_command(command);

    if (!parsed_command) {
        dprintf(teams_server->actual_sockfd, "500|Internal Server Error\n");
        dprintf(teams_server->actual_sockfd, END_STR);
        free(parsed_command);
        return;
    }
    if (loop_user(teams_server, parsed_command) == KO) {
        free(parsed_command);
        return;
    }
    dprintf(teams_server->actual_sockfd, "500|user not found\n");
    dprintf(teams_server->actual_sockfd, END_STR);
    free(parsed_command);
}

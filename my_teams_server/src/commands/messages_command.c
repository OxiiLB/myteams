/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** messages_command
*/


#include "myteams_server.h"

user_t *get_user_by_uuid(teams_server_t *teams_server, char *uuid)
{
    user_t *user = NULL;

    TAILQ_FOREACH(user, &teams_server->all_user, next) {
        if (strcmp(user->uuid, uuid) == 0)
            return user;
    }
    return NULL;
}

void print_messages(teams_server_t *teams_server, user_t *user1, user_t *user2)
{
    message_t *message = NULL;

    dprintf(teams_server->actual_sockfd, "200|/messages%s", END_LINE);
    TAILQ_FOREACH(message, &teams_server->private_messages, next) {
        if ((strcmp(message->receiver_uuid, user1->uuid) == 0 ||
            strcmp(message->receiver_uuid, user2->uuid) == 0) &&
            (strcmp(message->sender_uuid, user1->uuid) == 0 ||
            strcmp(message->sender_uuid, user2->uuid) == 0)) {
            dprintf(teams_server->actual_sockfd,
                "200|/messages%s%s%s%s%s%s%s",
                END_LINE, message->sender_uuid, SPLIT_LINE, ctime(&message->timestamp),
                SPLIT_LINE, message->text, END_LINE);
        }
    }
    dprintf(teams_server->actual_sockfd, END_STR);
}

void messages_command(teams_server_t *teams_server,
    char __attribute__((unused)) * command)
{
    user_t *user1 = teams_server->clients[teams_server->actual_sockfd].user;
    user_t *user2 = NULL;

    if (user1 == NULL || strlen(command) == 0) {
        dprintf(teams_server->actual_sockfd, "502|Unauthorized action\n%s",
            END_STR);
        return;
    }
    command = &command[2];
    command[strlen(command) - 1] = '\0';
    user2 = get_user_by_uuid(teams_server, command);
    if (user2 == NULL) {
        dprintf(teams_server->actual_sockfd, "501|User not found\n%s",
            END_STR);
        return;
    }
    print_messages(teams_server, user1, user2);
}

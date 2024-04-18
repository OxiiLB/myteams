/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** messages_command
*/


#include "myteams_server.h"

void messages_command(teams_server_t *teams_server,
    char __attribute__((unused)) * command)
{
    user_t *user1 = teams_server->clients[teams_server->actual_sockfd].user;
    user_t *user2 = NULL;
    message_t *message = NULL;


    if (user1 == NULL) {
        dprintf(teams_server->actual_sockfd, "502|Unauthorized action\n%s",
            END_STR);
        return;
    }
    dprintf(teams_server->actual_sockfd, "200|/messages%s", END_LINE);
    TAILQ_FOREACH(message, &teams_server->private_messages, next)
        if ((strcmp(message->receiver_uuid, user1->uuid) == 0 ||
            strcmp(message->sender_uuid, user1->uuid) == 0) &&
            (strcmp(message->receiver_uuid, user2->uuid) == 0 ||
            strcmp(message->sender_uuid, user2->uuid) == 0)) {
            dprintf(teams_server->actual_sockfd, "1%s", SPLIT_LINE);
    }
}

/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** get_object_by_uuid
*/

#include "../include/myteams_server.h"

void *search_in_messages(thread_t *thread, char **uuid)
{
    message_t *message = NULL;

    TAILQ_FOREACH(message, &thread->messages_head, next) {
        if (strcmp(message->message_uuid, uuid[3]) == 0)
            return message;
    }
    return NULL;
}

void *search_in_threads(channel_t *channel, char **uuid)
{
    thread_t *thread = NULL;

    if (strcmp(channel->channel_uuid, uuid[1]) == 0)
        return channel;
    TAILQ_FOREACH(thread, &channel->threads_head, next) {
        if (strcmp(thread->thread_uuid, uuid[2]) == 0)
            return thread;
    }
    return NULL;
}

void *get_object_by_uuid(struct teamhead teams_head, char *uuid)
{
    team_t *team = NULL;
    channel_t *channel = NULL;

    TAILQ_FOREACH(team, &teams_head, next) {
        if (strcmp(team->team_uuid, uuid) == 0)
            return team;
    }
    return NULL;
}
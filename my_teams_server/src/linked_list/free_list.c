/*
** EPITECH PROJECT, 2023
** free_list
** File description:
** free the list
*/

#include <stdlib.h>
#include "myteams_server.h"

void free_users(struct userhead *head)
{
    user_t *n1 = LIST_FIRST(head);
    user_t *n2 = NULL;

    while (n1 != NULL) {
        n2 = n1;
        n1 = LIST_NEXT(n1, next);
        free(n2);
    }
}

void free_messages(struct messagehead *head)
{
    message_t *n1 = LIST_FIRST(head);
    message_t *n2 = NULL;

    while (n1 != NULL) {
        n2 = n1;
        if (n2->text)
            free(n2->text);
        if (n2->sender_uuid)
            free(n2->sender_uuid);
        if (n2->receiver_uuid)
            free(n2->receiver_uuid);
        if (n2->message_uuid)
            free(n2->message_uuid);
        n1 = LIST_NEXT(n1, next);
        free(n2);
    }
}

void free_threads(struct threadhead *head)
{
    thread_t *n1 = LIST_FIRST(head);
    thread_t *n2 = NULL;

    while (n1 != NULL) {
        n2 = n1;
        if (n2->thread_desc)
            free(n2->thread_desc);
        if (n2->thread_name)
            free(n2->thread_name);
        if (n2->thread_uuid)
            free(n2->thread_uuid);
        if (LIST_EMPTY(&n2->messages_head) == 0)
            free_messages(&n2->messages_head);
        n1 = LIST_NEXT(n1, next);
        free(n2);
    }
}

void free_channels(struct channelhead *head)
{
    channel_t *n1 = LIST_FIRST(head);
    channel_t *n2 = NULL;

    while (n1 != NULL) {
        n2 = n1;
        n1 = LIST_NEXT(n1, next);
        if (n2->channel_desc)
            free(n2->channel_desc);
        if (n2->channel_name)
            free(n2->channel_name);
        if (n2->channel_uuid)
            free(n2->channel_uuid);
        if (LIST_EMPTY(&n2->threads_head) == 0)
            free_threads(&n2->threads_head);
        free(n2);
    }
}

void free_teams(struct teamhead *head)
{
    team_t *n1 = LIST_FIRST(head);
    team_t *n2 = NULL;

    while (n1 != NULL) {
        n2 = n1;
        if (n2->team_desc)
            free(n2->team_desc);
        if (n2->team_name)
            free(n2->team_name);
        if (n2->team_uuid)
            free(n2->team_uuid);
        if (LIST_EMPTY(&n2->channels_head) == 0)
            free_channels(&n2->channels_head);
        n1 = LIST_NEXT(n1, next);
        free(n2);
    }
}


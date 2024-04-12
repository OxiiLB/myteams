/*
** EPITECH PROJECT, 2023
** free_list
** File description:
** free the list
*/

#include <stdlib.h>
#include "myteams_server.h"

void free_messages(struct messagehead *head)
{
    message_t *n1 = LIST_FIRST(head);
    message_t *n2 = NULL;

    while (n1 != NULL) {
        n2 = n1;
        n1 = LIST_NEXT(n1, next);
        free(n2);
    }
}

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

void free_threads(struct threadhead *head)
{
    thread_t *n1 = LIST_FIRST(head);
    thread_t *n2 = NULL;

    while (n1 != NULL) {
        n2 = n1;
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
        free(n2);
    }
}

void free_teams(struct teamhead *head)
{
    team_t *n1 = LIST_FIRST(head);
    team_t *n2 = NULL;

    while (n1 != NULL) {
        n2 = n1;
        n1 = LIST_NEXT(n1, next);
        free(n2);
    }
}

/*
** EPITECH PROJECT, 2023
** free_list
** File description:
** free the list
*/

#include <stdlib.h>
#include "myteams_server.h"

void free_messages(struct messagehead *head) {
    message_t *n1 = LIST_FIRST(head);(head);
    while(n1 != NULL) {
        message_t *n2 = n1;
        n1 = LIST_NEXT(n1, next);
        free(n2);
    }
}

void free_users(struct userhead *head) {
    user_t *n1 = LIST_FIRST(head);
    while(n1 != NULL) {
        user_t *n2 = n1;
        n1 = LIST_NEXT(n1, next);
        free(n2);
    }
}

void free_threads(struct threadhead *head) {
    thread_t *n1 = LIST_FIRST(head);;
    while(n1 != NULL) {
        thread_t *n2 = n1;
        n1 = LIST_NEXT(n1, next);
        free(n2);
    }
}

void free_channels(struct channelhead *head) {
    channel_t *n1 = LIST_FIRST(head);
    while(n1 != NULL) {
        channel_t *n2 = n1;
        n1 = LIST_NEXT(n1, next);
        free(n2);
    }
}

void free_teams(struct teamhead *head) {
    team_t *n1 = LIST_FIRST(head);
    while(n1 != NULL) {
        team_t *n2 = n1;
        n1 = LIST_NEXT(n1, next);
        free(n2);
    }
}

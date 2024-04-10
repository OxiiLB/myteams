/*
** EPITECH PROJECT, 2023
** add_node
** File description:
** add node in a linked list
*/

#include <stdlib.h>
#include "myteams_server.h"

linked_team_t *add_team(linked_team_t *head, team_t *data)
{
    linked_team_t *new_node = malloc(sizeof(linked_team_t));
    linked_team_t *temp = head;

    new_node->team = data;
    new_node->next = NULL;
    if (head == NULL)
        return new_node;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
    return head;
}

linked_channel_t *add_channel(linked_channel_t *head, channel_t *data)
{
    linked_channel_t *new_node = malloc(sizeof(linked_channel_t));
    linked_channel_t *temp = head;

    new_node->channel = data;
    new_node->next = NULL;
    if (head == NULL)
        return new_node;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
    return head;
}

linked_message_t *add_message(linked_message_t *head, message_t *data)
{
    linked_message_t *new_node = malloc(sizeof(linked_message_t));
    linked_message_t *temp = head;

    new_node->message = data;
    new_node->next = NULL;
    if (head == NULL)
        return new_node;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
    return head;
}

linked_thread_t *add_thread(linked_thread_t *head, thread_t *data)
{
    linked_thread_t *new_node = malloc(sizeof(linked_thread_t));
    linked_thread_t *temp = head;

    new_node->thread = data;
    new_node->next = NULL;
    if (head == NULL)
        return new_node;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
    return head;
}

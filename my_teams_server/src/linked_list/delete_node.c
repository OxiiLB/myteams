/*
** EPITECH PROJECT, 2023
** delete_node
** File description:
** delete the node given as parameter
*/

#include <stdlib.h>
#include "linked_list.h"

void delete_node(linked_list_t **head, linked_list_t *node_to_delete)
{
    linked_list_t *current = *head;

    if (node_to_delete == *head)
        *head = node_to_delete->next;
    else {
        while (current->next != NULL && current->next != node_to_delete) {
            current = current->next;
        }
        if (current->next != NULL)
            current->next = node_to_delete->next;
    }
    if (node_to_delete->next != NULL)
        node_to_delete->next->prev = node_to_delete->prev;
    if (node_to_delete->prev != NULL)
        node_to_delete->prev->next = node_to_delete->next;
    free(node_to_delete);
}

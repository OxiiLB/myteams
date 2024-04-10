/*
** EPITECH PROJECT, 2023
** free_list
** File description:
** free the list
*/

#include <stdlib.h>
#include "linked_list.h"

void free_list(linked_list_t *head)
{
    linked_list_t *current = head;
    while (current != NULL) {
        linked_list_t *next = current->next;
        free(current);
        current = next;
    }
}

/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** get_arg_len
*/

#include "myteams_cli.h"

int get_arg_len(const char *input, int i)
{
    int len = 1;
    int quotes = 0;

    for (i = i; input[i] != '\0'; i++) {
        if (input[i] == '"')
            quotes++;
        if (quotes == 2) {
            break;
        }
        len++;
    }
    return len;
}

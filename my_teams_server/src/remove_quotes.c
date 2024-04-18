/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** remove_quotes
*/

#include "myteams_server.h"

char *remove_quotes(char *str)
{
    char *new_str = malloc(sizeof(char) * strlen(str));
    int i = 0;
    int j = 0;

    while (str[i] != '\0') {
        if (str[i] != '\"') {
            new_str[j] = str[i];
            j++;
        }
        i++;
    }
    new_str[j] = '\0';
    return new_str;
}

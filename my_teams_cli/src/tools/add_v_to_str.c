/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** tools
*/

#include "myteams_cli.h"

char *add_v_to_str(const char *input)
{
    char *modified = malloc(strlen(input) + 2);

    modified = strcpy(modified, input);
    modified = strcat(modified, END_STR);
    return modified;
}

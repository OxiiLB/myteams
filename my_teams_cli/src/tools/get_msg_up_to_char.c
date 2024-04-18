/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** tools
*/

#include "myteams_cli.h"

char *get_msg_up_to_char(char *str, char c, int i)
{
    int j = 0;
    char modified[(int)strlen(str)];

    for (i = i; str[i] != c; i++) {
        modified[j] = str[i];
        j++;
    }
    modified[j] = '\0';
    return strdup(modified);
}

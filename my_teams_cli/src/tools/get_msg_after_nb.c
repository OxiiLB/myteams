/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** tools
*/

#include "myteams_cli.h"

char *get_msg_after_nb(char const *const str, int nb)
{
    int len_str = strlen(str);
    char modified[len_str - (nb)];

    strcpy(modified, &str[nb]);
    modified[len_str - (nb)] = '\0';
    return strdup(modified);
}

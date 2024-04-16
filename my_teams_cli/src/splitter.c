/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** splitter
*/

#include <string.h>
#include <stdlib.h>

char **splitter(char const *const str, char *separator)
{
    int i = 0;
    char **tab = NULL;
    char *cpy_str = malloc(sizeof(char) * (strlen(str) + 1));
    char *tmp_str;

    strcpy(cpy_str, str);
    tmp_str = strtok(cpy_str, separator);
    if (tmp_str == NULL)
        return NULL;
    tab = malloc(sizeof(char *) * (strlen(str) + 1));
    if (tab == NULL)
        return NULL;
    while (tmp_str != NULL) {
        tab[i] = strdup(tmp_str);
        tmp_str = strtok(NULL, separator);
        i += 1;
    }
    tab[i] = NULL;
    free(cpy_str);
    return tab;
}

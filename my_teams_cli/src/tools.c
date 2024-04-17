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
    modified = strcat(modified, "\v");
    return modified;
}

char *get_msg_after_nb(char *str, int nb)
{
    int len = strlen(str);

    for (int i = 0; i < len - 1; i++) {
        str[i] = str[i + nb];
    }
    str[len - 1] = '\0';
    return str;
}

void do_multiple_frees(char *one, char *two, char *three, char *four)
{
    if (one != NULL)
        free(one);
    if (two != NULL)
        free(two);
    if (three != NULL)
        free(three);
    if (four != NULL)
        free(four);
}

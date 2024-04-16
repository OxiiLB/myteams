/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** tools
*/

#include "myteams_cli.h"

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

/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** tools
*/

#include "myteams_cli.h"

void print_2d_array(char **array, int i)
{
    for (i = i; array[i] != NULL; i++) {
        printf("%s\n", array[i]);
    }
}

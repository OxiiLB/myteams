/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** tools
*/

#include "myteams_cli.h"

char *get_msg_after_nb(char *str, int nb)
{
    int i = 0;
    char modified[(int)strlen(str) - (nb + 1)];
    
    for (nb = nb; nb < (int)strlen(str); nb++) {
        modified[i] = str[nb];
        i++;
    }
    modified[i] = '\0';
    return strdup(modified);
}

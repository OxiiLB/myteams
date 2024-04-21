/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** check_nb_args
*/


#include "myteams_cli.h"

static int quotes_if(const char *input, int i)
{
    if (input[i] == '"')
        return 1;
    return 0;
}

static int check_nb_args_3(const char *input, int should_have)
{
    int i = 0;
    int quotes = 0;

    if (should_have == 3) {
        for (i = 0; input[i] != ' ' && input[i] != '\0'; i++);
        if (input[i] == '\0')
            return KO;
        for (i = i; input[i] != '\0'; i++)
            quotes += quotes_if(input, i);
        if (quotes != 6)
            return KO;
    }
    return OK;
}

static int check_nb_args_2(const char *input, int should_have)
{
    int i = 0;
    int quotes = 0;

    if (should_have == 2) {
        for (i = 0; input[i] != ' ' && input[i] != '\0'; i++);
        if (input[i] == '\0')
            return KO;
        for (i = i; input[i] != '\0'; i++)
            quotes += quotes_if(input, i);
        if (quotes != 4)
            return KO;
    }
    return check_nb_args_3(input, should_have);
}

int check_nb_args(const char *input, int should_have)
{
    int i = 0;
    int quotes = 0;

    if (should_have == 0) {
        for (i = 0; input[i] != ' ' && input[i] != '\0'; i++);
        if (input[i] != '\0')
            return KO;
    }
    if (should_have == 1) {
        for (i = 0; input[i] != ' ' && input[i] != '\0'; i++);
        if (input[i] == '\0')
            return KO;
        for (i = i; input[i] != '\0'; i += 1)
            quotes += quotes_if(input, i);
        if (quotes != 2)
            return KO;
    }
    return check_nb_args_2(input, should_have);
}

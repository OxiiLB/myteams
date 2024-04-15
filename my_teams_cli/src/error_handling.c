/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** error_handling
*/

#include "myteams_cli.h"

static int quotes_if(const char *input, int i)
{
    if (input[i] == '"')
        return 1;
    return 0;
}

int check_nb_args(const char *input, int should_have)
{
    int i = 0;
    int quotes = 0;
    int res = OK;

    if (should_have == 0) {
        for (i = 0; input[i] != ' ' && input[i] != '\0'; i++);
        if (input[i] != '\0') {
            write(1, "Error: command should not have arguments\n", 42);
            return KO;
        }
    }
    if (should_have == 1) {
        for (i = 0; input[i] != ' ' && input[i] != '\0'; i++);
        if (input[i] == '\0')
            res = KO;
        for (i = i; input[i] != '\0'; i++)
            quotes += quotes_if(input, i);
        if (quotes != 2)
            res = KO;
        if (res == KO)
            write(1, "Error: command should have 1 argument\n", 39);
    }
    if (should_have == 2) {
        for (i = 0; input[i] != ' ' && input[i] != '\0'; i++);
        if (input[i] == '\0')
            res = KO;
        for (i = i; input[i] != '\0'; i++)
            quotes += quotes_if(input, i);
        if (quotes != 4)
            res = KO;
        if (res == KO)
            write(1, "Error: command should have 2 arguments\n", 40);
    }
    return res;
}

int check_quotes(const char *input, int input_len, int cmd_len)
{
    if (input[cmd_len + 1] != '"' || input[input_len - 2] != '"') {
        //printf("first check: %c\n", input[cmd_len + 1]); //////////////////////////////////////
        //printf("second check: %c\n", input[input_len - 2]); //////////////////////////////////////
        write(1, "Error: invalid argument, missing quotes\n", 40);
        return KO;
    }
}

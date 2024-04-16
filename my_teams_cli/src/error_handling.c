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

static int get_error(int should_have)
{
    if (should_have == 0) {
        write(1, "Error: command should not have arguments\n", 42);
        return KO;
    }
    if (should_have == 1) {
        write(1, "Error: command should have 1 argument\n", 39);
        return KO;
    }
    if (should_have == 2) {
        write(1, "Error: command should have 2 arguments\n", 40);
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
            return get_error(should_have);
        for (i = i; input[i] != '\0'; i++)
            quotes += quotes_if(input, i);
        if (quotes != 4)
            return get_error(should_have);
    }
    return OK;
}

int check_nb_args(const char *input, int should_have)
{
    int i = 0;
    int quotes = 0;

    if (should_have == 0) {
        for (i = 0; input[i] != ' ' && input[i] != '\0'; i++);
        if (input[i] != '\0')
            return get_error(should_have);
    }
    if (should_have == 1) {
        for (i = 0; input[i] != ' ' && input[i] != '\0'; i++);
        if (input[i] == '\0')
            return get_error(should_have);
        for (i = i; input[i] != '\0'; i++)
            quotes += quotes_if(input, i);
        if (quotes != 2)
            return get_error(should_have);
    }
    return check_nb_args_2(input, should_have);
}

int check_quotes(const char *input, int input_len, int cmd_len)
{
    if (input[cmd_len + 1] != '"' || input[input_len - 2] != '"') {
        write(1, "Error: invalid argument, missing quotes\n", 40);
        return KO;
    }
    return OK;
}

int do_error_handling(const char *input, int a_nb, int q_len, int q_nb)
{
    if (check_nb_args(input, a_nb) == KO)
        return KO;
    if (check_quotes(input, q_len, q_nb) == KO)
        return KO;
    return OK;
}

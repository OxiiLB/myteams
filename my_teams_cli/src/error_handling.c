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

static int check_nb_args(const char *input, int should_have)
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

static int check_quotes(const char *input, int input_len, int cmd_len)
{
    if (input[cmd_len + 1] != '"' || input[input_len - 2] != '"') {
        write(1, "Error: invalid argument, missing quotes\n", 40);
        return KO;
    }
    return OK;
}

static int get_arg_len(const char *input, int i)
{
    int len = 0;
    int quotes = 0;

    for (i = i; input[i] != '\0'; i++) {
        if (input[i] == '"')
            quotes++;
        if (quotes == 2) {
            i++;
            break;
        }
    }
    for (i = i; input[i] != '\0'; i++) {
        len++;
    }
    return len;
}

int do_error_handling(const char *input)
{
    if (strncmp(input, "/help", 5) == 0 && check_nb_args(input, 0) == KO)
        return KO;
    if (strncmp(input, "/login", 6) == 0 && check_nb_args(input, 1) == OK) {
        if (check_quotes(input, strlen(input), 6) == KO)
            return KO;
    }
    if (strncmp(input, "/logout", 7) == 0 && check_nb_args(input, 0) == KO)
        return KO;
    if (strncmp(input, "/user", 5) == 0 && check_nb_args(input, 1) == OK) {
        if (check_quotes(input, strlen(input), 5) == KO)
            return KO;
    }
    if (strncmp(input, "/users", 6) == 0 && check_nb_args(input, 0) == KO)
        return KO;
    if (strncmp(input, "/send", 5) == 0 && check_nb_args(input, 2) == OK) {
        if (check_quotes(input, strlen(input), 5) == KO ||
        check_quotes(input, strlen(input), (6 + get_arg_len(input, 5))) == KO)
            return KO;
    }
    if (strncmp(input, "/messages", 9) == 0 && check_nb_args(input, 1) == OK) {
        if (check_quotes(input, strlen(input), 9) == KO)
            return KO;
    }
    if (strncmp(input, "/subscribed", 11) == 0 && check_nb_args(input, 0) == KO) {
        if (check_nb_args(input, 1) == OK) {
            if (check_quotes(input, strlen(input), 11) == OK)
                return OK;
        }
        return KO;
    }
    if (strncmp(input, "/subscribe", 10) == 0 && check_nb_args(input, 1) == OK) {
        if (check_quotes(input, strlen(input), 10) == KO)
            return KO;
    }
    if (strncmp(input, "/unsubscribe", 12) == 0 && check_nb_args(input, 1) == OK) {
        if (check_quotes(input, strlen(input), 12) == KO)
            return KO;
    }
    
    // finish checking other commands

    return OK;
}
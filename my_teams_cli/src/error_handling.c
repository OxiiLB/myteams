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

static int check_nb_args(const char *input, int should_have)
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

static int check_quotes(const char *input, int start, int end)
{
    if (input[start] != '"' || input[end] != '"') {
        write(1, "Error: invalid argument, missing quotes\n", 40);
        return KO;
    }
    return OK;
}

static int do_error_handling_5(const char *input)
{
    int first_arg = 0;

    if (strncmp(input, "/messages", 9) == 0) {
        if (check_nb_args(input, 1) == KO) {
            printf("Error: incorrect no. of arguments.\n");
            return KO;
        }
        if (check_quotes(input, 10, (int)strlen(input) - 2) == KO)
            return KO;
    }
    if (strncmp(input, "/unsubscribe", 12) == 0 &&
    check_nb_args(input, 1) == OK) {
        if (check_quotes(input, 13, strlen(input) - 2) == KO)
            return KO;
    }
    if (strncmp(input, "/create", 7) == 0) {
        if (check_nb_args(input, 2) == KO) {
            printf("Error: incorrect no. of arguments.\n");
            return KO;
        }
        first_arg = get_arg_len(input, 8);
        if (check_quotes(input, 8, 7 + first_arg) == KO ||
        check_quotes(input, 9 + first_arg, (int)strlen(input) - 2) == KO)
            return KO;
    }
    if (strncmp(input, "/list", 5) == 0) {
        if (check_nb_args(input, 0) == KO) {
            printf("Error: incorrect no. of arguments.\n");
            return KO;
        }
    }
    if (strncmp(input, "/info", 5) == 0) {
        if (check_nb_args(input, 0) == KO) {
            printf("Error: incorrect no. of arguments.\n");
            return KO;
        }
    }
    return OK;
}

static int do_error_handling_4(const char *input)
{
    if (strncmp(input, "/subscribed", 11) == 0) {
        if (check_nb_args(input, 0) == OK)
            return OK;
        if (check_nb_args(input, 1) == OK &&
        check_quotes(input, 12, (int)strlen(input) - 2) == KO)
            return KO;
    }
    if (strncmp(input, "/subscribe", 10) == 0) {
        if (check_nb_args(input, 1) == KO) {
            printf("Error: incorrect no. of arguments.\n");
            return KO;
        }
        if (check_quotes(input, 11, strlen(input) - 2) == KO)
            return KO;
    }
    return OK;
}

static int do_error_handling_3(const char *input)
{
    int first_arg = 0;

    if (strncmp(input, "/use", 4) == 0) {
        if (check_nb_args(input, 0) == KO && check_nb_args(input, 1) == KO &&
        check_nb_args(input, 2) == KO && check_nb_args(input, 3) == KO) {
            printf("Error: incorrect no. of arguments.\n");
            return KO;
        }
    }
    if (strncmp(input, "/send", 5) == 0) {
        if (check_nb_args(input, 2) == KO) {
            printf("Error: incorrect no. of arguments.\n");
            return KO;
        }
        first_arg = get_arg_len(input, 6);
        if (check_quotes(input, 6, 5 + first_arg) == KO ||
        check_quotes(input, 7 + first_arg, (int)strlen(input) - 2) == KO)
            return KO;
    }
    return OK;
}

static int do_error_handling_2(const char *input)
{
    if (strncmp(input, "/users", 6) == 0) {
        if (check_nb_args(input, 0) == KO) {
            printf("Error: incorrect no. of arguments.\n");
            return KO;
        } else
            return OK;
    }
    if (strncmp(input, "/user", 5) == 0) {
        if (check_nb_args(input, 1) == KO) {
            printf("Error: incorrect no. of arguments.\n");
            return KO;
        }
        if (check_quotes(input, 6, (int)strlen(input) - 2) == KO)
            return KO;
        return OK;
    }
    return OK;
}

int do_error_handling(const char *input)
{
    if (strncmp(input, "/help", 5) == 0 && check_nb_args(input, 0) == KO)
        return KO;
    if (strncmp(input, "/login", 6) == 0) {
        if (check_nb_args(input, 1) == KO) {
            printf("Error: incorrect no. of arguments.\n");
            return KO;
        }
        if (check_quotes(input, 7, (int)strlen(input) - 2) == KO)
            return KO;
        return OK;
    }
    if (strncmp(input, "/logout", 7) == 0 && check_nb_args(input, 0) == KO)
        return KO;
    if (do_error_handling_2(input) == KO || do_error_handling_3(input) == KO ||
    do_error_handling_4(input) == KO)
        return KO;
    return do_error_handling_5(input);
}

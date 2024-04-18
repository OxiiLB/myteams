/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_cmds
*/

#include "myteams_cli.h"

void handle_help(char **info)
{
    print_2d_array(info, 1);
}

void handle_login(char **info)
{
    client_event_logged_in(info[1], info[2]);
}

void handle_logout(char **info)
{
    printf("info[1]: %s\n", info[1]); ///////////////////////////////////////
    printf("info[2]: %s\n", info[2]); ///////////////////////////////////////
    client_event_logged_out(info[1], info[2]);
}

void handle_users(char **info)
{
    int user_status = 0;

    user_status = atoi(info[1]);
    printf("%s", info[4]);
    client_print_users(info[3], info[2], user_status);
}

void handle_user(char **info)
{
    int user_status = 0;

    user_status = atoi(info[1]);
    printf("%s", info[4]);
    client_print_user(info[2], info[3], user_status);
}

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
    printf("\n");
}

void handle_login(char **info)
{
    client_event_logged_in(info[1], info[2]);
    printf("\n");
}

void handle_logout(char **info)
{
    char *user_name = get_msg_up_to_char(info[1], '\a', 0);
    char *user_uuid = get_msg_after_nb(info[1], (int)strlen(user_name));

    client_event_logged_out(user_uuid, user_name);
    do_multiple_frees(user_uuid, user_name, NULL, NULL);
    free_2d_array(info);
    exit(0);
}

void handle_users(char **info)
{
    int i = 0;
    int user_status = 0;
    char *user_name = NULL;
    char *user_uuid = NULL;

    for (i = 1; info[i] != NULL; i++) {
        user_status = info[i][0] - '0';
        user_uuid = get_msg_up_to_char(info[i], '\a', 2);
        user_name = get_msg_after_nb(info[i], (int)strlen(user_uuid) + 2);
        client_print_users(user_uuid, user_name, user_status);
        do_multiple_frees(user_uuid, user_name, NULL, NULL);
    }
    printf("\n");
}

void handle_user(char **info)
{
    int user_status = info[1][0] - '0';
    char *user_uuid = get_msg_up_to_char(info[1], '\a', 2);
    char *user_name = get_msg_after_nb(info[1], (int)strlen(user_uuid) + 2);
    client_print_user(user_uuid, user_name, user_status);
}

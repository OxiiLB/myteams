/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_list_cmds
*/

#include "myteams_cli.h"

void list_users(char **info)
{
    int user_status = atoi(info[2]);
    char *user_uuid = get_msg_up_to_char(info[2], *SPLIT_LINE, 2);
    char *user_name = get_msg_after_nb(info[2], (int)strlen(user_uuid) + 3);

    client_print_user(user_uuid, user_name, user_status);
}

/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_list_cmds
*/

#include "myteams_cli.h"

// printf("\n"); //////////////////////////////////////////////
// print_2d_array(info, 0); //////////////////////////////////////////////
// printf("\n"); //////////////////////////////////////////////
void list_teams(char **info)
{
    char *team_uuid = NULL;
    char *team_name = NULL;
    char *team_desc = NULL;

    for (int i = 2; info[i] != NULL; i++) {
        team_uuid = get_msg_up_to_char(info[2], *SPLIT_LINE, 0);
        team_name = get_msg_up_to_char(info[2], *SPLIT_LINE,
        (int)strlen(team_uuid) + 1);
        team_desc = get_msg_after_nb(info[2], (int)strlen(team_uuid)
        + (int)strlen(team_name) + 2);
        client_print_teams(team_uuid, team_name, team_desc);
        do_multiple_frees(team_uuid, team_name, team_desc, NULL);
    }
}

void list_channels(char **info)
{
    char *channel_uuid = NULL;
    char *channel_name = NULL;
    char *channel_desc = NULL;

    for (int i = 2; info[i] != NULL; i++) {
        channel_uuid = get_msg_up_to_char(info[2], *SPLIT_LINE, 0);
        channel_name = get_msg_up_to_char(info[2], *SPLIT_LINE,
        (int)strlen(channel_uuid) + 1);
        channel_desc = get_msg_after_nb(info[2], (int)strlen(channel_uuid)
        + (int)strlen(channel_name) + 2);
        client_team_print_channels(channel_uuid, channel_name, channel_desc);
        do_multiple_frees(channel_uuid, channel_name, channel_desc, NULL);
    }
}

void list_threads(char **info)
{
    int add = 0;
    char *thread_uuid = NULL;
    char *user_uuid = NULL;
    char *thread_timestamp = NULL;
    char *thread_title = NULL;
    char *thread_body = NULL;

    for (int i = 2; info[i] != NULL; i++) {
        add = 0;
        thread_uuid = get_msg_up_to_char(info[2], *SPLIT_LINE, 0);
        add = (int)strlen(thread_uuid) + 1;
        user_uuid = get_msg_up_to_char(info[2], *SPLIT_LINE, add);
        add += (int)strlen(user_uuid) + 1;
        thread_timestamp = get_msg_up_to_char(info[2], *SPLIT_LINE, add);
        add += (int)strlen(thread_timestamp) + 1;
        thread_title = get_msg_up_to_char(info[2], *SPLIT_LINE, add);
        add += (int)strlen(thread_title) + 1;
        thread_body = get_msg_after_nb(info[2], add);
        client_channel_print_threads(thread_uuid, user_uuid,
        (time_t)thread_timestamp, thread_title, thread_body);
        do_multiple_frees(thread_uuid, user_uuid, thread_timestamp,
        thread_title);
        free(thread_body);
    }
}

void list_replies(char **info)
{
    char *thread_uuid = NULL;
    char *user_uuid = NULL;
    char *reply_timestamp = NULL;
    char *reply_body = NULL;

    for (int i = 2; info[i] != NULL; i++) {
        thread_uuid = get_msg_up_to_char(info[2], *SPLIT_LINE, 0);
        user_uuid = get_msg_up_to_char(info[2], *SPLIT_LINE,
        (int)strlen(thread_uuid) + 1);
        reply_timestamp = get_msg_up_to_char(info[2], *SPLIT_LINE,
        (int)strlen(thread_uuid) + (int)strlen(user_uuid) + 2);
        reply_body = get_msg_after_nb(info[2], (int)strlen(thread_uuid) +
        (int)strlen(user_uuid) + (int)strlen(reply_timestamp) + 3);
        client_thread_print_replies(thread_uuid, user_uuid,
        (time_t)reply_timestamp, reply_body);
        do_multiple_frees(thread_uuid, user_uuid,
        reply_timestamp, reply_body);
    }
}

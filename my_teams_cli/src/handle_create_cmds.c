/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_create_cmds
*/

#include "myteams_cli.h"

// every logged user must receive this event ??????
void create_team(char **info)
{
    char *team_uuid = get_msg_up_to_char(info[2], *SPLIT_LINE, 0);
    char *team_name = get_msg_up_to_char(info[2], *SPLIT_LINE,
    (int)strlen(team_uuid) + 1);
    char *team_desc = get_msg_after_nb(info[2],
    (int)strlen(team_uuid) + (int)strlen(team_name) + 2);

    client_event_team_created(team_uuid, team_name, team_desc);
    client_print_team_created(team_uuid, team_name, team_desc);
    do_multiple_frees(team_uuid, team_name, team_desc, NULL);
}

void create_channel(char **info)
{
    char *channel_uuid = get_msg_up_to_char(info[2], *SPLIT_LINE, 0);
    char *channel_name = get_msg_up_to_char(info[2], *SPLIT_LINE,
    (int)strlen(channel_uuid) + 1);
    char *channel_desc = get_msg_after_nb(info[2],
    (int)strlen(channel_uuid) + (int)strlen(channel_name) + 2);

    client_event_channel_created(channel_uuid, channel_name, channel_desc);
    client_print_channel_created(channel_uuid, channel_name, channel_desc);
    do_multiple_frees(channel_uuid, channel_name, channel_desc, NULL);
}

void create_thread(char **info)
{
    char *user_uuid = NULL;
    char *thread_timestamp = NULL;
    char *thread_title = NULL;
    char *thread_body = NULL;
    char *thread_uuid = get_msg_up_to_char(info[2], *SPLIT_LINE, 0);
    int add = (int)strlen(thread_uuid) + 1;

    user_uuid = get_msg_up_to_char(info[2], *SPLIT_LINE, add);
    add += (int)strlen(user_uuid) + 1;
    thread_timestamp = get_msg_up_to_char(info[2], *SPLIT_LINE, add);
    add += (int)strlen(thread_timestamp) + 1;
    thread_title = get_msg_up_to_char(info[2], *SPLIT_LINE, add);
    add += (int)strlen(thread_title) + 1;
    thread_body = get_msg_after_nb(info[2], add);
    client_event_thread_created(thread_uuid, user_uuid,
    (time_t)thread_timestamp, thread_title, thread_body);
    client_print_thread_created(thread_uuid, user_uuid,
    (time_t)thread_timestamp, thread_title, thread_body);
    do_multiple_frees(thread_uuid, user_uuid, thread_timestamp, thread_title);
    free(thread_body);
}

// print_2d_array(info, 2); //////////////////////////////////////
// printf("\n"); /////////////////////////////////////////////////
void create_reply(char **info)
{
    char *thread_uuid = NULL;
    char *user_uuid = NULL;
    char *reply_timestamp = NULL;
    char *reply_body = NULL;
    char *team_uuid = get_msg_up_to_char(info[2], *SPLIT_LINE, 0);
    int add = (int)strlen(team_uuid) + 1;

    thread_uuid = get_msg_up_to_char(info[2], *SPLIT_LINE, add);
    add += (int)strlen(thread_uuid) + 1;
    user_uuid = get_msg_up_to_char(info[2], *SPLIT_LINE, add);
    add += (int)strlen(user_uuid) + 1;
    reply_timestamp = get_msg_up_to_char(info[2], *SPLIT_LINE, add);
    add += (int)strlen(reply_timestamp) + 1;
    reply_body = get_msg_after_nb(info[2], add);
    client_event_thread_reply_received(team_uuid, thread_uuid, user_uuid,
    reply_body);
    client_print_reply_created(thread_uuid, user_uuid,
    (time_t)reply_timestamp, reply_body);
    do_multiple_frees(team_uuid, thread_uuid, user_uuid, reply_timestamp);
    free(reply_body);
}

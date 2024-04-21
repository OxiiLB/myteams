/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_cmds_2
*/

#include "myteams_cli.h"

void handle_send(char **info, int __attribute__((unused)) socketfd)
{
    char *user_uuid = get_msg_up_to_char(info[1], *SPLIT_LINE, 0);
    char *user_name = get_msg_after_nb(info[1], (int)strlen(user_uuid));

    client_event_private_message_received(user_uuid, user_name);
    do_multiple_frees(user_uuid, user_name, NULL, NULL);
}

void handle_messages(char **info, int __attribute__((unused)) socketfd)
{
    char *sender_uuid = NULL;
    char *message_timestamp = NULL;
    char *message_body = NULL;

    for (int i = 1; info[i] != NULL; i++) {
        sender_uuid = get_msg_up_to_char(info[i], *SPLIT_LINE, 0);
        message_timestamp = get_msg_up_to_char(info[i], *SPLIT_LINE,
        (int)strlen(sender_uuid) + 1);
        message_body = get_msg_after_nb(info[i],
        (int)strlen(sender_uuid) + (int)strlen(message_timestamp) + 2);
        client_private_message_print_messages(sender_uuid,
        (time_t)message_timestamp, message_body);
        do_multiple_frees(sender_uuid, message_timestamp, message_body, NULL);
    }
}

void handle_subscribe(char **info, int __attribute__((unused)) socketfd)
{
    char *user_uuid = get_msg_up_to_char(info[1], *SPLIT_LINE, 0);
    char *team_uuid = get_msg_after_nb(info[1], (int)strlen(user_uuid) + 1);

    client_print_subscribed(user_uuid, team_uuid);
    do_multiple_frees(user_uuid, team_uuid, NULL, NULL);
}

static void subscribed_teams(char **info)
{
    char *team_uuid = NULL;
    char *team_name = NULL;
    char *team_desc = NULL;

    for (int i = 2; info[i] != NULL; i++) {
        team_uuid = get_msg_up_to_char(info[i], *SPLIT_LINE, 0);
        team_name = get_msg_up_to_char(info[i], *SPLIT_LINE,
        (int)strlen(team_uuid) + 1);
        team_desc = get_msg_after_nb(info[i],
        (int)strlen(team_uuid) + (int)strlen(team_name) + 2);
        client_print_teams(team_uuid, team_name, team_desc);
        do_multiple_frees(team_uuid, team_name, team_desc, NULL);
    }
}

static void subscribed_users(char **info)
{
    int user_status = 0;
    char *user_uuid = NULL;
    char *user_name = NULL;

    for (int i = 2; info[i] != NULL; i++) {
        user_status = atoi(get_msg_up_to_char(info[i], *SPLIT_LINE, 0));
        user_uuid = get_msg_up_to_char(info[i], *SPLIT_LINE, 2);
        user_name = get_msg_after_nb(info[i], (int)strlen(user_uuid) + 3);
        client_print_users(user_uuid, user_name, user_status);
        do_multiple_frees(user_uuid, user_name, NULL, NULL);
    }
}

void handle_subscribed(char **info, int __attribute__((unused)) socketfd)
{
    if (strncmp(info[1], "teams", 5) == 0)
        subscribed_teams(info);
    else
        subscribed_users(info);
}

void handle_unsubscribe(char **info, int __attribute__((unused)) socketfd)
{
    char *user_uuid = get_msg_up_to_char(info[1], *SPLIT_LINE, 0);
    char *team_uuid = get_msg_after_nb(info[1], (int)strlen(user_uuid) + 1);

    client_print_unsubscribed(user_uuid, team_uuid);
    do_multiple_frees(user_uuid, team_uuid, NULL, NULL);
}

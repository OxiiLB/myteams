/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** list_command
*/
#include "myteams_server.h"

void list_message(my_teams_server_struct_t *my_teams_server_struct,
    char __attribute__((unused)) *command)
{
    message_t *message = NULL;

    LIST_FOREACH(message, &my_teams_server_struct->clients[my_teams_server_struct->actual_sockfd].user.messages_head, next)
        write(my_teams_server_struct->actual_sockfd, message_name, strlen(message_name));
}

void list_thread(my_teams_server_struct_t *my_teams_server_struct,
    char __attribute__((unused)) *command)
{
    thread_t *thread = NULL;

    LIST_FOREACH(thread, &my_teams_server_struct->clients[my_teams_server_struct->actual_sockfd].user.threads_head, next)
        write(my_teams_server_struct->actual_sockfd, thread_name, strlen(thread_name));
}

void list_channel(my_teams_server_struct_t *my_teams_server_struct,
    char __attribute__((unused)) *command)
{
    channel_t *channel = NULL;

    LIST_FOREACH(channel, &my_teams_server_struct->clients[my_teams_server_struct->actual_sockfd].user.channels_head, next)
        write(my_teams_server_struct->actual_sockfd, channel_name, strlen(channel_name));
}

void list_team(my_teams_server_struct_t *my_teams_server_struct,
    char __attribute__((unused)) *command)
{
    team_t *team = NULL;

    LIST_FOREACH(team, &my_teams_server_struct->clients[my_teams_server_struct->actual_sockfd].user.teams_head, next)
        write(my_teams_server_struct->actual_sockfd, team_name, strlen(team_name));
}

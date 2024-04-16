/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** create_command
*/

#include "myteams_server.h"

void create_message(my_teams_server_struct_t *my_teams_server_struct,
    char __attribute__((unused)) *command)
{
    char **command_line = my_strtok(my_teams_server_struct->clients[my_teams_server_struct->actual_sockfd].buffer);
    char *message_text = command_line[1];
    char *receiver_uuid = command_line[2];
    char *message_uuid = generate_uuid();

    message_t *message = malloc(sizeof(message_t));
    message->text = strdup(message_text);
    message->sender_uuid = strdup(my_teams_server_struct->clients[my_teams_server_struct->actual_sockfd].user->uuid);
    message->receiver_uuid = strdup(receiver_uuid);
    message->message_uuid = strdup(message_uuid);

    // LIST_INSERT_HEAD(&my_teams_server_struct->clients[my_teams_server_struct->actual_sockfd].user.messages_head, message, next);
    server_event_private_message_sended(message_uuid, message_text, my_teams_server_struct->clients[my_teams_server_struct->actual_sockfd].user->uuid, receiver_uuid);
}

void create_thread(my_teams_server_struct_t *my_teams_server_struct,
    char __attribute__((unused)) *command)
{
    char **command_line = my_strtok(my_teams_server_struct->clients[my_teams_server_struct->actual_sockfd].buffer);
    char *thread_name = command_line[1];
    char *thread_desc = command_line[2];
    char *thread_uuid = generate_uuid();

    thread_t *thread = malloc(sizeof(thread_t));
    thread->thread_name = strdup(thread_name);
    thread->thread_desc = strdup(thread_desc);
    thread->thread_uuid = strdup(thread_uuid);

    // LIST_INSERT_HEAD(&my_teams_server_struct->clients[my_teams_server_struct->actual_sockfd].user.threads_head, thread, next);
    server_event_thread_created(thread_uuid, thread_name, thread_desc);
}

void create_channel(my_teams_server_struct_t *my_teams_server_struct,
    char __attribute__((unused)) *command)
{
    char **command_line = my_strtok(my_teams_server_struct->clients[my_teams_server_struct->actual_sockfd].buffer);
    char *channel_name = command_line[1];
    char *channel_desc = command_line[2];
    char *channel_uuid = generate_uuid();

    channel_t *channel = malloc(sizeof(channel_t));
    channel->channel_name = strdup(channel_name);
    channel->channel_desc = strdup(channel_desc);
    channel->channel_uuid = strdup(channel_uuid);

    // LIST_INSERT_HEAD(&my_teams_server_struct->clients[my_teams_server_struct->actual_sockfd].user.channels_head, channel, next);
    server_event_channel_created(channel_uuid, channel_name, channel_desc);
}

void create_team(my_teams_server_struct_t *my_teams_server_struct,
    char __attribute__((unused)) *command)
{
    char **command_line = my_strtok(my_teams_server_struct->clients[my_teams_server_struct->actual_sockfd].buffer);
    char *team_name = command_line[1];
    char *team_desc = command_line[2];
    char *team_uuid = generate_uuid();

    team_t *team = malloc(sizeof(team_t));
    team->team_name = strdup(team_name);
    team->team_desc = strdup(team_desc);
    team->team_uuid = strdup(team_uuid);

    // LIST_INSERT_HEAD(&my_teams_server_struct->clients[my_teams_server_struct->actual_sockfd].user.teams_head, team, next);
    server_event_team_created(team_uuid, team_name, team_desc);
}
/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** create_command
*/

#include "myteams_server.h"

static int write_new_channel(int client_fd, channel_t *new_channel)
{
    dprintf(client_fd, "200|/create%s%s%s%s%s%s%s%s", END_LINE,
        new_channel->channel_uuid, SPLIT_LINE,
        new_channel->channel_name, SPLIT_LINE,
        new_channel->channel_desc, END_LINE,
        END_STR);
    return OK;
}

static int find_channel(struct channelhead *all_channel, char *channel_name)
{
    channel_t *channel = NULL;

    TAILQ_FOREACH(channel, all_channel, next) {
        if (strcmp(channel->channel_name, channel_name) == 0) {
            return OK;
        }
    }
    return KO;
}

static int create_channel(teams_server_t *teams_server, char **command_line,
    all_context_t *all_context)
{
    channel_t *new_channel = NULL;

    new_channel = calloc(sizeof(channel_t), 1);
    TAILQ_INIT(&(new_channel->threads_head));
    strcpy(new_channel->channel_name, command_line[1]);
    strcpy(new_channel->channel_desc, command_line[3]);
    generate_random_uuid(new_channel->channel_uuid);
    TAILQ_INSERT_TAIL(&(all_context->team->channels_head), new_channel,
        next);
    server_event_channel_created(all_context->team->team_uuid,
        new_channel->channel_uuid, new_channel->channel_name);
    write_new_channel(teams_server->actual_sockfd, new_channel);
    return OK;
}

int add_channel(teams_server_t *teams_server, char **command_line,
    int nb_args, all_context_t *all_context)
{
    if (all_context->channel == NULL) {
        if (4 != nb_args) {
            dprintf(teams_server->actual_sockfd, "500|channel\n");
            return KO;
        }
        if (find_channel(&(all_context->team->channels_head), command_line[1])
            == OK) {
            dprintf(teams_server->actual_sockfd, "503|/create%s%s", END_LINE,
                END_STR);
            return KO;
        }
        create_channel(teams_server, command_line, all_context);
        return KO;
    }
    return OK;
}

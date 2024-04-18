/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** list_command
*/
#include "myteams_server.h"

static int list_team(teams_server_t *teams_server,
    all_context_t *all_context)
{
    team_t *actual_team = NULL;

    if (all_context->team == NULL) {
        dprintf(teams_server->actual_sockfd, "200|Team list%s", END_LINE);
        TAILQ_FOREACH(actual_team, &(teams_server->all_teams), next) {
            dprintf(teams_server->actual_sockfd, "%s%s%s%s%s%s",
                actual_team->team_uuid, SPLIT_LINE,
                actual_team->team_name, SPLIT_LINE,
                actual_team->team_desc, END_LINE);
        }
        dprintf(teams_server->actual_sockfd, END_STR);
        return KO;
    }
    return OK;
}

static int list_channel(teams_server_t *teams_server,
    all_context_t *all_context)
{
    channel_t *actual_channel = NULL;

    if (all_context->channel == NULL) {
        dprintf(teams_server->actual_sockfd, "200|Channel list%s", END_LINE);
        TAILQ_FOREACH(actual_channel, &(all_context->team->channels_head),
            next) {
            dprintf(teams_server->actual_sockfd, "%s%s%s%s%s%s",
                actual_channel->channel_uuid, SPLIT_LINE,
                actual_channel->channel_name, SPLIT_LINE,
                actual_channel->channel_desc, END_LINE);
        }
        dprintf(teams_server->actual_sockfd, END_STR);
        return KO;
    }
    return OK;
}

static int list_thread(teams_server_t *teams_server,
    all_context_t *all_context)
{
    thread_t *actual_thread = NULL;

    if (all_context->thread == NULL) {
        dprintf(teams_server->actual_sockfd, "200|Thread list%s", END_LINE);
        TAILQ_FOREACH(actual_thread, &(all_context->channel->threads_head),
            next) {
            dprintf(teams_server->actual_sockfd, "%s%s%s%s%s%s%s",
                actual_thread->thread_uuid, SPLIT_LINE,
                actual_thread->thread_name, SPLIT_LINE,
                actual_thread->thread_desc, END_LINE);
        }
        dprintf(teams_server->actual_sockfd, END_STR);
        return OK;
    }
    return OK;
}

static int list_message(teams_server_t *teams_server,
    all_context_t *all_context)
{
    message_t *actual_message = NULL;

    dprintf(teams_server->actual_sockfd, "200|Message list%s", END_LINE);
    TAILQ_FOREACH(actual_message, &(all_context->thread->messages_head),
        next) {
        dprintf(teams_server->actual_sockfd,
            "200|Team created%s%s%s%s%s%s%s%s",
            END_LINE, actual_message->message_uuid, SPLIT_LINE,
            actual_message->text, SPLIT_LINE, END_LINE);
    }
    dprintf(teams_server->actual_sockfd, END_STR);
    return OK;
}

int list_all(teams_server_t *teams_server, all_context_t *all_context)
{
    if (list_team(teams_server, all_context) == KO)
        return KO;
    if (list_channel(teams_server, all_context) == KO)
        return KO;
    if (list_thread(teams_server, all_context) == KO)
        return KO;
    if (list_message(teams_server, all_context) == KO)
        return KO;
    return OK;
}

void list_command(teams_server_t *teams_server, char *command)
{
    all_context_t all_context = {.team = NULL, .channel = NULL,
        .thread = NULL};

    if (command[0] != ' ') {
        dprintf(teams_server->actual_sockfd, "500|Invalid command\n");
        dprintf(teams_server->actual_sockfd, END_STR);
        return;
    }
    if (find_all_context(teams_server, all_context.team, all_context.channel,
        all_context.thread) == KO) {
        return;
    }
    list_all(teams_server,  &all_context);
}

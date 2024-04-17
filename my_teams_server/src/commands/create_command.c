/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** create_command
*/

#include "myteams_server.h"

static int find_team(teams_server_t *teams_server, team_t *team)
{
    if (teams_server->clients[teams_server->actual_sockfd].user->
        team_context[0] != '\0') {
        team = search_in_teams(&teams_server->all_teams, teams_server->
        clients[teams_server->actual_sockfd].user->team_context);
        if (team == NULL) {
            dprintf(teams_server->actual_sockfd, "500|You need to be in a team\n");
            dprintf(teams_server->actual_sockfd, SPLITTER_STR);
            return KO;
        }
    }
    return OK;
}

static int find_channel(teams_server_t *teams_server, team_t *team, channel_t *channel)
{
    if (teams_server->clients[teams_server->actual_sockfd].user->
        channel_context[0] != '\0') {
        channel = search_in_channels(&team->channels_head, teams_server->
        clients[teams_server->actual_sockfd].user->channel_context);
        if (channel == NULL) {
            dprintf(teams_server->actual_sockfd, "500|You need to be in a channel\n");
            dprintf(teams_server->actual_sockfd, SPLITTER_STR);
            return KO;
        }
    }
    return OK;
}

static int find_thread(teams_server_t *teams_server, channel_t *channel, thread_t *thread)
{
    if (teams_server->clients[teams_server->actual_sockfd].user->
        thread_context[0] != '\0') {
        thread = search_in_threads(&channel->threads_head, teams_server->
        clients[teams_server->actual_sockfd].user->thread_context);
        if (thread == NULL) {
            dprintf(teams_server->actual_sockfd, "500|You need to be in a thread\n");
            dprintf(teams_server->actual_sockfd, SPLITTER_STR);
            return KO;
        }
    }
    return OK;
}

int add_team(teams_server_t *teams_server, char **command_line, int nb_args, team_t *team)
{
    if (team == NULL) {
        if (4 != nb_args) {
            dprintf(teams_server->actual_sockfd, "500|You need to be in a team\n");
            return KO;
        }
        team_t *new_team = calloc(sizeof(team_t), 1);
        TAILQ_INIT(&(new_team->channels_head));
        strcpy(new_team->team_name, command_line[1]);
        strcpy(new_team->team_desc, command_line[3]);
        generate_random_uuid(new_team->team_uuid);
        TAILQ_INSERT_TAIL(&(teams_server->all_teams), new_team, next);
        dprintf(teams_server->actual_sockfd, "200|Team created\n");
        dprintf(teams_server->actual_sockfd, SPLITTER_STR);
        return OK;
    }
    return OK;
}

int add_channel(teams_server_t *teams_server, char **command_line, int nb_args, team_t *team, channel_t *channel)
{
    if (channel == NULL) {
        if (4 != nb_args) {
            dprintf(teams_server->actual_sockfd, "500|You need to be in a channel\n");
            return KO;
        }
        channel_t *new_channel = calloc(sizeof(channel_t), 1);
        TAILQ_INIT(&(new_channel->threads_head));
        strcpy(new_channel->channel_name, command_line[1]);
        strcpy(new_channel->channel_desc, command_line[3]);
        generate_random_uuid(new_channel->channel_uuid);
        TAILQ_INSERT_TAIL(&(team->channels_head), new_channel, next);
        dprintf(teams_server->actual_sockfd, "200|Channel created\n");
        dprintf(teams_server->actual_sockfd, SPLITTER_STR);
        return OK;
    }
    return OK;
}

int add_thread(teams_server_t *teams_server, char **command_line, int nb_args, channel_t *channel, thread_t *thread)
{
    if (thread == NULL) {
        if (4 != nb_args) {
            dprintf(teams_server->actual_sockfd, "500|no hread\n");
            return KO;
        }
        thread_t *new_thread = calloc(sizeof(thread_t), 1);
        strcpy(new_thread->thread_name, command_line[1]);
        strcpy(new_thread->thread_desc, command_line[3]);
        generate_random_uuid(new_thread->thread_uuid);
        TAILQ_INSERT_TAIL(&(channel->threads_head), new_thread, next);
        dprintf(teams_server->actual_sockfd, "200|");
        dprintf(teams_server->actual_sockfd, thread->thread_uuid);
        dprintf(teams_server->actual_sockfd, "\b");
        dprintf(teams_server->actual_sockfd, thread->thread_name);
        dprintf(teams_server->actual_sockfd, "\b");
        dprintf(teams_server->actual_sockfd, thread->thread_desc);
        dprintf(teams_server->actual_sockfd, "\n");
        dprintf(teams_server->actual_sockfd, SPLITTER_STR);
        return OK;
    }
    return OK;
}

int add_message(teams_server_t *teams_server, char **command_line,
    int nb_args, thread_t *thread)
{
    if (2 != nb_args) {
        dprintf(teams_server->actual_sockfd, "500|no thread\n");
        return KO;
    }
    message_t *new_message = calloc(sizeof(message_t), 1);
    strcpy(new_message->text, command_line[1]);
    generate_random_uuid(new_message->message_uuid);
    TAILQ_INSERT_TAIL(&(thread->messages_head), new_message, next);
    dprintf(teams_server->actual_sockfd, "200|Thread created\n");
    dprintf(teams_server->actual_sockfd, SPLITTER_STR);
    return OK;
}

int find_all(teams_server_t *teams_server, team_t *team, channel_t *channel,
    thread_t *thread)
{
    if (find_team(teams_server, team) == KO)
        return KO;
    if (find_channel(teams_server, team, channel) == KO)
        return KO;
    if (find_thread(teams_server, channel, thread) == KO)
        return KO;
    return OK;
}

int add_all(teams_server_t *teams_server, char **command_line, int nb_args,
    team_t *team, channel_t *channel, thread_t *thread)
{
    if (add_team(teams_server, command_line, nb_args, team) == KO)
        return KO;
    if (add_channel(teams_server, command_line, nb_args, team, channel) == KO)
        return KO;
    if (add_thread(teams_server, command_line, nb_args, channel, thread) == KO)
        return KO;
    if (add_message(teams_server, command_line, nb_args, thread) == KO)
        return KO;
    return OK;
}

void create_command(teams_server_t *teams_server, char *command)
{
    team_t *team = NULL;
    channel_t *channel = NULL;
    thread_t *thread = NULL;
    char **command_line = splitter(command, "\"");
    int nb_args = get_len_char_tab(command_line);

    if (command[0] != ' ') {
        dprintf(teams_server->actual_sockfd, "500|Invalid command\n");
        dprintf(teams_server->actual_sockfd, SPLITTER_STR);
        return;
    }
    if (find_all(teams_server, team, channel, thread) == KO)
        return;
    if (add_all(teams_server, command_line, nb_args, team, channel, thread)
        == KO)
        return;
}

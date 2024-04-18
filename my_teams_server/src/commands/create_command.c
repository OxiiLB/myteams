/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** create_command
*/

#include "myteams_server.h"

static int write_new_team(int client_fd, team_t *new_team)
{
    dprintf(client_fd, "200|Team created\n");
    dprintf(client_fd, new_team->team_uuid);
    dprintf(client_fd, "\b");
    dprintf(client_fd, new_team->team_name);
    dprintf(client_fd, "\b");
    dprintf(client_fd, new_team->team_desc);
    dprintf(client_fd, "\n");
    dprintf(client_fd, SPLITTER_STR);
    return OK;
}

static int add_team(teams_server_t *teams_server, char **command_line,
    int nb_args, all_context_t *all_context)
{
    team_t *new_team = NULL;

    if (all_context->team == NULL) {
        if (4 != nb_args) {
            dprintf(teams_server->actual_sockfd, "500|azea\n");
            return KO;
        }
        new_team = calloc(sizeof(team_t), 1);
        TAILQ_INIT(&(new_team->channels_head));
        strcpy(new_team->team_name, command_line[1]);
        strcpy(new_team->team_desc, command_line[3]);
        generate_random_uuid(new_team->team_uuid);
        TAILQ_INSERT_TAIL(&(teams_server->all_teams), new_team, next);
        write_new_team(teams_server->actual_sockfd, new_team);
        return OK;
    }
    return OK;
}

static int write_new_channel(int client_fd, channel_t *new_channel)
{
    dprintf(client_fd, "200|Channel created\n");
    dprintf(client_fd, new_channel->channel_uuid);
    dprintf(client_fd, "\b");
    dprintf(client_fd, new_channel->channel_name);
    dprintf(client_fd, "\b");
    dprintf(client_fd, new_channel->channel_desc);
    dprintf(client_fd, "\n");
    dprintf(client_fd, SPLITTER_STR);
    return OK;
}

static int add_channel(teams_server_t *teams_server, char **command_line,
    int nb_args, all_context_t *all_context)
{
    channel_t *new_channel = NULL;

    if (all_context->channel == NULL) {
        if (4 != nb_args) {
            dprintf(teams_server->actual_sockfd, "500|channel\n");
            return KO;
        }
        new_channel = calloc(sizeof(channel_t), 1);
        TAILQ_INIT(&(new_channel->threads_head));
        strcpy(new_channel->channel_name, command_line[1]);
        strcpy(new_channel->channel_desc, command_line[3]);
        generate_random_uuid(new_channel->channel_uuid);
        TAILQ_INSERT_TAIL(&(all_context->team->channels_head), new_channel,
            next);
        write_new_channel(teams_server->actual_sockfd, new_channel);
        return OK;
    }
    return OK;
}

int write_new_thread(int client_fd, thread_t *new_thread)
{
    dprintf(client_fd, "200|Thread created\n");
    dprintf(client_fd, new_thread->thread_uuid);
    dprintf(client_fd, "\b");
    dprintf(client_fd, new_thread->thread_name);
    dprintf(client_fd, "\b");
    dprintf(client_fd, new_thread->thread_desc);
    dprintf(client_fd, "\n");
    dprintf(client_fd, SPLITTER_STR);
    return OK;
}

static int add_thread(teams_server_t *teams_server, char **command_line,
    int nb_args, all_context_t *all_context)
{
    thread_t *new_thread = NULL;

    if (all_context->thread == NULL) {
        if (4 != nb_args) {
            dprintf(teams_server->actual_sockfd, "500|no thread\n");
            return KO;
        }
        new_thread = calloc(sizeof(thread_t), 1);
        strcpy(new_thread->thread_name, command_line[1]);
        strcpy(new_thread->thread_desc, command_line[3]);
        generate_random_uuid(new_thread->thread_uuid);
        TAILQ_INSERT_TAIL(&(all_context->channel->threads_head), new_thread,
            next);
        write_new_thread(teams_server->actual_sockfd, new_thread);
        return OK;
    }
    return OK;
}

int add_message(teams_server_t *teams_server, char **command_line,
    int nb_args, all_context_t *all_context)
{
    message_t *new_message = NULL;

    if (2 != nb_args) {
        dprintf(teams_server->actual_sockfd, "500|no thread\n");
        return KO;
    }
    new_message = calloc(sizeof(message_t), 1);
    strcpy(new_message->text, command_line[1]);
    generate_random_uuid(new_message->message_uuid);
    TAILQ_INSERT_TAIL(&(all_context->thread->messages_head), new_message,
        next);
    dprintf(teams_server->actual_sockfd, "200|Thread created\n");
    dprintf(teams_server->actual_sockfd, SPLITTER_STR);
    return OK;
}

int add_all(teams_server_t *teams_server, char **command_line,
    int nb_args, all_context_t *create)
{
    if (add_team(teams_server, command_line, nb_args, create) == KO)
        return KO;
    if (add_channel(teams_server, command_line, nb_args, create) == KO)
        return KO;
    if (add_thread(teams_server, command_line, nb_args, create) == KO)
        return KO;
    if (add_message(teams_server, command_line, nb_args, create) == KO)
        return KO;
    return OK;
}

void create_command(teams_server_t *teams_server, char *command)
{
    all_context_t create = {.team = NULL, .channel = NULL, .thread = NULL};
    char **command_line = splitter(command, "\"");
    int nb_args = get_len_char_tab(command_line);

    if (command[0] != ' ') {
        dprintf(teams_server->actual_sockfd, "500|Invalid command\n");
        dprintf(teams_server->actual_sockfd, SPLITTER_STR);
        return;
    }
    if (find_all_context(teams_server, create.team, create.channel,
        create.thread) == KO)
        return;
    if (add_all(teams_server, command_line, nb_args, &create)
        == KO)
        return;
}

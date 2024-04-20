/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** create_command
*/

#include "myteams_server.h"

static int write_new_thread(int client_fd, thread_t *new_thread)
{
    dprintf(client_fd, "200|/create%s%s%s%s%s", END_LINE,
        new_thread->thread_uuid, SPLIT_LINE,
        new_thread->thread_name, SPLIT_LINE,
        new_thread->thread_desc, END_LINE,
        END_STR);
    return OK;
}

static int find_thread(struct threadhead *all_thread, char *thread_name)
{
    thread_t *thread = NULL;

    TAILQ_FOREACH(thread, all_thread, next) {
        if (strcmp(thread->thread_name, thread_name) == 0) {
            return OK;
        }
    }
    return KO;
}

static int create_thead(teams_server_t *teams_server, char **command_line,
    all_context_t *all_context)
{
    thread_t *new_thread = NULL;

    new_thread = calloc(sizeof(thread_t), 1);
    strcpy(new_thread->thread_name, command_line[1]);
    strcpy(new_thread->thread_desc, command_line[3]);
    generate_random_uuid(new_thread->thread_uuid);
    TAILQ_INSERT_TAIL(&(all_context->channel->threads_head), new_thread,
        next);
    server_event_thread_created(
        all_context->channel->channel_uuid, new_thread->thread_uuid,
        teams_server->clients[teams_server->actual_sockfd].user->uuid,
        new_thread->thread_name, new_thread->thread_desc);
    write_new_thread(teams_server->actual_sockfd, new_thread);
    return OK;
}

static int add_thread(teams_server_t *teams_server, char **command_line,
    int nb_args, all_context_t *all_context)
{
    if (all_context->thread == NULL) {
        if (4 != nb_args) {
            dprintf(teams_server->actual_sockfd, "500|no thread\n");
            return KO;
        }
        if (find_thread(&(all_context->team->channels_head), command_line[1])
            == OK) {
            dprintf(teams_server->actual_sockfd, "503|/create%s%s", END_LINE,
                END_STR);
            return KO;
        }
        create_thead(teams_server, command_line, all_context);
        return KO;
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
    server_event_reply_created(
        all_context->thread->thread_uuid,
        teams_server->clients[teams_server->actual_sockfd].user->uuid,
        new_message->text);
    dprintf(teams_server->actual_sockfd, "200|/create%s", END_LINE);
    dprintf(teams_server->actual_sockfd, END_STR);
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

    if (command[0] != ' ' || (count_str_char(command, "\"") != 2 &&
        count_str_char(command, "\"") != 4)) {
        dprintf(teams_server->actual_sockfd, "500|Invalid command\n");
        dprintf(teams_server->actual_sockfd, END_STR);
        return;
    }
    if (find_all_context(teams_server, create.team, create.channel,
        create.thread) == KO)
        return;
    if (add_all(teams_server, command_line, nb_args, &create)
        == KO)
        return;
}

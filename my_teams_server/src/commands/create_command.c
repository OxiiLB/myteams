/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** create_command
*/

#include "myteams_server.h"

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

static int handle_error(teams_server_t *teams_server, char **command_line,
    char *command)
{
    if (teams_server->clients[teams_server->actual_sockfd].user == NULL) {
        dprintf(teams_server->actual_sockfd, "502|Unauthorized action%s%s",
            END_LINE, END_STR);
        return KO;
    }
    if (command[0] != ' ' || (count_str_char(command, '\"') != 2 &&
        count_str_char(command, '\"') != 4)) {
        dprintf(teams_server->actual_sockfd, "500|Invalid command\n");
        dprintf(teams_server->actual_sockfd, END_STR);
        return KO;
    }
    return OK;
}

void create_command(teams_server_t *teams_server, char *command)
{
    all_context_t create = {.team = NULL, .channel = NULL, .thread = NULL};
    char **command_line = splitter(command, "\"");
    int nb_args = get_len_char_tab(command_line);

    if (handle_error(teams_server, command_line, command) == KO){
        free_array(command_line);
        return;
    }
    if (find_all_context(teams_server, create.team, create.channel,
        create.thread) == KO)
        return;
    if (add_all(teams_server, command_line, nb_args, &create)
        == KO)
        return;
}

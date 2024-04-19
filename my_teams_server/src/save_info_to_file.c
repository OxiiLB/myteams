/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** save_info_to_file
*/

#include "myteams_server.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void save_users(teams_server_t *teams_server, int file, char *str)
{
    user_t *new_user = NULL;

    str[0] = USERS_CHAR;
    TAILQ_FOREACH(new_user, &teams_server->all_user, next) {
        if (new_user->username[0] != 0) {
            write(file, str, sizeof(USERS_CHAR));
            write(file, new_user, sizeof(new_user->username) +
            sizeof(new_user->uuid) + sizeof(new_user->next) +
            sizeof(new_user->team_context) + sizeof(new_user->channel_context)
            + sizeof(new_user->thread_context) +
            sizeof(new_user->valid_context) + sizeof(new_user->nb_clients));
        }
    }
}

static void save_privates_messages(teams_server_t *teams_server, int file,
    char *str)
{
    message_t *new_message = NULL;

    str[0] = MP_CHAR;
    TAILQ_FOREACH(new_message, &teams_server->all_user, next) {
        if (new_message->text[0] != 0) {
            write(file, str, sizeof(USERS_CHAR));
            write(file, new_message, sizeof(new_message->message_uuid) + 
                sizeof(new_message->text) + sizeof(new_message->sender_uuid)
                + sizeof(new_message->receiver_uuid) +
                sizeof(new_message->timestamp) + sizeof(new_message->next));
        }
    }
}

int save_info_to_file(teams_server_t *teams_server)
{
    int file = open(SAVE_FILE, O_CREAT | O_TRUNC | O_WRONLY | O_APPEND, 00777);
    char str[BUFSIZ];

    memset(str, 0, BUFSIZ);
    if (file == -1)
        return ERROR;
    save_users(teams_server, file, str);
    save_privates_messages(teams_server, file, str);
    close(file);
    return OK;
}

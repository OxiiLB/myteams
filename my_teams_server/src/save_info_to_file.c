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

static void save_users(struct userhead *user_head, int file, char *str)
{
    user_t *new_user = NULL;

    str[0] = USERS_CHAR;
    TAILQ_FOREACH(new_user, user_head, next) {
        if (new_user->username[0] != 0) {
            write(file, str, sizeof(USERS_CHAR));
            write(file, new_user, sizeof(new_user->username) +
            sizeof(new_user->uuid) + sizeof(new_user->next) +
            sizeof(new_user->team_context) + sizeof(new_user->channel_context)
            + sizeof(new_user->thread_context) + sizeof(new_user->nb_clients));
        }
    }
}

static void save_privates_messages(struct messagehead *message_head, int file,
    char *str)
{
    message_t *new_message = NULL;

    str[0] = PRIVATE_MESSAGE_CHAR;
    TAILQ_FOREACH(new_message, message_head, next) {
        if (new_message->text[0] != 0) {
            write(file, str, sizeof(PRIVATE_MESSAGE_CHAR));
            write(file, new_message, sizeof(new_message->message_uuid) +
                sizeof(new_message->text) + sizeof(new_message->sender_uuid)
                + sizeof(new_message->receiver_uuid) +
                sizeof(new_message->timestamp) + sizeof(new_message->next));
        }
    }
}

static void save_subscribed(struct subscribedhead *subscribe_head, int file,
    char *str)
{
    subscribed_t *new_subscribe = NULL;

    str[0] = SUBSCRIBE_CHAR;
    TAILQ_FOREACH(new_subscribe, subscribe_head, next) {
        if (new_subscribe->user_uuid[0] != 0) {
            write(file, str, sizeof(SUBSCRIBE_CHAR));
            write(file, new_subscribe, sizeof(new_subscribe->team_uuid) +
                sizeof(new_subscribe->user_uuid) +
                sizeof(new_subscribe->next));
        }
    }
}

static void save_reply(struct replyhead *reply_head, int file,
    char *str)
{
    reply_t *new_reply = NULL;

    str[0] = REPLY_CHAR;
    TAILQ_FOREACH(new_reply, reply_head, next) {
        if (new_reply->reply_uuid[0] != 0) {
            write(file, str, sizeof(REPLY_CHAR));
            write(file, new_reply, sizeof(new_reply->reply_uuid) +
                sizeof(new_reply->sender_uuid) + sizeof(new_reply->text)
                + sizeof(new_reply->next) + sizeof(new_reply->thread_uuid) +
                sizeof(new_reply->timestamp));
        }
    }
}

static void save_thread(struct threadhead *thread_head, int file,
    char *str)
{
    thread_t *new_thread = NULL;

    str[0] = THREADS_CHAR;
    TAILQ_FOREACH(new_thread, thread_head, next) {
        if (new_thread->thread_uuid[0] != 0) {
            write(file, str, sizeof(THREADS_CHAR));
            write(file, new_thread, sizeof(new_thread->thread_uuid) +
                sizeof(new_thread->title) + sizeof(new_thread->body)
                + sizeof(new_thread->next) + sizeof(new_thread->replys_head)
                + sizeof(new_thread->channel_uuid) +
                sizeof(new_thread->timestamp));
            save_reply(&new_thread->replys_head, file, str);
        }
    }
}

static void save_channel(struct channelhead *channel_head, int file,
    char *str)
{
    channel_t *new_channel = NULL;

    str[0] = CHANNELS_CHAR;
    TAILQ_FOREACH(new_channel, channel_head, next) {
        if (new_channel->channel_uuid[0] != 0) {
            write(file, str, sizeof(CHANNELS_CHAR));
            write(file, new_channel, sizeof(new_channel->channel_uuid) +
                sizeof(new_channel->name) + sizeof(new_channel->desc)
                + sizeof(new_channel->next) + sizeof(new_channel->threads_head)
                + sizeof(new_channel->team_uuid));
            save_thread(&new_channel->threads_head, file, str);
        }
    }
}

static void save_team(struct teamhead *teams_head, int file,
    char *str)
{
    team_t *new_team = NULL;

    str[0] = TEAMS_CHAR;
    TAILQ_FOREACH(new_team, teams_head, next) {
        if (new_team->team_uuid[0] != 0) {
            write(file, str, sizeof(TEAMS_CHAR));
            write(file, new_team, sizeof(new_team->team_uuid) +
                sizeof(new_team->name) + sizeof(new_team->desc)
                + sizeof(new_team->next) + sizeof(new_team->channels_head));
        }
        save_channel(&new_team->channels_head, file, str);
    }
}

int save_info_to_file(teams_server_t *teams_server)
{
    int file = open(SAVE_FILE, O_CREAT | O_TRUNC | O_WRONLY | O_APPEND, 00777);
    char str[BUFSIZ];

    memset(str, 0, BUFSIZ);
    if (file == -1)
        return ERROR;
    save_users(&teams_server->all_user, file, str);
    save_privates_messages(&teams_server->private_messages, file, str);
    save_subscribed(&teams_server->subscribed_teams_users, file, str);
    save_team(&teams_server->all_teams, file, str);
    close(file);
    return OK;
}

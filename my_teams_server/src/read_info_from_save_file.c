/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** save_info_to_file
*/

#include "myteams_server.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static int add_save_user(teams_server_t *teams_server, int file)
{
    user_t *user1 = calloc(sizeof(user_t), 1);

    if (read(file, user1, sizeof(user1->username) + sizeof(user1->uuid) +
        sizeof(user1->next) + sizeof(user1->team_context) +
        sizeof(user1->channel_context) + sizeof(user1->thread_context)
        + sizeof(user1->nb_clients)) == -1)
        return KO;
    if (user1->username[0] == '\0' || user1->uuid[0] == '\0') {
        free(user1);
    } else {
        memset(user1->team_context, 0, MAX_UUID_LENGTH);
        memset(user1->channel_context, 0, MAX_UUID_LENGTH);
        memset(user1->thread_context, 0, MAX_UUID_LENGTH);
        user1->nb_clients = 0;
        server_event_user_loaded(user1->uuid, user1->username);
        TAILQ_INSERT_TAIL(&teams_server->all_user, user1, next);
    }
    return OK;
}

static int add_save_private_message(teams_server_t *teams_server, int file)
{
    message_t *private_message = calloc(sizeof(message_t), 1);

    if (read(file, private_message, sizeof(private_message->sender_uuid) +
        sizeof(private_message->receiver_uuid) +
        sizeof(private_message->text) + sizeof(private_message->next) +
        sizeof(private_message->timestamp)) == -1)
        return KO;
    if (private_message->sender_uuid[0] == '\0' ||
        private_message->receiver_uuid[0] == '\0') {
        free(private_message);
    } else {
        TAILQ_INSERT_TAIL(&teams_server->private_messages, private_message,
            next);
    }
    return OK;
}

static int add_save_subscribe(teams_server_t *teams_server, int file)
{
    subscribed_t *subscribe = calloc(sizeof(subscribed_t), 1);

    if (read(file, subscribe, sizeof(subscribe->team_uuid) +
        sizeof(subscribe->user_uuid) + sizeof(subscribe->next)) == -1)
        return KO;
    if (subscribe->user_uuid[0] == '\0' || subscribe->team_uuid[0] == '\0') {
        free(subscribe);
    } else {
        TAILQ_INSERT_TAIL(&teams_server->subscribed_teams_users, subscribe,
            next);
    }
    return OK;
}

static int add_save_team(teams_server_t *teams_server, int file)
{
    team_t *new_team = calloc(sizeof(team_t), 1);

    if (read(file, new_team, sizeof(new_team->team_uuid) +
        sizeof(new_team->name) + sizeof(new_team->desc) +
        sizeof(new_team->next) + sizeof(new_team->channels_head)) == -1)
        return KO;
    if (new_team->team_uuid[0] == '\0') {
        free(new_team);
    } else {
        TAILQ_INSERT_TAIL(&teams_server->all_teams, new_team, next);
    }
    return OK;
}

static int add_save_channel(teams_server_t *teams_server, int file)
{
    channel_t *new_channel = calloc(sizeof(channel_t), 1);

    if (read(file, new_channel, sizeof(new_channel->channel_uuid) +
        sizeof(new_channel->name) + sizeof(new_channel->desc) +
        sizeof(new_channel->next) + sizeof(new_channel->team_uuid)
        + sizeof(new_channel->threads_head)) == -1)
        return KO;
    if (new_channel->channel_uuid[0] == '\0') {
        free(new_channel);
    } else {
        team_t *team = get_team_by_uuid(teams_server, new_channel->team_uuid);
        TAILQ_INSERT_TAIL(&team->channels_head, new_channel, next);
    }
    return OK;
}

int choose_elem(teams_server_t *teams_server, int file, char delimiter)
{
    switch (delimiter) {
    case USERS_CHAR:
        add_save_user(teams_server, file);
        break;
    case PRIVATE_MESSAGE_CHAR:
        add_save_private_message(teams_server, file);
        break;
    case SUBSCRIBE_CHAR:
        add_save_subscribe(teams_server, file);
        break;
    case TEAMS_CHAR:
        add_save_team(teams_server, file);
        break;
    case CHANNELS_CHAR:
        add_save_channel(teams_server, file);
        break;
    default:
        break;
    }
    return OK;
}

int read_info_from_save_file(teams_server_t *teams_server)
{
    int file = open(SAVE_FILE, O_RDONLY, 00777);
    int n_byte = 0;
    char str[BUFSIZ];

    memset(str, 0, BUFSIZ);
    if (file == -1)
        return KO;
    do {
        n_byte = read(file, str, sizeof(USERS_CHAR));
        if (n_byte == -1)
            break;
        choose_elem(teams_server, file, str[0]);
    } while (n_byte != 0);
    close(file);
    return OK;
}

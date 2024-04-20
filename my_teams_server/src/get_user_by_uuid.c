/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** get_user_by_uuid
*/

#include "myteams_server.h"

user_t *get_user_by_uuid(teams_server_t *teams_server, char *uuid)
{
    user_t *user = NULL;

    TAILQ_FOREACH(user, &teams_server->all_user, next) {
        if (strcmp(user->uuid, uuid) == 0)
            return user;
    }
    return NULL;
}
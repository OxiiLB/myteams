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

int save_info_to_file(teams_server_t *teams_server)
{
    int file = open(SAVE_FILE, O_CREAT | O_TRUNC | O_WRONLY | O_APPEND, 00777);
    user_t *user1 = NULL;
    char str[BUFSIZ];

    memset(str, 0, BUFSIZ);
    if (file == -1)
        return ERROR;
    str[0] = USERS_CHAR;
    TAILQ_FOREACH(user1, &teams_server->all_user, next) {
        if (user1->username[0] != 0) {
        write(file, str, sizeof(USERS_CHAR));
        write(file, user1, sizeof(user1->username) + sizeof(user1->uuid) +
            sizeof(user1->next) + sizeof(user1->team_context) +
            sizeof(user1->channel_context) + sizeof(user1->thread_context) +
            sizeof(user1->valid_context) + sizeof(user1->nb_clients));
        }
    }
    close(file);
    return OK;
}

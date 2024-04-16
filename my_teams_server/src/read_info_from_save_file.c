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

int add_user(teams_server_t *teams_server, int file)
{
    user_t *user1 = malloc(sizeof(user_t));

    if (read(file, user1, sizeof(user1->username) + sizeof(user1->uuid) +
        sizeof(user1->next)) == -1)
        return KO;
    user1->next.le_next = NULL;
    user1->next.le_prev = NULL;
    if (user1->username[0] == 0) {
        free(user1);
    } else {
        server_event_user_loaded(user1->uuid, user1->username);
        LIST_INSERT_HEAD(&teams_server->all_user, user1, next);
    }
    return OK;
}

int choose_elem(teams_server_t *teams_server, int file, char delimiter)
{
    switch (delimiter) {
    case USERS_CHAR:
        if (add_user(teams_server, file) == KO)
            return KO;
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

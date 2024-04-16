/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** login_command
*/

#include "myteams_server.h"

int count_str_char(char *str, char c)
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            count++;
    }
    return count;
}


void login_command(teams_server_t *teams_server,
    char *command)
{
    user_t *user1 = NULL;
    user_t *user2 = NULL;

    if (strlen(command) == 0 || command[0] != ' ' || count_str_char(command,
        '\"') != 2)
        return;
    command = &command[2];
    command[strlen(command) - 1] = '\0';
    LIST_FOREACH(user1, &teams_server->all_user, next){
        if (strcmp(user1->username, command) == 0) {
            user2 = user1;
        }
    }
    if (user2 == NULL) {
        user2 = malloc(sizeof(user_t));
        user2->username = strdup(command);
        user2->uuid = generate_random_uuid();
        server_event_user_created(user2->uuid, command);
        LIST_INSERT_HEAD(&teams_server->all_user, user2, next);
    }
    dprintf(teams_server->actual_sockfd, user2->uuid);
    dprintf(teams_server->actual_sockfd, SPLITTER_STR);
    server_event_user_logged_in(user2->uuid);
}

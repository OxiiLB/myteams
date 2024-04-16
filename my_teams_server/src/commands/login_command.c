/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** login_command
*/

#include "myteams_server.h"

void login_command(my_teams_server_struct_t *my_teams_server_struct,
    char __attribute__((unused)) * command)
{
    char *test = "zaerzrzerzer";
    char *uuid;
    user_t *user1 = NULL;

    LIST_FOREACH(user1, &my_teams_server_struct->all_user, next){
        if (strcmp(user1->username, command) == 0) {
            char* str = malloc(sizeof(char) * (strlen(user1->uuid) + 1 + 1));
            strcpy(str, user1->uuid);
            strcat(str, "\n");
            write(my_teams_server_struct->actual_sockfd, str, strlen(str));
            free(str);
            return;
        }
    }
    user1->username = strdup("username");
    user1->uuid = strdup("uuid");
    uuid = generate_random_uuid();

    LIST_INSERT_HEAD(&my_teams_server_struct->all_user, user1, next);

    server_event_user_created(uuid, command);
    char* str = malloc(sizeof(char) * (strlen(uuid) + 1 + 1));
    strcpy(str, uuid);
    strcat(str, "\n");
    write(my_teams_server_struct->actual_sockfd, str, strlen(str));
    free(str);
}

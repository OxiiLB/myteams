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


void login_command(my_teams_server_struct_t *my_teams_server_struct,
    char *command)
{
    char *test = "zaerzrzerzer";
    char *uuid;
    user_t *user1 = NULL;

    if (strlen(command) == 0 || command[0] != ' ' || count_str_char(command,
        '\"') != 0)
        return;
    LIST_FOREACH(user1, &my_teams_server_struct->all_user, next){
        if (strcmp(user1->username, command) == 0) {
            char* str = malloc(sizeof(char) * (strlen(user1->uuid) + 1 + 1));
            strcpy(str, user1->uuid);
            strcat(str, "\v");
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
    server_event_user_logged_in(uuid);
    free(str);
}

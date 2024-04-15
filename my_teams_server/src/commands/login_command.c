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

    // my_teams_server_struct->all_user
    uuid = generate_random_uuid();

    server_event_user_created(uuid, command);
    char* str = malloc(sizeof(char) * (strlen(uuid) + 1 + 1));
    strcpy(str, uuid);
    strcat(str, "\n");
    write(my_teams_server_struct->actual_sockfd, str, strlen(str));
}

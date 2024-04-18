/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** use_command
*/


#include "myteams_server.h"

int handle_errors(teams_server_t *teams_server, char *command)
{
    if (teams_server->clients[teams_server->actual_sockfd].user == NULL) {
        dprintf(teams_server->actual_sockfd, "500|not logged in\n");
        dprintf(teams_server->actual_sockfd, END_STR);
        return 1;
    }
    if (strlen(command) != MAX_UUID_LENGTH + 1) {
        dprintf(teams_server->actual_sockfd, "500|Invalid UUID\n");
        dprintf(teams_server->actual_sockfd, END_STR);
        return 1;
    }
    return 0;
}

int get_array_len(char **array)
{
    int i = 0;

    for (; array[i] != NULL; i++);
    return i;
}

int fill_context_2(teams_server_t *teams_server, char **split_command)
{
    if (get_array_len(split_command) == 3) {
        strcpy(teams_server->clients[teams_server->actual_sockfd].user->
        team_context, split_command[1]);
        strcpy(teams_server->clients[teams_server->actual_sockfd].user->
        channel_context, split_command[2]);
        return 0;
    }
    if (get_array_len(split_command) == 4) {
        strcpy(teams_server->clients[teams_server->actual_sockfd].user->
        team_context, split_command[1]);
        strcpy(teams_server->clients[teams_server->actual_sockfd].user->
        channel_context, split_command[2]);
        strcpy(teams_server->clients[teams_server->actual_sockfd].user->
        thread_context, split_command[3]);
        return 0;
    }
    free_array(split_command);
    return 0;
}

int fill_context(teams_server_t *teams_server, char *command)
{
    char **split_command = splitter(command, " ");

    memset(teams_server->clients[teams_server->actual_sockfd].user->
    team_context, 0, MAX_UUID_LENGTH);
    memset(teams_server->clients[teams_server->actual_sockfd].user->
    channel_context, 0, MAX_UUID_LENGTH);
    memset(teams_server->clients[teams_server->actual_sockfd].user->
    thread_context, 0, MAX_UUID_LENGTH);
    if (get_array_len(split_command) == 2) {
        strcpy(teams_server->clients[teams_server->actual_sockfd].user->
        team_context, split_command[1]);
        return 0;
    }
    return fill_context_2(teams_server, split_command);
}

void use_command(teams_server_t *teams_server, char *command)
{
    char **split_command = splitter(command, " ");

    fill_context(teams_server, command);
    if (handle_errors(teams_server, command) == 1) {
        free_array(split_command);
        return;
    }
    teams_server->clients[teams_server->actual_sockfd].user->valid_context =
        true;
    dprintf(teams_server->actual_sockfd, "200|\n");
    dprintf(teams_server->actual_sockfd, END_STR);
}

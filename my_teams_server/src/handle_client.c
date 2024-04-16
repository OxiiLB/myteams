/*
** EPITECH PROJECT, 2024
** server_functions
** File description:
** server_functions
*/

#include "myteams_server.h"
#include "../../include/my_macro.h"

void handle_command(teams_server_t *teams_server,
    char *command)
{
    char *allow_command = "/help";

    if (strncmp(command, allow_command, strlen(allow_command)) == 0){
        help_command(teams_server, &command[strlen(allow_command)]);
    }
    allow_command = "/login";
    if (strncmp(command, allow_command, strlen(allow_command)) == 0){
        login_command(teams_server, &command[strlen(allow_command)]);
    }
}

static void last_split(teams_server_t *teams_server,
    char *buffer, char *last_split)
{
    if (buffer[strlen(buffer) - 1] == *SPLITTER_STR) {
        handle_command(teams_server, last_split);
        memset(buffer, 0, MAX_COMMAND_LENGTH);
    } else {
        strcpy(buffer, last_split);
    }
    free(last_split);
}

void malloc_input_buffer(teams_server_t *teams_server)
{
    if (!teams_server->clients[teams_server->
        actual_sockfd].buffer.input_buffer) {
        teams_server->clients[teams_server->
            actual_sockfd].buffer.input_buffer = malloc(sizeof(char) *
            MAX_COMMAND_LENGTH);
        memset(teams_server->clients[teams_server->
            actual_sockfd].buffer.input_buffer, 0, MAX_COMMAND_LENGTH);
    }
}

void handle_client(teams_server_t *teams_server)
{
    int j = 0;
    char buffer[BUFSIZ];
    ssize_t n = read(teams_server->actual_sockfd, buffer,
        sizeof(buffer) - 1);
    char **lines = NULL;

    if (n == -1 || n == 0)
        return;
    malloc_input_buffer(teams_server);
    strcat(teams_server->clients[teams_server->
        actual_sockfd].buffer.input_buffer, buffer);
    lines = splitter(buffer, SPLITTER_STR);
    for (; lines[1] != NULL && lines[j + 1]; j += 1) {
        handle_command(teams_server, lines[j]);
        free(lines[j]);
    }
    last_split(teams_server, buffer, lines[j]);
    free(lines);
}

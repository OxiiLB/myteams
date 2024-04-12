/*
** EPITECH PROJECT, 2024
** server_functions
** File description:
** server_functions
*/

#include "myteams_server.h"
#include "../../include/my_macro.h"

void handle_command(my_teams_server_struct_t *my_teams_server_struct,
    char *command)
{
    char *allow_command = "/help";

    printf("command: %s\n", command);
    if (strncmp(command, allow_command, strlen(allow_command)) == 0){
        help_command(my_teams_server_struct, &command[strlen(allow_command)]);
    }
    allow_command = "/login ";
    if (strncmp(command, allow_command, strlen(allow_command)) == 0){
        login_command(my_teams_server_struct, &command[strlen(allow_command)]);
    }
}

static void last_split(my_teams_server_struct_t *my_teams_server_struct,
    char *buffer, char *last_split)
{
    if (buffer[strlen(buffer) - 1] == '\n') {
        handle_command(my_teams_server_struct, last_split);
        memset(buffer, 0, MAX_COMMAND_LENGTH);
    } else {
        strcpy(buffer, last_split);
    }
    free(last_split);
}

void malloc_input_buffer(my_teams_server_struct_t *my_teams_server_struct)
{
    if (!my_teams_server_struct->clients[my_teams_server_struct->
        actual_sockfd].buffer.input_buffer) {
        my_teams_server_struct->clients[my_teams_server_struct->
            actual_sockfd].buffer.input_buffer = malloc(sizeof(char) *
            MAX_COMMAND_LENGTH);
        memset(my_teams_server_struct->clients[my_teams_server_struct->
            actual_sockfd].buffer.input_buffer, 0, MAX_COMMAND_LENGTH);
    }
}

void handle_client(my_teams_server_struct_t *my_teams_server_struct)
{
    int j = 0;
    char buffer[BUFSIZ];
    ssize_t n = read(my_teams_server_struct->actual_sockfd, buffer,
        sizeof(buffer) - 1);
    char **lines = NULL;

    if (n == -1 || n == 0)
        return;
    malloc_input_buffer(my_teams_server_struct);
    strcat(my_teams_server_struct->clients[my_teams_server_struct->
        actual_sockfd].buffer.input_buffer, buffer);
    lines = splitter(buffer, "\n");
    for (; lines[1] != NULL && lines[j + 1]; j += 1) {
        handle_command(my_teams_server_struct, lines[j]);
        free(lines[j]);
    }
    last_split(my_teams_server_struct, buffer, lines[j]);
    free(lines);
}

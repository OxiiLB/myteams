/*
** EPITECH PROJECT, 2024
** server_functions
** File description:
** server_functions
*/

#include "myteams_server.h"
#include "../../include/my_macro.h"

int setup_server(int port, int max_clients)
{
    int my_socket;
    struct sockaddr_in my_socket_addr;

    my_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (my_socket == KO)
        return KO;
    my_socket_addr.sin_family = AF_INET;
    my_socket_addr.sin_addr.s_addr = INADDR_ANY;
    my_socket_addr.sin_port = htons(port);
    if (bind(my_socket, (const struct sockaddr *)&my_socket_addr,
        sizeof(my_socket_addr)) == KO)
        return KO;
    if (listen(my_socket, max_clients) == KO)
        return KO;
    return my_socket;
}

void handle_command(my_teams_server_struct_t *my_teams_server_struct,
    char *command)
{
    char *uuid;

    printf("command: %s\n", command);
    printf("command: %s\n", my_teams_server_struct->actual_command);
    uuid = generate_random_uuid();
    printf("command: %s\n", uuid);
    free(uuid);
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

void handle_client(my_teams_server_struct_t *my_teams_server_struct,
    int client_fd)
{
    char buffer[BUFSIZ];
    int j = 0;
    ssize_t n = read(client_fd, buffer, sizeof(buffer) - 1);
    char **lines = NULL;

    if (n == -1 || n == 0)
        return;
    if (!my_teams_server_struct->clients[client_fd].buffer.input_buffer) {
        my_teams_server_struct->clients[client_fd].buffer.input_buffer =
            malloc(sizeof(char) * MAX_COMMAND_LENGTH);
    }
    strcat(my_teams_server_struct->clients[client_fd].buffer.input_buffer,
        buffer);
    lines = splitter(buffer, "\n");
    for (; lines[1] != NULL && lines[j + 1]; j += 1) {
        handle_command(my_teams_server_struct, lines[j]);
        free(lines[j]);
    }
    last_split(my_teams_server_struct, buffer, lines[j]);
    free(lines);
}

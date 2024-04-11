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

static int fd_is_set(my_teams_server_struct_t *my_teams_server_struct, int i)
{
    if (FD_ISSET(i, &my_teams_server_struct->fd.input)) {
        if (check_new_connection(my_teams_server_struct, i) == ERROR)
            return ERROR;
        return 0;
    }
    return 0;
}

int scan_fd(my_teams_server_struct_t *my_teams_server_struct)
{
    for (int i = 0; i < __FD_SETSIZE; i++) {
        if (fd_is_set(my_teams_server_struct, i) == ERROR)
            return ERROR;
    }
    return 0;
}

void handle_command(my_teams_server_struct_t *my_teams_server_struct,
    char *command)
{
    printf("command: %s\n", command);
    printf("command: %s\n", my_teams_server_struct->actual_command);
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

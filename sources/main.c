#include "step1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char **spliter_by_sep(char const *const str, char *separator)
{
    int i = 0;
    char **tab = NULL;
    char *tkt_str = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(tkt_str, str);
    char *tmp_str = strtok(tkt_str, separator);
    if (tmp_str == NULL)
        return NULL;
    tab = malloc(sizeof(char *) * (strlen(str) + 1));
    if (tab == NULL)
        return NULL;
    while (tmp_str != NULL) {
        tab[i] = strdup(tmp_str);
        tmp_str = strtok(NULL, separator);
        i += 1;
    }
    tab[i] = NULL;
    free(tkt_str);
    return tab;
}

int str_count_c(char *str, char c)
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
        count++;
        }
    }
    return count;
}

char *str_upper(char *str)
{
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] >= 'a' && str[i] <= 'z') {
        str[i] -= 32;
        }
    }
    return str;
}

int setup_server(int port, int max_clients)
{
    int my_socket;
    struct sockaddr_in my_socket_addr;

    my_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (my_socket == -1)
        return -1;
    my_socket_addr.sin_family = AF_INET;
    my_socket_addr.sin_addr.s_addr = INADDR_ANY;
    my_socket_addr.sin_port = htons(port);
    if (bind(my_socket,
            (const struct sockaddr *)&my_socket_addr,
            sizeof(my_socket_addr)) == -1)
        return -1;
    if (listen(my_socket, max_clients) == -1)
        return -1;
    return my_socket;
}

int accept_new_connection(int my_socket)
{
    int other_socket;
    socklen_t other_socket_addr_len;
    struct sockaddr_in other_socket_addr;

    other_socket_addr_len = sizeof(other_socket_addr);
    other_socket = accept(
        my_socket, (struct sockaddr *)&other_socket_addr, &other_socket_addr_len);
    if (other_socket == -1)
        return -1;
    return other_socket;
}

void display_command(char *command)
{
    char *tmp = malloc(sizeof(char) * (MAX_COMMAND_LENGTH));

    memset(tmp, 0, MAX_COMMAND_LENGTH);
    strcpy(tmp, command);
    strcat(tmp, "\n");
    str_upper(tmp);
    write(1, tmp, strlen(tmp));
    free(tmp);
}

void handle_command(char *buffer)
{
    int j = 0;
    char **lines = spliter_by_sep(buffer, "\n");
    for (; lines[1] != NULL && lines[j + 1]; j += 1) {
        display_command(lines[j]);
        free(lines[j]);
    }
    if (buffer[strlen(buffer) - 1] == '\n') {
        display_command(lines[j]);
        memset(buffer, 0, MAX_COMMAND_LENGTH);
    } else {
        strcpy(buffer, lines[j]);
    }
    free(lines[j]);
    free(lines);
}


int main(void)
{
    buffer_t test_tkt;
    client_t list[FD_SETSIZE];
    fd_set save_input;
    char *buffer = malloc(sizeof(char) * (MAX_COMMAND_LENGTH + 1));
    char *tmp_buffer = malloc(sizeof(char) * (MAX_COMMAND_LENGTH + 1));
    int status = 0;
    bool running = true;
    memset(tmp_buffer, 0, MAX_COMMAND_LENGTH);
    int my_port = 4244;
    int max_clients = 42;
    int my_socket = setup_server(my_port, max_clients);

    FD_ZERO(&save_input);
    FD_SET(my_socket, &save_input);
    FD_ZERO(&test_tkt.ouput);
    FD_SET(my_socket, &test_tkt.ouput);
    do {
        test_tkt.input = save_input;
        int ready = select(FD_SETSIZE, &test_tkt.input, &test_tkt.ouput, NULL, NULL);
        if (ready == -1) {
            perror("select()");
            return EXIT_FAILURE;
        } else if (ready > 0) {
        for (int i = 0; i < FD_SETSIZE; i += 1) {
            if (FD_ISSET(i, &test_tkt.input)) {
            if (i == my_socket) {
                int client_socket = accept_new_connection(my_socket);
                dprintf(client_socket, "220 Service ready for new user.\r\n");
                FD_SET(client_socket, &save_input);
            } else {
                memset(buffer, 0, MAX_COMMAND_LENGTH);
                status = read(i, buffer, MAX_COMMAND_LENGTH);
                if (status == -1) {
                    perror("read()");
                    return EXIT_FAILURE;
                } else if (status > 0) {
                    strcat(tmp_buffer, buffer);
                    handle_command(tmp_buffer);
                }
            }
            }
        }
        }
    } while (running);
    FD_CLR(0, &test_tkt.input);
    FD_CLR(1, &test_tkt.ouput);
    free(buffer);
    free(tmp_buffer);

    return EXIT_SUCCESS;
}

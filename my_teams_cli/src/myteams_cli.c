/*
** EPITECH PROJECT, 2023
** new_project_folder_file
** File description:
** my_project
*/

#include "myteams_cli.h"

    // {"/send", &handle_send},
    // {"/messages", &handle_messages},
    // {"/subscribe", &handle_subscribe},
    // {"/subscribed", &handle_subscribed},
    // {"/unsubscribe", &handle_unsubscribe},
    // {"/use", &handle_use},
    // {"/create", &handle_create},
    // {"/list", &handle_list},
    // {"/info", &handle_info},

const struct cmd_s CMD_FUNCS[] = {
    {"/help", &handle_help},
    {"/login", &handle_login},
    {"/logout", &handle_logout},
    {"/users", &handle_users},
    {"/user", &handle_user},
    {"NULL", NULL}
};

static void handle_input(char *cmd, user_info_t *user_info, int socketfd)
{
    int i = 0;
    for (i = 0; CMD_FUNCS[i].cmd != NULL; i ++) {
        if (strncmp(cmd, CMD_FUNCS[i].cmd, strlen(CMD_FUNCS[i].cmd)) == 0) {
            CMD_FUNCS[i].func(user_info, socketfd, cmd);
            return;
        }
    }
    printf("Invalid command\n");
}

static int read_client_input(fd_set readfds, int socketfd)
{
    int len = 0;
    char input[MAX_COMMAND_LENGTH];
    user_info_t user_info;

    if (FD_ISSET(STDIN_FILENO, &readfds)) {
        if (fgets(input, MAX_COMMAND_LENGTH, stdin) == NULL) {
            fprintf(stderr, "Error reading input from stdin\n");
            return KO;
        }
        len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
            input[len - 1] = *SPLITTER_STR;
        handle_input(input, &user_info, socketfd);
    }
    return OK;
}

static int check_buffer(char *buffer)
{
    int code = atoi(buffer);

    if (code == 500 || code == 0) {
        if (strncmp(get_msg_after_nb(buffer, 4), "user not found", 14) == 0)
            return OK;
        printf("Error: %s\n", get_msg_after_nb(buffer, 4));
        return KO;
    }
    // if (code == send code) then call /send func from logging_client.h
    return OK;
}

char *read_server_message(int socketfd)
{
    char buffer[BUFSIZ];
    int n_bytes_read = 0;
    int msg_size = 0;

    n_bytes_read = read(socketfd, buffer + msg_size, sizeof(buffer) -
        msg_size - 1);
    if (n_bytes_read <= 0)
        return NULL;
    while (n_bytes_read > 0) {
        msg_size += n_bytes_read;
        if (msg_size > BUFSIZ - 1 || buffer[msg_size - 1] == *SPLITTER_STR)
            break;
        n_bytes_read = read(socketfd, buffer + msg_size, sizeof(buffer) -
            msg_size - 1);
    }
    buffer[msg_size] = '\0';
    if (buffer[msg_size - 1] == *SPLITTER_STR)
        buffer[msg_size - 1] = '\0';
    if (check_buffer(buffer) == KO)
        return NULL;
    return strdup(buffer);
}

static void client_loop(int socketfd)
{
    //int maxfd = 0;
    fd_set readfds;

    FD_ZERO(&readfds);
    while (1) {
        FD_SET(socketfd, &readfds);
        FD_SET(STDIN_FILENO, &readfds);
        //maxfd = (socketfd > STDIN_FILENO) ? socketfd : STDIN_FILENO;
        if (select(socketfd + 1, &readfds, NULL, NULL, NULL) == -1)
            exit(EXIT_FAILURE);
        if (FD_ISSET(socketfd, &readfds)) {
            if (read_server_message(socketfd) == NULL)
                continue;
        }
        if (read_client_input(readfds, socketfd) == KO)
            continue;
    }
}

int connect_to_server(char *ip, char *port)
{
    struct sockaddr_in server_addr;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketfd == -1) {
        fprintf(stderr, "Failed to connect to the server\n");
        close(socketfd);
        return EXIT_FAILURE;
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(port));
    server_addr.sin_addr.s_addr = inet_addr(ip);
    if (connect(socketfd, (struct sockaddr *)&server_addr,
    sizeof(server_addr)) == -1) {
        perror("Error (connect)");
        close(socketfd);
        return EXIT_FAILURE;
    }
    client_loop(socketfd);
    close(socketfd);
    return EXIT_SUCCESS;
}

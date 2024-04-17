/*
** EPITECH PROJECT, 2023
** new_project_folder_file
** File description:
** my_project
*/

#include "myteams_cli.h"

// if (strncmp(input, "/user", 5) == 0)
//     handle_user(&user_info, socketfd, input);

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
    return strdup(buffer);
}

static void handle_input(int socketfd, const char *input)
{
    user_info_t user_info;

    if (strncmp(input, "/help", 5) == 0)
        handle_help(socketfd, input);
    if (strncmp(input, "/login", 6) == 0)
        handle_login(&user_info, socketfd, input);
    if (strncmp(input, "/logout", 7) == 0)
        handle_logout(&user_info, socketfd, input);
    if (strncmp(input, "/users", 6) == 0)
        handle_users(&user_info, socketfd, input);
    if (strncmp(input, "/user", 5) == 0)
        handle_user(&user_info, socketfd, input);
    // if (strncmp(input, "/send", 5) == 0)
    //     handle_send(&user_info, socketfd, input);
    // if (strncmp(input, "/messages", 9) == 0)
    //     handle_messages(&user_info, socketfd, input);
}

static void client_loop(int socketfd)
{
    int maxfd = 0;
    int len = 0;
    fd_set readfds;
    char input[MAX_COMMAND_LENGTH];
    char *server_connect_msg = read_server_message(socketfd);

    if (server_connect_msg == NULL)
        fprintf(stderr, "Error reading message from server\n");
    else {
        printf("server code: %s", server_connect_msg);
        free(server_connect_msg);
    }
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(socketfd, &readfds);
        FD_SET(STDIN_FILENO, &readfds);
        maxfd = (socketfd > STDIN_FILENO) ? socketfd : STDIN_FILENO;
        if (select(maxfd + 1, &readfds, NULL, NULL, NULL) == -1)
            exit(EXIT_FAILURE);
        // if (FD_ISSET(socketfd, &readfds))
        //     handle_socket_input(socketfd);
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            if (fgets(input, MAX_COMMAND_LENGTH, stdin) == NULL) {
                fprintf(stderr, "Error reading input from stdin\n");
                continue;
            }
            len = strlen(input);
            if (len > 0 && input[len - 1] == '\n')
                input[len - 1] = *SPLITTER_STR;
            handle_input(socketfd, input);
        }
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

/*
** EPITECH PROJECT, 2023
** new_project_folder_file
** File description:
** my_project
*/

#include "myteams_cli.h"

char *read_server_message(int socketfd)
{
    char buffer[BUFSIZ];
    int n_bytes_read = 0;
    int msg_size = 0;

    n_bytes_read = read(socketfd, buffer + msg_size, sizeof(buffer) -
        msg_size - 1);
    while (n_bytes_read > 0) {
        msg_size += n_bytes_read;
        if (msg_size > BUFSIZ - 1 || buffer[msg_size - 1] == '\n')
            break;
        n_bytes_read = read(socketfd, buffer + msg_size, sizeof(buffer) -
            msg_size - 1);
    }
    // if (check_return(n_bytes_read, "read") == KO)
    //     return NULL;
    buffer[msg_size] = '\0';
    if (n_bytes_read == 0)
        return NULL;
    return strdup(buffer);
}

// static char *get_uuid(void)  /////////////////////// change to read user_uuid from server
// {
//     uuid_t uuid;
//     char user_uuid[50];

//     uuid_generate(uuid);
//     uuid_unparse(uuid, user_uuid);
//     return strdup(user_uuid);
// }

static void handle_input(int socketfd, const char *input)
{
    if (strncmp(input, "/help", 5) == 0)
        handle_help(socketfd, input);
    if (strncmp(input, "/login", 6) == 0)
        handle_login(socketfd, input);
    if (strncmp(input, "/logout", 7) == 0)
        handle_logout(socketfd, input);
    // if (strncmp(input, "/users", 6) == 0)
    //     handle_users(input);
    // if (strncmp(input, "/user", 5) == 0)
    //     handle_user(input);
    // if (strncmp(input, "/send", 5) == 0)
    //     handle_send(input);
    // if (strncmp(input, "/messages", 9) == 0)
    //     handle_messages(input);
    // if (strncmp(input, "/subscribe", 10) == 0)
    //     handle_subscribe(input);
}

static void server_loop(int socketfd)
{
    char input[MAX_COMMAND_LENGTH];
    char *server_connect_msg = read_server_message(socketfd);

    if (server_connect_msg == NULL)
        fprintf(stderr, "Error reading message from server\n");
    else {
        printf("server code: %s", server_connect_msg);
        free(server_connect_msg);
    }
    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            fprintf(stderr, "Error reading input from stdin\n");
            break;
        }
        handle_input(socketfd, input);
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
    server_loop(socketfd);
    close(socketfd);
    return EXIT_SUCCESS;
}

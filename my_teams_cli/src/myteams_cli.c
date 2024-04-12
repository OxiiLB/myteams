/*
** EPITECH PROJECT, 2023
** new_project_folder_file
** File description:
** my_project
*/

#include "myteams_cli.h"

static char *get_uuid(void)  /////////////////////// change to read user_uuid from server
{
    uuid_t uuid;
    char user_uuid[50];

    uuid_generate(uuid);
    uuid_unparse(uuid, user_uuid);
    return strdup(user_uuid);
}

static void handle_input(const char *input)
{
    char *user_uuid = get_uuid();

    if (strncmp(input, "/help", 5) == 0)
        handle_help();
    if (strncmp(input, "/login", 6) == 0)
        handle_login(user_uuid, input);
    if (strncmp(input, "/logout", 7) == 0)
        handle_logout(user_uuid, input);
    if (strncmp(input, "/users", 6) == 0)
        handle_users(user_uuid, input);
    if (strncmp(input, "/user", 5) == 0)
        handle_user(user_uuid, input);
    if (strncmp(input, "/send", 5) == 0)
        handle_send(user_uuid, input);
    if (strncmp(input, "/messages", 9) == 0)
        handle_messages(user_uuid, input);
    if (strncmp(input, "/subscribe", 10) == 0)
        handle_subscribe(user_uuid, input);
}

static void server_loop(int socketfd)
{
    size_t len;
    char input[MAX_COMMAND_LENGTH];

    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            fprintf(stderr, "Error reading input from stdin\n");
            break;
        }
        len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
            input[len - 1] = '\0';
        handle_input(input);
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

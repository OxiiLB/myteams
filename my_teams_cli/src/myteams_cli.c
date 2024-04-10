/*
** EPITECH PROJECT, 2023
** new_project_folder_file
** File description:
** my_project
*/

#include "myteams_cli.h"

static void handle_cmd(const char *cmd)
{
    if (strncmp(cmd, "/help", 5) == 0)
        display_usage();
}

static void server_loop(int socketfd)
{
    size_t len;
    char cmd[MAX_COMMAND_LENGTH];

    while (1) {
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            fprintf(stderr, "Error reading cmd from stdin\n");
            break;
        }
        len = strlen(cmd);
        if (len > 0 && cmd[len - 1] == '\n')
            cmd[len - 1] = '\0';
        handle_cmd(cmd);
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

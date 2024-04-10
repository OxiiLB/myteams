/*
** EPITECH PROJECT, 2023
** new_project_folder_file
** File description:
** my_project
*/

#include "myteams_cli.h"

#define MAX_COMMAND_LENGTH 1024

static void handle_cmd(int socketfd, const char *cmd){
    if (strncmp(cmd, "/help", 5) == 0)
        display_usage();
}

int connect_to_server(char *ip, char *port)
{
    struct sockaddr_in server_addr;
    char cmd[MAX_COMMAND_LENGTH];
    int socketfd;
    size_t len;

    if (ip == NULL || port == NULL)
        return EXIT_FAILURE;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(port));
    server_addr.sin_addr.s_addr = inet_addr(ip);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        fprintf(stderr, "Failed to connect to the server\n");
        return EXIT_FAILURE;
    }

    if (connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error (connect)");
        close(socketfd);
        return EXIT_FAILURE;
    }

    printf("Connected to server\n"); //////////////////////////////////////////////////////

    while (1) {
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            fprintf(stderr, "Error reading cmd from stdin\n");
            break;
        }
        len = strlen(cmd);
        if (len > 0 && cmd[len - 1] == '\n')
            cmd[len - 1] = '\0';
        handle_cmd(socketfd, cmd);
    }
    close(socketfd);
    return EXIT_SUCCESS;
}

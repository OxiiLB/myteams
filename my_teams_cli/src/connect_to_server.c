/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** connect_to_server
*/


#include "myteams_cli.h"

int connect_to_server(char *ip, int port)
{
    struct sockaddr_in server_addr;
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1) {
        fprintf(stderr, "Failed to connect to the server\n");
        close(socket_fd);
        return KO;
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    if (connect(socket_fd, (struct sockaddr *)&server_addr,
    sizeof(server_addr)) == -1) {
        perror("Error (connect)");
        close(socket_fd);
        return KO;
    }
    return socket_fd;
}

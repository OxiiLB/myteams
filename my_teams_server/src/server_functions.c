/*
** EPITECH PROJECT, 2024
** server_functions
** File description:
** server_functions
*/

#include "myteams_server.h"
#include "../../include/my_macro.h"

int setup_server(ftp_struct_t *ftp_struct, int backlog,
    char const *const *argv)
{
    ftp_struct->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (ftp_struct->sockfd == -1)
        return ERROR;
    ftp_struct->server_addr.sin_family = AF_INET;
    ftp_struct->server_addr.sin_port = htons(atoi(argv[1]));
    ftp_struct->server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(ftp_struct->sockfd, (struct sockaddr *)&ftp_struct->server_addr,
    sizeof(ftp_struct->server_addr)) == -1) {
        free(ftp_struct);
        return ERROR;
    }
    if (listen(ftp_struct->sockfd, backlog) == -1) {
        free(ftp_struct);
        return ERROR;
    }
    return OK;
}

int fd_is_set(ftp_struct_t *ftp_struct, int i)
{
    if (FD_ISSET(i, &ftp_struct->ready_sockets)) {
        if (check_new_connection(ftp_struct, i) == ERROR)
            return ERROR;
        return 0;
    }
    return 0;
}

void set_fds(ftp_struct_t *ftp_struct)
{
    FD_ZERO(&ftp_struct->current_sockets);
    FD_SET(ftp_struct->sockfd, &ftp_struct->current_sockets);
}

int scan_fd(ftp_struct_t *ftp_struct)
{
    for (int i = 0; i < __FD_SETSIZE; i++) {
        if (fd_is_set(ftp_struct, i) == ERROR)
            return ERROR;
    }
    return 0;
}

int read_from_client(ftp_struct_t *ftp_struct)
{
    char buffer[BUFSIZ];
    ssize_t n = read(ftp_struct->client_sockfd, buffer, sizeof(buffer) - 1);

    if (n == 0)
        return -1;
    if (n == -1)
        return ERROR;
    buffer[n] = '\0';
    if (buffer[n - 1] == '\n')
        buffer[n - 1] = '\0';
    if (buffer[n - 2] == '\r')
        buffer[n - 2] = '\0';
    ftp_struct->actual_command = strdup(buffer);
    return OK;
}

/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** myteams_server
*/

#ifndef MYTEAMS_SERVER_H_
    #define MYTEAMS_SERVER_H_

    #include "../../include/myteams.h"
    #include <sys/select.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <limits.h>
    #include <unistd.h>
    #include <string.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <dirent.h>
    #include <stdbool.h>

typedef struct client_s {
    char *current_path;
    char *username;
    bool is_logged;
    bool is_connected;
    bool username_entered;
} client_t;

typedef struct ftp_struct_s {
    int sockfd;
    int client_sockfd;
    fd_set current_sockets;
    fd_set ready_sockets;
    struct sockaddr_in server_addr;
    fd_set exceptfds;
    fd_set writefds;
    struct client_s clients[__FD_SETSIZE];
    char *home;
    char *actual_command;
}ftp_struct_t;

int myteams_server(int argc, char const *const *argv);
int init_server(char const *const *argv);
int fd_is_set(ftp_struct_t *ftp_struct, int i);
void set_fds(ftp_struct_t *ftp_struct);
int scan_fd(ftp_struct_t *ftp_struct);
int read_from_client(ftp_struct_t *ftp_struct);
int check_new_connection(ftp_struct_t *ftp_struct, int i);
int setup_server(ftp_struct_t *ftp_struct, int backlog,
    char const *const *argv);
#endif /* !MYTEAMS_SERVER_H_ */

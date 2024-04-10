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

typedef struct command_s {
    char *command;
    // void (*func)(ftp_struct_t *ftp_struct, int i);
} command_t;

typedef struct message_s {
    char *text;
    char *sender_uuid;
    char *receiver_uuid;
} message_t;

typedef struct linked_message_s {
    struct linked_message_s *next;
    message_t *message;
} linked_message_t;

typedef struct user_s {
    char *username;
    char *uuid;
} user_t;

typedef struct linked_user_s {
    struct linked_user_s *next;
    user_t *user;
} linked_user_t;

typedef struct thread_s {
    struct linked_message_s *messages;
    char *thread_name;
    char *thread_desc;
    char *thread_uuid;
} thread_t;

typedef struct linked_thread_s {
    struct linked_thread_s *next;
    thread_t *thread;
} linked_thread_t;

typedef struct channel_s {
    struct linked_thread_s *threads;
    char *channel_name;
    char *channel_desc;
    char *channel_uuid;
} channel_t;

typedef struct linked_channel_s {
    struct linked_channel_s *next;
    channel_t *channel;
} linked_channel_t;

typedef struct team_s {
    struct linked_channel_s *channels;
    char *team_name;
    char *team_desc;
    char *team_uuid;
} team_t;

typedef struct linked_team_s {
    struct linked_team_s *next;
    team_t *team;
} linked_team_t;

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

linked_team_t *add_team(linked_team_t *head, team_t *data);
linked_channel_t *add_channel(linked_channel_t *head, channel_t *data);
linked_thread_t *add_thread(linked_thread_t *head, thread_t *data);
linked_message_t *add_message(linked_message_t *head, message_t *data);

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

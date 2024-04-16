/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** myteams_server
*/

#ifndef MYTEAMS_SERVER_H_
    #define MYTEAMS_SERVER_H_

    #include "../../include/myteams.h"
    #include "../../libs/myteams/logging_server.h"
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
    #include <sys/queue.h>
    #define SAVE_FILE "save.txt"
    #define USERS_CHAR 'u'
    #define MP_CHAR 'q'
    #define TEAMS_CHAR 't'
    #define CHANNELS_CHAR 'c'
    #define THREADS_CHAR 'h'
    #define COMMENTS_CHAR 'k'

typedef struct command_s {
    char *command;
    // void (*func)(my_teams_server_struct_t *my_teams_server_struct, int i);
} command_t;

typedef struct user_s {
    char *username;
    char *uuid;
    LIST_ENTRY(user_s) next;
} user_t;

struct userhead {
    struct user_s *lh_first;
};

typedef struct message_s {
    char *text;
    char *sender_uuid;
    char *receiver_uuid;
    char *message_uuid;
    LIST_ENTRY(message_s) next;
} message_t;

struct messagehead {
    struct message_s *lh_first;
};

typedef struct thread_s {
    char *thread_name;
    char *thread_desc;
    char *thread_uuid;
    struct messagehead messages_head;
    LIST_ENTRY(thread_s) next;
} thread_t;

struct threadhead {
    struct thread_s *lh_first;
};

typedef struct channel_s {
    char *channel_name;
    char *channel_desc;
    char *channel_uuid;
    struct threadhead threads_head;
    LIST_ENTRY(channel_s) next;
} channel_t;

struct channelhead {
    struct channel_s *lh_first;
};

typedef struct team_s {
    char *team_name;
    char *team_desc;
    char *team_uuid;
    struct channelhead channels_head;
    LIST_ENTRY(team_s) next;
} team_t;

struct teamhead {
    struct team_s *lh_first;
};

typedef struct buffer_s {
    char *input_buffer;
    char *output_buffer;
} buffer_t;

typedef struct fd_s {
    fd_set input;
    fd_set save_input;
    fd_set ouput;
} fd_t;

typedef struct client_s {
    bool is_logged;
    buffer_t buffer;
    user_t *user;
    struct sockaddr_in other_socket_addr;
} client_t;

typedef struct my_teams_server_struct_s {
    int my_socket;
    int actual_sockfd;
    fd_t fd;
    struct sockaddr_in server_addr;
    struct userhead all_user;
    struct teamhead all_teams;
    struct client_s clients[FD_SETSIZE];
} my_teams_server_struct_t;

// Linked list functions
void free_messages(struct messagehead *head);
void free_users(struct userhead *head);
void free_threads(struct threadhead *head);
void free_channels(struct channelhead *head);
void free_teams(struct teamhead *head);

int myteams_server(int port);
int init_server(my_teams_server_struct_t *my_teams_server_struct, int port);
void init_buffer_struct(buffer_t *buffer, int *my_socket);
int scan_fd(my_teams_server_struct_t *my_teams_server_struct);
void handle_client(my_teams_server_struct_t *my_teams_server_struct);
int setup_server(int port, int max_clients);
void handle_client(my_teams_server_struct_t *my_teams_server_struct);
char **splitter(char const *const str, char *separator);
char *generate_random_uuid(void);
int init_clients(my_teams_server_struct_t *my_teams_server_struct);
int accept_new_connection(int my_socket);
int setup_server(int port, int max_clients);
int save_info_to_file(my_teams_server_struct_t *my_teams_server_struct);

// COMMANDS

void help_command(my_teams_server_struct_t *my_teams_server_struct,
    char *command);
void login_command(my_teams_server_struct_t *my_teams_server_struct,
    char *command);



#endif /* !MYTEAMS_SERVER_H_ */

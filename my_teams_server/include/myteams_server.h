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
    // void (*func)(my_teams_server_struct_t *my_teams_server_struct, int i);
} command_t;

typedef struct message_s {
    char *text;
    char *sender_uuid;
    char *receiver_uuid;
} message_t;

typedef struct linked_message_s {
    struct linked_message_s *next;
    message_t *message;
    char *time;
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
    char *username;
    bool is_logged;
    bool is_connected;
    buffer_t buffer;
    struct sockaddr_in other_socket_addr;
} client_t;

typedef struct my_teams_server_struct_s {
    int my_socket;
    fd_set current_sockets;
    fd_t fd;
    struct sockaddr_in server_addr;
    struct client_s clients[FD_SETSIZE];
    char *actual_command;
} my_teams_server_struct_t;

linked_team_t *add_team(linked_team_t *head, team_t *data);
linked_channel_t *add_channel(linked_channel_t *head, channel_t *data);
linked_thread_t *add_thread(linked_thread_t *head, thread_t *data);
linked_message_t *add_message(linked_message_t *head, message_t *data);

int myteams_server(int port);
int init_server(my_teams_server_struct_t *my_teams_server_struct, int port);
void init_buffer_struct(buffer_t *buffer, int *my_socket);
int scan_fd(my_teams_server_struct_t *my_teams_server_struct);
void handle_client(my_teams_server_struct_t *my_teams_server_struct,
    int client_fd);
int check_connection(my_teams_server_struct_t *my_teams_server_struct,
    int i);
int setup_server(int port, int max_clients);
void handle_client(my_teams_server_struct_t *my_teams_server_struct,
    int client_fd);
char **splitter(char const *const str, char *separator);
char *generate_random_uuid(void);

#endif /* !MYTEAMS_SERVER_H_ */

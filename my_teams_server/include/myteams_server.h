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
    #include <time.h>
    #define SAVE_FILE "myteams_save.txt"
    #define USERS_CHAR 'u'
    #define PRIVATE_MESSAGE_CHAR 'm'
    #define TEAMS_CHAR 't'
    #define CHANNELS_CHAR 'c'
    #define THREADS_CHAR 'h'
    #define COMMENTS_CHAR 'k'
    #define SUBSCRIBE_CHAR 's'

typedef struct subscribed_s {
    char team_uuid[MAX_UUID_LENGTH];
    char user_uuid[MAX_UUID_LENGTH];
    TAILQ_ENTRY(subscribed_s) next;
} subscribed_t;

struct subscribedhead {
    struct subscribed_s *tqh_first;
    struct subscribed_s **tqh_last;
};

typedef struct user_s {
    char username[MAX_NAME_LENGTH];
    char uuid[MAX_UUID_LENGTH];
    char team_context[MAX_UUID_LENGTH];
    char channel_context[MAX_UUID_LENGTH];
    char thread_context[MAX_UUID_LENGTH];
    int nb_clients;
    TAILQ_ENTRY(user_s) next;
} user_t;

struct userhead {
    struct user_s *tqh_first;
    struct user_s **tqh_last;
};

typedef struct message_s {
    char text[MAX_BODY_LENGTH];
    char sender_uuid[MAX_UUID_LENGTH];
    char receiver_uuid[MAX_UUID_LENGTH];
    char message_uuid[MAX_UUID_LENGTH];
    time_t timestamp;
    TAILQ_ENTRY(message_s) next;
} message_t;

struct messagehead {
    struct message_s *tqh_first;
    struct message_s **tqh_last;
};

typedef struct reply_s {
    char text[MAX_BODY_LENGTH];
    char reply_uuid[MAX_UUID_LENGTH];
    char sender_uuid[MAX_UUID_LENGTH];
    char thread_uuid[MAX_UUID_LENGTH];
    time_t timestamp;
    TAILQ_ENTRY(reply_s) next;
} reply_t;

struct replyhead {
    struct reply_s *tqh_first;
    struct reply_s **tqh_last;
};


typedef struct thread_s {
    char title[MAX_NAME_LENGTH];
    char body[MAX_DESCRIPTION_LENGTH];
    char thread_uuid[MAX_UUID_LENGTH];
    char channel_uuid[MAX_UUID_LENGTH];
    time_t timestamp;
    struct replyhead replys_head;
    TAILQ_ENTRY(thread_s) next;
} thread_t;

struct threadhead {
    struct thread_s *tqh_first;
    struct thread_s **tqh_last;
};

typedef struct channel_s {
    char name[MAX_NAME_LENGTH];
    char desc[MAX_DESCRIPTION_LENGTH];
    char channel_uuid[MAX_UUID_LENGTH];
    char team_uuid[MAX_UUID_LENGTH];
    struct threadhead threads_head;
    TAILQ_ENTRY(channel_s) next;
} channel_t;

struct channelhead {
    struct channel_s *tqh_first;
    struct channel_s **tqh_last;
};

typedef struct team_s {
    char name[MAX_NAME_LENGTH];
    char desc[MAX_DESCRIPTION_LENGTH];
    char team_uuid[MAX_UUID_LENGTH];
    struct channelhead channels_head;
    TAILQ_ENTRY(team_s) next;
} team_t;

struct teamhead {
    struct team_s *tqh_first;
    struct team_s **tqh_last;
};

typedef struct buffer_s {
    char input_buffer[MAX_COMMAND_LENGTH];
    char output_buffer[MAX_COMMAND_LENGTH];
} buffer_t;

typedef struct fd_s {
    fd_set input;
    fd_set save_input;
    fd_set ouput;
} fd_t;

typedef struct client_s {
    buffer_t buffer;
    user_t *user;
    struct sockaddr_in other_socket_addr;
} client_t;

typedef struct teams_server_s {
    int my_socket;
    int actual_sockfd;
    fd_t fd;
    struct sockaddr_in server_addr;
    struct userhead all_user;
    struct messagehead private_messages;
    struct subscribedhead subscribed_teams_users;
    struct teamhead all_teams;
    struct client_s clients[FD_SETSIZE];
} teams_server_t;

// Linked list functions
void free_messages(struct messagehead *head);
void free_users(struct userhead *head);
void free_threads(struct threadhead *head);
void free_channels(struct channelhead *head);
void free_teams(struct teamhead *head);

// Server functions
void free_array(char **array);
int myteams_server(int port);
int init_server(teams_server_t *teams_server, int port);
void init_buffer_struct(buffer_t *buffer, int *my_socket);
int scan_fd(teams_server_t *teams_server);
void handle_client(teams_server_t *teams_server);
int setup_server(int port, int max_clients);
void handle_client(teams_server_t *teams_server);
char **splitter(char const *const str, char *separator);
void generate_random_uuid(char *buffer);
int accept_new_connection(int my_socket);
int setup_server(int port, int max_clients);
int save_info_to_file(teams_server_t *teams_server);
int read_info_from_save_file(teams_server_t *teams_server);
thread_t *search_in_threads(struct threadhead *thread_head, char *uuid);
channel_t *search_in_channels(struct channelhead *channel_head, char *uuid);
team_t *search_in_teams(struct teamhead *team_head, char *uuid);
int get_len_char_tab(char **command);
int find_all_context(teams_server_t *teams_server, team_t **team,
    channel_t **channel, thread_t **thread);
time_t get_actual_time(void);
int count_str_char(char *str, char c);
user_t *get_user_by_uuid(struct userhead *user_head, char *uuid);
team_t *get_team_by_uuid(struct teamhead *teams_head, char *uuid);

typedef struct all_context_s {
    team_t *team;
    channel_t *channel;
    thread_t *thread;
} all_context_t;

// COMMANDS
typedef struct command_s {
    char *command;
    void (*func)(teams_server_t *teams_server, char *command);
} command_t;

void help_command(teams_server_t *teams_server, char *command);
void login_command(teams_server_t *teams_server, char *command);
void logout_command(teams_server_t *teams_server, char *command);
void users_command(teams_server_t *teams_server, char *command);
void user_command(teams_server_t *teams_server, char *command);
void send_command(teams_server_t *teams_server, char *command);
void messages_command(teams_server_t *teams_server, char *command);
void subscribe_command(teams_server_t *teams_server, char *command);
void subscribed_command(teams_server_t *teams_server, char *command);
void unsubscribe_command(teams_server_t *teams_server, char *command);
void use_command(teams_server_t *teams_server, char *command);
void create_command(teams_server_t *teams_server, char *command);
void list_command(teams_server_t *teams_server, char *command);
void info_command(teams_server_t *teams_server, char *command);


int add_team(teams_server_t *teams_server, char **command_line,
    int nb_args, all_context_t *all_context);
int add_channel(teams_server_t *teams_server, char **command_line,
    int nb_args, all_context_t *all_context);
int add_thread(teams_server_t *teams_server, char **command_line,
    int nb_args, all_context_t *all_context);

#endif /* !MYTEAMS_SERVER_H_ */

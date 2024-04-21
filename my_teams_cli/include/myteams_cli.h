/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** myteams_cli
*/

#ifndef MYTEAMS_CLI_H_
    #define MYTEAMS_CLI_H_

    #include <sys/socket.h>
    #include <sys/select.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/types.h>
    #include <uuid/uuid.h>
    #include <stdbool.h>
    #include <signal.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <string.h>
    #include <netdb.h>
    #include <errno.h>
    #include <stdio.h>
    #include <time.h>
    #include "../../libs/myteams/logging_client.h"
    #include "../../include/myteams.h"

    #define MAX_COMMAND_LENGTH 1024

typedef struct cmd_s {
    const char *cmd;
    void (*func)(char **info, int socketfd);
} cmd_t;

typedef struct create_s {
    const char *context;
    void (*func)(char **info);
} create_t;

typedef struct list_s {
    const char *context;
    void (*func)(char **info);
} list_t;

typedef struct info_s {
    const char *context;
    void (*func)(char **info);
} info_t;

void display_usage(void);

int myteams_cli(char *ip, int port);
int connect_to_server(char *ip, int port);
int read_server_message(bool *running, int socketfd);
int do_error_handling(const char *input);
int check_nb_args(const char *input, int should_have);
void handle_ctrl_c(int socketfd);

// basic commands
void handle_help(char **info, int socketfd);
void handle_login(char **info, int socketfd);
void handle_logout(char **info, int socketfd);
void handle_users(char **info, int socketfd);
void handle_user(char **info, int socketfd);
void handle_send(char **info, int socketfd);
void handle_messages(char **info, int socketfd);
void handle_subscribe(char **info, int socketfd);
void handle_subscribed(char **info, int socketfd);
void handle_unsubscribe(char **info, int socketfd);
void handle_use(char **info, int socketfd);
void handle_create(char **info, int socketfd);
void handle_list(char **info, int socketfd);
void handle_info(char **info, int socketfd);

// create commands
void create_team(char **info);
void create_channel(char **info);
void create_thread(char **info);
void create_reply(char **info);

// list commands
void list_teams(char **info);
void list_channels(char **info);
void list_threads(char **info);
void list_replies(char **info);

// info commands
void info_user(char **info);
void info_team(char **info);
void info_channel(char **info);
void info_thread(char **info);

// tools
char *add_v_to_str(const char *input);
char *get_msg_after_nb(char const *const str, int nb);
char *get_msg_up_to_char(char *str, char c, int i);
void do_multiple_frees(char *one, char *two, char *three, char *four);
char **splitter(char const *const str, char *separator);
void print_2d_array(char **array, int i);
void free_2d_array(char **array);
int get_arg_len(const char *input, int i);

#endif /* !MYTEAMS_CLI_H_ */

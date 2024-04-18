/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** myteams_cli
*/

#ifndef MYTEAMS_CLI_H_
    #define MYTEAMS_CLI_H_

    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <sys/select.h>
    #include <netinet/in.h>
    #include <netdb.h>
    #include <errno.h>
    #include <stdio.h>
    #include <uuid/uuid.h>
    #include "../../libs/myteams/logging_client.h"
    #include "../../include/myteams.h"

    #define MAX_COMMAND_LENGTH 1024

typedef struct cmd_s {
    const char *cmd;
    void (*func)(char **info);
} cmd_t;

void display_usage(void);

int connect_to_server(char *ip, char *port);

int read_server_message(int socketfd);

int check_nb_args(const char *input, int should_have);
int check_quotes(const char *input, int input_len, int cmd_len);
int do_error_handling(const char *input, int a_nb, int q_len, int q_nb);

void handle_help(char **info);
void handle_login(char **info);
void handle_logout(char **info);
void handle_users(char **info);
void handle_user(char **info);
void handle_send(char **info);

char *add_v_to_str(const char *input);
char *get_msg_after_nb(char *str, int nb);
char *get_msg_up_to_char(char *str, char c, int i);
void do_multiple_frees(char *one, char *two, char *three, char *four);
char **splitter(char const *const str, char *separator);
void print_2d_array(char **array, int i);
void free_2d_array(char **array);

#endif /* !MYTEAMS_CLI_H_ */

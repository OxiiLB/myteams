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
    #include <netinet/in.h>
    #include <netdb.h>
    #include <errno.h>
    #include <stdio.h>
    #include <uuid/uuid.h>
    #include "../../logging_client.h"
    #include "../../include/myteams.h"

    #define MAX_COMMAND_LENGTH 1024

typedef struct user_info_t {
    char *user_name;
    char *user_uuid;
} user_info_t;

void display_usage(void);

int connect_to_server(char *ip, char *port);

char *read_server_message(int socketfd);

int check_nb_args(const char *input, int should_have);
int check_quotes(const char *input, int input_len, int cmd_len);
int do_error_handling(const char *input, int a_nb, int q_len, int q_nb);

void handle_help(int socketfd, const char *input);
void handle_login(user_info_t *user_info, int socketfd, const char *input);
void handle_logout(user_info_t *user_info, int socketfd, const char *input);
void handle_users(user_info_t *user_info, int socketfd, const char *input);
void handle_user(user_info_t *user_info, int socketfd, const char *input);
void handle_send(user_info_t *user_info, int socketfd, const char *input);
void handle_messages(user_info_t *user_info, int socketfd, const char *input);

char *get_msg_after_status(char *server_msg);
char *get_msg(const char *input, int before_msg);
void do_multiple_frees(char *one, char *two, char *three, char *four);

#endif /* !MYTEAMS_CLI_H_ */

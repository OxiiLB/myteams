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
    #include <netinet/in.h>
    #include <netdb.h>
    #include <errno.h>
    #include <stdio.h>
    #include <uuid/uuid.h>
    #include "../../include/myteams.h"

    #define MAX_COMMAND_LENGTH 1024

char *read_server_message(int socketfd);

void display_usage(void);

int connect_to_server(char *ip, char *port);

void handle_help(int socketfd, const char *input);

void handle_login(int socketfd, const char *input);

void handle_logout(int socketfd, const char *input);

void handle_users(int socketfd, const char *input);

void handle_user(int socketfd, const char *input);

#endif /* !MYTEAMS_CLI_H_ */

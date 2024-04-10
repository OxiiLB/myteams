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
    #include "../../include/myteams.h"

    #define MAX_COMMAND_LENGTH 1024

void display_usage(void);

int connect_to_server(char *ip, char *port);

#endif /* !MYTEAMS_CLI_H_ */

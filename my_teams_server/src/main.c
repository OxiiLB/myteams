/*
** EPITECH PROJECT, 2023
** my_scripts
** File description:
** main
*/

#include "myteams_server.h"
#include "../../include/my_macro.h"

bool is_valid_port(const char *port)
{
    int port_num = 0;

    if (port == NULL || *port == '\0')
        return false;
    for (int i = 0; port[i] != '\0'; i++) {
        if (port[i] < '0' || port[i] > '9')
            return false;
    }
    port_num = atoi(port);
    if (port_num >= 0 && port_num <= 65535)
        return true;
    return false;
}

int main(int const argc, char const *const *argv)
{
    if (argc != 2)
        return ERROR;
    if (strcmp(argv[1], "-help") == 0) {
        printf("USAGE: ./myteams_server port\n\n\
        port is the port number on which the server socket listens\n");
        return OK;
    }
    if (!is_valid_port(argv[1])) {
        printf("Invalid port number\n");
        return ERROR;
    }
    return myteams_server(argc, argv);
}


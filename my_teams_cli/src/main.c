/*
** EPITECH PROJECT, 2023
** my_scripts
** File description:
** main
*/

#include "myteams_cli.h"

int check_input(char *ip, char *port)
{
    if (ip == NULL || port == NULL)
        return -1;
    for (int i = 0; ip[i] != '\0'; i++) {
        if (ip[i] < '0' || ip[i] > '9' || ip[i] != '.') {
            perror("Error: ip is invalid\n");
            return -1;
        }
    }
    for (int i = 0; port[i] != '\0'; i++) {
        if (port[i] < '0' || port[i] > '9') {
            perror("Error: port must be a number\n");
            return -1;
        }
    }
    return 0;
}

void display_usage(void)
{
    printf("USAGE: ./myteams_cli ip port\n\tip\tis the server ip"
        " address on which the server socket listens\n\tport\t is"
        " the port number on which the server socket listens\n");
}

int main(int const argc, char *argv[])
{
    if (argc < 1 || argc > 2)
        return 84;
    if (argc == 1 && strcmp(argv[1], "-help") == 0) {
        display_usage();
        return 84;
    }
    if (checkInput(argv[1], argv[2]) == -1)
        return 84;
    if (myteams_cli(argc, argv) == -1)
        return 84;
    return 0;
}

/*
** EPITECH PROJECT, 2024
** my_scripts
** File description:
** main
*/

#include "myteams_cli.h"

static int check_input(char *ip, char *port)
{
    if (ip == NULL || port == NULL)
        return KO;
    for (int i = 0; ip[i] != '\0'; i++) {
        if ((ip[i] < '0' || ip[i] > '9') && ip[i] != '.') {
            write(2, "Error: ip is invalid\n", 21);
            return KO;
        }
    }
    for (int i = 0; port[i] != '\0'; i++) {
        if (port[i] < '0' || port[i] > '9') {
            write(2, "Error: port must be a number\n", 29);
            return KO;
        }
    }
    return OK;
}

void display_usage(void)
{
    printf("USAGE: ./myteams_cli ip port\n\tip\tis the server ip"
        " address on which the server socket listens\n\tport\t is"
        " the port number on which the server socket listens\n");
}

int main(int const argc, char *argv[])
{
    if (argc < 2 || argc > 3)
        return EXIT_FAILURE;
    if (argc == 2)
        if (strcmp(argv[1], "-help") == 0) {
            display_usage();
        return EXIT_FAILURE;
    }
    if (check_input(argv[1], argv[2]) == KO)
        return EXIT_FAILURE;
    if (myteams_cli(argv[1], atoi(argv[2])) == KO)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

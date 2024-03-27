/*
** EPITECH PROJECT, 2023
** my_scripts
** File description:
** main
*/

#include "myteams_server.h"
#include "../../include/my_macro.h"

int main(int const argc, char const *const *argv)
{
    if (argc != 2)
        return ERROR;
    if (strcmp(argv[1], "-help") == 0) {
        printf("USAGE: ./myteams_server port\n\n\
       port  is the port number on which the server socket listens\n");
        return OK;
    }
    return myteams_server(argc, argv);
}

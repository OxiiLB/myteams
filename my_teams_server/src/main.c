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
    return myteams_server(argc, argv);
}

/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** save_info_to_file
*/

#include "myteams_server.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int save_info_to_file(my_teams_server_struct_t *my_teams_server_struct)
{
    int file = open(SAVE_FILE, O_CREAT | O_TRUNC | O_WRONLY | O_APPEND, 00777);
    if (file == -1)
        return ERROR;
    // for (user_t *user = my_teams_server_struct->users_head; user != NULL;
    //     user = user->next.le_next) {
    //     write(file, &USERS_CHAR, 1);
    //     write(file, user, sizeof(user->username) + sizeof(user->uuid));
    // }
    fclose(file);
    return OK;
}

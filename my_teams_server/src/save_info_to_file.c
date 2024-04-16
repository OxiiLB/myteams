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
    user_t *user1;

    if (file == -1)
        return ERROR;
    if (LIST_EMPTY(&my_teams_server_struct->all_user) == 0) {
        LIST_FOREACH(user1, &my_teams_server_struct->all_user, next){
            write(file, USERS_CHAR, sizeof(USERS_CHAR));
            write(file, user1, sizeof(user1->username) + sizeof(user1->uuid)
            + sizeof(user1->next));
        }
    }
    close(file);
    return OK;
}

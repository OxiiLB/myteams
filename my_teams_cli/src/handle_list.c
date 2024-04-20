/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_create
*/

#include "myteams_cli.h"

void handle_list(char **info, int socketfd)
{
    char *team_uuid = NULL;
    char *team_name = NULL;
    char *team_desc = NULL;


    for (int i = 2; info[i] != NULL; i++) {
        team_uuid = get_msg_up_to_char(info[i], *SPLIT_LINE, 0);
        team_name = get_msg_after_nb(info[i], (int)strlen(team_uuid) + 1);
        team_desc = get_msg_after_nb(info[i], (int)strlen(team_uuid) +
        (int)strlen(team_name) + 2);
        client_print_teams(team_uuid, team_name, team_desc);
        do_multiple_frees(team_uuid, team_name, team_desc, NULL);
    }
    return;
}

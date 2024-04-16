/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_cmds_2
*/

#include "myteams_cli.h"

void handle_send(user_info_t *user_info, int socketfd, const char *input)
{
    int j = 0;
    int before_msg = 0;
    char *s_uuid = malloc(strlen(input) - 5);

    for (int i = 8; input[i] != '"'; i++) {
        s_uuid[j] = input[i];
        j++;
    }
    s_uuid[j] = '\0';
    if (do_error_handling(input, 2, 8 + strlen(s_uuid), 5) == KO) {
        free(s_uuid);
        return;
    }
    before_msg = (9 + ((int)strlen(s_uuid)));
    if (check_quotes(input, strlen(input),
    strlen(get_msg(input, before_msg))) == KO) {
        free(s_uuid);
        return;
    }
    client_event_private_message_received(s_uuid, get_msg(input, before_msg));
}

void handle_messages(user_info_t *user_info, int socketfd, const char *input)
{
    int j = 0;
    char *given_uuid = malloc(strlen(input) - 9);

    if (check_nb_args(input, 1) == KO)
        return;
    if (check_quotes(input, strlen(input), 9) == KO) {
        write(1, "Error: quotes\n", 15);
        free(given_uuid);
        return;
    }
    for (int i = 10; i < ((int)strlen(input)); i++) {
        given_uuid[j] = input[i];
        j++;
    }
    given_uuid[j] = '\0';
    free(given_uuid);
}

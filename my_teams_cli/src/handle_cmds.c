/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_cmds
*/

#include "myteams_cli.h"

void handle_help(user_info_t *user_info, int socketfd, const char *input)
{  
    printf("input: %s\n", input); //////////////////////////////////
    (void)user_info;
    char *server_msg = NULL;

    if (check_nb_args(input, 0) == KO)
        return;
    if (write(socketfd, add_v_to_str(input), strlen(input) + 2) == -1) {
        perror("write");
        exit(84);
    }
    server_msg = read_server_message(socketfd);
    if (server_msg == NULL)
        return;
    printf("%s\n", get_msg_after_nb(server_msg, 4));
    free(server_msg);
}

void handle_login(user_info_t *user_info, int socketfd, const char *input)
{
    char *server_msg = NULL;
    char *user_name = NULL;

    if (do_error_handling(input, 1, strlen(input), 6) == KO) {
        free(user_name);
        return;
    }
    if (write(socketfd, add_v_to_str(input), strlen(input) + 2) == -1)
        exit(84);
    server_msg = read_server_message(socketfd);
    if (server_msg == NULL)
        return;
    user_name = get_msg_after_nb(server_msg, 8);
    user_info->user_name = strdup(user_name);
    user_info->user_uuid = strdup(server_msg);
    client_event_logged_in(user_info->user_uuid, user_info->user_name);
}

void handle_logout(user_info_t *user_info, int socketfd, const char *input)
{
    if (check_nb_args(input, 0) == KO)
        return;
    if (write(socketfd, add_v_to_str(input), strlen(input) + 2) == -1) {
        perror("write");
        exit(84);
    }
    client_event_logged_out(user_info->user_uuid, user_info->user_name);
}

void handle_users(user_info_t *user_info, int socketfd, const char *input)
{
    int user_status = 0;
    char *server_msg = NULL;
    if (check_nb_args(input, 0) == KO)
        return;
    if (write(socketfd, add_v_to_str(input), strlen(input) + 2) == -1)
        exit(84);
    server_msg = read_server_message(socketfd);
    if (server_msg == NULL)
        return;
    user_status = atoi(get_msg_after_nb(server_msg, 4));
    printf("%s", get_msg_after_nb(server_msg, 5));
    client_print_users(user_info->user_uuid, user_info->user_name,
    user_status);
    free(server_msg);
}

void handle_user(user_info_t *user_info, int socketfd, const char *input)
{
    int user_status = 0;
    char *server_msg = NULL;
    char *given_uuid = NULL;

    if (do_error_handling(input, 1, strlen(input), 5) == KO)
        return;
    given_uuid = get_msg_after_nb(input, 5);
    if (write(socketfd, add_v_to_str(input), strlen(input) + 2) == -1)
        exit(84);
    server_msg = read_server_message(socketfd);
    if (server_msg == NULL)
        return;
    if (atoi(server_msg) == 500) {
        client_error_unknown_user(given_uuid);
        free(given_uuid);
        return;
    }
    user_status = atoi(get_msg_after_nb(server_msg, 4));
    printf("%s", get_msg_after_nb(server_msg, 5));
    client_print_user(given_uuid, user_info->user_name,
    user_status);
    free(given_uuid);
}

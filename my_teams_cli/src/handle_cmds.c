/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_cmds
*/

#include "myteams_cli.h"

void handle_help(int socketfd, const char *input)
{
    char *server_msg = NULL;

    if (check_nb_args(input, 0) == KO)
        return;
    if (write(socketfd, input, strlen(input)) == -1) {
        perror("write");
        exit(84);
    }
    server_msg = read_server_message(socketfd);
    if (server_msg == NULL) {
        write(1, "Error: server message is NULL\n", 31);
        return;
    }
    printf("%s\n", server_msg);
    free(server_msg);
}

void handle_login(user_info_t *user_info, int socketfd, const char *input)
{
    int j = 0;
    char *server_msg = NULL;
    char *user_name = malloc(strlen(input) - 6);

    if (do_error_handling(input, 1, strlen(input), 6) == KO) {
        free(user_name);
        return;
    }
    if (write(socketfd, input, strlen(input)) == -1)
        exit(84);
    server_msg = read_server_message(socketfd);
    for (int i = 8; i < ((int)strlen(input) - 2); i++) {
        user_name[j] = input[i];
        j++;
    }
    user_name[j] = '\0';
    user_info->user_name = strdup(user_name);
    user_info->user_uuid = strdup(server_msg);
    client_event_logged_in(user_info->user_uuid, user_info->user_name);
    do_multiple_frees(user_name, server_msg, NULL, NULL);
}

void handle_logout(user_info_t *user_info, int socketfd, const char *input)
{
    if (check_nb_args(input, 0) == KO)
        return;
    if (write(socketfd, input, strlen(input)) == -1) {
        perror("write");
        exit(84);
    }
    client_event_logged_out(user_info->user_uuid, user_info->user_name);
}

void handle_users(user_info_t *user_info, int socketfd, const char *input)
{
    int user_status = 0;
    char *server_msg = NULL;

    printf("input: %s\n", input);
    if (write(socketfd, input, strlen(input)) == -1) {
        perror("write");
        exit(84);
    }
    if (check_nb_args(input, 0) == KO)
        return;
    server_msg = read_server_message(socketfd);
    if (server_msg == NULL) {
        write(1, "Error: server message is NULL\n", 31);
        return;
    }
    user_status = (server_msg[0] - '0');
    printf("%s", get_msg_after_status(server_msg));
    client_print_users(user_info->user_uuid, user_info->user_name,
        user_status);
    free(server_msg);
}

// void handle_user(user_info_t *user_info, int socketfd, const char *input)
// {
//     int j = 0;
//     int user_status = 0;
//     char *server_msg = NULL;
//     char *given_uuid = malloc(strlen(input) - 5);

//     if (do_error_handling(input, 1, strlen(input), 5) == KO) {
//         free(given_uuid);
//         return;
//     }
//     for (int i = 8; i < ((int)strlen(input) - 1); i++) {
//         given_uuid[j] = input[i];
//         j++;
//     }
//     given_uuid[j] = '\0';
//     if (strcmp(given_uuid, user_info->user_uuid) != 0) {
//         client_error_unknown_user(given_uuid);
//         free(given_uuid);
//         return;
//     }
//     write(socketfd, input, strlen(input));
//     server_msg = read_server_message(socketfd);
//     user_status = atoi(server_msg[0]);
//     printf("%s", get_msg_after_status(server_msg));
//     client_print_user(user_info->user_uuid, user_info->user_name,
//        user_status);
//     free(given_uuid);
// }

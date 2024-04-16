/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_cmds
*/

#include "myteams_cli.h"

// For the functions that return int, ask the pedagos what to do with that !

static char *get_message(char *input, int before_msg)
{
    int j = 0;
    char message_body[strlen(input) - before_msg];

    for (int i = before_msg; i < ((int)strlen(input)); i++) {
        message_body[j] = input[i];
        j++;
    }
    message_body[j] = '\0';
    return strdup(message_body);
}

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
    if (server_msg == NULL)
        return;
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
    char *server_msg = NULL;

    if (check_nb_args(input, 0) == KO)
        return;
    server_msg = read_server_message(socketfd);
    if (server_msg == NULL) {
        write(1, "Error: server message is NULL\n", 31);
        return;
    }
    user_info->user_status = strdup(server_msg);
    client_print_users(user_info->user_uuid, user_info->user_name,
        user_info->user_status);
    free(server_msg);
}

void handle_user(user_info_t *user_info, int socketfd, const char *input)
{
    int i = 0;
    int j = 0;
    char *given_uuid = malloc(strlen(input) - 5);

    if (do_error_handling(input, 1, strlen(input), 5) == KO) {
        free(given_uuid);
        return;
    }
    for (i = 8; i < ((int)strlen(input) - 1); i++) {
        given_uuid[j] = input[i];
        j++;
    }
    given_uuid[j] = '\0';
    if (strcmp(given_uuid, user_info->user_uuid) != 0)
        client_error_unknown_user(given_uuid);
    else
        client_print_user(user_info->user_uuid, user_info->user_name,
            user_info->user_status);
    free(given_uuid);
}

void handle_send(user_info_t *user_info, int socketfd, const char *input)
{
    int j = 0;
    int before_msg = 0;
    char *given_uuid = malloc(strlen(input) - 5);
    char *message_body = NULL;

    if (check_nb_args(input, 2) == KO)
        return;
    for (int i = 8; input[i] != '"'; i++) {
        given_uuid[j] = input[i];
        j++;
    }
    given_uuid[j] = '\0';
    if (check_quotes(input, 8 + strlen(given_uuid), 5) == KO) {
        printf("Error: uuid quotes\n"); /////////////////////////////////////:
        free(given_uuid);
        return;
    }

    // write(socketfd, input, strlen(input));               //////////////////////////////////
    // printf("/send: ", read_server_message(socketfd));    //////////////////////////////////

    //if (given_uuid user doesnt exist)
    //    client_error_unknown_user(given_uuid);
    //else {
        before_msg = (9 + ((int)strlen(given_uuid)));
        message_body = get_message(input, before_msg);
        if (check_quotes(input, strlen(input), strlen(message_body)) == KO) {
            write(1, "Error: message quotes\n", 15);
            free(given_uuid);
            free(message_body);
            return;
        }
        client_event_private_message_received(given_uuid, message_body);
    //}
    do_multiple_frees(given_uuid, message_body, NULL, NULL);
}

void handle_messages(user_info_t *user_info, int socketfd, const char *input)
{
    int j = 0;
    char *server_message = NULL;
    char *given_uuid = malloc(strlen(input) - 9);
    //time_t message_timestamp;

    if (check_nb_args(input, 1) == KO)
        return;
    if (check_quotes(input, strlen(input), 9) == KO) {
        write(1, "Error: quotes\n", 15);
        free(given_uuid);
        return;
    }
    //write(socketfd, input, strlen(input));
    //server_message = read_server_message(socketfd);
    //if (server_message == NULL) {
    //    write(1, "Error: server message is NULL\n", 31);
    //    return;
    //}
    //printf("server_message: %s\n", server_message); ////////////////////////////////////////
    //message_timestamp = (time_t)atoi(server_message);
    for (int i = 10; i < ((int)strlen(input)); i++) {
        given_uuid[j] = input[i];
        j++;
    }
    given_uuid[j] = '\0';
    //if (if given_uuid user doesnt exist)
        client_error_unknown_user(given_uuid);
    //else {
        // client_private_message_print_messages(given_uuid, message_timestamp, message_body);
    //}
    free(given_uuid);
}

// void handle_subscribe(char *user_uuid, const char *input)
// {
//     int i = 0;
//     int j = 0;
//     char *team_uuid = malloc(strlen(input) - 10);
//     if (check_quotes(input, strlen(input), 10) == KO) {
//         write(1, "Error: quotes\n", 15);
//         free(team_uuid);
//         return;
//     }
//     for (i = 11; i < ((int)strlen(input)); i++) {
//         team_uuid[j] = input[i];
//         j++;
//     }
//     team_uuid[j] = '\0';
//     //if (if team (team_uuid) doesnt exist)
//     //    client_error_unknown_team(team_uuid);
//     //else {
//         client_print_subscribed(user_uuid, team_uuid);
//     //}
//     free(team_uuid);
// }

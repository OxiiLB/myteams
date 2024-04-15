/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_cmds
*/

#include "myteams_cli.h"

// Need to be able to get user_name and user_status always !
// For the functions that return int, ask the pedagos what to do with that !

static int check_quotes(char *input, int input_len, int cmd_len)
{
    if (input[cmd_len + 1] != '"' || input[input_len - 2] != '"') {
        printf("first check: %c\n", input[cmd_len + 1]); //////////////////////////////////////
        printf("second check: %c\n", input[input_len]); //////////////////////////////////////
        write(1, "Error: invalid argument, missing quotes\n", 40);
        return KO;
    }
}

void handle_help(int socketfd, const char *input)
{
    char *server_msg = NULL;
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

void handle_login(int socketfd, const char *input)
{
    int i = 0;
    int j = 0;
    char *server_msg = NULL;
    char *user_name = malloc(strlen(input) - 6);

    if (check_quotes(input, strlen(input), 6) == KO) {
        write(1, "Error: quotes\n", 15);
        free(user_name);
        return;
    }
    if (write(socketfd, input, strlen(input)) == -1) {
        perror("write");
        exit(84);
    }
    server_msg = read_server_message(socketfd);
    if (server_msg == NULL) {
        write(1, "Error: server message is NULL\n", 31);
        return;
    }
    printf("%s\n", server_msg); /////////////////////////////////////////////:
    for (i = 8; i < ((int)strlen(input) - 1); i++) {
        user_name[j] = input[i];
        j++;
    }
    user_name[j] = '\0';
    //client_event_logged_in(user_uuid, user_name);
    free(user_name);
    free(server_msg);
}

void handle_logout(int socketfd, const char *input)
{
    char *server_msg = NULL;

    if (write(socketfd, input, strlen(input)) == -1) {
        perror("write");
        exit(84);
    }
    server_msg = read_server_message(socketfd);
    if (server_msg == NULL) {
        write(1, "Error: server message is NULL\n", 31);
        return;
    }
    // client_event_logged_out(user_uuid, user_name);
    free(server_msg);
}

// void handle_users(int socketfd, const char *input) // get user_status from server
// {
//     // client_print_users(user_uuid, user_name, user_status);
// }

// void handle_user(int socketfd, const char *input) // get user_status from server
// {
//     int i = 0;
//     int j = 0;
//     char *given_uuid = malloc(strlen(input) - 5);

//     if (check_quotes(input, strlen(input), 5) == KO) {
//         write(1, "Error: quotes\n", 15);
//         free(given_uuid);
//         return;
//     }
//     for (i = 8; i < ((int)strlen(input) - 1); i++) {
//         given_uuid[j] = input[i];
//         j++;
//     }
//     given_uuid[j] = '\0';
//     if (strcmp(given_uuid, user_uuid) != 0)
//         client_error_unknown_user(given_uuid);
//     else {
//         // client_print_user(user_uuid, user_name, user_status);
//     }
//     free(given_uuid);
// }

// static get_message(char *input, int len)
// {
//     int i = 0;
//     int j = 0;
//     char *message_body = malloc(sizeof(char) * ((int)strlen(input) - (len + 1)));

//     for (i = len; input[i] != NULL; i++) {
//         message_body[j] = input[i];
//         j++;
//     }
//     message_body[j] = '\0';
//     return message_body;
// }

// void handle_send(char *user_uuid, const char *input)
// {
//     int i = 0;
//     int j = 0;
//     int len = 0;
//     char *given_uuid = malloc(strlen(input) - 5);
//     char *message_body = NULL;

//     for (i = 8; input[i] != '"'; i++) {
//         given_uuid[j] = input[i];
//         j++;
//     }
//     given_uuid[j] = '\0';
//     if (check_quotes(input, 8 + strlen(given_uuid), 5) == KO) {
//         write(1, "Error: quotes\n", 15);
//         free(given_uuid);
//         return;
//     }
//     if (strcmp(given_uuid, user_uuid) != 0)
//         client_error_unknown_user(given_uuid);
//     else {
//         len = (8 + ((int)strlen(given_uuid)));
//         message_body = strdup(get_message(input, len));
//         if (check_quotes(input, strlen(input), strlen(message_body)) == KO) {
//             write(1, "Error: quotes\n", 15);
//             free(given_uuid);
//             free(message_body);
//             return;
//         }
//         client_event_private_message_received(user_uuid, message_body);
//     }
//     free(given_uuid);
//     free(message_body);
// }

// void handle_messages(char *user_uuid, const char *input)
// {
//     int i = 0;
//     int j = 0;
//     char *sender_uuid = malloc(strlen(input) - 9);
//     // time_t message_timestamp;

//     if (check_quotes(input, strlen(input), 9) == KO) {
//         write(1, "Error: quotes\n", 15);
//         free(sender_uuid);
//         return;
//     }
//     for (i = 10; i < ((int)strlen(input)); i++) {
//         sender_uuid[j] = input[i];
//         j++;
//     }
//     sender_uuid[j] = '\0';
//     if (strcmp(sender_uuid, user_uuid) != 0)
//         client_error_unknown_user(sender_uuid);
//     else {
//         // client_private_message_print_messages(sender_uuid, message_timestamp, message_body);
//     }
//     free(sender_uuid);
// }

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

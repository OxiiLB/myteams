/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_cmds
*/

#include "myteams_cli.h"

// Need to be able to get user_name and user_status always !
// For the functions that return int, ask the pedagos what to do with that !

void handle_login(char *user_uuid, const char *cmd)
{
    int i = 0;
    int j = 0;
    char *user_name = malloc(strlen(cmd) - 6);

    for (i = 7; i < ((int)strlen(cmd)); i++) {
        user_name[j] = cmd[i];
        j++;
    }
    user_name[j] = '\0';
    client_event_logged_in(user_uuid, user_name);
}

void handle_logout(char *user_uuid, const char *cmd)
{
    // get user_name from server
    // client_event_logged_out(user_uuid, user_name);
}

void handle_users(char *user_uuid, const char *cmd) // get user_status from server
{
    // client_print_users(user_uuid, user_name, user_status);
}

void handle_user(char *user_uuid, const char *cmd) // get user_status from server
{
    int i = 0;
    int j = 0;
    char *given_uuid = malloc(strlen(cmd) - 5);

    for (i = 6; i < ((int)strlen(cmd)); i++) {
        given_uuid[j] = cmd[i];
        j++;
    }
    given_uuid[j] = '\0';
    if (strcmp(given_uuid, user_uuid) != 0)
        client_error_unknown_user(given_uuid);
    else {
        // client_print_user(user_uuid, user_name, user_status);
    }
}

static get_message(char *cmd, int len)
{
    int i = 0;
    int j = 0;
    char *message_body = malloc(sizeof(char) * ((int)strlen(cmd) - (len + 1)));

    for (i = len; cmd[i] != NULL; i++) {
        message_body[j] = cmd[i];
        j++;
    }
    message_body[j] = '\0';
    return message_body;
}

void handle_send(char *user_uuid, const char *cmd)
{
    int i = 0;
    int j = 0;
    int len = 0;
    char *given_uuid = malloc(strlen(cmd) - 5);
    char *message_body = NULL;

    for (i = 6; cmd[i] != ' '; i++) {
        given_uuid[j] = cmd[i];
        j++;
    }
    given_uuid[j] = '\0';
    if (strcmp(given_uuid, user_uuid) != 0)
        client_error_unknown_user(given_uuid);
    else {
        len = (6 + ((int)strlen(given_uuid)));
        message_body = strdup(get_message(cmd, len));
        client_event_private_message_received(user_uuid, message_body);
    }
    free(given_uuid);
    free(message_body);
}

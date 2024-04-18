/*
** EPITECH PROJECT, 2023
** new_project_folder_file
** File description:
** my_project
*/

#include "myteams_cli.h"

    // {"/subscribed", &handle_subscribed},
    // {"/subscribe", &handle_subscribe},
    // {"/unsubscribe", &handle_unsubscribe},
    // {"/use", &handle_use},
    // {"/list", &handle_list},
    // {"/info", &handle_info},

const struct cmd_s CMD_FUNCS[] = {
    {"/help", &handle_help},
    {"/login", &handle_login},
    {"/logout", &handle_logout},
    {"/users", &handle_users},
    {"/user", &handle_user},
    {"/send", &handle_send},
    {"/messages", &handle_messages},
    {"/create", &handle_create},
    {"NULL", NULL}
};

static void handle_input(char *input)
{
    int i = 0;
    char *cut_str = get_msg_after_nb(input, 4);
    char **info = splitter(cut_str, END_LINE);

    for (i = 0; CMD_FUNCS[i].func != NULL; i += 1) {
        if (strncmp(info[0], CMD_FUNCS[i].cmd, strlen(CMD_FUNCS[i].cmd)) == 0) {
            CMD_FUNCS[i].func(info);
            do_multiple_frees(input, cut_str, NULL, NULL);
            free_2d_array(info);
            return;
        }
    }
    printf("Invalid command\n");
    do_multiple_frees(input, cut_str, NULL, NULL);
    free_2d_array(info);
}

static int read_client_input(fd_set readfds, int socketfd)
{
    int len = 0;
    char *str_v = NULL;
    char input[MAX_COMMAND_LENGTH];

    if (FD_ISSET(STDIN_FILENO, &readfds)) {
        if (fgets(input, MAX_COMMAND_LENGTH, stdin) == NULL) {
            fprintf(stderr, "Error reading input from stdin\n");
            return KO;
        }
        len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
            input[len - 1] = *END_STR;
        // if (do_error_handling(input) == KO) {
            // printf("\n");
            // return KO;
        // }
        str_v = add_v_to_str(input);
        if (write(socketfd, str_v, strlen(str_v) + 1) == -1) {
            perror("write");
            exit(84);
        }
        free(str_v);
    }
    return OK;
}

static int check_buffer_code(char *buffer)
{
    printf("buffer: |%s|\n", buffer); /////////////////////////////////////////////////////
    int code = atoi(buffer);

    if (code != 500 && code != 0 && code != 501 && code != 502 &&
    code != 503 && code != 504 && code != 505 && code != 506 && code != 220)
        return OK;
    if (code == 500 || code == 0 || code == 220) {
        printf("%s\n", get_msg_after_nb(buffer, 4));
    }
    if (code == 501)
        client_error_unknown_user(get_msg_after_nb(buffer, 4));
    if (code == 502)
        client_error_unauthorized();
    if (code == 503)
        client_error_already_exist();
    if (code == 504)
        client_error_unknown_team(get_msg_after_nb(buffer, 4));
    if (code == 505)
        client_error_unknown_channel(get_msg_after_nb(buffer, 4));
    if (code == 506)
        client_error_unknown_thread(get_msg_after_nb(buffer, 4));
    return KO;
}

int read_server_message(int socketfd)
{
    char buffer[BUFSIZ];
    int n_bytes_read = 0;
    int msg_size = 0;

    n_bytes_read = read(socketfd, buffer + msg_size, sizeof(buffer) -
        msg_size - 1);
    if (n_bytes_read == -1) {
        perror("Error reading from server");
        return KO;
    }
    while (n_bytes_read > 0) {
        msg_size += n_bytes_read;
        if (msg_size > BUFSIZ - 1 || buffer[msg_size - 1] == *END_STR)
            break;
        n_bytes_read = read(socketfd, buffer + msg_size, sizeof(buffer) -
            msg_size - 1);
    }
    buffer[msg_size] = '\0';
    if (buffer[msg_size - 1] == *END_STR)
        buffer[msg_size - 1] = '\0';
    if (check_buffer_code(buffer) == KO)
        return KO;
    handle_input(strdup(buffer));
    return OK;
}

static void client_loop(int socketfd)
{
    fd_set readfds;

    FD_ZERO(&readfds);
    while (1) {
        FD_SET(socketfd, &readfds);
        FD_SET(STDIN_FILENO, &readfds);
        if (select(FD_SETSIZE, &readfds, NULL, NULL, NULL) == KO)
            exit(EXIT_FAILURE);
        if (FD_ISSET(socketfd, &readfds))
            read_server_message(socketfd);
        if (FD_ISSET(STDIN_FILENO, &readfds))
            read_client_input(readfds, socketfd);
    }
}

int connect_to_server(char *ip, char *port)
{
    struct sockaddr_in server_addr;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketfd == -1) {
        fprintf(stderr, "Failed to connect to the server\n");
        close(socketfd);
        return EXIT_FAILURE;
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(port));
    server_addr.sin_addr.s_addr = inet_addr(ip);
    if (connect(socketfd, (struct sockaddr *)&server_addr,
    sizeof(server_addr)) == -1) {
        perror("Error (connect)");
        close(socketfd);
        return EXIT_FAILURE;
    }
    client_loop(socketfd);
    close(socketfd);
    return EXIT_SUCCESS;
}

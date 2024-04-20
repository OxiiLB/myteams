/*
** EPITECH PROJECT, 2023
** new_project_folder_file
** File description:
** my_project
*/

#include "myteams_cli.h"

volatile sig_atomic_t ctrl_c = false;

    // {"/subscribed", &handle_subscribed},
    // {"/subscribe", &handle_subscribe},
    // {"/unsubscribe", &handle_unsubscribe},
    // {"/use", &handle_use},
    // {"/list", &handle_list},
    // {"/info", &handle_info},

const struct cmd_s CMD_FUNCS[] = {
    {"/help", &handle_help},
    {"/logout", &handle_logout},
    {"/login", &handle_login},
    {"/users", &handle_users},
    {"/user", &handle_user},
    {"/use", &handle_use},
    {"/send", &handle_send},
    {"/messages", &handle_messages},
    {"/create", &handle_create},
    {"NULL", NULL}
};

static void handle_ctrl_c(int sig)
{
    ctrl_c = true;
    printf("ctrl+c\n");
}

static void handle_input(char *input)
{
    char *cut_str = get_msg_after_nb(input, 4);
    char **info = splitter(cut_str, END_LINE);

    for (int i = 0; CMD_FUNCS[i].func != NULL; i++) {
        if (strncmp(info[0], CMD_FUNCS[i].cmd,
        strlen(CMD_FUNCS[i].cmd)) == 0) {
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

static int check_buffer_code(char *buffer)
{
    int code = atoi(buffer);

    if (code != 500 && code != 0 && code != 501 && code != 502 &&
    code != 503 && code != 504 && code != 505 && code != 506 && code != 220)
        return OK;
    if (code == 500 || code == 0 || code == 220)
        printf("%s\n", get_msg_after_nb(buffer, 4));
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
    int size = 0;
    int n_bytes_read = 0;
    char buf[BUFSIZ];

    n_bytes_read = read(socketfd, buf + size, sizeof(buf) - size - 1);
    if (n_bytes_read == -1)
        return KO;
    while (n_bytes_read > 0) {
        size += n_bytes_read;
        if (size > BUFSIZ - 1 || buf[size - 1] == *END_STR)
            break;
        n_bytes_read = read(socketfd, buf + size, sizeof(buf) - size - 1);
    }
    buf[size] = '\0';
    buf[size - 1] = (buf[size - 1] == *END_STR) ? '\0' : buf[size - 1];
    if (check_buffer_code(buf) == KO)
        return KO;
    handle_input(strdup(buf));
    return OK;
}

static int get_client_input_write(fd_set readfds, int socketfd)
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
        if (do_error_handling(input) == KO) {
            printf("\n");
            return KO;
        }
        str_v = add_v_to_str(input);
        if (write(socketfd, str_v, strlen(str_v) + 1) == -1) {
            perror("write");
            exit(84);
        }
        free(str_v);
    }
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
            get_client_input_write(readfds, socketfd);
        if (ctrl_c == true)
            write(socketfd, "/logout\v", strlen("/logout") + 1);
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
    signal(SIGINT, handle_ctrl_c);
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

/*
** EPITECH PROJECT, 2024
** new_project_folder_file
** File description:
** my_project
*/

#include "myteams_cli.h"

    // {"/info", &handle_info},

static bool running = true;

const struct cmd_s CMD_FUNCS[] = {
    {"/help", &handle_help},
    {"/logout", &handle_logout},
    {"/login", &handle_login},
    {"/users", &handle_users},
    {"/user", &handle_user},
    {"/use", &handle_use},
    {"/send", &handle_send},
    {"/messages", &handle_messages},
    {"/unsubscribe", &handle_unsubscribe},
    {"/subscribed", &handle_subscribed},
    {"/subscribe", &handle_subscribe},
    {"/create", &handle_create},
    {"/list", &handle_list},
    {"NULL", NULL}
};

static void signal_handler(int signal)
{
    if (signal == SIGINT)
        running = false;
}

// printf("input: %s\n", input); //////////////////////////////////////////////
static void handle_input(char *input, int socketfd)
{
    char *cut_str = get_msg_after_nb(input, 4);
    char **info = splitter(cut_str, END_LINE);

    for (int i = 0; CMD_FUNCS[i].func != NULL; i++) {
        if (strncmp(info[0], CMD_FUNCS[i].cmd,
        strlen(CMD_FUNCS[i].cmd)) == 0) {
            CMD_FUNCS[i].func(info, socketfd);
            do_multiple_frees(input, cut_str, NULL, NULL);
            free_2d_array(info);
            printf("\n");
            return;
        }
    }
    printf("Invalid command\n");
    do_multiple_frees(input, cut_str, NULL, NULL);
    free_2d_array(info);
}

static void call_error_func(int code, char *msg)
{
    if (code == 501)
        client_error_unknown_user(msg);
    if (code == 502)
        client_error_unauthorized();
    if (code == 503)
        client_error_already_exist();
    if (code == 504)
        client_error_unknown_team(msg);
    if (code == 505)
        client_error_unknown_channel(msg);
    if (code == 506)
        client_error_unknown_thread(msg);
}

static int check_buffer_code(bool *running, char *buffer)
{
    int code = atoi(buffer);
    char *msg = get_msg_after_nb(buffer, 4);

    if (code != 500 && code != 0 && code != 501 && code != 502 &&
    code != 503 && code != 504 && code != 505 && code != 506 && code != 220){
        free(msg);
        return OK;
    }
    if (code == 500 || code == 0 || code == 220) {
        if (msg != NULL)
            printf("%s\n", msg);
        else
            *running = false;
    }
    call_error_func(code, msg);
    free(msg);
    return KO;
}

int read_server_message(bool *running, int socketfd)
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
    if (check_buffer_code(running, buf) == KO)
        return KO;
    handle_input(strdup(buf), socketfd);
    return OK;
}

static int get_client_input_write(fd_set readfds, int socketfd)
{
    int len = 0;
    char *str_v = NULL;
    char input[MAX_COMMAND_LENGTH];

    if (fgets(input, MAX_COMMAND_LENGTH, stdin) == NULL)
        return KO;
    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n')
        input[len - 1] = *END_STR;
    if (do_error_handling(input) == KO) {
        printf("\n");
        return KO;
    }
    str_v = add_v_to_str(input);
    if (write(socketfd, str_v, strlen(str_v) + 1) == -1) {
        free(str_v);
        exit(84);
    }
    free(str_v);
    return OK;
}

static void client_loop(int socketfd)
{
    fd_set readfds;

    FD_ZERO(&readfds);
    while (running) {
        FD_SET(socketfd, &readfds);
        FD_SET(STDIN_FILENO, &readfds);
        if (select(FD_SETSIZE, &readfds, NULL, NULL, NULL) == KO
            && errno != EINTR)
            exit(EXIT_FAILURE);
        if (errno == EINTR)
            return (handle_ctrl_c(socketfd));
        if (FD_ISSET(socketfd, &readfds))
            read_server_message(&running, socketfd);
        if (FD_ISSET(STDIN_FILENO, &readfds))
            get_client_input_write(readfds, socketfd);
    }
}

int myteams_cli(char *ip, int port)
{
    int socketfd = connect_to_server(ip, port);

    signal(SIGINT, signal_handler);
    client_loop(socketfd);
    close(socketfd);
    return OK;
}

/*
** EPITECH PROJECT, 2023
** my_scripts
** File description:
** main
*/

#include "myteams_server.h"
#include "../../include/my_macro.h"
#include <sys/queue.h>

bool is_valid_port(const char *port)
{
    int port_num = 0;

    if (port == NULL || *port == '\0')
        return false;
    for (int i = 0; port[i] != '\0'; i++) {
        if (port[i] < '0' || port[i] > '9')
            return false;
    }
    port_num = atoi(port);
    if (port_num >= 0 && port_num <= 65535)
        return true;
    return false;
}

int main(int const argc, char const *const *argv)
{
    if (argc != 2)
        return ERROR;
    if (strcmp(argv[1], "-help") == 0) {
        printf("USAGE: ./myteams_server port\n\n\
        port  is the port number on which the server socket listens\n");
        return OK;
    }
    if (!is_valid_port(argv[1])) {
        printf("Invalid port number\n");
        return ERROR;
    }
    return myteams_server(atoi(argv[1]));
}


    // linked_team_t *teams = NULL;
    // team_t team1 = {
    //     .team_uuid = strdup("team1"),
    //     .team_name = strdup("team1"),
    //     .channels = NULL,
    // };
    // channel_t channel1 = {
    //     .channel_uuid = strdup("channel1"),
    //     .channel_name = strdup("channel1"),
    //     .channel_desc = strdup("channel1"),
    //     .threads = NULL,
    // };
    // thread_t thread1 = {
    //     .thread_uuid = strdup("thread1"),
    //     .thread_name = strdup("thread1"),
    //     .thread_desc = strdup("thread1"),
    //     .messages = NULL,
    // };
    // message_t message1 = {
    //     .text = strdup("message1"),
    //     .sender_uuid = strdup("sender1"),
    //     .receiver_uuid = strdup("receiver1"),
    // };

    // team_t team2 = {
    //     .team_uuid = strdup("team2"),
    //     .team_name = strdup("team2"),
    //     .channels = NULL,
    // };

    // teams = add_team(teams, &team1);
    // teams->team->channels = add_channel(teams->team->channels, &channel1);
    // teams->team->channels->channel->threads = add_thread(
    //     teams->team->channels->channel->threads, &thread1);
    // teams->team->channels->channel->threads->thread->messages =
    //     add_message(teams->team->channels->channel->threads->thread
    //     ->messages, &message1);
    // printf("%s\n", teams->team->channels->channel->threads->thread->
    //     messages->message->text);

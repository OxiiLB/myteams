/*
** EPITECH PROJECT, 2023
** my_scripts
** File description:
** main
*/

#include "myteams_server.h"

bool is_valid_port(const char *port)
{
    int port_num = 0;

    if (port == NULL || *port == '\0')
        return false;
    for (int i = 0; port[i] != '\0'; i += 1) {
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

    // team_t *team1;
    // channel_t *channel1, *channel2;
    // struct teamhead head;
    // LIST_INIT(&head);
    // head.lh_first = NULL;

    // team1 = malloc(sizeof(team_t));
    // team1->team_name = strdup("team1");
    // team1->team_desc = strdup("team1_desc");
    // team1->team_uuid = strdup("team1_uuid");

    // LIST_INIT(&team1->channels_head);
    // team1->channels_head.lh_first = NULL;

    // LIST_INSERT_HEAD(&head, team1, next);

    // channel1 = malloc(sizeof(channel_t));
    // channel1->channel_name = strdup("channel1");
    // channel1->channel_desc = strdup("channel1_desc");
    // channel1->channel_uuid = strdup("channel1_uuid");
    // channel1->threads_head.lh_first = NULL;

    // LIST_INSERT_HEAD(&team1->channels_head, channel1, next);

    // channel2 = malloc(sizeof(channel_t));
    // channel2->channel_name = strdup("channel2");
    // channel2->channel_desc = strdup("channel2_desc");
    // channel2->channel_uuid = strdup("channel2_uuid");
    // channel2->threads_head.lh_first = NULL;

    // thread_t *thread1 = malloc(sizeof(thread_t));
    // thread1->thread_name = strdup("thread1");
    // thread1->thread_desc = strdup("thread1_desc");
    // thread1->thread_uuid = strdup("thread1_uuid");
    // thread1->messages_head.lh_first = NULL;

    // LIST_INSERT_HEAD(&channel1->threads_head, thread1, next);

    // LIST_INSERT_HEAD(&team1->channels_head, channel2, next);

    // LIST_FOREACH(team1, &head, next)
    // {
    //     printf("team_name: %s\n", team1->team_name);
    //     LIST_FOREACH(channel1, &team1->channels_head, next)
    //     {
    //         printf("\tchannel_name: %s\n", channel1->channel_name);
    //         LIST_FOREACH(thread1, &channel1->threads_head, next)
    //         {
    //             printf("\t\tthread_name: %s\n", thread1->thread_name);
    //         }
    //     }
    // }

    // free_teams(&head);

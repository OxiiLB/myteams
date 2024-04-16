/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** info_command
*/


// #include "myteams_server.h"

// void info_user(teams_server_t *my_teams_server, char *command)
// {
//     user_t *user = NULL;

//     LIST_FOREACH(user, &my_teams_server->all_user, next){
//         if (strcmp(user->uuid, command) == 0) {
//             char* str = malloc(sizeof(char) *
//             (strlen(user->username) + 1 + 1));
//             strcpy(str, user->username);
//             strcat(str, "\n");
//             write(my_teams_server->actual_sockfd, str, strlen(str));
//             free(str);
//             return;
//         }
//     }
// }

// void info_team(teams_server_t *my_teams_server, char *command)
// {
//     team_t *team = NULL;

//     LIST_FOREACH(team, &my_teams_server->all_teams, next){
//         if (strcmp(team->team_uuid, command) == 0) {
//             char* str = malloc(sizeof(char) * (strlen(team->team_name) +
//             strlen(team->team_desc) + 1 + 1 + 1));
//             strcpy(str, team->team_name);
//             strcat(str, " ");
//             strcat(str, team->team_desc);
//             strcat(str, "\n");
//             write(my_teams_server->actual_sockfd, str, strlen(str));
//             free(str);
//             return;
//         }
//     }
// }

// void info_channel(teams_server_t *my_teams_server, char *command)
// {
//     channel_t *channel = NULL;

//     LIST_FOREACH(channel, &my_teams_server->all_channels, next){
//         if (strcmp(channel->channel_uuid, command) == 0) {
//             char* str = malloc(sizeof(char) *
//             (strlen(channel->channel_name) + strlen(channel->channel_desc)
//             + 1 + 1 + 1));
//             strcpy(str, channel->channel_name);
//             strcat(str, " ");
//             strcat(str, channel->channel_desc);
//             strcat(str, "\n");
//             write(my_teams_server->actual_sockfd, str, strlen(str));
//             free(str);
//             return;
//         }
//     }
// }

// void info_thread(teams_server_t *my_teams_server, char *command)
// {
//     thread_t *thread = NULL;

//     LIST_FOREACH(thread, &my_teams_server->all_threads, next){
//         if (strcmp(thread->thread_uuid, command) == 0) {
//             char* str = malloc(sizeof(char) * (strlen(thread->thread_name)
//             + strlen(thread->thread_desc) + 1 + 1 + 1));
//             strcpy(str, thread->thread_name);
//             strcat(str, " ");
//             strcat(str, thread->thread_desc);
//             strcat(str, "\n");
//             write(my_teams_server->actual_sockfd, str, strlen(str));
//             free(str);
//             return;
//         }
//     }
// }

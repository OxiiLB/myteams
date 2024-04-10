#include "step1.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char **spliter_by_sep(char const * const str, char *separator)
{
    int i = 0;
    char **tab = NULL;
    char *tkt_str = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(tkt_str, str);
    char *tmp_str = strtok(tkt_str, separator);
    if (tmp_str == NULL)
        return NULL;
    tab = malloc(sizeof(char *) * (strlen(str) + 1));
    if (tab == NULL)
        return NULL;
    while (tmp_str != NULL) {
        tab[i] = strdup(tmp_str);
        tmp_str = strtok(NULL, separator);
        i += 1;
    }
    tab[i] = NULL;
    free(tkt_str);
    return tab;
}

int str_count_c(char *str, char c)
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            count++;
        }
    }
    return count;
}

char * str_upper(char *str)
{
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32;
        }
    }
    return str;
}

int main(void)
{
    // disable printf buffering for stdout.
    // do not remove please.
    // setvbuf(stdout, NULL, _IONBF, 0);
    step1_t test_tkt;
    /**
     * EXAMPLE CODE WHICH WILL NOT WORK ...
     * PLEASE PATCH IT ;-)
     */
    char *buffer = malloc(sizeof(char) * (MAX_COMMAND_LENGTH + 1));
    char *tmp_buffer = malloc(sizeof(char) * (MAX_COMMAND_LENGTH + 1));
    int status = 0;
    memset(tmp_buffer, 0, MAX_COMMAND_LENGTH);

    do {
        FD_ZERO(&test_tkt.input);
        FD_SET(0, &test_tkt.input);
        FD_ZERO(&test_tkt.ouput);
        FD_SET(1, &test_tkt.ouput);

        int ready = select(FD_SETSIZE, &test_tkt.input, &test_tkt.ouput, NULL, NULL);
        if (ready == -1) {
            perror("select()");
            return EXIT_FAILURE;
        } else if (ready > 0) {
            if (FD_ISSET(0, &test_tkt.input)) {
                memset(buffer, 0, MAX_COMMAND_LENGTH);
                status = read(0, buffer, MAX_COMMAND_LENGTH);
                if (status == -1) {
                    perror("read()");
                    return EXIT_FAILURE;
                } else {
                    strcat(tmp_buffer, buffer);
                    int i = 0;
                    char **lines = spliter_by_sep(tmp_buffer, "\n");
                    for (; lines[1] != NULL && lines[i + 1] ; i += 1) {
                        char *tmp = malloc(sizeof(char) * (MAX_COMMAND_LENGTH));
                        memset(tmp, 0, MAX_COMMAND_LENGTH);
                        strcpy(tmp, lines[i]);
                        strcat(tmp, "\n");
                        str_upper(tmp);
                        write(1, tmp, strlen(tmp));
                        free(tmp);
                        free(lines[i]);
                    }
                    if (tmp_buffer[strlen(tmp_buffer) - 1] == '\n') {
                        char *tmp = malloc(sizeof(char) * (MAX_COMMAND_LENGTH));
                        memset(tmp, 0, MAX_COMMAND_LENGTH);
                        strcpy(tmp, lines[i]);
                        strcat(tmp, "\n");
                        str_upper(tmp);
                        write(1, tmp, strlen(tmp));
                        free(tmp);
                        free(tmp_buffer);
                        tmp_buffer = malloc(sizeof(char) * (MAX_COMMAND_LENGTH + 1));
                    } else {
                        strcpy(tmp_buffer, lines[i]);
                    }
                    free(lines[i]);
                    free(lines);
                }
            }
        }
    } while (status);
    FD_CLR(0, &test_tkt.input);
    FD_CLR(1, &test_tkt.ouput);
    free(buffer);
    free(tmp_buffer);

    return EXIT_SUCCESS;
}

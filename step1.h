#ifndef _STEP_1_H_
#define _STEP_1_H_

#include <stdbool.h>
#include <sys/select.h>

#define MAX_COMMAND_LENGTH 32

#define EPI_EXIT_SUCCESS 0
#define EPI_EXIT_FAILURE 84

/**
 * on_command will test if the buffer look right.
 * if not it will try to explain why.
 *
 * @param command A NULL terminated editable buffer which should be at least
 * MAX_COMMAND_LENGTH + 1 length.
 * @return the command will return true on success.
 */
bool on_command(char *command);

typedef struct step1_s {
    fd_set input;
    fd_set ouput;
    char input_buffer[MAX_COMMAND_LENGTH + 1];
    char output_buffer[MAX_COMMAND_LENGTH + 1];
} step1_t;


#endif
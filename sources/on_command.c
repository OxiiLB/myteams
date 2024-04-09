#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "step1.h"

#define PRINT_COMMAND_BUFFER_LENGTH ((MAX_COMMAND_LENGTH * 2) + 1)
int _print_command(char *command) {
  char buffer[PRINT_COMMAND_BUFFER_LENGTH] = {0};

  for (size_t i = 0; i < MAX_COMMAND_LENGTH; i++) {
    if (isprint(command[i])) {
      strncat(buffer, &command[i], 1);
    } else {
      switch (command[i]) {
      case '\0':
        strcat(buffer, "\\0");
        break;
      case '\a':
        strcat(buffer, "\\a");
        break;
      case '\b':
        strcat(buffer, "\\b");
        break;
      case '\t':
        strcat(buffer, "\\t");
        break;
      case '\n':
        strcat(buffer, "\\n");
        break;
      case '\v':
        strcat(buffer, "\\v");
        break;
      case '\f':
        strcat(buffer, "\\f");
        break;
      case '\r':
        strcat(buffer, "\\r");
        break;
      default:
        strcat(buffer, "\\?");
      }
    }
  }
  return fprintf(stdout, "COMMAND: \"%s\"\n", buffer);
}

/**
 * on_command will test if the buffer look right.
 * if not it will try to explain why.
 *
 * @param command A NULL terminated editable buffer which should be at least
 * MAX_COMMAND_LENGTH + 1 length.
 * @return the command will return true on success.
 */
bool on_command(char *command) {
  char *line_break = strchr(command, '\n');
  size_t size = (line_break + 1) - command;

  _print_command(command);
  if (strlen(command) == 0) {
    fprintf(stderr, "ERROR: A valid command MUST not be empty.\n");
    return false;
  }

  if (line_break == NULL) {
    fprintf(stderr,
            "ERROR: A valid command MUST contain a line break (\\n).\n");
    return false;
  }

  if (strchr(line_break + 1, '\n') != NULL) {
    fprintf(stderr,
            "ERROR: A valid command MUST contain only one line break (\\n).\n");
    return false;
  }

  for (size_t i = size; i < MAX_COMMAND_LENGTH; i++) {
    if (command[i] != '\0') {
      fprintf(stderr, "ERROR: A valid command MUST not contain any data after "
                      "the line break(\\n).\n");
      return false;
    }
  }

  memset(command, '@', MAX_COMMAND_LENGTH);
  fprintf(stderr, "OK: the command seems all right.\n");
  return true;
}

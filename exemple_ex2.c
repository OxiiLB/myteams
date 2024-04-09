#include <stddef.h>
#include <sys/select.h>

int main(void)
{
  fd_set read_fds;
  fd_set write_fds;
  fd_set except_fds;
  do {
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    FD_ZERO(&except_fds);
    FD_SET(1, &write_fds);
  } while (select(4, &read_fds, &write_fds, &except_fds, NULL) != -1);
}
FILES = \
	main.c\
	on_command.c\

SOURCES = $(FILES:%=sources/%)
OBJECTS = $(SOURCES:%.c=%.o)

CC = gcc
CFLAGS = -I. -Wall -Wformat -Wextra -Wshadow

all: bin

bin: $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

test: bin
	@./tests.sh

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) bin

re: fclean all
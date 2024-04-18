##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile
##

SRC			=	myteams_server.c					\
				handle_client.c						\
				splitter.c							\
				scan_fd.c							\
				init_server.c						\
				generate_random_uuid.c				\
				accept_new_connection.c				\
				setup_server.c						\
				linked_list/free_list.c				\
				save_info_to_file.c					\
				read_info_from_save_file.c			\
				free_array.c						\
				search_in_object.c					\
				get_len_char_tab.c					\
				find_all_context.c					\
				remove_quotes.c						\
				${DIR_COMMAND}

COMMAND		=	help_command.c						\
				login_command.c						\
				logout_command.c					\
				users_command.c						\
				user_command.c						\
				send_command.c						\
				messages_command.c					\
				subscribe_command.c					\
				subscribed_command.c				\
				unsubscribe_command.c				\
				use_command.c						\
				create_command.c					\
				list_command.c						\
				info_command.c

DIR_SRC		=	$(addprefix src/, $(SRC))

DIR_COMMAND	=	$(addprefix commands/, $(COMMAND))

MAIN		=	main.c						\

DIR_MAIN		=	$(addprefix src/, $(MAIN))

TEST		=	\

DIR_TESTS	=	$(addprefix tests/, $(TEST))

OBJ_DIR_SRC	=	$(DIR_SRC:.c=.o)

OBJ_MAIN	=	$(DIR_MAIN:.c=.o)

OBJ			=	$(OBJ_DIR_SRC) $(OBJ_MAIN)

CPPFLAGS	=	-I include/\
				-I ../libs/myteams\

LDLIBS		=	-luuid -lmyteams

CFLAGS		=	-Wall -Wextra

LDFLAGS		=	-L../libs/myteams

NAME		=	../myteams_server

$(NAME):	$(LIBS) $(OBJ)
		gcc -o $(NAME) $(OBJ) $(LDLIBS) $(LDFLAGS)

all: $(NAME)

debug:
		gcc -o $(NAME) $(DIR_SRC) $(DIR_MAIN) $(CPPFLAGS) $(LDLIBS) $(CFLAGS) \
		$(LDFLAGS) -ggdb3

clean:
		rm -f $(OBJ)

fclean: clean
		rm -rf unit_tests
		rm -rf *.gcov
		rm -f $(NAME)

re:		fclean all

unit_tests:	re
		mkdir unit_tests
		gcc -o unit_tests/unit_tests $(DIR_SRC) $(DIR_TESTS)\
		$(CPPFLAGS) $(LDLIBS) --coverage -lcriterion

tests_run:	unit_tests
		./unit_tests/unit_tests

.PHONY: all clean fclean re tests_run

##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile
##

SRC			=	myteams_server.c					\
				server_functions.c					\
				splitter.c							\
				scan_fd.c							\
				init_server.c						\
				generate_random_uuid.c				\

DIR_SRC		=	$(addprefix src/, $(SRC))

MAIN		=	main.c						\

DIR_MAIN		=	$(addprefix src/, $(MAIN))

TEST		=	\

DIR_TESTS	=	$(addprefix tests/, $(TEST))

OBJ_DIR_SRC	=	$(DIR_SRC:.c=.o)

OBJ_MAIN	=	$(DIR_MAIN:.c=.o)

OBJ			=	$(OBJ_DIR_SRC) $(OBJ_MAIN)

CPPFLAGS	=	-I include/						\

LDLIBS		=	-luuid

CFLAGS		=	-Wall -Wextra

NAME		=	../myteams_server

$(NAME):	$(LIBS) $(OBJ)
		gcc -o $(NAME) $(OBJ) $(LDLIBS)

all: $(NAME)

debug:
		gcc -o $(NAME) $(DIR_SRC) $(DIR_MAIN) $(CPPFLAGS) $(CFLAGS) $(LDLIBS)\
		-ggdb3

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

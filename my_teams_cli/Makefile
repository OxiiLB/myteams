##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile
##

SRC			=	myteams_cli.c		\
				handle_cmds.c		\
				handle_cmds_2.c		\
				error_handling.c	\
				tools.c				\

DIR_SRC		=	$(addprefix src/, $(SRC))

MAIN		=	main.c						\

DIR_MAIN	=	$(addprefix src/, $(MAIN))

TEST		=	\

DIR_TESTS	=	$(addprefix tests/, $(TEST))

OBJ_DIR_SRC	=	$(DIR_SRC:.c=.o)

OBJ_MAIN	=	$(DIR_MAIN:.c=.o)

OBJ			=	$(OBJ_DIR_SRC) $(OBJ_MAIN)

CPPFLAGS	=	-I include/						\

CFLAGS		=	-Wall -Wextra

LDFLAGS		=	-L../ -L ../libs/myteams

LDLIBS		=	-lmyteams -luuid

NAME		=	../myteams_cli

$(NAME):	$(LIBS) $(OBJ)
		gcc -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

all: $(NAME)

# export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH

debug:
	gcc -o $(NAME) $(DIR_SRC) $(DIR_MAIN) $(CPPFLAGS)
		$(CFLAGS) $(LDFLAGS) $(LDLIBS) -ggdb3

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

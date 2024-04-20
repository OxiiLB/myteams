##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##

all:
	make all -C my_teams_server
	make all -C my_teams_cli

debug:
	make debug -C my_teams_server
	make debug -C my_teams_cli

clean:
	make clean -C my_teams_server
	make clean -C my_teams_cli

fclean: clean
	make fclean -C my_teams_server
	make fclean -C my_teams_cli

re:
	make re -C my_teams_server
	make re -C my_teams_cli

unit_tests:
	make unit_tests -C my_teams_server
	make unit_tests -C my_teams_cli

tests_run:
	make tests_run -C my_teams_server
	make tests_run -C my_teams_cli

.PHONY: all clean fclean re tests_run

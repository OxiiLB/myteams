/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** tools
*/

#include "myteams_cli.h"

char *add_v_to_str(const char *input)
{
    char *modified = malloc(strlen(input) + 2);

    modified = strcpy(modified, input);
    modified = strcat(modified, "\v");
    return modified;
}

char *get_msg_after_nb(char *str, int nb)
{
    int i = 0;
    char modified[(int)strlen(str) - (nb + 1)];
    
    for (nb = nb; nb < (int)strlen(str); nb++) {
        modified[i] = str[nb];
        i++;
    }
    modified[i] = '\0';
    return strdup(modified);
}

char *get_msg_up_to_char(char *str, char c, int i)
{
    int j = 0;
    char modified[(int)strlen(str)];
    
    for (i = i; str[i] != c; i++) {
        modified[j] = str[i];
        j++;
    }
    modified[j] = '\0';
    return strdup(modified);
}

void print_2d_array(char **array, int i)
{
    for (i = i; array[i] != NULL; i++) {
        printf("%s\n", array[i]);
    }
}

void free_2d_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++) {
        free(array[i]);
    }
    free(array);
}

void do_multiple_frees(char *one, char *two, char *three, char *four)
{
    if (one != NULL)
        free(one);
    if (two != NULL)
        free(two);
    if (three != NULL)
        free(three);
    if (four != NULL)
        free(four);
}

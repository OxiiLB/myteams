/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** get_qctuql_time
*/

#include <time.h>
#include "myteams_server.h"

time_t get_actual_time(void)
{
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);

    return mktime(tm_struct);
}

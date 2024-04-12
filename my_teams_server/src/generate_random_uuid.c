/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** generate_random_uuid
*/

#include <uuid/uuid.h>
#include <string.h>

char *generate_random_uuid(void)
{
    uuid_t uuid;
    char user_uuid[50];

    uuid_generate_random(uuid);
    uuid_unparse(uuid, user_uuid);
    return strdup(user_uuid);
}

#include "../../includes/Model/user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/Model/glibwarning.h"

#define MAX_BUFFERLINE 1000000

/**
 * @brief Estrutura de um allUsers.
 * 
 */
struct allUsers
{
    GHashTable *users_full; /** GHashTable de todos os utilizadores. */
};

struct user
{
    char *user_id;   /** Apontador char para um Id de um uilizador. */
    char *user_name; /** Apontador char para nome de um utilizador. */
    char *friends;   /** Hashtable de amigos de um determinado utilizador. */
};

char *U_getUser_id(User u)
{
    return strdup(u->user_id);
}

char *U_getUser_name(User u)
{
    return strdup(u->user_name);
}

char *U_getFriends(User u)
{
    return strdup(u->friends);
}

User initUser(char *buffer, int f)
{
    User new_user = malloc(sizeof(struct user));
    char *x;
    int count = 0;
    x = strtok(buffer, ";");
    while (x != NULL && count <= 1){

        if (count==0) new_user->user_id= strdup(x);
        if (count==1) new_user->user_name = strdup(x);
        if (count!=1) x = strtok(NULL, ";");
        count++;
    }
    /*if (f == 0)
    {
        if ((new_user->friends = strdup(strtok(NULL, "\r\n"))) == NULL)
            return NULL;
    }
    else {
        new_user->friends == NULL;
    }*/
    if (count != 2) return NULL;
    return new_user;
}

allUsers read_users(char *filename, int friends)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        perror("File cannot be opened.");
    }

    allUsers all = malloc(sizeof(struct allUsers));
    User u;
    all->users_full = g_hash_table_new_full(g_str_hash, g_str_equal, free, destroyUsers);

    char buffer[MAX_BUFFERLINE];
    for (int i = 0; fgets(buffer, MAX_BUFFERLINE, f) != NULL; i++)
    {
        if (i != 0)
        {
            char *userLine = (strtok((buffer), "\r\n"));
            u = initUser(userLine, friends);
            if (u != NULL)
                g_hash_table_insert(all->users_full, U_getUser_id(u), u);
        }
    }

    return all;
}

User cloneUser(User u)
{
    User new_user = malloc(sizeof(struct user));
    new_user->user_id = U_getUser_id(u);
    new_user->user_name = U_getUser_name(u);
   // if (u->friends != NULL) new_user->friends = U_getFriends(u);
    return new_user;
}

void *getUserFull_HT(allUsers all)
{
    GHashTableIter iter;
    gpointer key, value;
    GHashTable *new = g_hash_table_new_full(g_str_hash, g_str_equal, free, destroyUsers);
    g_hash_table_iter_init(&iter, all->users_full);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        g_hash_table_insert(new, strdup(key), cloneUser(value));
    }
    return new;
}

void destroyUsers(void *a)
{
    User u = (User)a;
    free(u->user_id);
    free(u->user_name);
    //if (u->friends != NULL) free(u->friends);
    free(u);
}

void destroyAllUser(allUsers allU)
{
    g_hash_table_remove_all(allU->users_full);
    free(allU);
}
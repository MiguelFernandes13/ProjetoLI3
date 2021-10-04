#include "../../includes/Model/business.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/Model/glibwarning.h"

#define MAX_BUFFERLINE 1000000

/**
 * @brief Estrtura de um allBusiness.
 * 
 */
struct allBusiness
{
    GHashTable *business_full; /** GHashTable de todos os businesses*/
};

/**
 * @brief Estrutura de um business.
 * 
 */
struct business
{
    char *business_id;      /** Id de um dado business. */
    char *name;             /** Nome de uma dado business. */
    char *city;             /** Cidade de um dado business. */
    char *state;            /** Estado de um dado business*/
    GHashTable *categories; /**Categotias a que um business pertence */
};

char *B_getBusiness_id(Business b)
{
    return strdup(b->business_id);
}
char *B_getName(Business b)
{
    return strdup(b->name);
}
char *B_getCity(Business b)
{
    return strdup(b->city);
}
char *B_getState(Business b)
{
    return strdup(b->state);
}
void *B_getCategories_HT(Business b)
{
    GHashTableIter iter;
    gpointer key, value;
    GHashTable *new = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
    g_hash_table_iter_init(&iter, b->categories);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        g_hash_table_insert(new, strdup(key), strdup(value));
    }
    return new;
}

Business initBusiness(char *tmp)
{
    Business new_business = malloc(sizeof(struct business));
    char *x;
    int count = 0;
    x = strtok(tmp, ";");
    while (x != NULL && count <= 3){

        if (count==0) new_business->business_id = strdup(x);
        if (count==1) new_business->name = strdup(x);
        if (count==2) new_business->city=strdup(x);
        if (count==3) new_business->state=strdup(x);
        if (count!=3) x = strtok(NULL, ";");
        count++;
    }
    GHashTable *categorie = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
    char *c;
    while ((c = strtok(NULL, ",")) != NULL)
    {
        g_hash_table_insert(categorie, strdup(c), strdup(c));
    }
    new_business->categories = categorie;
    if (count != 4) return NULL;
    return new_business;
}

allBusiness read_business(char *filename)
{

    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        perror("File cannot be opened.");
    }

    Business b;
    GHashTable *h = g_hash_table_new_full(g_str_hash, g_str_equal, free, destroyBusiness);

    char buffer[MAX_BUFFERLINE];

    for (int i = 0; (fgets(buffer, MAX_BUFFERLINE, f) != NULL); i++)
    {
        if (i != 0)
        {
            char *businessLine = (strtok((buffer), "\r\n"));
            b = initBusiness(businessLine);
            if (b != NULL)
                g_hash_table_insert(h, B_getBusiness_id(b), b);
        }
    }

    fclose(f);
    allBusiness all = malloc(sizeof(struct allBusiness));
    all->business_full = h;
    return all;
}

Business cloneBusiness(Business b)
{
    Business new_business = malloc(sizeof(struct business));
    new_business->business_id = B_getBusiness_id(b);
    new_business->name = B_getName(b);
    new_business->city = B_getCity(b);
    new_business->state = B_getState(b);
    new_business->categories = (GHashTable *)B_getCategories_HT(b);
    return new_business;
}

void *getBusinessFull_HT(allBusiness all)
{
    GHashTableIter iter;
    gpointer key, value;
    GHashTable *new = g_hash_table_new_full(g_str_hash, g_str_equal, free, destroyBusiness);
    g_hash_table_iter_init(&iter, all->business_full);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        g_hash_table_insert(new, strdup(key), cloneBusiness((Business)value));
    }
    return new;
}

void destroyBusiness(void *a)
{
    Business b = (Business)a;
    free(b->business_id);
    free(b->name);
    free(b->city);
    free(b->state);
    g_hash_table_destroy(b->categories);
    free(b);
}

void destroyAllBusiness(allBusiness allB)
{
    g_hash_table_destroy(allB->business_full);
    free(allB);
}
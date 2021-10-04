#include "../../includes/Model/auxStructs.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int strncmpci(const void *s1, const void *s2, size_t num)
{
    int ret_code = 0;
    size_t chars_compared = 0;

    const char *str1 = (const char *)s1;
    const char *str2 = (const char *)s2;

    if (!str1 || !str2)
    {
        ret_code = INT_MIN;
        return ret_code;
    }

    while ((chars_compared < num) && (*str1 || *str2))
    {
        ret_code = tolower((int)(*str1)) - tolower((int)(*str2));
        if (ret_code != 0)
        {
            break;
        }
        chars_compared++;
        str1++;
        str2++;
    }

    return ret_code;
}

int strncmpci2(const void *s1, const void *s2)
{
    if (strcmpci(s1, s2) == 0)
        return 0;
    else
        return strcmp(s1, s2);
}
int strcmpci(const void *s1, const void *s2)
{
    int ret_code = 0;

    const char *str1 = (const char *)s1;
    const char *str2 = (const char *)s2;

    if (!str1 || !str2)
    {
        ret_code = INT_MIN;
        return ret_code;
    }

    while ((*str1 || *str2))
    {
        ret_code = tolower((int)(*str1)) - tolower((int)(*str2));
        if (ret_code != 0)
        {
            break;
        }
        str1++;
        str2++;
    }

    return ret_code;
}

struct info_business
{
    double totalStars;
    int n;
    char *business_id;
    char *name;
};

double getTotalStars(info_business b)
{
    return b->totalStars;
}

int getN(info_business b)
{
    return b->n;
}

char *getID(info_business b)
{
    return strdup(b->business_id);
}

char *getName(info_business b)
{
    return strdup(b->name);
}

double mean(info_business b)
{
    return (b->totalStars / b->n);
}

void addStars(info_business *b, double stars)
{
    (*b)->totalStars += stars;
    ((*b)->n)++;
}

info_business initInfo_business(char *id, int stars, char *name)
{
    info_business new = malloc(sizeof(struct info_business));
    new->totalStars = stars;
    new->n = 1;
    new->business_id = strdup(id);
    new->name = strdup(name);
    return new;
}

int ordCityBusiness(const void *a, const void *b)
{
    info_business c1 = (info_business)a;
    info_business c2 = (info_business)b;
    double mediaA = c1->totalStars / c1->n;
    double mediaB = c2->totalStars / c2->n;
    double r = mediaB - mediaA;
    if (r > 0)
        return 1;
    else if (r < 0)
        return -1;
    else
        return 0;
}
void destroyInfo_business(void *info)
{
    info_business c1 = (info_business)info;
    free(c1->business_id);
    free(c1->name);
    free(c1);
}

info_business cloneInfoBusiness(info_business ib)
{
    info_business new = malloc(sizeof(struct info_business));
    new->totalStars = ib->totalStars;
    new->n = ib->n;
    new->business_id = strdup(ib->business_id);
    new->name = strdup(ib->name);
    return new;
}

struct infoUser
{
    char *state;   /** Primeiro estado visitado. */
    int moreThen1; /** Int que determina se foi visitado mais de um estado. */
};

char *getState(infoUser u)
{
    return strdup(u->state);
}

char getMoreThen1(infoUser u)
{
    return u->moreThen1;
}

void setMoreThen1(infoUser *u)
{
    (*u)->moreThen1 = 1;
}

infoUser initInfoUser(char *state)
{
    infoUser u = malloc(sizeof(struct infoUser));
    u->state = strdup(state);
    u->moreThen1 = 0;
    return u;
}

void destroyInfoUser(void *u)
{
    infoUser u1 = (infoUser)u;
    free(u1->state);
    free(u1);
}

char *stringLower(char *s1)
{
    char *new = strdup(s1);
    new[0] = toupper(s1[0]);
    for (int i = 1; s1[i]; i++)
    {
        new[i] = tolower(s1[i]);
    }
    free(s1);
    return new;
}
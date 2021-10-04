#include "../../includes//Model/review.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../includes/Model/glibwarning.h"

#define MAX_BUFFERLINE 10000

/**
 * @brief Estrutura de um allReviews.
 * 
 */
struct allReviews
{
    GHashTable *reviews_full; /** GhashTable de todos os reviews */
};

/**
 * @brief Estrutura de uma review.
 * 
 */
struct review
{
    char *review_id;   /** Apontador do tipo char para o id da review. */
    char *user_id;     /** Apontador do tipo char para o id do utilizador. */
    char *business_id; /** Apontador do tipo char para o id do business. */
    double stars;      /** Número de estrelas de dum dado business. */
    int useful;        /** Classificação de quão "useful" é um business. */
    int funny;         /** Classificação de quão "funny" é um business. */
    int cool;          /** Classificação de quão "cool" é um business. */
    char *date;        /** Apontador do tipo char para a data em que foi publicada a review. */
    GTree *text;       /** Apontador para uma GTree do texto da review. */
};

char *R_getReview_id(Review r)
{
    return strdup(r->review_id);
}

char *R_getUser_id(Review r)
{
    return strdup(r->user_id);
}

char *R_getBusiness_id(Review r)
{
    return strdup(r->business_id);
}

double R_getStars(Review r)
{
    return r->stars;
}

int R_getUseful(Review r)
{
    return r->useful;
}

int R_getFunny(Review r)
{
    return r->funny;
}

int R_getCool(Review r)
{
    return r->cool;
}

char *R_getDate(Review r)
{
    return strdup(r->date);
}
static int fillTextTree(gpointer key, gpointer value, gpointer data)
{
    char *p = (strdup((char *)value));
    g_tree_insert(data, p, p);
    return FALSE;
}

void *R_getText_tree(Review r)
{
    GTree *new = g_tree_new_full((GCompareDataFunc)my_strcmp, NULL, free, NULL);
    g_tree_foreach(r->text, fillTextTree, new);
    return new;
}

int validReview(Review r, void *user_ht, void *business_ht)
{
    int result = 0;
    GHashTable *u = (GHashTable *)user_ht;
    GHashTable *b = (GHashTable *)business_ht;
    if (g_hash_table_lookup(u, r->user_id) == NULL || g_hash_table_lookup(b, r->business_id) == NULL)
        result = 1;
    return result;
}

Review initReview(char *r)
{
    char *x;
    int count = 0;
    Review new_review = malloc(sizeof(struct review));
    x = strtok(r, ";");
    while (x != NULL && count <= 7){

        if (count==0) new_review->review_id = strdup(x);
        if (count==1) new_review->user_id = strdup(x);
        if (count==2) new_review->business_id=strdup(x);
        if (count==3) new_review->stars = atof(x);
        if (count==4) new_review->useful = atoi(x);
        if (count==5) new_review->funny = atoi(x);
        if (count==6) new_review->cool = atoi(x);
        if (count==7) new_review->date = strdup(x);
        if (count != 7) x = strtok(NULL, ";");
        count++;
    }
    //GTree *txt = g_tree_new_full((GCompareDataFunc)my_strcmp, NULL, free, (GDestroyNotify)g_slist_free);
    GTree *txt = g_tree_new_full((GCompareDataFunc)my_strcmp, NULL, free, NULL);
    char *c = strtok(NULL, "\r\n");
    unsigned int i = 0;
    //printf("%d\n", strlen(c));
    while (i < strlen(c))
    { //Forma as palavras
        int lenW = 0, posicao = 0;
        char *palavra;
        while (strncmp(c + i, " ", 1) != 0 && my_ispunct(c[i]) == 0 && i < strlen(c))
        {
            lenW++;
            i++;
        }
        if (lenW == 0 && (my_ispunct(c[i]) != 0 || c[i] == ' '))
        { //Junta os espaços e a pontuação
            while ((my_ispunct(c[i]) != 0 || c[i] == ' ') && i < strlen(c))
            {
                lenW++;
                i++;
            }
        }
        palavra = strndup(c + i - lenW, lenW);
        /*posicao++;
        char pos[20];
        sprintf(pos, "%d", posicao);
        GSList *info = g_tree_lookup(txt, palavra);
        info = g_slist_append(info, pos);
        g_tree_insert(txt, palavra, info);*/
        g_tree_insert(txt, palavra, palavra);
    }
    new_review->text = txt;

    if (count != 8) return NULL;
    return new_review;
}

allReviews read_review(char *filename, void *user_ht, void *business_ht)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        perror("File cannot be opened.");
    }

    Review r;
    GHashTable *h = g_hash_table_new_full(g_str_hash, g_str_equal, free, destroyReview);
    char buffer[MAX_BUFFERLINE];
    for (int i = 0; (fgets(buffer, MAX_BUFFERLINE, f) != NULL); i++)
    {
        if (i != 0)
        {
            char *reviewLine = (strtok((buffer), "\r\n"));
            r = initReview(reviewLine);
            if (r != NULL && validReview(r, user_ht, business_ht) == 0)
                g_hash_table_insert(h, R_getReview_id(r), r);
        }
    }


    allReviews all = malloc(sizeof(struct allReviews));

    all->reviews_full = h;
    fclose(f);
    return all;
}

Review cloneReview(Review r)
{
    Review new_review = malloc(sizeof(struct review));
    new_review->review_id = R_getReview_id(r);
    new_review->user_id = R_getUser_id(r);
    new_review->business_id = R_getBusiness_id(r);
    new_review->stars = R_getStars(r);
    new_review->useful = R_getUseful(r);
    new_review->funny = R_getFunny(r);
    new_review->cool = R_getCool(r);
    new_review->date = R_getDate(r);
    new_review->text = R_getText_tree(r);
    return new_review;
}

void *getReviewsFull_HT(allReviews all)
{
    GHashTableIter iter;
    gpointer key, value;
    GHashTable *new = g_hash_table_new_full(g_str_hash, g_str_equal, free, destroyReview);
    g_hash_table_iter_init(&iter, all->reviews_full);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        g_hash_table_insert(new, strdup(key), cloneReview(value));
    }
    return new;
}

void destroyReview(void *a)
{
    Review r = (Review)a;
    free(r->business_id);
    free(r->date);
    free(r->review_id);
    free(r->user_id);
    g_tree_destroy(r->text);
    free(r);
}

void destroyAllReviews(allReviews allR)
{
    g_hash_table_destroy(allR->reviews_full);
    free(allR);
}

int my_ispunct(char c1)
{
    if (c1 == '\'')
        return 0;
    else
        return ispunct(c1);
}

int my_strcmp(const void *s1, const void *s2)
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
        ret_code = (int)(*str1) - (int)(*str2);
        if (ret_code != 0)
        {
            break;
        }
        str1++;
        str2++;
    }

    return ret_code;
}
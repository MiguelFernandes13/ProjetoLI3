#include "../../includes/Model/sgr.h"
#include "../../includes/Model/auxStructs.h"
#include "../../includes/Model/review.h"
#include "../../includes/Model/business.h"
#include "../../includes/Model/user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Defenicao da estrutura sgr.
 * 
 */
struct sgr
{
    allUsers users_all;
    allReviews reviews_all;
    allBusiness business_all;
};

SGR init_sgr()
{
    SGR sgr = malloc(sizeof(SGR));
    return sgr;
}

void free_sgr(SGR sgr)
{
    destroyAllUser(sgr->users_all);
    destroyAllBusiness(sgr->business_all);
    destroyAllReviews(sgr->reviews_all);
}

/* query 1 */

SGR load_sgr(char *users, char *businesses, char *reviews, int f)
{
    SGR sgr = init_sgr();
    sgr->users_all = read_users(users, f);
    sgr->business_all = read_business(businesses);
    GHashTable *user_ht = getUserFull_HT(sgr->users_all);
    GHashTable *business_ht = getBusinessFull_HT(sgr->business_all);
    sgr->reviews_all = read_review(reviews, user_ht, business_ht);
    g_hash_table_destroy(user_ht);
    g_hash_table_destroy(business_ht);
    return sgr;
}

/* query 2 */

TABLE businesses_started_by_letter(SGR sgr, char letter)
{
    TABLE t = newTable();
    newColumn(t, "Business name");
    GHashTableIter iter;
    gpointer key, value;
    GHashTable *business_ht = getBusinessFull_HT(sgr->business_all);
    GHashTable *visited = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
    g_hash_table_iter_init(&iter, business_ht);
    int i = 0;
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Business b = (Business)value;
        char *name = B_getName(b);
        if (tolower(name[0]) == tolower(letter) && g_hash_table_lookup(visited, name) == NULL)
        {
            insert(t, i, 0, name);
            g_hash_table_insert(visited, strdup(name), strdup(name));
            i++;
        }
        free(name);
    }
    char count[100];
    sprintf(count, "Total = %d", i);
    insert(t, i, 0, count);
    g_hash_table_destroy(visited);
    g_hash_table_destroy(business_ht);

    return t;
}
/* query 3 */

TABLE business_info(SGR sgr, char *business_id)
{
    TABLE t = newTable();
    newColumn(t, "Business name");
    newColumn(t, "Business city ");
    newColumn(t, "Business state");
    newColumn(t, "Stars");
    newColumn(t, "Number of Reviews");

    GHashTableIter iter;
    gpointer key, value;
    GHashTable *business_ht = getBusinessFull_HT(sgr->business_all);
    GHashTable *review_ht = getReviewsFull_HT(sgr->reviews_all);
    Business b = (Business)g_hash_table_lookup(business_ht, business_id);
    g_hash_table_iter_init(&iter, review_ht);
    int i = 0;
    double meanS = 0;
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Review r = (Review)value;
        if (strcmpci(R_getBusiness_id(r), business_id) == 0)
        {
            i++;
            meanS += R_getStars(r);
        }
    }
    if (i != 0)
    {
        meanS /= i;
    }
    else
        return t;

    char mean[100];
    char count[100];
    char *name = B_getName(b);
    char *city = B_getCity(b);
    char *state = B_getState(b);
    sprintf(mean, "%.2f", meanS);
    sprintf(count, "%d", i);
    insert(t, 0, 0, name);
    insert(t, 0, 1, city);
    insert(t, 0, 2, state);
    insert(t, 0, 3, mean);
    insert(t, 0, 4, count);
    free(name);
    free(city);
    free(state);

    g_hash_table_destroy(business_ht);
    g_hash_table_destroy(review_ht);

    return t;
}

/* query 4 */

TABLE businesses_reviewed(SGR sgr, char *user_id)
{
    TABLE t = newTable();
    newColumn(t, "Business ID  ");
    newColumn(t, "Business name");
    GHashTableIter iter;
    gpointer key, value;
    GHashTable *business_ht = getBusinessFull_HT(sgr->business_all);
    GHashTable *review_ht = getReviewsFull_HT(sgr->reviews_all);
    GHashTable *visited = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
    g_hash_table_iter_init(&iter, review_ht);
    int i = 0;
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Review r = (Review)value;
        char *business_id = R_getBusiness_id(r);
        if (strcmpci(R_getUser_id(r), user_id) == 0)
        {
            Business b = (Business)g_hash_table_lookup(business_ht, business_id);
            if (g_hash_table_lookup(visited, business_id) == NULL)
            {
                insert(t, i, 0, B_getBusiness_id(b));
                insert(t, i, 1, B_getName(b));
                g_hash_table_insert(visited, strdup(business_id), strdup(business_id)); // Aciona no visited para garantir que nao existe repetições
                i++;
            }
        }
        free(business_id);
    }
    g_hash_table_destroy(visited);
    g_hash_table_destroy(business_ht);
    g_hash_table_destroy(review_ht);
    return t;
}

/* query 5 */

TABLE businesses_with_stars_and_city(SGR sgr, float stars, char *city)
{
    TABLE t = newTable();
    newColumn(t, "Business ID  ");
    newColumn(t, "Business name");
    GHashTableIter iter;
    gpointer key, value;
    GHashTable *business_ht = getBusinessFull_HT(sgr->business_all);
    GHashTable *review_ht = getReviewsFull_HT(sgr->reviews_all);
    GHashTable *cidade = g_hash_table_new_full(g_str_hash, g_str_equal, free, destroyInfo_business);
    g_hash_table_iter_init(&iter, review_ht);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Review r = (Review)value;
        char *business_id = R_getBusiness_id(r);
        Business b = (Business)g_hash_table_lookup(business_ht, business_id);
        char *city_name = B_getCity(b);
        char *name = B_getName(b);
        if (strcmpci(city, city_name) == 0)
        {
            info_business c = g_hash_table_lookup(cidade, business_id);
            if (c != NULL) //Caso o business_id já tenha aparecido incrementa o numero de estrelas
            {
                addStars(&c, R_getStars(r));
            }
            else // Caso contratio cria o info_business
            {
                c = initInfo_business(business_id, R_getStars(r), name);
            }

            g_hash_table_insert(cidade, strdup(business_id), cloneInfoBusiness(c));
            free(business_id);
            free(city_name);
            free(name);
        }
    }

    int i = 0;
    g_hash_table_iter_init(&iter, cidade);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        info_business c = (info_business)value;
        if (mean(c) > stars)
        {
            char *id = getID(c);
            char *name = getName(c);
            insert(t, i, 0, getID(c));
            insert(t, i, 1, getName(c));
            free(id);
            free(name);
            i++;
        }
    }
    g_hash_table_destroy(cidade);
    g_hash_table_destroy(business_ht);
    g_hash_table_destroy(review_ht);
    return t;
}

/* query 6 */

TABLE top_businesses_by_city(SGR sgr, int top)
{
    TABLE t = newTable();
    //newColumn(t, "City");
    /*for (int j = 1; j <= top; j++)
    {
        char buf[200];
        sprintf(buf, "Top %d", j);
        newColumn(t, buf);
    }*/
    newColumn(t, "Tops");
    newColumn(t, "Info of the business");
    GHashTableIter iter;
    gpointer key, value;
    GHashTable *business_ht = getBusinessFull_HT(sgr->business_all);
    GHashTable *review_ht = getReviewsFull_HT(sgr->reviews_all);
    GHashTable *cidades = g_hash_table_new(g_str_hash, g_str_equal);
    //GHashTable *cidades = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)g_hash_table_destroy);
    g_hash_table_iter_init(&iter, review_ht);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Review r = (Review)value;
        Business b = (Business)g_hash_table_lookup(business_ht, R_getBusiness_id(r));

        char *cityName = stringLower(B_getCity(b));
        GHashTable *cid = (GHashTable *)g_hash_table_lookup(cidades, cityName); //Procura se a cidade ja esta na hashtable
        info_business c = initInfo_business(B_getBusiness_id(b), R_getStars(r), B_getName(b));
        if (cid != NULL)
        {
            info_business find = g_hash_table_lookup(cid, B_getBusiness_id(b)); //Procura se aquele business esta na lista
            if (find != NULL)
            {
                addStars(&find, R_getStars(r));
                g_hash_table_insert(cid, B_getBusiness_id(b), find);
            }
            else
            {
                g_hash_table_insert(cid, B_getBusiness_id(b), c);
            }
        }
        else
        {
            cid = g_hash_table_new(g_str_hash, g_str_equal);
            //cid = g_hash_table_new_full(g_str_hash, g_str_equal, free, destroyInfo_business);
            g_hash_table_insert(cid, B_getBusiness_id(b), c);
        }
        g_hash_table_insert(cidades, strdup(cityName), cid); // adiciona à hashtable cidade
        free(cityName);
    }

    g_hash_table_destroy(business_ht);
    g_hash_table_destroy(review_ht);

    g_hash_table_iter_init(&iter, cidades);
    int y = 0;
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        GSList *bests = NULL;
        GHashTableIter iter2;
        gpointer key2, value2;
        g_hash_table_iter_init(&iter2, value);
        for (int i = 0; g_hash_table_iter_next(&iter2, &key2, &value2); i++)
        {
            info_business c = (info_business)value2;
            bests = g_slist_insert_sorted(bests, c, ordCityBusiness); //Adicona os elementos À lista por ordem decrescente da média
        }

        for (int i = 1; i <= top && bests != NULL; i++)
        {
            info_business c = (info_business)(bests->data);
            char buf[100];
            sprintf(buf, "Top %d", i);
            char arr[200];
            sprintf(arr, "City: %s/ Name: %s/ Business ID: %s/ Stars: %f", (char *)key, getName(c), getID(c), mean(c));
            insert(t, y, 0, buf);
            insert(t, y, 1, arr);
            bests = bests->next;
            y++;
        }
        g_slist_free(bests);
    }
    g_hash_table_destroy(cidades);
    reverseTable(t);
    return t;
}

/* query 7 */

TABLE international_users(SGR sgr)
{
    TABLE t = newTable();
    newColumn(t, "User ID  ");
    GHashTableIter iter;
    gpointer key, value;
    GHashTable *user_ht = getUserFull_HT(sgr->users_all);
    GHashTable *business_ht = getBusinessFull_HT(sgr->business_all);
    GHashTable *review_ht = getReviewsFull_HT(sgr->reviews_all);
    GHashTable *users_info = g_hash_table_new(g_str_hash, g_str_equal);
    //GHashTable *users_info = g_hash_table_new_full(g_str_hash, g_str_equal, free, destroyInfoUser);
    g_hash_table_iter_init(&iter, review_ht);
    int i = 0, x = 0;
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Review r = (Review)value;
        User u = (User)g_hash_table_lookup(user_ht, R_getUser_id(r));
        Business b = (Business)g_hash_table_lookup(business_ht, R_getBusiness_id(r));

        infoUser info = (infoUser)g_hash_table_lookup(users_info, R_getUser_id(r));
        if (info == NULL)
        {
            info = initInfoUser(B_getState(b));
        }
        else if (getMoreThen1(info) == 0 && (strcmpci(getState(info), B_getState(b)) != 0))
        {
            setMoreThen1(&info);
            insert(t, i, 0, R_getUser_id(r));
            i++;
        }
        g_hash_table_insert(users_info, strdup(R_getUser_id(r)), info);
    }

    char buf[100];
    sprintf(buf, "Total number of users who have visited more than one state: %d", i);
    insert(t, i, 0, buf);

    //g_hash_table_destroy(users_info);
    g_hash_table_destroy(business_ht);
    g_hash_table_destroy(review_ht);
    g_hash_table_destroy(user_ht);
    return t;
}

/* query 8 */

TABLE top_businesses_with_category(SGR sgr, int top, char *category)
{
    TABLE t = newTable();
    char b[200];
    sprintf(b, "Top %d businesses in %s", top, category);
    newColumn(t, b);
    GHashTableIter iter;
    gpointer key, value;
    GHashTable *business_ht = getBusinessFull_HT(sgr->business_all);
    GHashTable *review_ht = getReviewsFull_HT(sgr->reviews_all);
    GHashTable *categorie = g_hash_table_new_full(g_str_hash, g_str_equal, free, destroyInfo_business);
    g_hash_table_iter_init(&iter, review_ht);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Review r = (Review)value;
        Business b = (Business)g_hash_table_lookup(business_ht, R_getBusiness_id(r));
        if (g_hash_table_lookup((GHashTable *)B_getCategories_HT(b), category) != NULL)
        {
            info_business c = g_hash_table_lookup(categorie, B_getBusiness_id(b));
            if (c != NULL)
            {
                addStars(&c, R_getStars(r));
            }
            else
            {
                c = initInfo_business(B_getBusiness_id(b), R_getStars(r), B_getName(b));
            }

            g_hash_table_insert(categorie, B_getBusiness_id(b), cloneInfoBusiness(c));
        }
    }

    newColumn(t, "Info Businesses");
    g_hash_table_iter_init(&iter, categorie);
    GSList *bests = NULL;
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        info_business c = (info_business)value;
        bests = g_slist_insert_sorted(bests, c, ordCityBusiness);
    }
    for (int i = 0; i < top && bests != NULL; i++)
    {
        info_business c = (info_business)(bests->data);
        char arr[200];
        char buf[100];
        sprintf(buf, "Top %d                  ", i + 1);
        insert(t, i, 0, buf);
        sprintf(arr, "Name: %s/ Business ID: %s/ Stars: %f", getName(c), getID(c), mean(c));
        insert(t, i, 1, arr);
        bests = bests->next;
    }
    g_slist_free(bests);
    g_hash_table_destroy(categorie);
    g_hash_table_destroy(business_ht);
    g_hash_table_destroy(review_ht);
    reverseTable(t);
    return t;
}

/* query 9 */

TABLE reviews_with_word(SGR sgr, int top, char *word)
{
    TABLE t = newTable();
    newColumn(t, "Review ID ");
    GHashTableIter iter;
    gpointer key, value;
    GHashTable *review_ht = getReviewsFull_HT(sgr->reviews_all);
    g_hash_table_iter_init(&iter, review_ht);
    int i = 0;
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Review r = (Review)value;
        GTree *pal = (GTree *)R_getText_tree(r);
        if ((g_tree_lookup(pal, word)) != NULL)
        {
            char *review_id = R_getReview_id(r);
            insert(t, i++, 0, review_id);
            free(review_id);
        }
        g_tree_destroy(pal);
    }
    g_hash_table_destroy(review_ht);
    return t;
}
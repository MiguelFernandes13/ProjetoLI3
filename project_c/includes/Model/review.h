#ifndef REVIEWS_H
#define REVIEWS_H

/**
 * @brief Estrutura que facilita o acesso ao allReviews.
 * 
 */
typedef struct allReviews *allReviews;

/**
 * @brief Estrutura de dados review.
 * 
 */
typedef struct review *Review;

/**
 * @brief Funcao que devolve o review_id de uma review.
 * 
 * @param r 
 * @return char* 
 */
char *R_getReview_id(Review r);

/**
 * @brief Funcao que devolve o user_id de uma dada review.
 * 
 * @param r 
 * @return char* 
 */
char *R_getUser_id(Review r);

/**
 * @brief Funcao que devolve o business_id de uma dada review.
 * 
 * @param r 
 * @return char* 
 */
char *R_getBusiness_id(Review r);

/**
 * @brief Funcao que devolve o numero de estrelas de uma dada review.
 * 
 * @param r 
 * @return double 
 */
double R_getStars(Review r);

/**
 * @brief Funcao que devolve a classificacao de usefulness de uma dade review.
 * 
 * @param r 
 * @return int 
 */
int R_getUseful(Review r);

/**
 * @brief Funcao que devolve a funniness de uma dada review.
 * 
 * @param r 
 * @return int 
 */
int R_getFunny(Review r);

/**
 * @brief Funcao que devolve a cooliness de uma dada review.
 * 
 * @param r 
 * @return int 
 */
int R_getCool(Review r);

/**
 * @brief Fucnao que devolve a data de uma dada review.
 * 
 * @param r 
 * @return char* 
 */
char *R_getDate(Review r);

/**
 * @brief 
 * 
 * @param r 
 * @return GTree* 
 */
void *R_getText_tree(Review r);
/**
 * @brief Valida se o business_id e o user_id existem.
 * 
 * @param r 
 * @param user_ht 
 * @param business_ht 
 * @return int 
 */
int validReview(Review r, void *user_ht, void *business_ht);

/**
 * @brief Função que inicializa uma dada review.
 * 
 * @param r
 * @return Devolve o endereço da nova review.
 */
Review initReview(char *r);

/**
 * @brief Função de leitura(do ficheiro) e escrita(na hashtable) de uma lista de reviews.
 * 
 * @param filename 
 * @return Devolve o endereço para a hashtable. 
 */
allReviews read_review(char *filename, void *user_ht, void *business_ht);

/**
 * @brief Funcao que clona um dado review.
 * 
 * @param r 
 * @return Review 
 */
Review cloneReview(Review r);

/**
 * @brief Funcao ue cria e devolve uma GHasTable de allReviews.
 * 
 * @param all 
 * @return GHashTable* 
 */
void *getReviewsFull_HT(allReviews all);

/**
 * @brief Funcao que destroi uma review.
 * 
 */
void destroyReview(void *r);

/**
 * @brief Funcao que destroi uma allReviews.
 * 
 * @param allR 
 */
void destroyAllReviews(allReviews allR);

/**
 * @brief Funcao que verifica se um dado caracter e pontuacao, tendo e conta o caso especial do apostrofe.
 * 
 * @param c1 
 * @return int 
 */
int my_ispunct(char c1);

/**
 * @brief Funcao semelhante a strcmp mas que opera sobre const.
 * 
 * @param s1 
 * @param s2 
 * @return int 
 */
int my_strcmp(const void *s1, const void *s2);

#endif

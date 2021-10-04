#ifndef SGR_H
#define SGR_H
#include "../View/table.h"

typedef struct sgr *SGR;

/**
 * @brief Funcao que inicia o SGR.
 * 
 * @return SGR 
 */
SGR init_sgr();

/**
 * @brief Funcao que liberta o SGR.
 * 
 * @param sgr 
 */
void free_sgr(SGR sgr);

/**
 * @brief Query 1:
 * 
 * Dado o caminho para os 3 ficheiros (Users, Businesses, e Reviews), le o seu
 *conteúdo e carrega as estruturas de dados correspondentes. Durante a interação com o
 *utilizador (no menu da aplicação), este poderá ter a opção de introduzir os paths
 *manualmente ou, opcionalmente, assumir um caminho por omissão. Note-se que qualquer
 *nova leitura destes ficheiros irá de imediato reiniciar e refazer as estruturas de dados
 *em memória como se de uma reinicialização se tratasse.
 * @param users 
 * @param businesses 
 * @param reviews 
 * @return SGR 
 */
SGR load_sgr(char *users, char *businesses, char *reviews, int f);

/**
 * @brief Query 2:
 * 
 * Determina a lista de nomes de negócios e o número total de negócios cujo nome
 *inicia por uma dada letra. Note que a procura não é case sensitive.
 * @param sgr 
 * @param letter 
 * @return TABLE 
 */
TABLE businesses_started_by_letter(SGR sgr, char letter);

/**
 * @brief Query 3:
 * 
 * Dado um id de negócio, determina a sua informação: nome, cidade, estado, stars,
 *e número total reviews.
 * @param sgr 
 * @param business_id 
 * @return TABLE 
 */
TABLE business_info(SGR sgr, char *business_id);

/**
 * @brief Query 4:
 * 
 *  Dado um id de utilizador, determina a lista de negocios aos quais este fez review.
 * A Informacao associada a cada negocio deve ser o id e o nome.
 * 
 * @param sgr 
 * @param user_id 
 * @return TABLE 
 */
TABLE businesses_reviewed(SGR sgr, char *user_id);

/**
 * @brief Query 5:
 * 
 *  Dado um numero n de stars e uma cidade, determina a lista de negocios com n ou mais stars na dada cidade.
 * A informacao associada a cada negocio tem o id e o nome.
 * 
 * @param sgr 
 * @param stars 
 * @param city 
 * @return TABLE 
 */
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char *city);

/**
 * @brief Query 6:
 * 
 *  Dado um numero inteiro n, determina a lista dos top n negocios-8 tendo em conta o numeros medio de stars) em cada cidade.
 * A informacao associada a cada negocio e o seu id, nome, numero e estrelas.
 * 
 * @param sgr 
 * @param top 
 * @return TABLE 
 */
TABLE top_businesses_by_city(SGR sgr, int top);

/**
 * @brief Query 7:
 * 
 * Determina a lista de ids de utilizadores e o numero total de utlizadores que tenham visitado mais de um estador, i.e. que tenham feito reviews em negocios de diferentes estados.
 * 
 * @param sgr 
 * @return TABLE 
 */
TABLE international_users(SGR sgr);

/**
 * @brief Query 8:
 * 
 * Dado um numero inteiro n e uma categoria, determina a lista dos top n negocios( tendo em conta o numero medio de stars) que pertencem a uma determinada categoria.
 * A informacao associada a cada negocio e seu id, nome e numero de estrelas.
 * 
 * @param sgr 
 * @param top 
 * @param category 
 * @return TABLE 
 */
TABLE top_businesses_with_category(SGR sgr, int top, char *category);

/**
 * @brief Query 9:
 * 
 *  Dada uma palavra, determina a lista de ids de reviews que a referem no campo text.
 * 
 * @param sgr 
 * @param top 
 * @param word 
 * @return TABLE 
 */
TABLE reviews_with_word(SGR sgr, int top, char *word);

#endif
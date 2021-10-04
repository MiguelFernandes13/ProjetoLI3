#ifndef AUXSTRUCTS_H
#define AUXSTRUCTS_H
#include "glibwarning.h"

/**
 * @brief Funcao de comparacao, que compara dois objetos, ate um determinado num.
 * 
 * @param s1 
 * @param s2 
 * @param num 
 * @return int 
 */
int strncmpci(const void *s1, const void *s2, size_t num);

/**
 * @brief Funcao que compara dois objetos.
 * 
 * @param str1 
 * @param str2 
 * @param num 
 * @see https://stackoverflow.com/questions/5820810/case-insensitive-string-comp-in-c/55293507#55293507
 * @return int 
 */
int strcmpci(const void *s1, const void *s2);

/**
 * @brief Semelhante a strcmpi, mas usada para o tree_cmp.
 * 
 * @param s1 
 * @param s2 
 * @return int 
 */
int strncmpci2(const void *s1, const void *s2);

/**
 * @brief Funcao de comparacao semelhante a strcmpi, mas opera sobre gbooleans.
 * 
 * @param v1 
 * @param v2 
 * @return int 
 */
int g_str_equal_cs(gconstpointer v1, gconstpointer v2);

/**
 * @brief Estrutura que facilita o acesso a um info_business.
 * 
 */
typedef struct info_business *info_business;

/**
 * @brief Funcao que inicia um info_business.
 * 
 * @param id 
 * @param stars 
 * @param nome 
 * @return info_business* 
 */
info_business initInfo_business(char *id, int stars, char *nome);

/**
 * @brief Funcao que devolve o numero total de estrelas de um info_business.
 * 
 * @param b 
 * @return double 
 */
double getTotalStars(info_business b);

/**
 * @brief Funcao que devolve o numero de reviews de um dado info_business.
 * 
 * @param b 
 * @return int 
 */
int getN(info_business b);

/**
 * @brief Funcao que devolve o business_id de um dado info_business.
 * 
 * @param b 
 * @return char* 
 */
char *getID(info_business b);

/**
 * @brief Funcao que devolve o nome de um dado info_business.
 * 
 * @param b 
 * @return char* 
 */
char *getName(info_business b);

/**
 * @brief Funcao que devolve a media do numero de estrelas de um dado info_business.
 * 
 * @param b 
 * @return double 
 */
double mean(info_business b);

/**
 * @brief Funcao ue adiciona o numero de estrelas dado ao info_business.
 * 
 * @param b 
 * @param stars 
 */
void addStars(info_business *b, double stars);

/**
 * @brief Funcao que ordena info_business consoante o numero medio de estrelas.
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int ordCityBusiness(const void *a, const void *b);

/**
 * @brief Funcao que clona um info_business.
 * 
 * @param ib 
 * @return info_business 
 */
info_business cloneInfoBusiness(info_business ib);

/**
 * @brief Funcao que destroi um info_business.
 * 
 * @param info 
 */
void destroyInfo_business(void *info);

/**
 * @brief Estrutra de dados de infoUser.
 * 
 */
typedef struct infoUser *infoUser;

/**
 * @brief Funcao que devolve o estado de um infoUser.
 * 
 * @param u 
 * @return char* 
 */
char *getState(infoUser u);

/**
 * @brief Funcao que devolve o int que determina se o user visitou mais de um estado.
 * 
 * @param u 
 * @return char 
 */
char getMoreThen1(infoUser u);

/**
 * @brief Funcao que altera o int que determina se o user visitou mais de um estado.
 * 
 * @param u 
 */
void setMoreThen1(infoUser *u);

/**
 * @brief Funcao que destroi um infoUser.
 * 
 * @param u 
 */
void destroyInfoUser(void *u);

/**
 * @brief Funcao que inicia um infoUser.
 * 
 * @param state 
 * @return infoUser 
 */
infoUser initInfoUser(char *state);

/**
 * @brief Funcao que transorma uma string no seu equivalente apenas em minusculas.
 * 
 * @param s1 
 * @return char* 
 */
char *stringLower(char *s1);

#endif

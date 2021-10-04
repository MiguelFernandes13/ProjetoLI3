#ifndef BUSINESS_H
#define BUSINESS_H

/**
 * @brief Estrutura de dados para facilitar o acessi ao allbusiness.
 * 
 */
typedef struct allBusiness *allBusiness;

/**
 * @brief Estrutura de dados para facilitar o acesso ao business.
 * 
 */
typedef struct business *Business;

/**
 * @brief Funcao que devolve o business_id de uma dado business.
 * 
 * @param b 
 * @return char* 
 */
char *B_getBusiness_id(Business b);

/**
 * @brief Funcao que devolve o nome de um dado business.
 * 
 * @param b 
 * @return char* 
 */
char *B_getName(Business b);

/**
 * @brief Funcao que devolve a cidade de um dado business. 
 * 
 * @param b 
 * @return char* 
 */
char *B_getCity(Business b);

/**
 * @brief Funcao que devolve o estado de um dado business.
 * 
 * @param b 
 * @return char* 
 */
char *B_getState(Business b);

/**
 * @brief Funcao que devolve o apontador para uma GHashTable das categorias de um dado business.
 * 
 * @param b 
 * @return void* 
 */
void *B_getCategories_HT(Business b);

/**
 * @brief Função que incializa um dado business.
 * 
 * @param r 
 * @return Devolve o endereço do novo business.
 */
Business initBusiness(char *r);

/**
 * @brief Função de leitura(do ficheiro) e escrita(na hashtable) de uma lista de businesses.
 * 
 * @param filename 
 * @return Devolve o endereço da hashtable.
 */
allBusiness read_business(char *filename);

/**
 * @brief Funcao que clona um dado business.
 * 
 * @param b 
 * @return Business 
 */
Business cloneBusiness(Business b);

/**
 * @brief Funcao que cria devolve uma hashtable composta por allBusiness.
 * 
 * @param all 
 * @return GHashTable* 
 */
void *getBusinessFull_HT(allBusiness all);

/**
 * @brief Funcao que destroi um business.
 * 
 */
void destroyBusiness(void *a);

/**
 * @brief Funcao que destroi um allBusiness.
 * 
 * @param allB 
 */
void destroyAllBusiness(allBusiness allB);

#endif
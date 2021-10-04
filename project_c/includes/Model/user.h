#ifndef USER_H
#define USER_H

/**
 * @brief Estrutura que facilita o acesso a estrutura allUsers.
 * 
 */
typedef struct allUsers *allUsers;

/**
 * @brief Estrutura que facilita o acesso a estrutura user;
 * 
 */
typedef struct user *User;

/**
 * @brief Funcao que devolve o user_id de um dado utilizador.
 * 
 * @param u 
 * @return char* 
 */
char *U_getUser_id(User u);

/**
 * @brief Funcao que devolve o nome de um dado utilizador.
 * 
 * @param u 
 * @return char* 
 */
char *U_getUser_name(User u);

/**
 * @brief Funcao que devolve os amigos de um dado utilizador.
 * 
 * @param u 
 * @return GHashTable* 
 */
char *U_getFriends(User u);

/**
 * @brief Função que inicializa uma dado user.
 * 
 * @param buffer 
 * @return Devolve o endereço do novo utilizador.
 */
User initUser(char *buffer, int f);

/**
 * @brief Função de leitura(do ficheiro) e escrita(na hashtable) de uma lista de users.
 * 
 * @param filename 
 * @return Devolve o endereço para a hashtable. 
 */
allUsers read_users(char *filename, int f);

/**
 * @brief Funcao que clona um dado utilizador.
 * 
 * @param u 
 * @return User 
 */
User cloneUser(User u);

/**
 * @brief Funcao que cria e devolve uma GHashTable de allUsers.
 * 
 * @param all 
 * @return GHashTable* 
 */
void *getUserFull_HT(allUsers all);

/**
 * @brief Funcao que destroi um utilizador.
 * 
 */
void destroyUsers(void *u);

/**
 * @brief Funcao que destroi um allUsers.
 * 
 * @param allU 
 */
void destroyAllUser(allUsers allU);

#endif
#ifndef TABLE_H
#define TABLE_H

/**
 * @brief Estrutura que facilita o acesso a TABLE.
 *
 */
typedef struct table *TABLE;

/**
 * @brief Estrutura de um operador.
 *
 */
typedef enum operador
{
	LT = -1, /** Menor*/
	EQ,		 /** Igual*/
	GT		 /** Maior*/
} OPERATOR;

/**
 * @brief Cria uma nova coluna.
 *
 * @param x
 * @param col
 */
void newColumn(TABLE x, char *col);

/**
 * @brief Insera um novo valor ou substitui um existente num ponto da TABLE.
 *
 * @param x
 * @param line
 * @param col
 * @param s
 * @return int
 */
int insert(TABLE x, int line, int col, char *s);

void reverseTable(TABLE x);

/**
 * @brief Cria uma nova TABLE.
 *
 * @return TABLE
 */
TABLE newTable();

/**
 * @brief Destroi uma TABLE.
 *
 * @param x
 */
void destroyTable(TABLE x);

/**
 * @brief Clona uma TABLE.
 *
 * @param x
 * @return TABLE
 */
TABLE cloneTable(TABLE x);

/**
 * @brief Mostra uma TABLE.
 *
 * @param x
 */
void show(TABLE x);

/**
 * @brief Escreve uma dada TABLE num ficheiro CSV.
 *
 * @param x
 * @param delim
 * @param filepath
 */
void toCSV(TABLE x, char delim, char filepath[]);

/**
 * @brief Transforma um ficheiro CSV numa TABLE.
 *
 * @param filepath
 * @param delim
 * @return TABLE
 */
TABLE fromCSV(char filepath[], char delim);

/**
 * @brief Filtra a TABLE.
 *
 * @param x
 * @param column_name
 * @param value
 * @param oper
 * @return TABLE
 */
TABLE filter(TABLE x, char column_name[], char value[], OPERATOR oper);

/**
 * @brief Obtem um subconjunto de colunas de uma TABLE.
 *
 * @param x
 * @param cols
 * @param size_cols
 * @return TABLE
 */
TABLE proj(TABLE x, int *cols, int size_cols);

/**
 * @brief Obtem o value de uma dada coluna e linha.
 *
 * @param x
 * @param line
 * @param col
 * @return TABLE
 */
TABLE get_value(TABLE x, int line, int col);

/**
 * @brief Devolve o numero de linhas na TABLE.
 *
 * @param x
 * @return int
 */
int count(TABLE x);

/**
 * @brief Junta duas TABLEs.
 *
 * @param x
 * @param y
 * @return TABLE
 */
TABLE join(TABLE x, TABLE y);

#endif

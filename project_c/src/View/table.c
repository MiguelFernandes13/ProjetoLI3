#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/View/table.h"
#include "../../includes/Model/glibwarning.h"

#define MAX_HORIZONTAL 50
#define MAX_VERTICAL 20

typedef struct line
{
	int num_columns;
	char **values;
} * LINE;

struct table
{
	int num_lines, num_columns;
	char **column_names;
	GSList *list;
};

LINE newLine(int col)
{
	LINE l = malloc(sizeof(struct line));
	l->num_columns = col;
	l->values = (char **)calloc(col, sizeof(char *));
	return l;
}

void insertOnLine(LINE l, int col, char *str)
{
	if (col > l->num_columns)
		return;

	if (l->values[col] != NULL)
		free(l->values[col]);

	l->values[col] = strdup(str);
}

void destroyLine(LINE l)
{
	int col;
	for (col = 0; col < l->num_columns; col++)
	{
		free(l->values[col]);
	}
	free(l->values);
	free(l);
}

LINE cloneLine(LINE l)
{
	int i;
	LINE r = newLine(l->num_columns);
	for (i = 0; i < l->num_columns; i++)
	{
		insertOnLine(r, i, l->values[i]);
	}
	return r;
}

void newColumn(TABLE x, char *col)
{
	int i;
	//alocar uma nova column_names:
	char **new_column_names = (char **)malloc(sizeof(char *) * (x->num_columns + 1));

	//copiar os valores antigos:
	for (i = 0; i < x->num_columns; i++)
	{
		new_column_names[i] = x->column_names[i];
	}

	//substituir na struct:
	free(x->column_names);
	x->column_names = new_column_names;

	//inserir a nova coluna:
	x->column_names[x->num_columns] = strdup(col);
	x->num_columns++;
}

int insert(TABLE x, int line, int col, char *s)
{
	if (col >= x->num_columns)
	{
		return 1;
	}

	if (line >= x->num_lines)
	{
		//no caso de nova linha:
		LINE l = newLine(x->num_columns);
		insertOnLine(l, col, s);
		x->list = g_slist_prepend(x->list, l);
		x->num_lines++;
	}
	else
	{
		LINE l = g_slist_nth_data(x->list, x->num_lines - line - 1);
		insertOnLine(l, col, s);
	}

	return 0;
}

void reverseTable(TABLE x)
{
	x->list = g_slist_reverse(x->list);
}

TABLE newTable()
{
	TABLE r = (TABLE)malloc(sizeof(struct table));
	r->num_lines = 0;
	r->num_columns = 0;
	r->column_names = 0;
	r->list = NULL;
	return r;
}

void destroyTable(TABLE x)
{
	int col;
	for (col = 0; col < x->num_columns; col++)
	{
		free(x->column_names[col]);
	}
	free(x->column_names);

	g_slist_free_full(x->list, (GDestroyNotify)destroyLine);

	free(x);
}

TABLE cloneTable(TABLE x)
{
	int i;
	TABLE r = newTable();
	for (i = 0; i < x->num_columns; i++)
	{
		newColumn(r, x->column_names[i]);
	}
	r->list = g_slist_copy_deep(x->list, (GCopyFunc)cloneLine, NULL);
	r->num_lines = x->num_lines;
	return r;
}

void decorator()
{
	int i;
	for (i = 0; i < MAX_HORIZONTAL; i++)
		putchar('-');
	putchar('\n');
}

void show(TABLE x)
{
	int line, col;

	decorator(); //-------

	//print column_names:
	for (col = 0; col < x->num_columns; col++)
	{
		printf("| %s ", x->column_names[col]);
	}
	printf("|\n");

	decorator(); //-------

	//print values:
	GSList *next_list = x->list;
	char c;
	int pagina = 0, pagina_max = x->num_lines / MAX_VERTICAL - 1;
	if (x->num_lines % MAX_VERTICAL != 0)
	{
		pagina_max++;
	}

	for (line = 0; line < x->num_lines; line++)
	{
		//Paginação:
		if (line % MAX_VERTICAL == 0 && line != 0)
		{
			printf("Page %d / %d : Input '<' or '>' to navigate pages, or 'q' to stop...", pagina, pagina_max);
			do
			{
				c = fgetc(stdin);

				if (c == 'q')
				{
					return;
				}

				if (c == '<' && pagina > 0)
				{
					line -= MAX_VERTICAL;
					pagina--;
					next_list = g_slist_nth(x->list, line);
					break;
				}
				if (c == '>' && pagina < pagina_max)
				{
					pagina++;
					next_list = g_slist_nth(x->list, line);
					break;
				}
			} while (1);
		}

		//TODO: Centre & Wrapping
		LINE l = g_slist_nth_data(next_list, 0);
		for (col = 0; col < x->num_columns; col++)
		{
			printf("| %s ", l->values[col]);
		}
		printf("|\n");
		decorator(); //-------
		next_list = next_list->next;
	}
}

void toCSV(TABLE x, char delim, char filepath[])
{
	FILE *f = fopen(filepath, "w");
	int line, col;

	//print column_names:
	for (col = 0; col < x->num_columns; col++)
	{
		fprintf(f, "%s%c", x->column_names[col], delim);
	}
	fputc('\n', f);

	//print values:
	GSList *next_list = x->list;
	for (line = 0; line < x->num_lines; line++)
	{
		LINE l = g_slist_nth_data(next_list, 0);
		for (col = 0; col < x->num_columns; col++)
		{
			fprintf(f, "%s%c", l->values[col], delim);
		}
		fputc('\n', f);
		next_list = next_list->next;
	}

	fclose(f);
}

TABLE fromCSV(char filepath[], char delim)
{
	FILE *f = fopen(filepath, "r");
	int line, col;
	char *str, *token;
	str = malloc(sizeof(char) * 1024);

	//ler column_names:
	if ((str = fgets(str, 1024, f)) == NULL)
	{
		return NULL;
	}
	TABLE r = newTable();
	str[strcspn(str, "\n")] = 0; //Removing trailing newline character from fgets() input
	token = strtok(str, &delim);
	while (token != NULL)
	{
		newColumn(r, token);
		token = strtok(NULL, &delim);
	}

	//ler values:
	//Erro se houver '\n' no meio dos valores
	for (line = 0; fgets(str, 1024, f) != NULL; line++)
	{
		str[strcspn(str, "\n")] = 0; //Removing trailing newline character from fgets() input
		token = strtok(str, &delim);
		for (col = 0; token != NULL; col++)
		{
			insert(r, line, col, token);
			token = strtok(NULL, &delim);
		}
	}

	free(str);
	return r;
}

TABLE filter(TABLE x, char column_name[], char value[], OPERATOR oper)
{
	int line, col, i, j;

	TABLE r = newTable();

	//clonar os column_names:
	for (i = 0; i < x->num_columns; i++)
	{
		newColumn(r, x->column_names[i]);
	}

	//encontrar o indice da coluna column_name:
	for (col = 0; col < x->num_columns; col++)
	{
		if (strcmp(x->column_names[col], column_name) == 0)
			break;
	}

	//inserir as que 'passam pelo filtro':
	GSList *next_list = x->list;
	for (line = 0, j = 0; line < x->num_lines; line++)
	{
		LINE l = g_slist_nth_data(next_list, 0);
		if (strcmp(l->values[col], value) == oper)
		{
			for (i = 0; i < x->num_columns; i++)
			{
				insert(r, j, i, l->values[i]);
			}
			j++;
		}
		next_list = next_list->next;
	}

	return r;
}

TABLE proj(TABLE x, int *cols, int size_cols)
{
	int line, col, i;

	TABLE r = newTable();

	//clonar os column_names:
	for (i = 0; i < size_cols; i++)
	{
		col = cols[i];
		newColumn(r, x->column_names[col]);
	}

	//inserir os valores das colunas dadas:
	GSList *next_list = x->list;
	for (line = 0; line < x->num_lines; line++)
	{
		LINE l = g_slist_nth_data(next_list, 0);
		for (i = 0; i < size_cols; i++)
		{
			col = cols[i];
			insert(r, line, i, l->values[col]);
		}
		next_list = next_list->next;
	}

	return r;
}

//TABLE x[int][int]:
TABLE get_value(TABLE x, int line, int col)
{
	TABLE r = newTable();
	newColumn(r, x->column_names[col]);
	LINE l = g_slist_nth_data(x->list, line);
	insert(r, 0, 0, l->values[col]);
	return r;
}

int count(TABLE x)
{
	return x->num_lines; //?
}

TABLE join(TABLE x, TABLE y)
{
	//!ASSUMINDO COLUNAS IGUAIS; PODE HAVER LINHAS REPETIDAS!

	if (x->num_columns != y->num_columns)
		return NULL;

	int line, col, i;

	TABLE r = newTable();

	//clonar os column_names:
	for (col = 0; col < x->num_columns; col++)
	{
		newColumn(r, x->column_names[col]);
	}

	//inserir x:
	GSList *next_list = x->list;
	for (line = 0, i = 0; line < x->num_lines; line++)
	{
		for (col = 0; col < x->num_columns; col++)
		{
			LINE l = g_slist_nth_data(next_list, 0);
			insert(r, i, col, l->values[col]);
		}
		next_list = next_list->next;
		i++;
	}

	//inserir y:
	next_list = y->list;
	for (line = 0; line < y->num_lines; line++)
	{
		for (col = 0; col < y->num_columns; col++)
		{
			LINE l = g_slist_nth_data(next_list, 0);
			insert(r, i, col, l->values[col]);
		}
		next_list = next_list->next;
		i++;
	}

	return r;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../includes/Controller/interpretador.h"

typedef struct var
{
	char *nome;
	TABLE value;
	struct var *next_var;
} * VAR;

void clearWindow();
void printMenu();
void printQueries();
int askForString(char* question, char* result);
VAR newVar(VAR v, char *new_name, TABLE new_value);
TABLE lookUpVars(VAR v, char *str);
void clearVar(VAR v);
void clearAllVars(VAR v);
int *insertInt(int n, int *v, int size);

int interpreter()
{
	SGR sgr = NULL;
	VAR v = NULL;
	TABLE t = NULL, t_aux1 = NULL, t_aux2 = NULL;
	int top, command, command2;
	char c,buffer[1024], *input, function[256], new_name[256], name1[256], name2[256], arg1[256], arg2[256], arg3[256]; //it's gonna stay like this
	clearWindow();

	while (1)
	{
		printMenu();
		printf("> ");
		if (fscanf(stdin, "%d", &command) == 0) fprintf(stderr, "\nError! Couldn't read command number.\n");
		t = NULL;
		switch(command)
		{
			case 1:
				printQueries();
				printf("> ");
				if (fscanf(stdin, "%d", &command2) == 0) fprintf(stderr, "\nError! Couldn't read query number.\n");
				switch(command2)
				{
					case 1:
						//QUERRY 1
						if (askForString("Users' filepath", arg1) == -1) break;
						if (askForString("Businesses' filepath", arg2) == -1) break;
						if (askForString("Reviews' filepath", arg3) == -1) break;
						if (sgr != NULL) free_sgr(sgr); else sgr = init_sgr();
						sgr = load_sgr(arg1, arg2, arg3, 1);
						break;
					case 2:
						//QUERRY 2
						if (sgr == NULL) {fprintf(stderr, "\nError! SGR not loaded.\n"); break;}
						if (askForString("New name", new_name) == -1) break;
						if (askForString("Letter", arg1) == -1) break;
						c = arg1[0];
						t = businesses_started_by_letter(sgr, c);
						break;
					case 3:
						//QUERRY 3
						if (sgr == NULL) {fprintf(stderr, "\nError! SGR not loaded.\n"); break;}
						if (askForString("New name", new_name) == -1) break;
						if (askForString("Business id", arg1) == -1) break;
						t = business_info(sgr, arg1);
						break;
					case 4:
						//QUERRY 4
						if (sgr == NULL) {fprintf(stderr, "\nError! SGR not loaded.\n"); break;}
						if (askForString("New name", new_name) == -1) break;
						if (askForString("User id", arg1) == -1) break;
						t = businesses_reviewed(sgr, arg1);
						break;
					case 5:;
						//QUERRY 5
						float stars = 0.0;
						if (sgr == NULL) {fprintf(stderr, "\nError! SGR not loaded.\n"); break;}
						if (askForString("New name", new_name) == -1) break;
						if (askForString("Stars", arg1) == -1) break;
						if (askForString("City", arg2) == -1) break;
						stars = atof(arg1);
						t = businesses_with_stars_and_city(sgr, stars, arg2);
						break;
					case 6:;
						//QUERRY 6
						if (sgr == NULL) {fprintf(stderr, "\nError! SGR not loaded.\n"); break;}
						if (askForString("New name", new_name) == -1) break;
						if (askForString("Top", arg1) == -1) break;
						top = atoi(arg1);
						t = top_businesses_by_city(sgr, top);
						break;
					case 7:
						//QUERRY 7
						if (sgr == NULL) {fprintf(stderr, "\nError! SGR not loaded.\n"); break;}
						if (askForString("New name", new_name) == -1) break;
						t = international_users(sgr);
						break;
					case 8:;
						//QUERRY 8
						if (sgr == NULL) {fprintf(stderr, "\nError! SGR not loaded.\n"); break;}
						if (askForString("New name", new_name) == -1) break;
						if (askForString("Top", arg1) == -1) break;
						if (askForString("Category", arg2) == -1) break;
						top = atoi(arg1);
						t = top_businesses_with_category(sgr, top, arg2);
						break;
					case 9:;
						//QUERRY 9
						if (sgr == NULL) {fprintf(stderr, "\nError! SGR not loaded.\n"); break;}
						if (askForString("New name", new_name) == -1) break;
						if (askForString("Top", arg1) == -1) break;
						if (askForString("Word", arg2) == -1) break;
						top = atoi(arg1);
						t = reviews_with_word(sgr, top, arg2);
						break;
					default:
						fprintf(stderr, "\nError! Query \'%d\' not recognised.\n", command);
						break;
				}
				printf("\nExit query %d\n", command2);
				break;
			case 2:
				//show( TABLE x )
				if (askForString("Table name", name1) == -1) break;
				t_aux1 = lookUpVars(v, name1);
				if (t_aux1 != NULL)
				 show(t_aux1);
				else
				 fprintf(stderr, "\nError! Table \"%s\" does not exist.\n", name1);
				break;
			case 3:
				//toCSV( TABLE x , char delim , char* filepath )
				if (askForString("Table name", name1) == -1) break;
				if (askForString("Delimiter", arg1) == -1) break;
				if (askForString("Filepath", arg2) == -1) break;
				c = arg1[0];
				t_aux1 = lookUpVars(v, name1);
				if (t_aux1 != NULL)
				 toCSV(t_aux1, c, arg2);
				else
				 fprintf(stderr, "\nError! Table \"%s\" does not exist.\n", name1);
				break;
			case 4:
				//x = fromCSV( char* filepath , char delim )
				if (askForString("New table name", new_name) == -1) break;
				if (askForString("Filepath", arg1) == -1) break;
				if (askForString("Delimiter", arg2) == -1) break;
				c = arg2[0];
				t = fromCSV(arg1, c);
				break;
			case 5:;
				//y = filter( TABLE x , char* column_name , char* value , enum {LT, EQ, GT} )
				int oper = 0;
				if (askForString("New table name", new_name) == -1) break;
				if (askForString("Table name", name1) == -1) break;
				if (askForString("Column name", arg1) == -1) break;
				if (askForString("Value", arg2) == -1) break;
				if (askForString("Oper", arg3) == -1) break;
				if ((t_aux1 = lookUpVars(v, name1)) == NULL) {fprintf(stderr, "\nError! Table \"%s\" does not exist.\n", name1); break;}
				oper = (strcmp(arg3, "LT") == 0) ? (-1) : ((strcmp(arg3, "GT") == 0) ? (1) : (0));
				t = filter(t_aux1, arg1, arg2, oper);
				break;
			case 6:;
				//y = proj( TABLE x , int cols[] )
				int *arr = NULL, n = 0;
				if (askForString("New table name", new_name) == -1) break;
				if (askForString("Table name", name1) == -1) break;
				if (askForString("Column list", arg1) == -1) break;
				if ((t_aux1 = lookUpVars(v, name1)) == NULL) {fprintf(stderr, "\nError! Table \"%s\" does not exist.\n", name1); break;}
				char *token;
				token = strtok(arg1, ",");
				while (token != NULL)
				{
					arr = insertInt(atoi(token), arr, n);
					n++;
					token = strtok(NULL, ",");
				}
				t = proj(t_aux1, arr, n);
				free(arr);
				break;
			case 7:;
				//y = x[int][int]
				int linha = 0, coluna = 0;
				if (askForString("New table name", new_name) == -1) break;
				if (askForString("Table name", name1) == -1) break;
				if (askForString("Line", arg1) == -1) break;
				if (askForString("Column", arg2) == -1) break;
				linha = atoi(arg1);
				coluna = atoi(arg2);
				if ((t_aux1 = lookUpVars(v, name1)) == NULL) {fprintf(stderr, "\nError! Table \"%s\" does not exist.\n", name1); break;}
				t = get_value(t_aux1, linha, coluna);
				break;
			case 8:
				//z = join( TABLE x , TABLE y )
				if (askForString("New table name", new_name) == -1) break;
				if (askForString("Table name #1", name1) == -1) break;
				if (askForString("Table name #2", name2) == -1) break;
				if ((t_aux1 = lookUpVars(v, name1)) == NULL) {fprintf(stderr, "\nError! Table \"%s\" does not exist.\n", name1); break;}
				if ((t_aux2 = lookUpVars(v, name2)) == NULL) {fprintf(stderr, "\nError! Table \"%s\" does not exist.\n", name2); break;}
				t = join(t_aux1, t_aux2);
				break;
			case 9:
				//count( TABLE x )
				if (askForString("Table name", name1) == -1) break;
				t_aux1 = lookUpVars(v, name1);
				if (t_aux1 != NULL )
					printf("The table %s has %d entries.\n",name1, count(t_aux1));
				else
					fprintf(stderr, "\nError! Table \"%s\" does not exist.\n", name1);
				break;
			case 10:
				//quit
				if (sgr != NULL) free_sgr(sgr);
				clearAllVars(v);
				return 0;
				break;
			default:
				fprintf(stderr, "\nError! Command \'%d\' not recognised.\n", command);
				break;
			}

		if( t != NULL )
		{
			printf("\nnew var %s...",new_name);
			v = newVar(v, new_name, t);
			printf("!\n");
			t = NULL;
		}
	}
}

void printMenu()
{
	printf("\n"
	"===============================================================================\n"
	"Possiveis inputs:\n\n"
	"1.	[x =] queryN( ... )\n"
	"2.	show( TABLE x )\n"
	"3.	toCSV( TABLE x , char delim , char* filepath )\n"
	"4.	x = fromCSV( char* filepath , char delim )\n"
	"5.	y = filter( TABLE x , char* column_name , char* value , enum {LT, EQ, GT} )\n"
	"6.	y = proj( TABLE x , int cols[] )\n"
	"7.	y = x[int][int]\n"
	"8.	z = join( TABLE x , TABLE y )\n"
	"9.	count( TABLE x )\n"
	"10.	quit\n"
	"===============================================================================\n");
}

void printQueries()
{
	printf("\n"
	"===============================================================================\n"
	"Queries:\n\n"
	"1.	SGR load_sgr( char* users, char* businesses, char* reviews );\n"
	"2.	x = businesses_started_by_letter( SGR sgr, char letter );\n"
	"3.	x = business_info( SGR sgr, char* business_id );\n"
	"4.	x = businesses_reviewed( SGR sgr, char* user_id );\n"
	"5.	x = businesses_with_stars_and_city( SGR sgr, float stars, char* city );\n"
	"6.	x = top_businesses_by_city( SGR sgr, int top );\n"
	"7.	x = international_users( SGR sgr );\n"
	"8.	x = top_businesses_with_category( SGR sgr, int top, char* category );\n"
	"9.	x = reviews_with_word( SGR sgr, int top, char* word );\n"
	"===============================================================================\n");
}

int askForString(char* question, char* result)
{
	printf("%s: ", question);
	if (fscanf(stdin, "%s", result) == 0)
	{
		question[0] = tolower(question[0]);
		fprintf(stderr, "\nError! Couldn't read %s.\n", question);
		return -1;
	}
	result[strcspn(result, "\n")] = 0;
	return 0;
}

VAR newVar(VAR v, char *new_name, TABLE new_value)
{
	VAR next = v;

	if (next == NULL)
	{
		VAR new_var = (VAR)malloc(sizeof(struct var));
		new_var->nome = strdup(new_name);
		new_var->value = new_value;
		new_var->next_var = NULL;
		return new_var;
	}

	while (next != NULL)
	{
		if (strcmp(next->nome, new_name) == 0)
		{
			destroyTable(next->value);
			next->value = new_value;
			break;
		}
		if (next->next_var == NULL)
		{
			VAR new_var = (VAR)malloc(sizeof(struct var));
			new_var->nome = strdup(new_name);
			new_var->value = new_value;
			new_var->next_var = NULL;
			next->next_var = new_var;
			break;
		}
		next = next->next_var;
	}

	return v;
}

TABLE lookUpVars(VAR v, char *str)
{
	VAR next = v;

	while (next != NULL)
	{
		if (strcmp(next->nome, str) == 0)
		{
			return next->value;
		}
		else
		{
			next = next->next_var;
		}
	}

	return NULL;
}

void clearVar(VAR v)
{
	free(v->nome);
	destroyTable(v->value);
	free(v);
}

void clearAllVars(VAR v)
{
	VAR next;
	while (v != NULL)
	{
		next = v->next_var;
		clearVar(v);
		v = next;
	}
}

int *insertInt(int n, int *v, int size)
{
	int i;
	int *r = calloc(size + 1, sizeof(int));
	for (i = 0; i < size; i++)
	{
		r[i] = v[i];
	}
	r[i] = n;
	free(v);
	return r;
}

void clearWindow() {
    if (system("clear") == -1) return;
}

FLAGS= -std=c99 -Wextra -O2 -D_GNU_SOURCE -g
PKG = `pkg-config --cflags --libs glib-2.0`
COMPILER=gcc
INCLUDES=includes
SRC=src
OBJ=obj
##CFLAGS = `pkg-config --cflags glib-2.0` 
##LDLIBS = `pkg-config --libs glib-2.0`

all: auxStructs user review business sgr table interpretador main program
	
auxStructs: $(SRC)/Model/auxStructs.c $(INCLUDES)/Model/auxStructs.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/Model/auxStructs.o $(PKG) -c $(SRC)/Model/auxStructs.c

user: $(SRC)/Model/user.c $(INCLUDES)/Model/user.h 
	$(COMPILER) $(FLAGS) -o $(OBJ)/Model/user.o $(PKG) -c $(SRC)/Model/user.c

review: $(SRC)/Model/review.c $(INCLUDES)/Model/review.h 
	$(COMPILER) $(FLAGS) -o $(OBJ)/Model/review.o $(PKG) -c $(SRC)/Model/review.c

business: $(SRC)/Model/business.c $(INCLUDES)/Model/business.h 
	$(COMPILER) $(FLAGS) -o $(OBJ)/Model/business.o $(PKG) -c $(SRC)/Model/business.c	

table : $(SRC)/View/table.c $(INCLUDES)/View/table.h 
	$(COMPILER) $(FLAGS) -o $(OBJ)/View/table.o $(PKG) -c $(SRC)/View/table.c	

sgr : $(SRC)/Model/sgr.c $(INCLUDES)/Model/sgr.h 
	$(COMPILER) $(FLAGS) -o $(OBJ)/Model/sgr.o $(PKG) -c $(SRC)/Model/sgr.c	

interpretador : $(SRC)/Controller/interpretador.c $(INCLUDES)/Controller/interpretador.h 
	$(COMPILER) $(FLAGS) -o $(OBJ)/Controller/interpretador.o $(PKG) -c $(SRC)/Controller/interpretador.c	


main: $(SRC)/main.c 
	$(COMPILER) $(FLAGS) -o $(OBJ)/main.o $(PKG) -c $(SRC)/main.c


program: $(SRC)/main.c $(OBJ)/main.o $(OBJ)/Model/auxStructs.o $(OBJ)/Model/user.o $(OBJ)/Model/review.o $(OBJ)/View/table.o $(OBJ)/Model/sgr.o $(OBJ)/Controller/interpretador.o
	$(COMPILER) $(FLAGS) $(OBJ)/Model/auxStructs.o $(OBJ)/Model/user.o $(OBJ)/Model/review.o $(OBJ)/Model/business.o $(OBJ)/View/table.o $(OBJ)/Model/sgr.o $(OBJ)/Controller/interpretador.o $(OBJ)/main.o $(PKG)  -o program


memcheck:
	valgrind --leak-check=yes ./program

clean:
	rm -rf $(OBJ)/*.o program

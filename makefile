#changer le nom des deux lignes suivantes si nécessaire
CC=gcc
SOURCE = polynomes.c
OUTPUT = polynomes
LIB = -lm 
OPT = -g -Wall -Werror 

all: $(OUTPUT)
	
clean: $(OUTPUT)
	rm $(OUTPUT) *.o;

$(OUTPUT): source.o
	@gcc source.o -o $(OUTPUT) $(LIB)

source.o: $(SOURCE)
	@gcc $(OPT) -c $(SOURCE) -o source.o








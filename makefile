COMPILE=gcc
FLAGS= -g -Wall -pedantic
index: main.o indexer.o tokenizer.o
	$(COMPILE) $(FLAGS) tokenizer.o indexer.o main.o -o index
tokenizer.o: tokenizer.c
	$(COMPILE) $(FLAGS) -c tokenizer.c
indexer.o: indexer.c
	$(COMPILE) $(FLAGS) -c indexer.c
main.o: main.c
	$(COMPILE) $(FLAGS) -c main.c 
clean:
	rm -rf *.o PGM

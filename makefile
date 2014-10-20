COMPILE=gcc

index: main.o indexer.o tokenizer.o
	$(COMPILE) tokenizer.o indexer.o main.o -g -o index
tokenizer.o: tokenizer.c
	$(COMPILE) -c -g tokenizer.c
indexer.o: indexer.c
	$(COMPILE) -c -g indexer.c
main.o: main.c
	$(COMPILE) -c -g main.c 
clean:
	rm -rf *.o index

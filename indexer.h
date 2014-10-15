#ifndef INDEXER_H
#define INDEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*index hashtable*/
struct Indexer {
	
};
typedef struct Indexer Index;

/*token node contains token name, pointer to first file node, 
  and pointer to next token*/
struct tkNode_{
	char* tk;
	struct fileNode* file;
	struct tkNode* next;
};
typedef struct tkNode_ tkNode;

/*file node contains file name, frequency of token in file, 
and pointer to the next node*/
struct fileNode_ {
	char* fileName;
	int count;
	struct fileNode* next;
};
typedef struct fileNode_ fileNode;

/*creates a new hashtable to index*/
Index *IndexCreate(char* outputName);

/*take in hashed list, insert it into index*/
int IndexInsert(Index *indx, char* tk,  char* fileName);

/*output contents of index to file*/
int IndexOutput(Index *indx);

/*hash function that insert uses*/
int Hash(char c);

/*reads the file and tokenizes data*/
int ReadFile(char *fileName);

/*appends character to end of string*/
char* Concat(char* string, char c);

/*combines strings*/
char* ConcatStr(char* p1, char* p2);

/*destroys indexer*/
void IndexDestroy(Index *indx);

#endif

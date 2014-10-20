#ifndef INDEXER_H
#define INDEXER_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
//#include "tokenizer.h"//is this correct? without this I get errors maybe we have to merge the tokenizer and indexer .h files
struct TokenizerT_ {
	char* copied_string;
	char* delimiters;
	char* current_position;
};
typedef struct TokenizerT_ TokenizerT;
/*index hashtable*/
struct Indexer {
	struct tkNode* Array;
};
typedef struct Indexer Index;

/*token node contains token name, pointer to first file node,
  and pointer to next token*/
struct tkNode{
	char* tk;
	struct fileNode* fileNodePTR;
	struct tkNode* next;
};
typedef struct tkNode tkNode;

/*file node contains file name, frequency of token in file,
and pointer to the next node*/
struct fileNode {
	const char* fileName;
	int Count;
	struct fileNode* next;
};
typedef struct fileNode fileNode;
//global variables definition
FILE *file_read;    //pointer to file to read from
FILE *file_write;   //pointer to file to output hash content
Index *indx;        //pointer to hash table
/*creates a new hashtable to index*/
Index *IndexCreate(char* outputName);

/*take in hashed list, insert it into index*/
int IndexInsert(Index *indx, char* tk,  char* fileName);

/*output contents of index to file*/
void IndexOutput(Index *indx);

/*hash function that insert uses*/
int Hash(char c);

/*reads the file and returns string*/
int hashToken(char* fileName);//NEW 10/19 5.13PM

/*reads from directory:*/
int ReadDir(char* dirpath);

/*appends character to end of string*/
char* Concat(char* String, char c);

/*combines strings*/
char* ConcatStr(char* p1, char* p2);

/*destroys indexer*/
void IndexDestroy(Index *indx);

//tokenizer methods
typedef struct TokenizerT_ TokenizerT;

TokenizerT* tokenizer;

TokenizerT *TKCreate(char *separators, char *ts);

void TKDestroy(TokenizerT *tk);

char *TKGetNextToken(TokenizerT *tk);

char is_escape_character(char character);

int char_to_hex(char character);

int char_to_oct(char character);

int is_oct_digit(char oct_digit);

char* unescape_string(char* string);

char is_delimiter(char character, char* delimiters);
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "indexer.h"

Index IndexCreate(SortedListPtr list, char* indexName) {
	/*calloc space for the index*/
	Index index = (Index)calloc(1, sizeof(struct Index));
	/*calloc 36 token nodes for the array*/
	index->array = calloc(36 * sizeof(tkNode));
	/*null out all 36 token nodes (just to be sure)*/
	for(int i = 0; i < 36; i++) {
		index->array[i]->tk = NULL;
		index->array[i]->file = NULL;
		index->array[i]->next = NULL;
	}
	/*if the index ends up null return null*/
	if (index == NULL) {
		return NULL;
	}
	/*if the index is made right return the index*/
	if (index != NULL) {
		return index;
	}
	/*if somehow those 2 conditions aren't met return null*/
	return NULL;
}

int IndexInsert(Index *indx, char* tk, char* fileName) {
	/*initialize the position in the table to 0*/
	int indxPos = 0;
	/*find the first character of the given token*/
	char firstChar = tk[0];
	/*calloc a test node to insert the given data into*/
	fileNode testf = calloc(sizeof(fileNode));
	/*set the fileName field to the given file name*/
	testf->fileName = fileName;
	/*set the token count to 1 by default*/
	testf->count = 1;
	/*initially set next to null*/
	testf->next = NULL;
	/*determine position in table via hash function*/
	indxPos = Hash(firstChar);
	/*if the position is empty, add it there*/
	if (indx[indxPos]->tk == NULL) {
		/*set the token to the given one*/
		indx->array[indxPos]->tk = tk;
		/*sets the file node to the current one*/
		indx->array[indxPos]->file = testf;
		/*return 0 because it worked*/
		return 0;
	} else {
		/*if the position is not empty make new token node*/
		tkNode testt = calloc(sizeof(tkNode));
		testt->tk = tk;
		testt->file = test;
		testt->next = NULL;
		/*prepare to walk through linked list at indxPos*/
		tkNode *previous = indx->array[indxPos];
		tkNode *current = testt;
		/*begin to walk through linked list*/
		while (current != NULL) {
			if (previous->tk == current->tk) {
				
			}
			if (previous->next == NULL) {
				previous->next = current;
				current->next = NULL;
			}
			previous = current;
			current = current->next;		
		}
}

int IndexOutput(Index *indx) {
	
}

int Hash(char c) {
	/*convert character to ascii*/
	int charNum = c;
	/*check if character is 0-9 (48-57). If yes, put at front of array*/
	if(charNum >= 48 && charNum <= 57) {
		charNum = charNum - 48;
		return charNum;
	}
	/*check if character is a-z (65-90 if uppercase). If yes, put after numbers*/
	if(charNum >= 65 && charNum <= 90) {
		charNum = charNum - 55;
		return charNum;
	}
	/*returns null, prints error message*/
	printf("character not in expected range\n");
	return 0;
}

char* ReadFile(char* fileName) {
	/*if the file isn't there*/
	if (fileName == NULL) {
		return 1;
	}
	/*make test variables for character and string, null out*/
	char c;
	char* test = (char*)calloc(sizeof(char));
	test = "";
	/*check access permissions, should return 0 if ok*/
	int a = access(fileName, F_OK)
	/*if we have permission, open and read*/
	if (a == 0) {
		/*open given file, put into global file variable*/
		file = fopen(fileName, "r");
		/*get the first character*/
		c = getc(file);
		/*until end of file is reached concatenate all characters*/
		while (c != EOF) {
			c = tolower(c);
			test = Concat(test, c);
			c = getc(file);
		}
		fclose(file);
		return test;
	}
	if (a != 0) {
		printf("cannot read from file");
		return 1;
	}
}

char* ReadDir(char* dirPath) {

}

char* Concat(char* string, char c) {
	int length = strlen(string);
	char* test = calloc(length * sizeof(char));
	test = strncat(string, &c, 1);
	return test;
}

char* ConcatStr(char* p1, char* p2) {
	char* test = calloc(length * sizeof(char));
	test = strcat(p1, p2);
	return test;
}

void IndexDestroy(Index *indx) {
	if (indx = NULL) {
		return;
	}
		
}

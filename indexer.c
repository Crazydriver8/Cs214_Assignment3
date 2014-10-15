#include <stdlib.h>
#include <string.h>

#include "indexer.h"

Index IndexCreate(SortedListPtr list) {
	Index index = (Index)calloc(1, sizeof(struct Index));
	index->head = list->head;
	if (list->head == NULL) {
		return NULL;
	}
	if (index != NULL) {
		return index;
	}
	return NULL;
}

int IndexInsert(Index *indx, char* tk, char* fileName) {
	
}

int IndexOutput(Index *indx) {
	
}

int Hash(char c) {
	
}

int ReadFile(char* fileName) {
	
}

char* Concat(char* string, char c) {
	
}

char* ConcatStr(char* p1, char* p2) {
	
}

void IndexDestroy(Index *indx) {
	
}

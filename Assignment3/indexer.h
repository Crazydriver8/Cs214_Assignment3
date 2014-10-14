#ifndef INDEXER_H
#define INDEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Indexer_ {
	
}
typedef struct Indexer* Index;

/*creates a new hashtable to index*/
Index IndexCreate(SortedListPtr list, char* indexName);

/*take in list, hash it*/
int IndexInsert(SortedListPtr list, char* indexName);

/*remove all elements in provided list*/
int IndexRemove(SortedListPtr list);

/*destroy indexer*/
void IndexDestroy(Index indx);


#endif

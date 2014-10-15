#include <stdio.h>
#include <string.h>

int main(int argc, char argv**) {
	char* indexName = argv[1];
	char* fileName = argv[2];
	SortedListPtr list = readFile(fileName);
	if (indexName == NULL) {
		Index indx = IndexCreate(list, indexName);
	} else {
		IndexInsert(list, indexName);
	}
	if (indx == NULL) {
		return NULL;
	}
	writeFile(indx, indexName);
}

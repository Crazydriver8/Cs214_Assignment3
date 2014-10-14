#include <stdlib.h>
#include <string.h>

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


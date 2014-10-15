#ifndef INDEXIO_H
#define INDEXIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*read from file, create list from it, return list*/
SortedListPtr readFile(char* fileName);

/*read from directory*/
SortedListPtr readDir(char* fileName);

/*write to file, maintains proper format*/
void writeFile(Index indx, char* indexName);

/*
Laszlo Glant & Brandon Berrios
*/
#include <stdio.h>
#include <string.h>
#include "indexer.h"
int main(int argc, char * argv[]) {
  
	char* dirName;
	char* indexName;
	if(argc > 3)
   	 {
       		 printf("Error too many arguments\n");
       		 return -1;
   	 }

   	 if(argc < 3)
   	{
       		 printf("Error few arguments\n");
       		 return -1;
  	}
	dirName = argv[2];
	indexName = argv[1];
	indx = IndexCreate(indexName);

	ReadDir(dirName);
	IndexOutput(indx);
	IndexDestroy(indx);
	return 0;
}

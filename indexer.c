#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "indexer.h"
/*done*/
Index IndexCreate(char* indexName) {
	/*calloc space for the index*/
	Index* index = (Index*)calloc(1, sizeof(Index));
	indexFile = fopen(indexName, "w");
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
/*check this*/
int IndexInsert(Index *indx, char* tk, char* fileName) {
	int indxPos = 0;
	char firstChar = tk[0];
	
	fileNode tempf = calloc(sizeof(fileNode));
	tkNode tempt = calloc(sizeof(tkNode));
	
	tempf->fileName = fileName;
	tempf->count = 1;
	tempf->next = NULL;
	
	tempt->tk = tk;
	tempt->file = tempf;
	tempt->next = NULL;
	
	indxPos = Hash(firstChar);

	/*if that position in the array is empty, add it there*/
	if (indx->array[indxPos]->tk == NULL) {
		indx->array[indxPos]->tk = tk;
		indx->array[indxPos]->file = tempf;
		return 0;
	}

	tempt->tk = tk;
	tempt->file = tempf;
	tempt->next = NULL;
	tkNode *previous = indx->array[indxPos];

	/*if there is only one token node in the list*/
	if (previous != NULL && previous->next == NULL) {
		int a = strcmp(previous->tk, tempt->tk);
		if (a > 0) {
			/*insert before*/
			tempt->next = previous;
			indx->array[indxPos] = tempt;
			return 1;
		}
		if (a < 0) {
			/*insert after*/
			previous->next = tempt;
			tempt->next = NULL;
			return 1;
		}
		if (a == 0) {
			fileNode* prevFile = previous->file;
			if (prevFile != NULL && prevFile->next == NULL) {
				int b = strcmp(prevFile->fileName, tempf->fileName);
				if (b > 0) {
					/*insert before*/
					tempf->next = prevFile;
					previous->file = tempf;
					return 1;
				}
				if (b < 0) {
					/*insert after*/
					prevFile->next = tempf;
					tempf->next = NULL;
					return 1;
				}
				if (b == 0) {
					/*increment token count in file*/
					prevFile->count++;
					return 1;
				}
				return 0;
			}
			fileNode *currFile = prevFile->next;
			while (currFile != NULL) {
				int b = strcmp(currFile->fileName, tempf->fileName);
				if (b > 0) {
					/*insert before*/
					tempf->next = currFile;
					prevFile->next = tempf;
					return 1;
				}
				if (b == 0) {
					/*increment count because same filename*/
					currFile->count++;
					return 1;
				}
				if (currFile->next == NULL) {
					currFile->next = tempf;
					tempf->next = NULL;
					return 1;
				}
				prevFile = currFile;
				currFile = currFile->next;
			}
			return 0;
		}
		return 0;
	}
	fileNode *current = previous->next;
	while (current != NULL) {
		int a = strcmp(current->tk, tempt->tk);
		if (a > 0) {
			/*insert before because previous is larger than current*/
			tempt->next = current;
			previous->next = tempt;
			return 1;
		}
		if (a == 0) {
			/*same token, move through file list*/
			fileNode *prevFile = current->file;
			if (prevFile != NULL && prevFile->next == NULL) {
				int b = strcmp(prevFile, tempf);
				if (b > 0) {
					/*add before*/
					tempf->next = prevFile;
					previous->file = tempf;
					return 1;
				}
				if (b < 0) {
					/*add after*/
					prevFile->next = tempf;
					tempf->next = NULL;
					return 1;
				}
				if (b == 0) {
					/*increment token count for file name*/	
					prevFile->count++;
					return 1;
				}
				return 0;
			}
			/*make sure first file in list is smaller than given name*/
			int c = strcmp(prevFile->fileName, tempf->fileName);
			if (b > 0) {
				/*add before because first file is larger*/
				tempf->next = prevFile;
				current->file = tempf;
				return 1;	
			}
			fileNode *currFile = prevFile->next;
			while (currFile != NULL) {
				int b = strcmp(currFile->fileName, tempf->fileName);
				if (b > 0) {
					/*add before*/
					tempf->next = currFile;
					prevFile->next = tempf;
					return 1;
					
				}
				if (b == 0) {
					/*increment token count*/
					currFile->count++;
					return 1;
				}
				if (currFile->next == NULL) {
					/*add after*/
					currFile->next = tempf;
					tempf->next = NULL:
					return 1;
				}
				prevFile = currFile;
				currFile = currFile->next;
			}
		}
		/*if current->next is null add temp node to end*/
		if (current->next = NULL) {
			current->next = tempt;
			tempt->next = NULL;
			return 1;
		}
		/*if previous token is less than current token continue walk*/
		previous = current;
		current = current->next;		
	}
}
/*done*/
int IndexOutput(Index *indx) {
	int i, j;
	fileNode *fileNode_Ptr;
	tkNode *tkNode_Ptr;
	j = 0;
	/*check all buckets in index*/
	for(i = 0; i < 36; i++) {
		tkNode_Ptr = &indx->array[i];
		fileNode_Ptr = indx->array[i].file;
		/*while there is a token in the index bucket*/
		while(tkNode_Ptr != NULL) {
			/*if the token is not null, print header with token*/
			if(tkNode_Ptr->tk != NULL) {
				fprintf(indexFile, "<list> %s \n \n", tkNode_Ptr->tk);
			}
			/*while the fileNode is not null*/
			while(fileNode_Ptr != NULL) {
				/*if the next fileNode dne, print the end of the list*/
				if (fileNode_Ptr->next == NULL) {
					fprintf(indexFile, " %s %d \n \n </list> \n \n", fileNode_Ptr->fileName, fileNode_Ptr->count);
					break;
				/*otherwise print the file nodes and counts*/
				} else {
					/*if there are 5 nodes on a line, make a new line*/
					if (j == 5) {
						fprintf(indexFile, "\n");
						j = 0;
					/*print the file nodes and counts*/
					} else {
						fprintf(indexFile, " %s %d ", fileNode_Ptr->fileName, fileNode_Ptr->count);
						fileNode_Ptr = fileNode_Ptr->next;
						j++;
					}
				}
			}
			tkNode_Ptr = tkNode_Ptr->next;
			if (tkNode_Ptr != NULL) {
				fileNode_Ptr = tkNode_Ptr->file;
			}
		}
	}	
}
/*done*/
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
/*done*/
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
/*done*/
char* Concat(char* string, char c) {
	int length = strlen(string);
	char* test = calloc(length * sizeof(char));
	test = strncat(string, &c, 1);
	return test;
}
/*done*/
char* ConcatStr(char* p1, char* p2) {
	char* test = calloc(length * sizeof(char));
	test = strcat(p1, p2);
	return test;
}

void IndexDestroy(Index *indx) {
	if (indx->array[] = NULL) {
		free(indx);
		return;
	}
	for(int i = 0; i < 36; i++) {
		
	}	
}

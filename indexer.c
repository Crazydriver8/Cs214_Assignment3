#include <dirent.h>
#include "indexer.h"
Index *IndexCreate(char* indexName) {
	Index* index = (Index*)calloc(1, sizeof(Index));
	index->Array[36];
	file_write = fopen(indexName, "w");
	if (index != NULL) {
		return index;
	}
	return NULL;
}

int IndexInsert(Index *indx, char* tk, char* fileName) {
	int indxPos = 0;
	int a, b;
	char firstChar = tk[0];

	fileNode *tempf = calloc(1, sizeof(fileNode));
	fileNode *currFile;
	fileNode *prevFile;
	fileNode *nextFile;
	tkNode *tempt = calloc(1, sizeof(fileNode));
	tkNode *current;
	tkNode *next;
	
	tempf->fileName = fileName;
	tempf->Count = 1;
	tempf->next = NULL;
	
	indxPos = Hash(firstChar);
	
/*
	if (indx->Array[indxPos].tk == NULL) {
		printf("insert to front");
		indx->Array[indxPos].tk = tk;
		indx->Array[indxPos].fileNodePTR = tempf;
		return 0;
	}

	tempt->tk = tk;
	tempt->fileNodePTR = tempf;
	tempt->next = NULL;

   	current = &indx->Array[indxPos];
	prevFile = current->fileNodePTR;
	if (current != NULL && current->next == NULL) {
		a = strcmp(current->tk, tempt->tk);
		if (a > 0) {
			printf("insert token before\n");
			tempt->next = current;
			indx->Array[indxPos].next = tempt;
			return 1;
		}
		if (a < 0) {
			printf("insert token after\n");
			current->next = tempt;
			tempt->next = NULL;
			return 1;
		}
		if (a == 0) {
			if (prevFile != NULL && prevFile->next == NULL) {
				a = strcmp(prevFile->fileName, tempf->fileName);
				if (a > 0) {
					printf("insert file before\n");
					tempf->next = prevFile;
					current->fileNodePTR = tempf;
					return 1;
				}
				if (a < 0) {
					printf("insert file after\n");
					prevFile->next = tempf;
					tempf->next = NULL;
					return 1;
				}
				if (a == 0) {
					printf("increment file count\n");
					prevFile->Count++;
					return 1;
				}
				return 0;
			}
			currFile = prevFile->next;
			while (currFile != NULL) {
				a = strcmp(currFile->fileName, tempf->fileName);
				if (a > 0) {
					printf("insert before\n");
					tempf->next = currFile;
					prevFile->next = tempf;
					return 1;
				}
				if (a == 0) {
					printf("increment count\n");
					currFile->Count++;
					return 1;
				}
				if (currFile->next == NULL) {
					printf("walk through\n");
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
	next = current->next;
	while (next != NULL) {
		a = strcmp(current->tk, tempt->tk);
		if (a > 0) {
			printf("insert token before\n");
			tempt->next = next;
			current->next = tempt;
			return 1;
		}
		if (a == 0) {
			printf("begin walk through file list\n");
            		b = strcmp(prevFile->fileName, tempf->fileName);
			currFile = current->fileNodePTR;
			if (currFile != NULL && currFile->next == NULL) {
				if (b > 0) {
					printf("insert file before\n");
					tempf->next = currFile;
					current->fileNodePTR = tempf;
					return 1;
				}
				else if (b < 0) {
					printf("insert file after\n");
					currFile->next = tempf;
					tempf->next = NULL;
					return 1;
				}
				else {
					printf("increment file count\n");
					prevFile->Count++;
					return 1;
				}
				return 0;
			}
			c = strcmp(prevFile->fileName, tempf->fileName);*/
			/*if (b > 0) {
				printf("add file before\n");
				tempf->next = currFile;
				currFile->next = tempf;
				return 1;
			}
			nextFile = currFile->next;
			while (nextFile != NULL) {
				b = strcmp(nextFile->fileName, tempf->fileName);
				if (b > 0) {
					printf("add file before\n");
					tempf->next = nextFile;
					currFile->next = tempf;
					return 1;

				}
				if (b == 0) {
					printf("increment file count\n");
					nextFile->Count++;
					return 1;
				}
				if (nextFile->next == NULL) {
					printf("add file after");
					nextFile->next = tempf;
					tempf->next = NULL;
					return 1;
				}
				currFile = nextFile;
				nextFile = nextFile->next;
			}
		}
		if (current->next == NULL) {
			printf("add token after");
			current->next = tempt;
			tempt->next = NULL;
			return 1;
		}
		current = next;
		next = next->next;
	}
	return 0;*/
}

void IndexOutput(Index *indx) {
	int i, j;
	tkNode *tkNode_Ptr;
	fileNode *fileNodeTmpPtr;
	j = 0;
	for(i = 0; i < 36; i++)
	{
		if (indx->Array == NULL) {
			printf("empty array\n");
			return;
		}
		tkNode_Ptr = &indx->Array[i];
		if(indx->Array[i].fileNodePTR != NULL) {
			fileNodeTmpPtr = indx->Array[i].fileNodePTR;
		}
		while(tkNode_Ptr != NULL)
        {
			if(tkNode_Ptr->tk != NULL)
			{
				fprintf(file_write, "<list> %s \n \n", tkNode_Ptr->tk);
			}
			while(fileNodeTmpPtr != NULL)
			{
				if (fileNodeTmpPtr->next == NULL)
				{
					fprintf(file_write, " %s %d \n \n </list> \n \n", fileNodeTmpPtr->fileName, fileNodeTmpPtr->Count);
					break;
				}
				else
				{
					if (j == 5)
					{
						fprintf(file_write, "\n");
						j = 0;
					}
					else
                    {
						fprintf(file_write, " %s %d ", fileNodeTmpPtr->fileName, fileNodeTmpPtr->Count);
						fileNodeTmpPtr = fileNodeTmpPtr->next;
						j++;
					}
				}
			}
			tkNode_Ptr = tkNode_Ptr->next;
			if (tkNode_Ptr != NULL)
            {
				fileNodeTmpPtr = tkNode_Ptr->fileNodePTR;
			}
		}
	}
}

int Hash(char c) {
	int charNum = c;
	if(charNum >= 48 && charNum <= 57) {
		charNum = charNum - 48;
		return charNum;
	}
	if(charNum >= 97 && charNum <= 122) {
		charNum = charNum - 55;
		return charNum;
	}
	printf("character not in expected range\n");
	return 0;
}

int hashToken(SortedListPtr list, char* fileName)
{
	char c;
	char* sep;
	int size, i;
	char* buffer;
	char* token;
	sep = " ";
	
	if (fileName == NULL)
    	{
        	printf("***File does not exist***\n");
		return 1;
	}

	if (access(fileName, F_OK) == 0)
    	{
		file_read = fopen(fileName, "r");
		fseek(file_read, 0L, SEEK_END);
		size = ftell(file_read);
		buffer = calloc(size, sizeof(char));
		fseek(file_read, 0L, SEEK_SET);
		printf("%d\n", size);
		for(i = 0; i < size; i++)
		{
			c = getc(file_read);
			if (c <= 90 || c >= 65 ) {
				c = tolower(c);
			}
			if (c == EOF) {
				buffer[i] = '\0';
			} else {
				buffer[i] = c;
			}
		}
		printf("%s\n", buffer);
	}
   	else
    	{
		printf("cannot read from file\n");
		return 1;
	}
	tokenizer = TKCreate(sep, buffer);/*create tokenzier object passing separator and token string*/
	for (i = 0; i < size; i++);
    	{
		token = TKGetNextToken(tokenizer);
		IndexInsert(list, indx, token, fileName);
   	}
	TKDestroy(tokenizer);
	fclose(file_read);
	return 0;
}
int ReadDir(char* dirPath)
{
	const char* dirPATH = (const char*)dirPath; 
	char *fileAccessPath; 
	DIR *dirStream; 
	struct dirent *readDir;
	list = SLCreate(cf, df);
	if((opendir(dirPATH)) == 0)
	{
		hashToken(list, (char*)dirPATH);
		return 0;
	}
	dirStream = opendir(dirPATH);
	while((readDir = readdir(dirStream)) != 0)
	{
		if(readDir->d_type == DT_REG && strcmp(readDir->d_name, ".DS_Store")) 
        	{
			fileAccessPath = (char*)dirPATH;
			fileAccessPath = Concat((char*)dirPATH, '/');
			fileAccessPath = ConcatStr(fileAccessPath, readDir->d_name);
			hashToken(list, fileAccessPath);	
		}
		else if(readDir->d_type == DT_DIR)
		{
			if(!strcmp(readDir->d_name,".") || !strcmp(readDir->d_name,".."))
            		{	
				continue;

			}
			else
            		{
				dirPATH = Concat((char*)dirPATH, '/');
				dirPATH = ConcatStr((char*)dirPATH, readDir->d_name);	
				ReadDir((char*)dirPATH);
				dirPATH = dirPath;	
			}
		}
	}
	closedir(dirStream);
	return 0;
}

char* Concat(char* string, char c) {
	char* test = malloc(sizeof(char));
	test = strncat(string, &c, 1);
	return test;
}
char* ConcatStr(char* p1, char* p2) {
	char* test;
	test = strcat(p1, p2);
	return test;
}

void IndexDestroy(Index *indx) {
	int i=0;
	tkNode *current_TK_temp = &indx->Array[0];
 	tkNode *next_TK_temp = NULL;
	fileNode *current_File_temp;
	fileNode *next_File_temp;
	if (indx->Array != NULL) {	
		current_File_temp = indx->Array[0].fileNodePTR;
		next_File_temp = NULL;
	}
	for(i = 0; i < 36; i++) {
		if (current_TK_temp != NULL) {
			if (next_TK_temp == NULL) {
				current_TK_temp = NULL;
				for(current_File_temp = current_TK_temp->fileNodePTR; current_File_temp != NULL; current_File_temp = next_File_temp) {
					next_File_temp = current_File_temp->next;
					current_File_temp->fileName = NULL;
					current_File_temp->Count = 0;
					free(current_File_temp);
				}
				free(current_TK_temp);
				continue;
			}
			for(current_TK_temp = indx->Array[i].next; current_TK_temp != NULL; current_TK_temp = next_TK_temp) {
				if (current_TK_temp->fileNodePTR == NULL) {
					next_TK_temp = current_TK_temp->next;
					current_TK_temp->tk = NULL;
					free(current_TK_temp);
					continue;
				}
				if (current_TK_temp->fileNodePTR->next == NULL) {
					next_TK_temp = current_TK_temp->next;
					current_TK_temp->tk = NULL;
					current_File_temp->fileName = NULL;
					current_File_temp->Count = 0;
					free(current_File_temp);
					free(current_TK_temp);
					continue;
				}
				for(current_File_temp = current_TK_temp->fileNodePTR; current_File_temp != NULL; current_File_temp = next_File_temp) {
					next_File_temp = current_File_temp->next;
					current_File_temp->fileName = NULL;
					current_File_temp->Count = 0;
					free(current_File_temp);
				}
				free(current_TK_temp);
			}
		}
	}
	free(indx);
}


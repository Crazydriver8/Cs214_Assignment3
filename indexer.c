#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "indexer.h"
//done no compile errors
Index *IndexCreate(char* indexName) {
	//calloc space for the index
	Index* index = (Index*)calloc(1, sizeof(Index));
	file_write = fopen(indexName, "w");
	//if the index is made right return the index
	if (index != NULL) {
		return index;
	}
	//if somehow those 2 conditions aren't met return null
	return NULL;
}
//check this

//Why do we want to return a value? Just in case we have bug testing
//It returns 0 if it detected a failure, 1 if it did not
//Can we use the sorted list to organize the nodes instead of rewriting the code
int IndexInsert(Index *indx, char* tk, char* fileName) {
	int indxPos = 0;
	char firstChar = tk[0];

	fileNode *tempf = calloc(1, (sizeof(fileNode)));
	tkNode *tempt = calloc(1, (sizeof(tkNode)));

	tempf->fileName = fileName;
	tempf->Count = 1;
	tempf->next = NULL;

	indxPos = Hash(firstChar);

	//if that position in the array is empty, add it there
	if (indx->Array[indxPos].tk == NULL) {
		indx->Array[indxPos].tk = tk;
		indx->Array[indxPos].fileNodePTR = tempf;
		return 0;
	}

	tempt->tk = tk;
	tempt->fileNodePTR = tempf;
	tempt->next = NULL;
	
	//this should set the previous node pointer to the token node
	//the bucket in the hash table is pointing at
	tkNode* previous = tkNode* indx->Array[indxPos];
    	
	fileNode* prevFile = previous->fileNodePTR;
	//if there is only one token node in the list
	if (previous != NULL && previous->next == NULL) {
		int a = strcmp(previous->tk, tempt->tk);
		if (a > 0) {
			//insert before
			tempt->next = previous;
			indx->Array[indxPos] = tempt;
			return 1;
		}
		if (a < 0) {
			//insert after
			previous->next = tempt;
			tempt->next = NULL;
			return 1;
		}
		if (a == 0) {
			//fileNode* prevFile = previous->fileNodePTR;
			if (prevFile != NULL && prevFile->next == NULL) {
				int b = strcmp(prevFile->fileName, tempf->fileName);
				if (b > 0) {
					//insert before
					tempf->next = prevFile;
					previous->fileNodePTR = tempf;
					return 1;
				}
				if (b < 0) {
					//insert after
					prevFile->next = tempf;
					tempf->next = NULL;
					return 1;
				}
				if (b == 0) {
					//increment token count in file
					prevFile->Count++;
					return 1;
				}
				return 0;
			}
			fileNode *currFile = prevFile->next;
			while (currFile != NULL) {
				int b = strcmp(currFile->fileName, tempf->fileName);
				if (b > 0) {
					//insert before
					tempf->next = currFile;
					prevFile->next = tempf;
					return 1;
				}
				if (b == 0) {
					//increment Count because same filename
					currFile->Count++;
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
		int a = strcmp(current->fileName, tempt->tk);
		if (a > 0) {
			//insert before because previous is larger than current
			tempt->next = current;
			previous->next = tempt;
			return 1;
		}
		if (a == 0) {
            int b = strcmp(prevFile, tempf);
			//same token, move through file list
			fileNode *prevFile = current->fileName;
			if (prevFile != NULL && prevFile->next == NULL) {
				if (b > 0) {
					//add before
					tempf->next = prevFile;
					previous->fileNodePTR = tempf;
					return 1;
				}
				if (b < 0) {
					//add after
					prevFile->next = tempf;
					tempf->next = NULL;
					return 1;
				}
				if (b == 0) {
					//increment token Count for file name
					prevFile->Count++;
					return 1;
				}
				return 0;
			}
			//make sure first file in list is smaller than given name
			int c = strcmp(prevFile->fileName, tempf->fileName);
			if (b > 0) {
				//add before because first file is larger
				tempf->next = prevFile;
				current->fileName = tempf;
				return 1;
			}
			fileNode *currFile = prevFile->next;
			while (currFile != NULL) {
				int b = strcmp(currFile->fileName, tempf->fileName);
				if (b > 0) {
					//add before
					tempf->next = currFile;
					prevFile->next = tempf;
					return 1;

				}
				if (b == 0) {
					//increment token Count
					currFile->Count++;
					return 1;
				}
				if (currFile->next == NULL) {
					//add after
					currFile->next = tempf;
					tempf->next = NULL;
					return 1;
				}
				prevFile = currFile;
				currFile = currFile->next;
			}
		}
		//if current->next is null add temp node to end
		if (current->next = NULL) {
			current->next = tempt;
			tempt->next = NULL;
			return 1;
		}
		//if previous token is less than current token continue walk
		previous = current;
		current = current->next;
	}
}

//done no compile errors
void IndexOutput(Index *indx) {
	int i, j;
	tkNode *tkNode_Ptr;
	fileNode *fileNodeTmpPtr;
	j = 0;
	//check all buckets in index
	for(i = 0; i < 36; i++)
    {
		tkNode_Ptr = &indx->Array[i];
		fileNodeTmpPtr = indx->Array[i].fileNodePTR;
		//while there is a token in the index bucket
		while(tkNode_Ptr != NULL)
        {
			//if the token is not null, print header with token
			if(tkNode_Ptr->tk != NULL)
			{
				fprintf(file_write, "<list> %s \n \n", tkNode_Ptr->tk);
			}
			//while the fileNode is not null
			while(fileNodeTmpPtr != NULL)
			{
				//if the next fileNode done, print the end of the list
				if (fileNodeTmpPtr->next == NULL)
				{
					fprintf(file_write, " %s %d \n \n </list> \n \n", fileNodeTmpPtr->fileName, fileNodeTmpPtr->Count);
					break;
				//otherwise print the file nodes and counts
				}
				else
				{
					//if there are 5 nodes on a line, make a new line
					if (j == 5)
					{
						fprintf(file_write, "\n");
						j = 0;
					//print the file nodes and counts
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

//done no compile errors
int Hash(char c) {
	//convert character to ascii
	int charNum = c;
	//check if character is 0-9 (48-57). If yes, put at front of array
	if(charNum >= 48 && charNum <= 57) {
		charNum = charNum - 48;
		return charNum;
	}
	//check if character is a-z (65-90 if uppercase). If yes, put after numbers
	if(charNum >= 65 && charNum <= 90) {
		charNum = charNum - 55;
		return charNum;
	}
	//returns null, prints error message
	printf("character not in expected range\n");
	return 0;
}

//done
char* ReadFile(char* fileName) {
	//if the file isn't there
	if (fileName == NULL) {
		return 1;
	}
	//make test variables for character and string, null out
	char c;
	char* test = (char*)calloc(1,(sizeof(char)));
	test = "";
	//check access permissions, should return 0 if ok
	int a = access(fileName, F_OK);
	//if we have permission, open and read
	if (a == 0) {
		//open given file, put into global file variable
		file_read = fopen(fileName, "r");
		//get the first character
		c = getc(file_read);
		//until end of file is reached concatenate all characters
		while (c != EOF) {
			c = tolower(c);
			test = Concat(test, c);
			c = getc(file_read);
		}
		fclose(file_read);
		return test;
	}
	if (a != 0) {
		printf("cannot read from file");
		return NULL;
	}
}
/*
char* ReadDir(char* dirPath) {

}*/
//done
char* Concat(char* string, char c) {
	int length = strlen(string);
	char* test = calloc(1,(length * sizeof(char)));
	test = strncat(string, &c, 1);
	return test;
}
//done
char* ConcatStr(char* p1, char* p2) {
    int length = strlen(p2);
	char* test = calloc(1,(length * sizeof(char)));
	test = strcat(p1, p2);
	return test;
}

void IndexDestroy(Index *indx) {
	//check if there is any data in hash table
	if (indx == NULL) {
		return;
	}
	int i=0;
	tkNode *current_TK_temp;
 	tkNode *next_TK_temp;
	fileNode *current_File_temp;
	fileNode *next_File_temp;
	//go through all 36 buckets of hashtable
	for(i = 0; i < 36; i++) {
		//if the bucket is not null
		if (current_TK_temp != NULL) {
			//if there are no tokens after the first token
			if (next_TK_temp == NULL) {
				//free that token and continue through the buckets
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
				//if the current_TK-temp tkNode doesn't have a fileNode
				if (current_TK_temp->fileNodePTR == NULL) {
					//free that tkNode, continue walking through tkNodes
					next_TK_temp = current_TK_temp->next;
					current_TK_temp->tk = NULL;
					free(current_TK_temp);
					continue;
				}
				//if there is only one fileNode in the tkNode
				if (current_TK_temp->fileNodePTR->next == NULL) {
					//free the fileNode and tkNode, continue walking
					next_TK_temp = current_TK_temp->next;
					current_TK_temp->tk = NULL;
					current_File_temp->fileName = NULL;
					current_File_temp->Count = 0;
					free(current_File_temp);
					free(current_TK_temp);
					continue;
				}
				//while there are more fileNodes in the tkNode
				for(current_File_temp = current_TK_temp->fileNodePTR; current_File_temp != NULL; current_File_temp = next_File_temp) {
					//walk through and free the files
					next_File_temp = current_File_temp->next;
					current_File_temp->fileName = NULL;
					current_File_temp->Count = 0;
					free(current_File_temp);
				}
				//free the tkNode and continue walking
				free(current_TK_temp);
			}
		}
	}
	//after all tkNodes and fileNodes are freed, free index and return
	free(indx);
}

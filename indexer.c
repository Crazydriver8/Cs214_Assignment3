#include <dirent.h>
#include "indexer.h"
Index *IndexCreate(char* indexName) {
	Index* index = (Index*)calloc(1, sizeof(Index));
	index->Array = malloc(36 * sizeof(tkNode));
	int i;
	/*initialize the hash table*/
	for(i = 0; i < 36; i++){
        index->Array[i].next = NULL;
        index->Array[i].fileNodePTR = NULL;
        index->Array[i].tk = NULL;
    }
	/*creates output file*/
	file_write = fopen(indexName, "w");
	if (index != NULL) {
		return index;
	}
	return NULL;
}

void IndexInsert (Index *indx, char *tk,const char *fileName)
{
	int compare;
	int duplicate = 0;
	int dupCompare;
	int hashPosition;
	int tokenNode = tk[0];
	int compareFile;
	fileNode *myFileNode = calloc(1, sizeof(fileNode));
	fileNode *currFile, *prevFile;
	fileNode *tempCurr, *tempPrev;
	fileNode *MynewFile;
	tkNode *myTokenNode;
	tkNode *current;
	tkNode *previous;
	myFileNode->fileName = fileName;
	myFileNode->next = NULL;
	myFileNode->Count = 1;
	hashPosition = Hash(tokenNode);
	/*front of linked list is empty*/
	printf("hash position is %d\n", hashPosition);
	printf("token is %s\n", indx->Array[hashPosition].tk);
	if(indx->Array[hashPosition].tk == NULL)
	{
        	indx->Array[hashPosition].tk = tk;
		printf("new token is %s\n", indx->Array[hashPosition].tk);
       		indx->Array[hashPosition].fileNodePTR = myFileNode;
    	}
   	else 
    	{    
		/*linked list not empty*/
        	myTokenNode = calloc(1,sizeof(tkNode));
	        myTokenNode->tk = tk;
		printf("myTokenNode = %s\n", myTokenNode->tk);
	        myTokenNode->next = NULL;
	        myTokenNode->fileNodePTR = myFileNode;
	        current = &indx->Array[hashPosition];
	        previous = NULL;
        
	        /*determine if a duplicate token exists*/
	        while(current != NULL)
	        {
	            printf("1st %s\n",myTokenNode->tk);
	            printf("2nd %s\n",current->tk);
	            dupCompare = compareStrings(myTokenNode->tk, current->tk);
	            if(dupCompare == 0){
	            duplicate = 1;
   	        }
        	previous = current;
        	current = current->next;
        }
        current = &indx->Array[hashPosition];
        previous = NULL;
	/*determine token position in linked list*/
        while(current != NULL)
        {
        	compare = compareStrings(myTokenNode->tk, current->tk);
		/*token goes before the token its being compared to*/
        	if(compare < 0 && !duplicate)
        	{
                	/*new token needs to be at front of linked list*/
                	if(previous == NULL)
                	{
                	/*a node already exists will be placed front of list*/
                		if(indx->Array[hashPosition].next != NULL)
               			{
                		        current->next = indx->Array[hashPosition].next;
                		        indx->Array[hashPosition].next = myTokenNode;
                       			myTokenNode->tk = indx->Array[hashPosition].tk;
		                        myTokenNode->fileNodePTR = indx->Array[hashPosition].fileNodePTR;
		                        indx->Array[hashPosition].tk = tk;
       			                indx->Array[hashPosition].fileNodePTR = myFileNode;
                    		}
                    		/*only one token in the list*/
                   		else
                   		{
                     			indx->Array[hashPosition].next = myTokenNode;
	                        	myTokenNode->tk = indx->Array[hashPosition].tk;
	                      		myTokenNode->fileNodePTR = indx->Array[hashPosition].fileNodePTR;
	    			        indx->Array[hashPosition].tk = tk;
	        	                indx->Array[hashPosition].fileNodePTR = myFileNode;
		                }
       		         }
        	        /*insert token in the middle*/
        	        else
        	        {
        		    myTokenNode->next = previous->next;
       		            previous->next = myTokenNode;
                	}
         	       return;
		}
			
		else if(compare > 0 && !duplicate)
		{
                /*token goes at the end of linked list*/
        	        if(current->next == NULL)
        	        {
        	            current->next = myTokenNode;
        	            return;
        	        }
                
      		}
        	/*increase file frequency count or add new file node*/
        	else if(compare == 0)
            	{
            		currFile = current->fileNodePTR;
            		prevFile = NULL;
               		/*find if there exists the same file*/
            		while(currFile != NULL)
    		        {
                		compareFile = compareStrings((char*)fileName, (char*)currFile->fileName);
                    		/*word and file already exists increment frequency count*/
                   		 if(compareFile == 0)
                    		{
                    			currFile->Count++;
                        		/*sort if necassary*/
                     			if(prevFile != NULL)
                     			{
                            			/*sorts filenames according to token count*/
                     			       	if(prevFile->Count > currFile->Count)
                            			{
                               				 return;
                            			}
                           			 /*files out of order*/
                     			       else 
                  			       {
                                			/*take file_node out of list to re-sort*/
                            				prevFile->next = currFile->next;
                    				        tempCurr = current->fileNodePTR;
                                			tempPrev = NULL;
                                			while(tempCurr != NULL)
                                			{
                            				        if(tempCurr->Count < currFile->Count)
                          				        {
                        				                if(tempPrev == NULL)
                                       					{
                                   					        current->fileNodePTR = currFile;
                                            					currFile->next = tempCurr;
                                            					return;
                                        				}
                                       					else
                                        				{
                                  					        tempPrev->next = currFile;
                                          					currFile->next = tempCurr;
                                        					return;
                                        				}
                                    				}
                                   			tempPrev = tempCurr;
                                 			tempCurr = tempCurr->next;
                                			}
                            			}
                        		}
                        		/*file incremented was first in list*/
                        		else
                        		{
                        			return;
                       			}
                    		}
                    		prevFile = currFile;
                    		currFile = currFile->next;
                	}
                	/*first occurence of this word in this file*/
                	MynewFile = (fileNode*)calloc(1,(sizeof(fileNode)));
                	MynewFile->fileName = fileName;
                	MynewFile->Count = 1;
               		MynewFile->next = NULL;
                	prevFile->next = MynewFile;
               		return;   
            	}
            	previous = current;
            	current = current->next;
     	}
    }
}
void IndexOutput(Index *indx) {/*original*/
	int i, j;
	tkNode *tkNode_Ptr;
	fileNode *fileNodeTmpPtr;
	j = 0;
	/*check all buckets in index*/
	for(i = 0; i < 36; i++)
    {
		tkNode_Ptr = &indx->Array[i];
		fileNodeTmpPtr = indx->Array[i].fileNodePTR;
		/*while there is a token in the index bucket*/
		while(tkNode_Ptr != NULL)
        {
			/*if the token is not null, print header with token*/
			if(tkNode_Ptr->tk != NULL)
			{
				fprintf(file_write, "<list> %s \n \n", tkNode_Ptr->tk);
			}
			/*while the fileNode is not null*/
			while(fileNodeTmpPtr != NULL)
			{
				/*if the next fileNode done, print the end of the list*/
				if (fileNodeTmpPtr->next == NULL)
				{
					fprintf(file_write, " %s %d \n \n </list> \n \n", fileNodeTmpPtr->fileName, fileNodeTmpPtr->Count);
					break;
				/*otherwise print the file nodes and counts*/
				}
				else
				{
					/*if there are 5 nodes on a line, make a new line*/
					if (j == 5)
					{
						fprintf(file_write, "\n");
						j = 0;
					/*print the file nodes and counts*/
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
	printf("charNum = %d\n", c);
	if(charNum >= 48 && charNum <= 57) {
		charNum = charNum - 48;
		return charNum;
	}
	if(charNum >= 97 && charNum <= 122) {
		charNum = charNum - 87;
		return charNum;
	}
	printf("character not in expected range\n");
	return 0;
}

int hashToken(const char *fileName){
    if(fileName == NULL){   //file doens't exist
        printf("***Filename does not exist***\n");
        return 1;
    }
    int fileCheck;
    char c, *sep;
    char *string = (char*)malloc(sizeof(char));
    string = "";
    sep = " \t\n";
    fileCheck = access(fileName, F_OK);
    if(fileCheck == 0){ /*open file */
        file_read = fopen(fileName, "r");
        c = getc(file_read);
        while(c != EOF){    /*create string to send to tokenizer*/
            c = tolower(c);
            printf("c = %c\n", c);
            string = Concat(string, c);
            c = getc(file_read);
        }
        printf("after while\n");
    }
        printf("after if\n");
    tokenizer = TKCreate(sep, string);
    printf("after call to tokenizer\n");
    char* token = TKGetNextToken(tokenizer);
    printf("after get next token\n");
    while(token != NULL ){ /*parse and insert tokens into hash table*/
    	printf("%s\n", token);
	IndexInsert(indx, token, fileName);
	token = TKGetNextToken(tokenizer);        
    }
    printf("before free token\n");
    free(token);
    fclose(file_read);
    printf("after file close\n");
    return 0;
}

int ReadDir(char* dirPath)
{
	printf("readdir hit\n");
    char *dirPATH = dirPath; //string contains directory path *path
    char *fileAccesPath; //string containing file path *filePath
    DIR *dirStream; //directory stream *dir
    struct dirent *readDir; //*entry;
    //if file hash it
    if((readDir = opendir(dirPATH)) == 0)
    {
		printf("hashtoken reached\n");
        hashToken(dirPATH);
        return 0;
    }
    //search through the file system to find and read all files
    while((readDir = readdir(dirStream)) != 0)
    {
        if(readDir->d_type == DT_REG && compareStrings(readDir->d_name, ".DS_Store")) //not hidden file
        {
			fileAccesPath = dirPATH;
			fileAccesPath = Concat(dirPATH, '/');//add "/" to string in dirPath
			fileAccesPath = ConcatStr(fileAccesPath, readDir->d_name);
			hashToken(fileAccesPath);	//hash file
		}
		else if(readDir->d_type == DT_DIR)//it is a directory
		{
			if(!compareStrings(readDir->d_name,".") || !compareStrings(readDir->d_name,".."))
            {	//if directory is a . or .. skip it
				continue;

			}
			else
            {
				dirPATH = Concat(dirPATH, '/');
				dirPATH = ConcatStr(dirPATH, readDir->d_name);	//concatenate "/" and directory name for recursing
				ReadDir(dirPATH);
				dirPATH = dirPath;	//after recursing reset path to current directory
			}
		}
    }
    closedir(dirStream);
	return 0;
}
char *Concat(char *string, char letter){    //concatenate character to end of a string
    char *str = string;
    char let = letter;
    size_t len = strlen(str);
    char *result = (char*) malloc((len + 2) * sizeof(char));
    memset (result,0,len+2);
    strcpy(result, str);
    result[len] = let;
    return result;
}

char *ConcatStr(char *string1, char *string2){   //concatenate 2 strings together
    size_t len = strlen(string2);
    int i;
    for(i = 0; i<len; i++){
        string1 = Concat(string1, string2[i]);
    }
    return string1;
}
void IndexDestroy(Index *indx) {
	int i;
    tkNode *tempT, *next;
    fileNode *tempF, *next2;
    for(i = 0; i < 36; i++){    
        for(tempT = indx->Array[i].next; tempT != NULL; tempT = next){ 
            next = tempT->next;
            tempT->tk = NULL;
            for(tempF = tempT->fileNodePTR; tempF != NULL; tempF = next2){ 
                next2 = tempF->next;
                tempF->fileName = NULL;
                tempF->Count = 0;
                free(tempF);
            }
            free(tempT);
        }
    }
    free(indx);
    if(tokenizer != NULL){
        TKDestroy(tokenizer);
    }   
    fclose(file_write);
}

int compareStrings(char *p1, char *p2){
    return strcmp(p1, p2);
}

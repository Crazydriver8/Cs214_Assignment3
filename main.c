/*
Laszlo Glant & Brandon Berrios
*/
#include <stdio.h>
#include <string.h>
#include "indexer.h"
int main(int argc, char * argv[]) {
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
    indx = IndexCreate(argv[1]);
    ReadDir((char*)argv[2]);
    IndexOutput(indx);
    IndexDestroy(indx);
    return 0;
} 
   /*
    **************PSEUDO CODE******************
    user enters file_name output_file_name input_dir/file_name
    IN MAIN with arg[1] call IndexCreate DONE
    IN MAIN with arg[2] call read file/read dir (probably it should be one method)DONE
    IN READdIR (from within read/dir function should call hash token *TO BE WRITTEN* function) DONE
    IN HASHtOKEN that will call tokenizer with the string from file, get the tokens and DONE
        call indexInsert to insert tokens into the hash table
    IN MAIN when no more files/dir found call IndexOutput to write the data in hash table DONE
    IN MAIN call indexDestroy to free memory DONE
}*/

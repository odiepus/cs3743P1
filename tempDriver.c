#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

int hashCreate(char *name);
FILE *hashOpen(char *name);
void errExit(const char szFmt[], ... );

int main(int argc, char *argv[]){
  char *input = argv[0];

  while(strcmp(input, "exit") != 0){
    fgets(input, 80, stdin);
    char *pos;
    if( (pos = strchr(input, '\n')) != NULL ){
      *pos = '\0';
    }
    if(strcmp(input, "CREATE") == 0 ){
      char *book = "book.dat";
      int rc = hashCreate(book);
      if (rc != 0){
        printf("book exists!!\n");
      }
    }
    else if( strcmp(input, "OPEN") == 0 ){
      char *book = "book.dat";
      FILE * bookPtr;
      bookPtr = hashOpen(book);
      if(1){
        printf("I made it here!\n");
        return 0;
      }
    }
    else if(strcmp(input, "INSERT") == 0){
      char *insertBook = "JOYPGM001,"
    }
  }
  return 0;
}


int hashCreate(char *name){
  FILE *pHashFile;

  pHashFile = fopen(name, "rb");

  if (pHashFile == NULL){
    pHashFile = fopen(name, "wb+");

    if (pHashFile == NULL){
      errExit("Failed to created file");
    }

    fclose(pHashFile);

    return 0;
  }

  return 1;
}

//opens the hash file specified
FILE *hashOpen(char *name){
  FILE *pHashOpenFile;

  pHashOpenFile = fopen(name, "rb");

  if (pHashOpenFile == NULL){
    return NULL;
  }

  return pHashOpenFile;
}

void errExit(const char szFmt[], ... )
{
    printf("\n");
    exit(200);
}


#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include "cs3743p1.h"



int hashCreate(char szFileNm[], HashHeader *pHashHeader){
  FILE *pHashFile = fopen(szFileNm, "rb");

  if (pHashFile == NULL){
    pHashFile = fopen(szFileNm, "wb+");

    if (pHashFile == NULL){
      errExit("Failed to created file");
    }

    pHashHeader->iHighOverflowRBN = pHashHeader->iNumPrimary;

    int iWriteToHash = fwrite(&pHashHeader, sizeof(HashHeader), 1L, pHashFile);
    assert(iWriteToHash == 1);

    fclose(pHashFile);

    return RC_OK;
  }

  fclose(pHashFile);
  return RC_FILE_EXISTS;
}

//opens the hash file specified
FILE *hashOpen(char szFileNm[], HashHeader *pHashHeader){
  FILE *pHashOpenFile = fopen(szFileNm, "rb");

  if (pHashOpenFile == NULL){
    return NULL;
  }

  int iReadHeader = fread(pHashHeader, sizeof(HashHeader), 1L, pHashOpenFile);

  if(iReadHeader == 1){
    return pHashOpenFile;
  }
  return NULL;
}

int readRec(FILE *pFile, int iRBN, void *pRecord, int iRecSize){
	int rcFseek = fseek(pFile, iRBN, SEEK_SET);
	assert(rcFseek == 0);

	int iReadRec = fread(&pRecord, sizeof(&pRecord), 1L, pFile);

	if (iReadRec == 1){
		return RC_OK;
	}

  return RC_LOC_NOT_FOUND;
}

int writeRec(FILE *pFile, int iRBN, void *pRecord, int iRecSize){
  int rcFseek = fseek(pFile, iRBN*iRecSize, SEEK_SET);
  int iWriteToHashFile = fwrite(&pRecord, iRecSize, 1L, pFile);

  if (iWriteToHashFile != 1){
    return RC_LOC_NOT_WRITTEN;
  }
  return RC_OK;
}


int bookInsert(FILE *pFile, HashHeader *pHashHeader, Book *pBook){
  int iRBN = hash(pBook->szBookId, pHashHeader);
  int rcFseek = fseek(pFile, iRBN, SEEK_SET);
  Book *pTempBook;
  int iReadHashFile = fread(pTempBook, sizeof(HashHeader), 1L, pFile);

  if (iReadHashFile == 0 || pTempBook->szBookId == '\0'){
    pBook->iNextChain = 0;
    int rcWrite = writeRec(pFile, iRBN, pBook, sizeof(Book));
    return rcWrite;
  }
  else if(pTempBook->szBookId != '\0' && pTempBook->szBookId == pBook->szBookId){
    return RC_REC_EXISTS;
  }
  else{
    return RC_SYNONYM;
  }
}

int bookRead(FILE *pFile, HashHeader *pHashHeader, Book *pBook){

  return 0;
}

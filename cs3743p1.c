
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include "cs3743p1.h"



int hashCreate(char szFileNm[], HashHeader *pHashHeader){
  int iWriteToHash;
  FILE *pHashFile;

  pHashFile = fopen(szFileNm, "rb");

  if (pHashFile == NULL){
    pHashFile = fopen(szFileNm, "wb+");

    if (pHashFile == NULL){
      errExit("Failed to created file");
    }

    pHashHeader->iHighOverflowRBN = pHashHeader->iNumPrimary;

    iWriteToHash = fwrite(&pHashHeader, sizeof(HashHeader), 1L, pHashFile);
    assert(iWriteToHash == 1);

    fclose(pHashFile);

    return RC_OK;
  }

  fclose(pHashFile);
  return RC_FILE_EXISTS;
}

//opens the hash file specified
FILE *hashOpen(char szFileNm[], HashHeader *pHashHeader){
  int iReadHeader;
  FILE *pHashOpenFile;

  pHashOpenFile = fopen(szFileNm, "rb");

  if (pHashOpenFile == NULL){
    return NULL;
  }

  iReadHeader = fread(pHashHeader, sizeof(HashHeader), 1L, pHashOpenFile);
  if(iReadHeader == 1){
    return pHashOpenFile;
  }
  return NULL;
}

int readRec(FILE *pFile, int iRBN, void *pRecord, int iRecSize){
	int iReadRec;
	int rcFseek;

	rcFseek = fseek(pFile, iRBN, SEEK_SET);
	assert(rcFseek == 0);

	iReadRec = fread(&pRecord, sizeof(&pRecord), 1L, pFile);

	if (iReadRec == 1){
		return RC_OK;
	}

  return RC_LOC_NOT_FOUND;
}

int writeRec(FILE *pFile, int iRBN, void *pRecord, int iRecSize){
  int rcFseek;
  int iWriteToHashFile;

  rcFseek = fseek(pFile, iRBN, SEEK_SET);
  iWriteToHashFile = fwrite(&pRecord, sizeof(pRecord), 1L, pFile);
  if (iWriteToHashFile != 1){
    return RC_LOC_NOT_WRITTEN;
  }
  return RC_OK;
}


int bookInsert(FILE *pFile, HashHeader *pHashHeader, Book *pBook){
  int iRBN = hash(pBook->szBookId, pHashHeader);
  int rcFseek = fseek(&pHashHeader, iRBN, SEEK_SET);
  int iReadHashFile = fread(&pHashHeader, sizeof(HashHeader), 1L, pFile);

  if ()
  int iWriteToHashFile = fwrite(&pHashHeader, sizeof(HashHeader), 1L, pFile);

  


  return 0;
}

int bookRead(FILE *pFile, HashHeader *pHashHeader, Book *pBook){

  return 0;
}

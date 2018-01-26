
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include "cs3743p1.h"


FILE *pHashFile;

int hashCreate(char szFileNm[], HashHeader *pHashHeader){
  int rcFseek;
  int iWriteToHash;

  pHashFile = fopen(szFileNm, "r");

  if (pHashFile == NULL){
    pHashFile = fopen(szFileNm, "wb+");

    if (pHashFile == NULL){
      errExit("Failed to created file");
    }
  }
  else{
    return RC_FILE_EXISTS;
  }

  pHashHeader->iHighOverflowRBN = pHashHeader->iNumPrimary;
  rcFseek = fseek(pHashFile, 0, SEEK_SET);
  assert(rcFseek == 0);

  iWriteToHash = fwrite(&pHashHeader, sizeof(HashHeader), 1L, pHashFile);
  assert(iWriteToHash == 1);

  fclose(pHashFile);

  return RC_OK;
}

FILE *hashOpen(char szFileNm[], HashHeader *pHashHeader){
  int rcFseek;
  int iReadHeader;
  pHashFile = fopen(szFileNm, "r");

  if (pHashFile == NULL){
    return NULL;
  }

  rcFseek = fseek(pHashFile, 0, SEEK_SET);
  assert(rcFseek == 0);

  iReadHeader = fread(&pHashHeader, sizeof(HashHeader), 1L, pHashFile);
  if(iReadHeader == 1){
    return pHashFile;
  }
  else{
    return NULL;
  }
}

int readRec(FILE *pFile, int iRBN, void *pRecord, int iRecSize){

  return 0;
}

int writeRec(FILE *pFile, int iRBN, void *pRecord, int iRecSize){

  return 0;
}

int bookInsert(FILE *pFile, HashHeader *pHashHeader, Book *pBook){

  return 0;
}

int bookRead(FILE *pFile, HashHeader *pHashHeader, Book *pBook){

  return 0;
}

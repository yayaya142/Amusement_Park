#ifndef __GENERAL__
#define __GENERAL__

#include <crtdbg.h> // TODO: remove before release
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define MAX_STR_LEN 255
// define macros
#define SUM(x,y) ((x)+(y))


char* getStrExactName(const char* msg);
char* myGets(char* buffer, int size);
char* getDynStr(char* str);
char** splitCharsToWords(char* str, int* pCount, int* pTotalLength);
void generalArrayFunction(void* arr, int size, size_t typeSize, void* (*func)(void* element));
int randomNum(int min, int max);
int validName(char* name);

#endif


#ifndef __GENERAL__
#define __GENERAL__

#define MAX_STR_LEN 255

// define macros
#define SUM(x,y) ((x)+(y))



#include <crtdbg.h> // TODO: remove before release


char* getStrExactName(const char* msg);
char* myGets(char* buffer, int size);
char* getDynStr(char* str);
char** splitCharsToWords(char* str, int* pCount, int* pTotalLength);
void generalArrayFunction(void* arr, int size, size_t typeSize, void* (*func)(void* element));
int randomNum(int min, int max);
int validName(char* name);

#endif


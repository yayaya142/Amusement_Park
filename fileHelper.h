#ifndef __FILE_HELPER__
#define __FILE_HELPER__


#include <crtdbg.h> // TODO: remove before release
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "General.h"

#define MAX_BUFFER_SIZE 256

int writeStringToTextFile(FILE* file, const char* str);
int writeIntToTextFile(FILE* file, int num);
int writeDoubleToTextFile(FILE* file, const double num);
int writeStringTobinFile(FILE* file, const char* str);
int readIntFromTextFile(FILE* file, int* num);
int readDoubleFromTextFile(FILE* file, double* num);
char* readStringFromTextFile(FILE* file, char* buffer, int size);
char* readStringFromBinFile(FILE* file);
int writeGeneralToBinFile(FILE* file, void* fileType, size_t sizeOfElement);
int readGeneralFromBinFile(FILE* file, void* readValue, size_t sizeOfElement);




#endif 

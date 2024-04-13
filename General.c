#include "General.h"



char* getStrExactName(const char* msg)
{
	char* str;
	char temp[MAX_STR_LEN];
	if (msg != NULL) {
		printf("%s", msg);
	}
	myGets(temp, MAX_STR_LEN);

	str = getDynStr(temp);
	return str;
}

char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
		return NULL;

	strcpy(theStr, str);
	return theStr;
}

char* myGets(char* buffer, int size)
{
	char* ok;
	if (buffer != NULL && size > 0)
	{
		do { //skip only '\n' strings
			ok = fgets(buffer, size, stdin);
		} while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
		if (ok)
		{
			char* back = buffer + strlen(buffer);
			//trim end spaces
			while ((buffer < back) && (isspace(*--back)));
			*(back + 1) = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}

char** splitCharsToWords(char* str, int* pCount, int* pTotalLength)
{
	char temp[255];
	char* delimiters = " ";
	char* word;
	int count = 0;

	strcpy(temp, str);
	char** wordsArray = NULL;
	*pTotalLength = 0;

	word = strtok(temp, delimiters);
	while (word != NULL)
	{
		char** temp = (char**)realloc(wordsArray, (count + 1) * sizeof(char*));
		if (!temp)
			return NULL;
		wordsArray = temp;
		wordsArray[count] = getDynStr(word);
		count++;
		*pTotalLength += (int)strlen(word);
		word = strtok(NULL, delimiters);
	}
	*pCount = count;
	return wordsArray;
}





// general function to activate a function on each element of an array
void generalArrayFunction(void* arr, int size, size_t typeSize, void* (*func)(void* element)) {
	if (!arr) {
		return;
	}
	for (int i = 0; i < size; i++)
	{
		// use the function on each element of the array
		func((char*)(arr)+i * typeSize);
	}
}


int randomNum(int min, int max) {
	return rand() % (max - min + 1) + min;
}

int validName(char* name) {
	if (name == NULL || strlen(name) == 0) {
		return 0;
	}
	for (int i = 0; i < strlen(name); i++) {
		if (((name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z')) && name[i] != ' ') {
			return 0;
		}
	}
	return 1;
}
#include "fileHelperShai.h"



/////////////////////////////////////////////////////////////////
// writeStringToFile
// Aim: To write string to text file	
// Input: file pointer, string to write
// Output: 1 if succeeded
/////////////////////////////////////////////////////////////////
int writeStringToTextFile(FILE* file, const char* str) {
	if (!file) {
		return 0;
	}
	fprintf(file, "%s\n", str);
	return 1;
}

/////////////////////////////////////////////////////////////////
// writeIntToTextFile
// Aim: To write int to text file
// Input: file pointer, int to write
// Output: 1 if succeeded
/////////////////////////////////////////////////////////////////
int writeIntToTextFile(FILE* file, int num) {
	if (!file) {
		return 0;
	}
	fprintf(file, "%d\n", num);
	return 1;
}


/////////////////////////////////////////////////////////////////
// writeStringTobinFile
// Aim: To write string to binary file
// Input: file pointer, string to write
// Output: 1 if succeeded
/////////////////////////////////////////////////////////////////

int writeStringTobinFile(FILE* file, const char* str) {
	if (!file) {
		return 0;
	}
	size_t len = (size_t)strlen(str) + 1; // +1 for the null terminator
	// write the length of the string
	if (fwrite(&len, sizeof(int), 1, file) != 1)
		return 0;
	// write the string
	if (fwrite(str, sizeof(char), len, file) != len)
		return 0;

	return 1;
}

/////////////////////////////////////////////////////////////////
// readStringFromTextFile
// Aim: To read string from text file
// Input: file pointer
// Output: dynamic allocated string read from file
/////////////////////////////////////////////////////////////////
char* readStringFromTextFile(FILE* file, char* buffer, int size) {
	// allocate dynamic memory for the string make sure to use cautiously! 
	char* ok;
	if (buffer != NULL && size > 0)
	{
		do { //skip only '\n' strings
			ok = fgets(buffer, size, file);
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


/////////////////////////////////////////////////////////////////
// readIntFromTextFile
// Aim: To read int from text file
// Input: file pointer
// Output: int read from file
/////////////////////////////////////////////////////////////////



int readIntFromTextFile(FILE* file, int* num) {
	if (!file) {
		return 0;
	}
	if (fscanf(file, "%d", num) != 1) {
		return 0;
	}
	return 1;
}


/////////////////////////////////////////////////////////////////
// readStringFromBinFile
// Aim: To read string from binary file
// Input: file pointer
// Output: dynamic allocated string read from file
/////////////////////////////////////////////////////////////////
char* readStringFromBinFile(FILE* file) {
	// allocate dynamic memory for the string make sure to use cautiously!
	if (!file) {
		return NULL;
	}
	int len;
	if (fread(&len, sizeof(int), 1, file) != 1) {
		return NULL;
	}
	char* str = (char*)malloc((len) * sizeof(char)); // TODO it was len+1 before need to make sure it work
	if (!str) {
		return NULL;
	}
	if (fread(str, sizeof(char), len, file) != len) {
		free(str);
		return NULL;
	}
	//str[len] = '\0'; // TODO need to check if it is needed
	return str;
}

/////////////////////////////////////////////////////////////////
// writeGeneralToBinFile
// Aim: To write any type of data to binary file
// Input: file pointer, data to write, size of the data
// Output: 1 if succeeded
/////////////////////////////////////////////////////////////////
int writeGeneralToBinFile(FILE* file, void* fileType, size_t sizeOfElement) {
	if (!file) {
		return 0;
	}

	if (fwrite(fileType, sizeOfElement, 1, file) != 1) {
		return 0;
	}
	return 1;
}



/////////////////////////////////////////////////////////////////
// readGeneralFromBinFile
// Aim: To read any type of data from binary file
// Input: file pointer, data to read, size of the data
// Output: 1 if succeeded
/////////////////////////////////////////////////////////////////
int readGeneralFromBinFile(FILE* file, void* readValue, size_t sizeOfElement) {
	if (!file) {
		return 0;
	}
	if (fread(readValue, sizeOfElement, 1, file) != 1) {
		return 0;
	}
	return 1;
}
#ifndef __PERSON_H__
#define __PERSON_H__

#include <stdio.h>
#include "General.h"
#include <stdlib.h>
#include <string.h>
#include "fileHelper.h"
#include <crtdbg.h> // TODO: remove before release

typedef struct _Person Person;

typedef void (*fptrinitPersonByUser)(Person*);
typedef void (*fptrPrintPerson)(const Person*);
typedef int (*fptrComparePersonByHeight)(const Person*, const Person*);
typedef void (*fptrFreePerson)(Person*);
typedef void (*fptrSavePersonToTextFile)(const Person*, FILE*);
typedef void (*fptrLoadPersonFromTextFile)(Person**, FILE*);
typedef void (*fptrSavePersonToBinFile)(const Person*, FILE*);
typedef void (*fptrLoadPersonFromBinFile)(Person**, FILE*);


typedef struct _Person {  
	void* pDerived;
	char* name;
	int age;
	double height;

	//function pointers (interfaces)
	fptrinitPersonByUser initPersonByUser;
	fptrPrintPerson printPerson;
	fptrFreePerson freePerson;
	fptrComparePersonByHeight comparePersonByHeight;
	fptrSavePersonToTextFile savePersonToTextFile;
	fptrLoadPersonFromTextFile loadPersonFromTextFile;
	fptrSavePersonToBinFile savePersonToBinFile;
	fptrLoadPersonFromBinFile loadPersonFromBinFile;
} Person;

Person* initPerson(char* name, double height, int age);//constructor
void freePerson(Person* p); //destructor
Person* initPersonByUser();
int isValidInfo(char* name, double height, int age);
int comparePersonByHeight(const Person* p1,const Person* p2);
void printPerson(const Person* p);
// save and load functions
int savePersonToTextFile(const Person* person, FILE* fp);
int loadPersonFromTextFile(Person** person, FILE* fp);
int savePersonToBinFile(const Person* person, FILE* fp);
int loadPersonFromBinFile(Person** person, FILE* fp);

#endif
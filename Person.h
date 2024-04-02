#ifndef __PERSON_H__
#define __PERSON_H__

#include <stdio.h>
#include "General.h"
#include <crtdbg.h> // TODO: remove before release

typedef struct _Person Person;

typedef void (*fptrinitPersonByUser)(Person*);
typedef void (*fptrPrintPerson)(const Person*);
typedef int (*fptrComparePersonByHeight)(const Person*, const Person*);
typedef void (*fptrFreePerson)(Person*);


typedef struct _Person {  
	char* name;
	int age;
	float height;
	//function pointers (interfaces)
	fptrinitPersonByUser initPersonByUser;
	fptrPrintPerson printPerson;
	fptrFreePerson freePerson;
	fptrComparePersonByHeight comparePersonByHeight;
} Person;

Person* initPerson(char* name, float height, int age);//constructor
void freePerson(Person* p); //destructor
Person* initPersonByUser();
int isValidInfo(char* name, float height, int age);
int comparePersonByHeight(const Person* p1,const Person* p2);
void printPerson(const Person* p);

#endif
#ifndef __PERSON_H__
#define __PERSON_H__

#include <stdio.h>
#include "General.h"
#include <crtdbg.h> // TODO: remove before release

typedef struct {  
	char* name;
	int age;
	float height;
} Person;

int initPerson(Person* p, char* name, float height, int age);
void initPersonByUser(Person* p);
int isValidInfo(char* name, float height, int age);
int comparePersonByHeight(const Person* p1,const Person* p2);
void printPerson(const Person* p);
void freePerson(Person* p);
#endif
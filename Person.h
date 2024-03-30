#ifndef __PERSON_H__
#define __PERSON_H__

#include <stdio.h>
#include "General.h"
#include <crtdbg.h> // TODO: remove before release

typedef struct {
	char* name;
	int age;
	float height;
	int id;
} Person;

int initPerson(Person* p, char* name, int height, int age, int id);
int isValidInfo(char* name, int height, int age, int id);
int comparePersonByHeight(Person* p1, Person* p2);
int comparePersonById(Person* p1, Person* p2);
void printPerson(Person* p);
void freePerson(Person* p);
#endif
#ifndef __WORKER_H__
#define __WORKER_H__
#define WORK_ID 8

#include "Person.h"
#include "General.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h> // TODO: remove before release

typedef struct _Worker Worker;
 

typedef enum { eCoffeeShop, eSecurity, eRestarunt, eStands, eNofTypes } Department;
static const char* typeTilte[eNofTypes] = { "CoffeeShop", "Security", "Restarunt", "Stands" };

typedef struct _Worker{
	Person*  personBase;
	int		WorkerId;
	Department department;	
} Worker;

Person* initWorker(Department dep, char* name, float height, int age); // constructor
void freeWorker(Person* worker); // destructor
Person* initWorkerByUser();
int isValidInfoWorker(Department department);
int generateWorkerID();
void printWorker(const Person* worker);


#endif
#ifndef __WORKER_H__
#define __WORKER_H__
#define WORK_ID 8

#include "Person.h"
#include "General.h"
#include <crtdbg.h> // TODO: remove before release

typedef struct _Worker Worker;
 

typedef enum { eCoffeeShop, eSecurity, eRestarunt, eStands, eNofTypes } Department;
static const char* typeTilte[eNofTypes] = { "CoffeeShop", "Security", "Restarunt", "Stands" };

typedef struct _Worker{
	Person*  personBase;
	int		WorkerId;
	Department department;
	//interfaces
	
} Worker;

Person* initWorker(Department dep, char* name, float height, int age); // constructor
void freeWorker(Person* worker); // destructor
Person* initWorkerByUser(Worker* w);
int isValidInfoWorker(Department department);
int generateWorkerID();
void printWorker(const Person* worker);


#endif
#ifndef __WORKER_H__
#define __WORKER_H__
#define WORK_ID 8

#include "Person.h"
#include "General.h"
#include <crtdbg.h> // TODO: remove before release


typedef enum { eCoffeeShop, eSecurity, eRestarunt, eStands, eNofTypes } Department;
static const char* typeTilte[eNofTypes] = { "CoffeeShop", "Security", "Restarunt", "Stands" };

typedef struct {
	Person*  person;//TODO: WATCH OUT
	int		WorkerId;
	Department department;
} Worker;

int initWorker(Worker* w, Person* p , Department dep);
void initWorkerByUser(Worker* w);
int isValidInfoWorker(Department department);
int generateWorkerID();
void printWorker(const void* worker);
void freeWorker(Worker* worker);

#endif
#ifndef __WORKER_H__
#define __WORKER_H__

#include "Person.h"
#include <crtdbg.h> // TODO: remove before release


typedef enum { CoffeeShop, Security, Restarunt, Stands, NofTypes } Department;
static const char* typeTilte[NofTypes] = { "CoffeeShop", "Security", "Restarunt", "Stands" };

typedef struct {
	Person  person;
	int		WorkerId;
	Department department;
} Worker;

int initWorker(Worker* w, int workerId, Department dep);
int isValidInfoWorker(int WorkerId, Department department);
void printWorker(const Worker* worker);
void freeWorker(Worker* worker);

#endif
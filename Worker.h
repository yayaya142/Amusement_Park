#ifndef __WORKER_H__
#define __WORKER_H__
#define WORK_ID 8

#include "Person.h"
#include "General.h"
#include "fileHelper.h"
#include "Shop.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h> // TODO: remove before release

typedef struct _Worker Worker;
 

//typedef enum { eCoffeeShop, eSecurity, eRestarunt, eStands, eNofTypes } Department;
//static const char* typeTilte[eNofTypes] = { "CoffeeShop", "Security", "Restarunt", "Stands" };

typedef struct _Worker{
	Person*  personBase;
	int		WorkerId;
	eShopType department;
} Worker;

Person* initWorker(eShopType dep, char* name, double height, int age); // constructor
void freeWorker(Person* worker); // destructor
Person* initWorkerByUser();
int isValidInfoWorker(eShopType department);
int generateWorkerID();
void printWorker(const Person* worker);

// save and load functions
int saveWorkerToTextFile(const Person* worker, FILE* fp);
int loadWorkerFromTextFile(Person** worker, FILE* fp);
int saveWorkerToBinFile(const Person* worker, FILE* fp);
int loadWorkerFromBinFile(Person** worker, FILE* fp);

#endif
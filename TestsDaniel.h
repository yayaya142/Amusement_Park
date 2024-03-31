#ifndef __TESTS_DANIEL__
#define __TESTS_DANIEL__

#include <crtdbg.h> // TODO: remove before release
#include <assert.h>
#include <stdio.h>



void runAllTestsDaniel();

void runPersonTests();
void  testInitPerson();
void  freePersonTest();

void workerTests();
void initWorkerTest();
void freeWorkerTest();

#endif
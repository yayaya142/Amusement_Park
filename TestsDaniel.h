#ifndef __TESTS_DANIEL__
#define __TESTS_DANIEL__

#include <crtdbg.h> // TODO: remove before release
#include <assert.h>
#include <stdio.h>



void runAllTestsDaniel();

void runPersonTests();

void testInitPersonValidInput();
void testInitPersonInvalidName();
void testInitPersonInvalidHeight();
void testInitPersonInvalidAge();
void testInitPersonInvalidId();

void workerTests();
void initWorkerTest();
void printWorkerTest();
void freeWorkerTest();

#endif
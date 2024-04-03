#ifndef __TESTS_DANIEL__
#define __TESTS_DANIEL__

#include <crtdbg.h> // TODO: remove before release
#include <assert.h>
#include <stdio.h>



void runAllTestsDaniel();

void runPersonTests();
void testComparePersonByHeight();
void testInitPerson();

void runWorkerTests();
void initWorkerTest();

void runFacilityTests();
void testInitFacility();
void testCompareFacilities();

void runGuestTests();
void initGuestTests();

//------File Test---------
void runAllSaveAndLoadTests();
void FacilitySaveAndLoadText();
void FacilitySaveAndLoadBin();
void PersonSaveAndLoadText();
void PersonSaveAndLoadBin();
void WorkerSaveAndLoadText();
void WorkerSaveAndLoadBin();
#endif
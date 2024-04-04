#ifndef __TESTS_DANIEL__
#define __TESTS_DANIEL__

#include <crtdbg.h> // TODO: remove before release
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Person.h"
#include "Worker.h"
#include "Guest.h"
#include "Facility.h"
#include "TicketMaster.h"
#include "LunaPark.h"



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

void runLunaParkTests();
void addWorkerToLunaParkTest();


//------File Test---------
void runAllSaveAndLoadTests();
void FacilitySaveAndLoadText();
void FacilitySaveAndLoadBin();
void PersonSaveAndLoadText();
void PersonSaveAndLoadBin();
void WorkerSaveAndLoadText();
void WorkerSaveAndLoadBin();
void GuestSaveAndLoadText();
void GuestSaveAndLoadBin();
#endif
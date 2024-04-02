#include "Person.h"
#include "Worker.h"
#include "Guest.h"
#include "Facility.h"
#include "TicketMaster.h"
#include "TestsDaniel.h"
#include <crtdbg.h> // TODO: remove before release
#include <assert.h>
#include <string.h>
#include <stdlib.h>

// Test 1:check initPerson functionality with valid and invalid inputs
void testInitPerson() {
    char* name = (char*)malloc(7 * sizeof(char));
    strcpy(name, "person");

    Person* p = initPerson(name, 170, 30);
    assert(p != NULL); // All inputs are valid
    assert(strcmp(p->name, "person") == 0);
    assert(p->height == 170);
    assert(p->age == 30);
    freePerson(p);

    name = (char*)malloc(7 * sizeof(char));
    strcpy(name, "person");
    // Test with NULL name
    p = initPerson(NULL, 170, 30);
    assert(p == NULL);
    freePerson(p);
    free(name);

    name = (char*)malloc(7 * sizeof(char));
    // Test with empty name
    strcpy(name, "");
    p = initPerson("", 170, 30);
    assert(p == NULL);
    freePerson(p);
    free(name);

    name = (char*)malloc(7 * sizeof(char));
    strcpy(name, "person");
    // Test with negative height
    p = initPerson(name, -170, 30);
    assert(p == NULL);
    free(name);

    name = (char*)malloc(7 * sizeof(char));
    strcpy(name, "person");
    // Test with zero height
    p = initPerson(name, 0, 30);
    assert(p == NULL);
    freePerson(p);
    free(name);

    name = (char*)malloc(7 * sizeof(char));
    strcpy(name, "person");
    // Test with negative age
    p = initPerson(name, 170, -30);
    assert(p == NULL);
    freePerson(p);
    free(name);

    name = (char*)malloc(7 * sizeof(char));
    strcpy(name, "person");
    // Test with zero age
    p = initPerson(name, 170, 0);
    assert(p == NULL);
    
    freePerson(p);
    free(name);
}

// Test 2: Check that comparePersonByHeight
void testComparePersonByHeight() {
    char* name1 = (char*)malloc(8* sizeof(char));
    strcpy(name1, "personA");
    char* name2 = (char*)malloc(8 * sizeof(char));
    strcpy(name2, "personB");

    Person* p1 = initPerson(name1, 180, 30);
    Person* p2 = initPerson(name2, 180, 30);

    // Test when heights are equal
    assert(comparePersonByHeight(p1, p2) == 0);
    freePerson(p1);


    // Test when p1's height is less than p2's height
    name1 = (char*)malloc(8 * sizeof(char));
    strcpy(name1, "personA");
    p1 = initPerson(name1, 170, 30);
    assert(comparePersonByHeight(p1, p2) < 0);
    freePerson(p1);


    // Test when p1's height is greater than p2's height
    name1 = (char*)malloc(8 * sizeof(char));
    strcpy(name1, "personA");
    p1 = initPerson(name1, 190, 30);
    assert(comparePersonByHeight(p1, p2) > 0);

    freePerson(p1);
    freePerson(p2);
    
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Test 1: Check that initWorker
void initWorkerTest() {
    char* name = (char*)malloc(7 * sizeof(char));
    strcpy(name, "person");

    // Test with valid parameters
    Person* worker = initWorker(eCoffeeShop, name, 170, 30);
    Worker* w = worker->pDerived;
    printf("inside worker----------------------------\n");
    worker->printPerson(worker);
    assert(worker != NULL);
    worker->freePerson(worker);


    // Test with invalid department
    worker = initWorker(eNofTypes, name, 170, 30);
    assert(worker == NULL);

    // Test with NULL name
    worker = initWorker(eCoffeeShop, NULL, 170, 30);
    assert(worker == NULL);

    // Test with empty name
    
    name = (char*)malloc(7 * sizeof(char));
    strcpy(name, "");
    worker = initWorker(eCoffeeShop, name, 170, 30);
    assert(worker == NULL);

    // Test with negative height
    strcpy(name, "person");
    worker = initWorker(eCoffeeShop, name, -170, 30);
    assert(worker == NULL);

    // Test with zero height
    worker = initWorker(eCoffeeShop, name, 0, 30);
    assert(worker == NULL);

    // Test with negative age
    worker = initWorker(eCoffeeShop, name, 170, -30);
    assert(worker == NULL);
   //Worker* w = worker->pDerived;
   // w->freeWorker(worker);
    free(name);
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 //Test 1: Check that initGuest 
void initGuestTests() {
    char* name = (char*)malloc(7 * sizeof(char));
    strcpy(name, "daniel");

    // Test with valid parameters
    Person* guest = initGuest(name, 170, 22);
    assert(guest != NULL); // Check if the guest was created
    Guest* g = guest->pDerived;
    assert(strcmp(guest->name, "daniel") == 0); // Check if the name was set correctly
    assert(guest->height == 170); // Check if the height was set correctly
    assert(guest->age == 22); // Check if the age was set correctly
    assert(g->ticket == NULL); // Check if the ticket is NULL as expected
    guest->freePerson(guest);

    // Test initGuest with a NULL name
    guest = initGuest(NULL, 170, 22);
    assert(guest == NULL);

    // Test initGuest with a negative height
    name = (char*)malloc(7 * sizeof(char));
    strcpy(name, "daniel");
    guest = initGuest(name, -170, 22);
    assert(guest == NULL);

    // Test initGuest with a zero age
    guest = initGuest(name, 170, 0);
    assert(guest == NULL);

   free(name);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Test 1: Check that initFacility
void testInitFacility() {
    Facility facility;

   // Test with valid parameters
    assert(initFacility(&facility, "Test Facility", 100, 200, eChildrenFacility) == 1);
    assert(facility.minHeight == 100);
    assert(facility.maxHeight == 200);
    assert(facility.category == eChildrenFacility);

    // Test with minHeight > maxHeight
    assert(initFacility(&facility, "Test Facility", 200, 100, eAdultFacility) == 0);

    // Test with negative minHeight
    assert(initFacility(&facility, "Test Facility", -100, 200, eExtremeFacility) == 0);

    // Test with negative maxHeight
    assert(initFacility(&facility, "Test Facility", 100, -200, eSuper_ExtremesFacility) == 0);

    // Test with invalid category
    assert(initFacility(&facility, "Test Facility", 100, 200, eNofTypesFacility) == 0);
}

// Test 2: Check that freeFacility correctly frees a facility
void testCompareFacilities() {
    Facility facility1, facility2;

    // Test when categories are different
    facility1.category = eChildrenFacility;
    facility2.category = eAdultFacility;
    assert(compareFacilitiesByCategory(&facility1, &facility2) < 0);

            
    // Test when categories are the same
    facility1.category = eChildrenFacility;
    facility2.category = eChildrenFacility;
    assert(compareFacilitiesByCategory(&facility1, &facility2) == 0);

    // Test when one categorie bigger from the other 
    facility1.category = eSuper_ExtremesFacility;
    facility2.category = eAdultFacility;
    assert(compareFacilitiesByCategory(&facility1, &facility2) > 0);


    // Test when one categorie smaller from the other
    facility1.category = eChildrenFacility;
    facility2.category = eExtremeFacility;
    assert(compareFacilitiesByCategory(&facility1, &facility2) < 0);

 
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void FacilitySaveAndLoadText() {
    const char* fileName = "AAAfacilityTest.txt";
    Facility facility1;
    char* tempName = (char*)malloc(10 * sizeof(char));
    strcpy(tempName, "Facility");
    initFacility(&facility1, tempName, 100, 200, eChildrenFacility);
    printFacility(&facility1);
    FILE* file = fopen(fileName, "w");
    assert(saveFacilityToTextFile(&facility1, file) == 1);
    fclose(file);

    Facility facility2;
    file = fopen(fileName, "r");
    assert(loadFacilityFromTextFile(&facility2, file) == 1);
    fclose(file);
    
    assert(strcmp(facility1.name, facility2.name) == 0);
    assert(facility1.minHeight == facility2.minHeight);
    assert(facility1.maxHeight == facility2.maxHeight);
    assert(facility1.category == facility2.category);

    freeFacility(&facility1);
    freeFacility(&facility2);

}
void FacilitySaveAndLoadBin() {
    const char* fileName = "AAAfacilityTest.bin";
	Facility facility1;
	char* tempName = (char*)malloc(10 * sizeof(char));
	strcpy(tempName, "Facilite");

	initFacility(&facility1, tempName, 100, 200, eChildrenFacility);
	printFacility(&facility1);
	FILE* file = fopen(fileName, "wb");
	assert(saveFacilityToBinFile(&facility1, file) == 1);
	fclose(file);

	Facility facility2;
	file = fopen(fileName, "rb");
	assert(loadFacilityFromBinFile(&facility2, file) == 1);
	fclose(file);
	
    assert(strcmp(facility1.name, facility2.name) == 0);
    assert(facility1.minHeight == facility2.minHeight);
    assert(facility1.maxHeight == facility2.maxHeight);
    assert(facility1.category == facility2.category);

	freeFacility(&facility1);
	freeFacility(&facility2);

}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Person
void runPersonTests() {
    testInitPerson();
    testComparePersonByHeight();
}

// Worker
void runWorkerTests() {
	initWorkerTest();
}
// Guest
void runGuestTests() {
    initGuestTests();
}
// Facility
void runFacilityTests() {
    testInitFacility();
    testCompareFacilities();
}


//Tests for load & save from file (text\bin)
void runAllSaveAndLoadTests() {
     FacilitySaveAndLoadText();
     FacilitySaveAndLoadBin();
}

//main test
void runAllTestsDaniel() {
    printf("------Running Daniel tests...--------\n");
    runPersonTests();
    runWorkerTests();
    runFacilityTests();
    runGuestTests();
    runAllSaveAndLoadTests();
    printf("---------All tests passed!----------\n");
}

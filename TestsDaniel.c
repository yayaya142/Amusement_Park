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
    Worker* w = malloc(sizeof(Worker));
    if (w == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    Person* p = malloc(sizeof(Person));
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    char* name = (char*)malloc(7 * sizeof(char));
    strcpy(name, "person");

    //assert(initPerson(p, name, 170, 30) == 1);// Initialize the person
    //assert(initWorker(w, p, eCoffeeShop) == 1); // Check that initWorker returns 1 when valid inputs are given
    //assert(initWorker(w, p, eNofTypes) == 0); // Check that initWorker returns 0 when invalid department is given
    freeWorker(w);
    free(w);
    
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Test 1: Check that initGuest 
void initGuestTest() {
    Guest g;
    Person tk; 

    char* name = malloc(sizeof(char) *7);
    strcpy(name, "daniel");
   // initPerson(&tk,name, 170, 22);
    initGuest(&g, &tk);

    //Manual ticket initial - assume that the ticket is correct
    Date d;
    initDate(&d, 21, 10, 2024);
    Ticket *t = malloc(sizeof(Ticket));
    if (t == NULL) {
		printf("Memory allocation failed\n");
		return;
	}
    assert(initTicket(t, 1, d) == 1);
    g.ticket = t;
    strcpy(g.ticket->id, "123456789234");
    assert(g.person->height == 170);
    assert(g.person->age == 22);
    assert(strcmp(g.person->name, "daniel") == 0);
    assert(strcmp(g.ticket->id, "123456789234") == 0);
    assert(g.ticket->dateOfVisit.day == 21);
    assert(g.ticket->dateOfVisit.month == 10);
    assert(g.ticket->dateOfVisit.year == 2024);
    freeGuest(&g);

    free(t);
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
    assert(compareFacilities(&facility1, &facility2) < 0);

    // Test when minHeight is different
    facility1.category = facility2.category = eAdultFacility;
    facility1.minHeight = 100;
    facility2.minHeight = 200;
    assert(compareFacilities(&facility1, &facility2) < 0);

    // Test when maxHeight is different
    facility1.minHeight = facility2.minHeight = 200;
    facility1.maxHeight = 300;
    facility2.maxHeight = 400;
    assert(compareFacilities(&facility1, &facility2) < 0);

    // Test when facilities are equal
    facility1.maxHeight = facility2.maxHeight = 400;
    assert(compareFacilities(&facility1, &facility2) == 0);
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
	initGuestTest();
}
// Facility
void runFacilityTests() {
    testInitFacility();
    testCompareFacilities();
}
//main test
void runAllTestsDaniel() {
    printf("------Running Daniel tests...--------\n");
    runPersonTests();
   /* runWorkerTests();
    runFacilityTests();
    runGuestTests();*/

    printf("---------All tests passed!----------\n");
}

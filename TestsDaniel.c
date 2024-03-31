#include "Person.h"
#include "Worker.h"
#include "Guest.h"
#include "Facility.h"
#include "TestsDaniel.h"
#include <crtdbg.h> // TODO: remove before release
#include <assert.h>
#include <string.h>

// Test 1:check initPerson functionality with valid and invalid inputs
void testInitPerson() {
    Person* p = malloc(sizeof(Person));
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    assert(initPerson(p, "daniel betzalel", 170, 30) == 1); // All inputs are valid
    assert(initPerson(p, "1234", 170, 30) == 0); // Name contains non-alphabetic characters
    assert(initPerson(p, "Test Name", -1, 30) == 0); // Height is negative
    assert(initPerson(p, "Test Name", 301, 30) == 0); // Height is more than 300
    assert(initPerson(p, "Test Name", 170, -1) == 0); // Age is negative
    assert(initPerson(p, "Test Name", 170, 121) == 0); // Age is more than 120
    
    freePerson(p);
}


// Test 2: Check that freePerson correctly frees a person
void freePersonTest() {
    Person* p = malloc(sizeof(Person));
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    initPerson(p, "Test Name", 170, 30);
    freePerson(p);
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
    assert(initPerson(p, "Test Name", 170, 30) == 1); // Initialize the person
    assert(initWorker(w, p, eCoffeeShop) == 1); // Check that initWorker returns 1 when valid inputs are given
    assert(initWorker(w, p, eNofTypes) == 0); // Check that initWorker returns 0 when invalid department is given
    
    freeWorker(w);
}

// Test 2: Check that freeWorker correctly frees a worker
void freeWorkerTest() {
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
    assert(initPerson(p, "Test Name", 170, 30) == 1); // Initialize the person
    initWorker(w, p, eCoffeeShop);
    freeWorker(w);
}
// Test 3: Check that comparePersonByHeight
void test_comparePersonByHeight() {
    Person p1, p2;

    // Test when heights are equal
    p1.height = 180;
    p2.height = 180;
    assert(comparePersonByHeight(&p1, &p2) == 0);

    // Test when p1's height is less than p2's height
    p1.height = 170;
    p2.height = 180;
    assert(comparePersonByHeight(&p1, &p2) < 0);

    // Test when p1's height is greater than p2's height
    p1.height = 190;
    p2.height = 180;
    assert(comparePersonByHeight(&p1, &p2) > 0);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Test 1: Check that initGuest 
void initGuestTest() {
    Person* p = malloc(sizeof(Person));
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    assert(initPerson(p, "Test Name", 170, 30) == 1); // Initialize the person

    Guest* g = malloc(sizeof(Guest));
    if (g == NULL) {
        printf("Memory allocation failed\n");
        freePerson(p);
        return;
    }
    Date date;
    initDate(&date, 21, 10, 2024); // Example date
    assert(initGuest(g, p, 1, date) == 1); // All inputs are valid
    assert(initGuest(g, p, eNofTypes, date) == 0); // Invalid guest type

    Date invalidDate = { 2022, 13, 32 }; // Invalid date
    assert(initGuest(g, p, 1, invalidDate) == 0); // Invalid date

    Date futureDate = { 3000, 1, 1 }; // Future date
    assert(initGuest(g, p, 1, futureDate) == 0); // Future date

    Date pastDate = { 1900, 1, 1 }; // Past date
    assert(initGuest(g, p, 1, pastDate) == 0); // Past date

    freeGuest(g);
}

// Test 2: Check that freeGuest correctly frees a guest
void freeGuestTest() {
    Guest* g = malloc(sizeof(Guest));
    if (g == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    Person* p = malloc(sizeof(Person));
    if (p == NULL) {
        printf("Memory allocation failed\n");
        free(g); // Don't forget to free g before returning
        return;
    }
    assert(initPerson(p, "Test Name", 170, 30) == 1);
    Date date;
    initDate(&date, 21, 10, 2024);
    initGuest(g, p, eStudent, date);

    freeGuest(g);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Test 1: Check that initFacility
void test_initFacility() {
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
void test_compareFacilities() {
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
    freePersonTest();
}

// Worker
void runWorkerTests() {
	initWorkerTest();
	freeWorkerTest();
}
// Guest
void runGuestTests() {
	//initGuestTest();
    freeGuestTest();
}

// Facility
void runFacilityTests() {
	test_initFacility();
	test_compareFacilities();
}
//main test
void runAllTestsDaniel() {
    runPersonTests();
    runWorkerTests();
    runFacilityTests();
    //runGuestTests();

    printf("---------All tests passed!----------\n");
}

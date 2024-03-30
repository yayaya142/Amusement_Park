#include "Person.h"
#include "Worker.h"
#include "TestsDaniel.h"
#include <assert.h>
#include <string.h>

// Test 1:check initPerson functionality with valid and invalid inputs
    
void testInitPersonValidInput() {
    Person* p = malloc(sizeof(Person));
    if (p == NULL) {
    	printf("Memory allocation failed\n");
        return;
    }
    assert(initPerson(p, "a a", 170, 30, 1234) == 1);// All inputs are valid
   freePerson(p);
}

void testInitPersonInvalidName() {
    Person* p = malloc(sizeof(Person));
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    assert(initPerson(p, "1234", 170, 30, 1234) == 0);// Name contains non-alphabetic characters
    freePerson(p);
}

void testInitPersonInvalidHeight() {
    Person* p = malloc(sizeof(Person));
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    assert(initPerson(p, "Test Name", -1, 30, 1234) == 0);// Height is negative
    assert(initPerson(p, "Test Name", 301, 30, 1234) == 0);// Height is more than 300
    freePerson(p);
}

void testInitPersonInvalidAge() {
    Person* p = malloc(sizeof(Person));
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    assert(initPerson(p, "Test Name", 170, -1, 1234) == 0); // Age is negative
    assert(initPerson(p, "Test Name", 170, 121, 1234) == 0); // Age is more than 120
    freePerson(p);
}

void testInitPersonInvalidId() {
    Person* p = malloc(sizeof(Person));
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    assert(initPerson(p, "Test Name", 170, 30, -1) == 0); // ID is negative
    freePerson(p);
}


// Test 2: Check that freePerson correctly frees a person
void freePersonTest() {
    Person* p = malloc(sizeof(Person));
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    initPerson(p, "Test Name", 170, 30, 1234);
    freePerson(p);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Test 1: Check that initWorker returns a non-null pointer when valid inputs are given
void initWorkerTest() {
    Worker* w = malloc(sizeof(Worker));
    if (w == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    assert(initWorker(w, 5678, CoffeeShop) == 1);// Check that initWorker returns 1 when valid inputs are given
 
    assert(initWorker(w, -1, CoffeeShop) == 0);// Check that initWorker returns 0 when invalid WorkerId is given
    
    assert(initWorker(w, 5678, NofTypes) == 0);// Check that initWorker returns 0 when invalid department is given

    freeWorker(w);
}

// Test 2: Check that freeWorker correctly frees a worker
void freeWorkerTest() {
    Worker* w = malloc(sizeof(Worker));
    if (w == NULL) {
		printf("Memory allocation failed\n");
		return;
	}
    initWorker(w, 5678, CoffeeShop);
    freeWorker(w);
    // This test would require some way to check that the memory has been freed, which is not straightforward in C
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 // Person
void runPersonTests() {
    testInitPersonValidInput();
   testInitPersonInvalidName();
    testInitPersonInvalidHeight();
    testInitPersonInvalidAge();
    testInitPersonInvalidId();
}

// Worker
void runWorkerTests() {
	initWorkerTest();
	freeWorkerTest();
}

void runAllTestsDaniel() {
    runPersonTests();
    runWorkerTests();
    printf("---------All tests passed!----------\n");
}

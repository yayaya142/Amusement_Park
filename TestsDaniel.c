#include "TestsDaniel.h"

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
//LunaPark
void runLunaParkTests() {
	addWorkerToLunaParkTest();
	addGuestToLunaParkTest();

}

//Tests for load & save from file (text\bin)
void runAllSaveAndLoadTests() {
	FacilitySaveAndLoadText();
	FacilitySaveAndLoadBin();
	PersonSaveAndLoadText();
	PersonSaveAndLoadBin();
	WorkerSaveAndLoadText();
	WorkerSaveAndLoadBin();
	GuestSaveAndLoadText();
	GuestSaveAndLoadBin();
}

//main test
void runAllTestsDaniel() {
	printf("------Running Daniel tests...--------\n");
	//runPersonTests();
	//runWorkerTests();
	runFacilityTests();
	//runGuestTests();
	//runAllSaveAndLoadTests();
	runLunaParkTests();
	printf("---------All tests passed!----------\n");
}


//PERSON TESTS
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
	char* name1 = (char*)malloc(8 * sizeof(char));
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

//WORKER TESTS
// Test 1: Check that initWorker
void initWorkerTest() {
	char* name = (char*)malloc(7 * sizeof(char));
	strcpy(name, "person");

	// Test with valid parameters
	Person* worker = initWorker(eCoffeeShop, name, 170, 30);
	Worker* w = worker->pDerived;
	assert(worker != NULL);
	worker->freePerson(worker);


	// Test with invalid department
	worker = initWorker(eNofShopTypes, name, 170, 30);
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
	free(name);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//GUEST TESTS
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

//FACILITY TESTS
//Test 1: Check that initFacility
void testInitFacility() {
	Facility facility;

	// Test with valid parameters
	assert(initFacility(&facility, "Test Facility", 100, 200, eChildrenFacility) == 1);
	assert(strcmp(facility.name, "Test Facility") == 0);
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

//SAVE AND LOAD TESTS
void FacilitySaveAndLoadText() {
	const char* fileName = "AAAfacilityTest.txt";
	Facility* facility1 = (Facility*)malloc(sizeof(Facility));
	char* tempName = (char*)malloc(10 * sizeof(char));
	strcpy(tempName, "Facility");
	initFacility(facility1, tempName, 100, 200, eChildrenFacility);
	FILE* file = fopen(fileName, "w");
	assert(saveFacilityToTextFile(facility1, file) == 1);
	fclose(file);

	Facility* facility2 = (Facility*)malloc(sizeof(Facility));
	file = fopen(fileName, "r");
	assert(loadFacilityFromTextFile(facility2, file) == 1);
	fclose(file);

	assert(strcmp(facility1->name, facility2->name) == 0);
	assert(facility1->minHeight == facility2->minHeight);
	assert(facility1->maxHeight == facility2->maxHeight);
	assert(facility1->category == facility2->category);

	freeFacility(facility1);
	freeFacility(facility2);

}
void FacilitySaveAndLoadBin() {
	const char* fileName = "AAAfacilityTest.bin";
	Facility* facility1 = (Facility*)malloc(sizeof(Facility));
	char* tempName = (char*)malloc(10 * sizeof(char));
	strcpy(tempName, "Facilite");

	initFacility(facility1, tempName, 100, 200, eChildrenFacility);
	FILE* file = fopen(fileName, "wb");
	assert(saveFacilityToBinFile(facility1, file) == 1);
	fclose(file);

	Facility* facility2 = (Facility*)malloc(sizeof(Facility));
	file = fopen(fileName, "rb");
	assert(loadFacilityFromBinFile(facility2, file) == 1);
	fclose(file);

	assert(strcmp(facility1->name, facility2->name) == 0);
	assert(facility1->minHeight == facility2->minHeight);
	assert(facility1->maxHeight == facility2->maxHeight);
	assert(facility1->category == facility2->category);

	freeFacility(facility1);
	freeFacility(facility2);

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void PersonSaveAndLoadText() {
	const char* fileName = "AAAPersonTest.txt";
	Person* person1;
	char* tempName = (char*)malloc(8 * sizeof(char));
	strcpy(tempName, "Person");
	person1 = initPerson(tempName, 170, 30);
	// Save the person to a file
	FILE* file = fopen(fileName, "w");
	assert(savePersonToTextFile(person1, file) == 1);
	fclose(file);

	Person* person2 = NULL;
	file = fopen(fileName, "r");
	assert(loadPersonFromTextFile(&person2, file) == 1);
	fclose(file);

	// Check if the loaded person is the same as the saved person
	assert(strcmp(person1->name, person2->name) == 0);
	assert(person1->height == person2->height);
	assert(person1->age == person2->age);


	freePerson(person1);
	freePerson(person2);
}
void PersonSaveAndLoadBin() {
	const char* fileName = "AAAPersonTest.bin";
	Person* person1;
	char* tempName = (char*)malloc(8 * sizeof(char));
	strcpy(tempName, "Person");
	person1 = initPerson(tempName, 170, 30);
	// Save the person to a file
	FILE* file = fopen(fileName, "wb");
	assert(savePersonToBinFile(person1, file) == 1);
	fclose(file);

	Person* person2 = NULL;
	file = fopen(fileName, "rb");
	assert(loadPersonFromBinFile(&person2, file) == 1);
	fclose(file);

	// Check if the loaded person is the same as the saved person
	assert(strcmp(person1->name, person2->name) == 0);
	assert(person1->height == person2->height);
	assert(person1->age == person2->age);

	freePerson(person1);
	freePerson(person2);

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void WorkerSaveAndLoadText() {
	const char* fileName = "AAAWorkerTest.txt";
	Person* worker1;
	char* tempName = (char*)malloc(7 * sizeof(char));
	strcpy(tempName, "Worker");
	worker1 = initWorker(eCoffeeShop, tempName, 170, 30);
	// Save the worker to a file
	FILE* file = fopen(fileName, "w");
	assert(saveWorkerToTextFile(worker1, file) == 1);
	fclose(file);

	Person* worker2 = NULL;
	file = fopen(fileName, "r");
	assert(loadWorkerFromTextFile(&worker2, file) == 1);
	fclose(file);

	// Check if the loaded worker is the same as the saved worker
	assert(strcmp(worker1->name, worker2->name) == 0);
	assert(worker1->height == worker2->height);
	assert(worker1->age == worker2->age);
	Worker* w1 = worker1->pDerived;
	Worker* w2 = worker2->pDerived;
	assert(w1->department == w2->department);
	assert(w1->WorkerId == w2->WorkerId);


	worker1->freePerson(worker1);
	worker2->freePerson(worker2);


}
void WorkerSaveAndLoadBin() {
	const char* fileName = "AAAWorkerTest.bin";
	Person* worker1;
	char* tempName = (char*)malloc(8 * sizeof(char));
	strcpy(tempName, "Worker");
	worker1 = initWorker(eCoffeeShop, tempName, 170, 30);
	// Save the worker to a file
	FILE* file = fopen(fileName, "wb");
	assert(saveWorkerToBinFile(worker1, file) == 1);
	fclose(file);

	Person* worker2 = NULL;
	file = fopen(fileName, "rb");
	assert(loadWorkerFromBinFile(&worker2, file) == 1);
	fclose(file);

	// Check if the loaded worker is the same as the saved worker
	assert(strcmp(worker1->name, worker2->name) == 0);
	assert(worker1->height == worker2->height);
	assert(worker1->age == worker2->age);
	Worker* w1 = worker1->pDerived;
	Worker* w2 = worker2->pDerived;
	assert(w1->department == w2->department);
	assert(w1->WorkerId == w2->WorkerId);

	worker1->freePerson(worker1);
	worker2->freePerson(worker2);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GuestSaveAndLoadText() {
	TicketMaster ticketMaster;
	initTicketMaster(&ticketMaster);

	Ticket* ticket1 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket2 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket3 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket4 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket5 = (Ticket*)malloc(sizeof(Ticket));

	Date date1, date2, date3, date4, date5;
	initDate(&date1, 1, 1, 2025);
	initDate(&date2, 2, 1, 2025);
	initDate(&date3, 3, 1, 2025);
	initDate(&date4, 4, 1, 2025);
	initDate(&date5, 5, 1, 2025);

	initTicket(ticket1, eChild, date1);
	initTicket(ticket2, eAdult, date2);
	initTicket(ticket3, eStudent, date3);
	initTicket(ticket4, eStudent, date4);
	initTicket(ticket5, eAdult, date5);

	addTicket(&ticketMaster, ticket1);
	addTicket(&ticketMaster, ticket2);
	addTicket(&ticketMaster, ticket3);
	addTicket(&ticketMaster, ticket4);
	addTicket(&ticketMaster, ticket5);

	const char* fileName = "AAAGuestTest.txt";
	Person* guest1;
	char* tempName = (char*)malloc(7 * sizeof(char));
	strcpy(tempName, "Guest");

	// Create a guest
	guest1 = initGuest(tempName, 170, 30);
	Guest* g = guest1->pDerived;
	g->ticket = ticket1;

	// Save the guest to a file
	FILE* file = fopen(fileName, "w");
	assert(saveGuestToTextFile(guest1, file) == 1);
	fclose(file);

	// Load the guest from the file
	Person* guest2 = NULL;
	file = fopen(fileName, "r");
	assert(loadGuestFromTextFile(&guest2, &ticketMaster, file) == 1);
	fclose(file);

	// Check if the loaded guest is the same as the saved guest

	assert(strcmp(guest1->name, guest2->name) == 0);
	assert(guest1->height == guest2->height);
	assert(guest1->age == guest2->age);
	Guest* g1 = guest1->pDerived;
	Guest* g2 = guest2->pDerived;
	assert(g1->ticket == g2->ticket);




	freeTicketMaster(&ticketMaster);
	guest1->freePerson(guest1);
	guest2->freePerson(guest2);

}
void GuestSaveAndLoadBin() {
	TicketMaster ticketMaster;
	initTicketMaster(&ticketMaster);

	Ticket* ticket1 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket2 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket3 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket4 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket5 = (Ticket*)malloc(sizeof(Ticket));

	Date date1, date2, date3, date4, date5;
	initDate(&date1, 1, 1, 2025);
	initDate(&date2, 2, 1, 2025);
	initDate(&date3, 3, 1, 2025);
	initDate(&date4, 4, 1, 2025);
	initDate(&date5, 5, 1, 2025);

	initTicket(ticket1, eChild, date1);
	initTicket(ticket2, eAdult, date2);
	initTicket(ticket3, eStudent, date3);
	initTicket(ticket4, eStudent, date4);
	initTicket(ticket5, eAdult, date5);

	addTicket(&ticketMaster, ticket1);
	addTicket(&ticketMaster, ticket2);
	addTicket(&ticketMaster, ticket3);
	addTicket(&ticketMaster, ticket4);
	addTicket(&ticketMaster, ticket5);

	const char* fileName = "AAAGuestTest.bin";
	Person* guest1;
	char* tempName = (char*)malloc(7 * sizeof(char));
	strcpy(tempName, "Guest");

	// Create a guest
	guest1 = initGuest(tempName, 170, 30);
	Guest* g = guest1->pDerived;
	g->ticket = ticket1;

	// Save the guest to a file
	FILE* file = fopen(fileName, "wb");
	assert(saveGuestToBinFile(guest1, file) == 1);
	fclose(file);

	// Load the guest from the file
	Person* guest2 = NULL;
	file = fopen(fileName, "rb");
	assert(loadGuestFromBinFile(&guest2, &ticketMaster, file) == 1);
	fclose(file);

	// Check if the loaded guest is the same as the saved guest

	assert(strcmp(guest1->name, guest2->name) == 0);
	assert(guest1->height == guest2->height);
	assert(guest1->age == guest2->age);
	Guest* g1 = guest1->pDerived;
	Guest* g2 = guest2->pDerived;
	assert(g1->ticket == g2->ticket);


	freeTicketMaster(&ticketMaster);
	guest1->freePerson(guest1);
	guest2->freePerson(guest2);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void addWorkerToLunaParkTest() {
	//init LunaPark
	LunaPark lunaPark;
	char* name = (char*)malloc(9 * sizeof(char));
	strcpy(name, "LunaPark");
	initLunaPark(&lunaPark, name);

	//init Worker
	char* name1 = (char*)malloc(7 * sizeof(char));
	strcpy(name1, "person");
	Person* worker = initWorker(eCoffeeShop, name1, 170, 30);

	//add worker number 1 to LunaPark
	assert(addWorkerToLunaPark(&lunaPark, worker) == 1);
	//check if worker was added to LunaPark
	assert(lunaPark.numOfWorkers == 1);
	assert(lunaPark.workers[0] == worker);
	assert(lunaPark.workers[0]->age == worker->age);
	assert(strcmp(lunaPark.workers[0]->name, worker->name) == 0);
	Worker* w = lunaPark.workers[0]->pDerived;
	assert(w->department == eCoffeeShop);

	//add worker number 2 to LunaPark
	char* name2 = (char*)malloc(7 * sizeof(char));
	strcpy(name2, "person");
	Person* worker2 = initWorker(eRestaurant, name2, 170, 30);
	assert(addWorkerToLunaPark(&lunaPark, worker2) == 1);
	//check if worker was added to LunaPark
	assert(lunaPark.numOfWorkers == 2);
	assert(lunaPark.workers[1]->age == worker2->age);
	assert(strcmp(lunaPark.workers[1]->name, worker2->name) == 0);

	Worker* w2 = lunaPark.workers[1]->pDerived;
	assert(w2->department == eRestaurant);


	//free memory
	freeLunaPark(&lunaPark);
}

void addGuestToLunaParkTest() {
	LunaPark lunaPark;
	char* name = (char*)malloc(9 * sizeof(char));
	strcpy(name, "LunaPark");
	initLunaPark(&lunaPark, name);

	TicketMaster ticketMaster;
	initTicketMaster(&ticketMaster);

	Ticket* ticket1 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket2 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket3 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket4 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket5 = (Ticket*)malloc(sizeof(Ticket));

	Date date1, date2, date3, date4, date5;
	initDate(&date1, 1, 1, 2025);
	initDate(&date2, 2, 1, 2025);
	initDate(&date3, 3, 1, 2025);
	initDate(&date4, 4, 1, 2025);
	initDate(&date5, 5, 1, 2025);

	initTicket(ticket1, eChild, date1);
	initTicket(ticket2, eAdult, date2);
	initTicket(ticket3, eStudent, date3);
	initTicket(ticket4, eStudent, date4);
	initTicket(ticket5, eAdult, date5);

	addTicket(&ticketMaster, ticket1);
	addTicket(&ticketMaster, ticket2);
	addTicket(&ticketMaster, ticket3);
	addTicket(&ticketMaster, ticket4);
	addTicket(&ticketMaster, ticket5);

	//init Guest
	char* name1 = (char*)malloc(7 * sizeof(char));
	strcpy(name1, "person");
	Person* guest = initGuest(name1, 170, 30);
	Guest* g = guest->pDerived;
	g->ticket = ticket1;

	//add guest number 1 to LunaPark
	assert(addGuestToLunaPark(&lunaPark, guest) == 1);
	//check if guest was added to LunaPark
	assert(lunaPark.numOfGuests == 1);
	assert(lunaPark.guests[0] == guest);
	assert(lunaPark.guests[0]->age == guest->age);
	assert(strcmp(lunaPark.guests[0]->name, guest->name) == 0);
	assert(g->ticket == ticket1);

	//add guest number 2 to LunaPark
	char* name2 = (char*)malloc(7 * sizeof(char));
	strcpy(name2, "person");
	Person* guest2 = initGuest(name2, 170, 30);
	Guest* g2 = guest2->pDerived;
	g2->ticket = ticket2;
	assert(addGuestToLunaPark(&lunaPark, guest2) == 1);
	//check if guest was added to LunaPark
	assert(lunaPark.numOfGuests == 2);
	assert(lunaPark.guests[1]->age == guest2->age);
	assert(strcmp(lunaPark.guests[1]->name, guest2->name) == 0);
	assert(g2->ticket == ticket2);

	//free memory
	freeLunaPark(&lunaPark);
	freeTicketMaster(&ticketMaster);
}
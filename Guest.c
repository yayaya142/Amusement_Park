#include "Guest.h"
//
Person* initGuest(char* name, double height, int age){
	Guest* pGuest;
	Person* pBase;
	pBase = initPerson(name, height, age);
	if (!pBase) {
		return NULL;
	}
	pGuest = (Guest*)malloc(sizeof(Guest));
	if (!pGuest) {
		printf("Memory allocation failed\n");
		pBase->freePerson(pBase);
		return NULL;
	}
	//init derived object
	pBase->pDerived = pGuest;
	pGuest->ticket = NULL;
	//change class interfaces
	pBase->freePerson = freeGuest;
	pBase->printPerson = printGuest;

	return pBase;
}

Person* initGuestByUser(TicketMaster* tMaster) {
	Person* tempPerson = initPersonByUser();
	Person* guest = NULL;
	int size = (int)strlen(tempPerson->name);
	int flag = 0;
	do {
		if (flag > 0) {
			printf("Please try again\n");
		}
		//copy person name again after freeing it because init guest failed
		char* new_name = (char*)malloc(size + 1);
		strcpy(new_name, tempPerson->name);
		guest = initGuest(new_name, tempPerson->height, tempPerson->age);
		flag = 1;
	} while (!guest);
	//free the temp person
	tempPerson->freePerson(tempPerson);
	Guest* pGuest= guest->pDerived;
	pGuest->ticket= buyTicket(tMaster);
	return guest;
}

void printGuest(const Person* pGuest) {
	const Guest* guest = pGuest->pDerived;
	
	printPerson(pGuest);
	printTicket(guest->ticket);
}

void freeGuest(Person* pguest) {
	Guest* guest;
	guest = pguest->pDerived;
	free(guest);
	freePerson(pguest);	
}
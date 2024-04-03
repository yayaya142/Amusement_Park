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
	pBase->loadPersonFromBinFile = loadGuestFromBinFile;
	pBase->loadPersonFromTextFile = loadGuestFromTextFile;
	pBase->savePersonToBinFile = saveGuestToBinFile;
	pBase->savePersonToTextFile = saveGuestToTextFile;

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

// save and load functions
int saveGuestToTextFile(const Person* guest, FILE* fp){
	if(fp == NULL || guest == NULL){
		return 0;
	}
	Guest* pGuest = guest->pDerived;
	
	if(isValidInfo(guest->name, guest->height, guest->age)==0) {
		return 0;
	}
	//save person
	savePersonToTextFile(guest, fp);
	//save ticket
	saveTicketToTextFile(pGuest->ticket, fp);
	return 1;

}
int loadGuestFromTextFile(Person** guest, TicketMaster* ticketMaster, FILE* fp){
	if(fp == NULL){
		return 0;
	}
	Person* tempPerson = NULL;
	//load person
	if(loadPersonFromTextFile(&tempPerson, fp) == 0){
		return 0;
	}
	
	//load ticket
	Ticket tempTicket;
	if(loadTicketFromTextFile(&tempTicket, fp) == 0){
		freePerson(tempPerson);
		return 0;
	}

	//find ticket by id from the ticket master
	Ticket* new_ticket = findTicketByID(ticketMaster, tempTicket.id);

	//copy person name to guest
	char * personName = (char*)malloc(strlen(tempPerson->name) + 1);
	strcpy(personName, tempPerson->name);

	//init guest
	*guest = initGuest(personName, tempPerson->height, tempPerson->age);
	freePerson(tempPerson);
	if (*guest == NULL) {
		free(personName);
		return 0;
	}
	Guest* pGuest = (*guest)->pDerived;
	pGuest->ticket = new_ticket;
	return 1;
}
int saveGuestToBinFile(const Person* guest, FILE* fp){
	if (fp == NULL || guest == NULL) {
		return 0;
	}
	//cast to guest
	Guest* pGuest = guest->pDerived;

	if (isValidInfo(guest->name, guest->height, guest->age) == 0) {
		return 0;
	}

	//save person
	savePersonToBinFile(guest, fp);
	//save ticket
	saveTicketToBinFile(pGuest->ticket, fp);
	
	return 1;
}
int loadGuestFromBinFile(Person** guest, TicketMaster* ticketMaster, FILE* fp){
	if (fp == NULL) {
		return 0;
	}
	Person* tempPerson = NULL;
	//load person
	if (loadPersonFromBinFile(&tempPerson, fp) == 0) {
		return 0;
	}

	//load ticket
	Ticket tempTicket;
	if (loadTicketFromBinFile(&tempTicket, fp) == 0) {
		freePerson(tempPerson);
		return 0;
	}

	//find ticket by id from the ticket master
	Ticket* new_ticket = findTicketByID(ticketMaster, tempTicket.id);

	//copy person name to guest
	char* personName = (char*)malloc(strlen(tempPerson->name) + 1);
	strcpy(personName, tempPerson->name);

	//init guest
	*guest = initGuest(personName, tempPerson->height, tempPerson->age);
	freePerson(tempPerson);
	if (*guest == NULL) {
		free(personName);
		return 0;
	}
	Guest* pGuest = (*guest)->pDerived;
	pGuest->ticket = new_ticket;
	return 1;
}
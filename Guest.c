#include "Guest.h"

int initGuest(Guest* guest, Person *p) {
	guest->person = p;
	//Buy ticket?
	guest->ticket = NULL;
	return 1;
}

void initGuestByUser(Guest* guest, TicketMaster* tMaster) {
	Person* p = malloc(sizeof(Person));
	if (!p) {
		printf("Memory allocation failed\n");
		return;
	}
	initPersonByUser(p);
	guest->person = p;
	guest->ticket=buyTicket(tMaster);
}

void printGuest(const Guest* guest) {
	printPerson(guest->person);
	printTicket(guest->ticket);
}

void freeGuest(Guest* guest) {
	freePerson(guest->person);
	
}
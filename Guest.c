#include "Guest.h"
#include "Person.h"
//#include "TicketMaster.h"

int initGuest(Guest* guest, Person *p, eGuestType guestType, Date dateOfVisit ) {
	guest->person = p;
	//Buy ticket
	guest->ticket = NULL;
	return 1;
}

void initguestByUser(Guest* guest, TicketMaster* tMaster) {
	Person* p = malloc(sizeof(Person));
	if (!p) {
		printf("Memory allocation failed\n");
		return 0;
	}
	initPersonByUser(p);
	guest->person = p;
	//Buy ticket
	guest->ticket=buyTicket(tMaster);
}

void printGuest(const Guest* guest) {
	printPerson(&guest->person);
	printTicket(&guest->ticket);
}

void freeGuest(Guest* guest) {
	freePerson(guest->person);
	free(guest);
}
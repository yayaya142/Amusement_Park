#ifndef __GUEST_H__
#define __GUEST_H__

#include "Ticket.h"
#include "Person.h"
#include <crtdbg.h> // TODO: remove before release

typedef struct {
	Person*  person;
	Ticket* ticket;
} Guest;

int initGuest(Guest* w,Person* p, eGuestType guestType, Date dateOfVisit);
void printGuest(const Guest* worker);
void freeGuest(Guest* guest);

#endif
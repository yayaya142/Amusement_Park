#ifndef __GUEST_H__
#define __GUEST_H__

#include "Ticket.h"
#include "Person.h"
#include "TicketMaster.h"
#include <crtdbg.h> // TODO: remove before release

typedef struct {
	Person*  person;
	Ticket* ticket;
} Guest;

int initGuest(Guest* w,Person* p);
void initGuestByUser(Guest* guest, TicketMaster* tMaster);
void printGuest(const Guest* guest);
void freeGuest(Guest* guest);

#endif
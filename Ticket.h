#ifndef __TICKET__
#define __TICKET__

#include <crtdbg.h> // TODO: remove before release
#include <stdio.h>
#include <string.h>
#include "Date.h"
#include "General.h"

#define ID_TICKET_LEN 12
#define BASE_TICKET_PRICE 100.0


typedef enum {
	eChild, eAdult, eStudent, eSoldier, eNofTicketTypes
} eGuestType;


static const char* TicketTypeStr[eNofTicketTypes] = { "Child", "Adult", "Student", "Soldier" };
static const double Discount[eNofTicketTypes] = { 0.5, 1, 0.77, 0.0 };

typedef struct {
	char id[ID_TICKET_LEN + 1]; // + 1 for null terminator
	eGuestType guestType;
	double price;
	int isUsed;
	Date dateOfVisit;

} Ticket;


int initTicket(Ticket* ticket, eGuestType guestType, Date dateOfVisit);
void generateID(char* id);
int isValidTicket(eGuestType guestType, Date dateOfVisit);
void printTicket(const Ticket* ticket);
int compareTicketsByID(const Ticket* ticket1, const Ticket* ticket2);
int compareTicketsByDate(const Ticket* ticket1, const Ticket* ticket2);
int compareTicketsByGuestType(const Ticket* ticket1, const Ticket* ticket2);



#endif 
#ifndef __TICKET__
#define __TICKET__

#include <crtdbg.h> // TODO: remove before release
#include <stdio.h>
#include <string.h>
#include "Date.h"
#include "General.h"
#include "fileHelper.h"

#define ID_TICKET_LEN 12
#define BASE_TICKET_PRICE 100.0
#define CURRENCY_SYMBOL "$" // because ¤ doesn't work in the terminal ): 


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
void printTicket(const void* ticket);
void printTicketWrapper(const void* ticket);
int compareTicketsByID(const void* ticket1, const void* ticket2);
int compareTicketsByDate(const void* ticket1, const void* ticket2);
int compareTicketsByGuestType(const void* ticket1, const void* ticket2);
void printGuestType();
void initTicketByUser(Ticket* ticket);
// save and load functions
int saveTicketToTextFile(const Ticket* ticket, FILE* fp);
int loadTicketFromTextFile(Ticket* ticket, FILE* fp);
int saveTicketToBinFile(const Ticket* ticket, FILE* fp);
int loadTicketFromBinFile(Ticket* ticket, FILE* fp);

#endif 
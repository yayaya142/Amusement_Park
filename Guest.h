#ifndef __GUEST_H__
#define __GUEST_H__

#include "Ticket.h"
#include "Person.h"
#include "TicketMaster.h"
#include "fileHelper.h"
#include "General.h"
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h> // TODO: remove before release

typedef struct _Guest Guest;


typedef struct _Guest{
	Person*  personBase;
	Ticket* ticket;
} Guest;

Person* initGuest(char* name, double height, int age); // constructor
void freeGuest(Person* guest); // destructor
Person* initGuestByUser(TicketMaster* tMaster);
void printGuest(const Person* guest);

// save and load functions
int saveGuestToTextFile(const Person* guest, FILE* fp);
int loadGuestFromTextFile(Person** guest, TicketMaster* ticketMaster, FILE* fp);
int saveGuestToBinFile(const Person* guest, FILE* fp);
int loadGuestFromBinFile(Person** guest, TicketMaster* ticketMaster, FILE* fp);


#endif
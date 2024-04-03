#ifndef __TICKET_MASTER__
#define __TICKET_MASTER__

#include <crtdbg.h> // TODO: remove before release
#include <stdio.h>
#include <stdlib.h>
#include "Ticket.h"
#include "General.h"
#include "fileHelper.h"

typedef enum {
	eNotSorted, eSortedByID, eSortedByDate, eSortedByGuestType, eNofSortTypes
} eSortType;

static const char* sortTypeStr[] = { "None", "ID", "Date", "Guest Type" };

typedef struct {
	Ticket** tickets;
	int numOfTickets;
	eSortType sortType;
} TicketMaster;


void initTicketMaster(TicketMaster* ticketMaster);
int addTicket(TicketMaster* ticketMaster, Ticket* ticket);
void printTicketMaster(const TicketMaster* ticketMaster);
void freeTicketMaster(TicketMaster* ticketMaster);
double calcDaily(const TicketMaster* ticketMaster, Date* date);
void printDailyIncome(const TicketMaster* ticketMaster, Date* date);
void sortTicketsByID(TicketMaster* ticketMaster);
void sortTicketsByDate(TicketMaster* ticketMaster);
void sortTicketsByGuestType(TicketMaster* ticketMaster);
void sortTicketsUser(TicketMaster* ticketMaster);
Ticket* buyTicket(TicketMaster* ticketMaster);
Ticket* findTicketByUser(const TicketMaster* ticketMaster);
Ticket* findTicketByID(TicketMaster* ticketMaster, char* id);
// save and load functions
int saveTicketMasterToTextFile(const TicketMaster* ticketMaster, FILE* fp);
int loadTicketMasterFromTextFile(TicketMaster* ticketMaster, FILE* fp);
int saveTicketMasterToBinFile(const TicketMaster* ticketMaster, FILE* fp);
int loadTicketMasterFromBinFile(TicketMaster* ticketMaster, FILE* fp);



#endif 
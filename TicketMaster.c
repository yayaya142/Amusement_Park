#include "TicketMaster.h"


void initTicketMaster(TicketMaster* ticketMaster) {
	ticketMaster->tickets = NULL;
	ticketMaster->numOfTickets = 0;
	ticketMaster->sortType = eNotSorted;
}

int addTicket(TicketMaster* ticketMaster, Ticket* ticket) {
	if (ticket == NULL) {
		return 0;
	}
	if (!isValidTicket(ticket->guestType, ticket->dateOfVisit) || ticket->id == NULL) {
		return 0;
	}

	ticketMaster->tickets = (Ticket**)realloc(ticketMaster->tickets, (ticketMaster->numOfTickets + 1) * sizeof(Ticket*));
	if (ticketMaster->tickets == NULL) {
		return 0;
	}

	ticketMaster->tickets[ticketMaster->numOfTickets] = ticket;
	ticketMaster->numOfTickets++;
	return 1;
}

void printTicketMaster(const TicketMaster* ticketMaster) {
	if (ticketMaster == NULL || ticketMaster->tickets == NULL) {
		printf("No ticket added yet\n");
		return;
	}
	for (int i = 0; i < ticketMaster->numOfTickets; i++) {
		printTicket(ticketMaster->tickets[i]);
	}
}


void freeTicketMaster(TicketMaster* ticketMaster) {
	if (ticketMaster == NULL) {
		return;
	}
	for (int i = 0; i < ticketMaster->numOfTickets; i++) {
		free(ticketMaster->tickets[i]);
	}
	free(ticketMaster->tickets);
	ticketMaster->numOfTickets = 0;
	ticketMaster->tickets = NULL;
}


double calcDaily(const TicketMaster* ticketMaster, Date* date) {
	if (ticketMaster == NULL || ticketMaster->tickets == NULL || date == NULL) {
		return 0;
	}
	double sum = 0;
	for (int i = 0; i < ticketMaster->numOfTickets; i++) {
		if (compareDates(ticketMaster->tickets[i]->dateOfVisit, *date) == 0) {
			sum += ticketMaster->tickets[i]->price;
		}
	}
	return sum;
}



void printDailyIncome(const TicketMaster* ticketMaster, Date* date) {
	if (ticketMaster == NULL || ticketMaster->tickets == NULL || date == NULL) {
		printf("No ticket added yet\n");
		return;
	}
	double daily = calcDaily(ticketMaster, date);
	printf("Daily income on %d/%d/%d: %.1lf%s\n", date->day, date->month, date->year, daily, CURRENCY_SYMBOL);

}



void sortTicketsByID(TicketMaster* ticketMaster) {
	if (ticketMaster == NULL || ticketMaster->tickets == NULL) {
		return;
	}

	qsort(ticketMaster->tickets, ticketMaster->numOfTickets, sizeof(Ticket*), compareTicketsByID);
	ticketMaster->sortType = eSortedByID;
}



void sortTicketsByDate(TicketMaster* ticketMaster) {
	if (ticketMaster == NULL || ticketMaster->tickets == NULL) {
		return;
	}

	qsort(ticketMaster->tickets, ticketMaster->numOfTickets, sizeof(Ticket*), compareTicketsByDate);
	ticketMaster->sortType = eSortedByDate;
}




void sortTicketsByGuestType(TicketMaster* ticketMaster) {
	if (ticketMaster == NULL || ticketMaster->tickets == NULL) {
		return;
	}

	qsort(ticketMaster->tickets, ticketMaster->numOfTickets, sizeof(Ticket*), compareTicketsByGuestType);
	ticketMaster->sortType = eSortedByGuestType;
}




void sortTicketsUser(TicketMaster* ticketMaster) {
	printf("Please choose sorting type:\n");
	for (int i = 1; i < eNofSortTypes; i++)
	{
		printf("%d. Sort By %s\n", i, sortTypeStr[i]);
	}
	int choice;
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		sortTicketsByID(ticketMaster);
		break;
	case 2:
		sortTicketsByDate(ticketMaster);
		break;
	case 3:
		sortTicketsByGuestType(ticketMaster);
		break;
	}
}





Ticket* findTicketByUser(const TicketMaster* ticketMaster) {
	if (ticketMaster == NULL || ticketMaster->tickets == NULL || ticketMaster->numOfTickets == 0) {
		printf("No ticket added yet\n");
		return NULL;
	}

	if (ticketMaster->sortType == eNotSorted) {
		printf("Please sort the tickets first\n");
		return NULL;
	}

	// Allocate memory for the ticket to search
	Ticket* toSearch = (Ticket*)malloc(sizeof(Ticket));
	Ticket** foundPtr = NULL;
	Ticket* found = NULL;

	if (toSearch == NULL) {
		printf("Memory allocation failed\n");
		return NULL;
	}


	// Search by the sorted type 
	switch (ticketMaster->sortType)
	{
	case eSortedByID:
		printf("Please enter the ticket ID you are looking for:\n");
		scanf("%s", toSearch->id);
		foundPtr = (Ticket**)bsearch(&toSearch, ticketMaster->tickets, ticketMaster->numOfTickets, sizeof(Ticket*), compareTicketsByID);
		break;
	case eSortedByDate:
		printf("Please enter the date you are looking for:\n");
		initDateByUser(&toSearch->dateOfVisit);
		foundPtr = (Ticket**)bsearch(&toSearch, ticketMaster->tickets, ticketMaster->numOfTickets, sizeof(Ticket*), compareTicketsByDate);
		break;
	case eSortedByGuestType:
		printf("Please enter the guest type you are looking for:\n");
		printGuestType();
		int guestType;
		scanf("%d", &guestType);
		toSearch->guestType = guestType - 1;
		foundPtr = (Ticket**)bsearch(&toSearch, ticketMaster->tickets, ticketMaster->numOfTickets, sizeof(Ticket*), compareTicketsByGuestType);
		break;
	}

	// If foundPtr is not NULL, the ticket was found
	if (foundPtr != NULL) {
		found = *foundPtr;
		printf("---- Ticket Found ----\n");
		printTicket(found);
	}
	else {
		printf("Ticket not found\n");
	}

	free(toSearch);
	return found;
}


Ticket* buyTicket(TicketMaster* ticketMaster) {

	Ticket* ticket = (Ticket*)malloc(sizeof(Ticket));
	if (ticket == NULL) {
		printf("Memory allocation failed\n");
		return NULL;
	}
	printf("Please provide the following information:\n");
	initTicketByUser(ticket);

	if (!addTicket(ticketMaster, ticket)) {
		printf("Invalid ticket\n");
		free(ticket);
		return NULL;
	}


	return ticket;

}
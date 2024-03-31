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
	if (ticketMaster == NULL || ticketMaster->numOfTickets == 0) {
		printf("No ticket added yet\n");
		return NULL;
	}

	if (ticketMaster->sortType == eNotSorted) {
		printf("Please sort the tickets first\n");
		return NULL;
	}

	Ticket* toSearch = (Ticket*)malloc(sizeof(Ticket));
	Ticket* found = NULL;

	if (toSearch == NULL) {
		printf("Memory allocation failed\n");
		return NULL;
	}

	switch (ticketMaster->sortType) {
	case eSortedByID:
		printf("Please enter the ID of the ticket you want to search\n");
		scanf("%s", toSearch->id);
		found = (Ticket*)bsearch(toSearch, ticketMaster->tickets, ticketMaster->numOfTickets, sizeof(Ticket), compareTicketsByID);
		break;
	}

	if (found == NULL) {
		printf("Ticket not found\n");
		free(toSearch);
		return NULL;
	}

	printf("Ticket found:\n");
	printf("Ticket ID: %s\n", found->id);
	printf("Price: %.2f$\n", found->price);
	printDate(&found->dateOfVisit);
	printf("Is Used: %s\n", found->isUsed ? "Yes" : "No");

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
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

	ticketMaster->tickets = (Ticket*)realloc(ticketMaster->tickets, (ticketMaster->numOfTickets + 1) * sizeof(Ticket));
	if (ticketMaster->tickets == NULL) {
		return 0;
	}

	ticketMaster->tickets[ticketMaster->numOfTickets] = *ticket;
	ticketMaster->numOfTickets++;
	return 1;
}

void printTicketMaster(const TicketMaster* ticketMaster) {
	if (ticketMaster == NULL || ticketMaster->tickets == NULL) {
		printf("No ticket added yet\n");
		return;
	}
	for (int i = 0; i < ticketMaster->numOfTickets; i++) {
		printTicket(&ticketMaster->tickets[i]);
	}
}


void freeTicketMaster(TicketMaster* ticketMaster) {
	if (ticketMaster->tickets != NULL) {
		free(ticketMaster->tickets);
	}
	ticketMaster->numOfTickets = 0;
	ticketMaster->tickets = NULL;
}


double calcDaily(const TicketMaster* ticketMaster, Date* date) {
	if (ticketMaster == NULL || ticketMaster->tickets == NULL || date == NULL) {
		return 0;
	}
	double sum = 0;
	for (int i = 0; i < ticketMaster->numOfTickets; i++) {
		if (compareDates(ticketMaster->tickets[i].dateOfVisit, *date) == 0) {
			sum += ticketMaster->tickets[i].price;
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

	qsort(ticketMaster->tickets, ticketMaster->numOfTickets, sizeof(Ticket), compareTicketsByID);
	ticketMaster->sortType = eSortedByID;
}

void sortTicketsByDate(TicketMaster* ticketMaster) {
	if (ticketMaster == NULL || ticketMaster->tickets == NULL) {
		return;
	}

	qsort(ticketMaster->tickets, ticketMaster->numOfTickets, sizeof(Ticket), compareTicketsByDate);
	ticketMaster->sortType = eSortedByDate;
}

void sortTicketsByGuestType(TicketMaster* ticketMaster) {
	if (ticketMaster == NULL || ticketMaster->tickets == NULL) {
		return;
	}

	qsort(ticketMaster->tickets, ticketMaster->numOfTickets, sizeof(Ticket), compareTicketsByGuestType);
	ticketMaster->sortType = eSortedByGuestType;
}
void sortTicketsUser(TicketMaster* ticketMaster) {
	// TODO NEED TO IMPLEMENT
}
#include "Ticket.h"



int initTicket(Ticket* ticket, eGuestType guestType, Date dateOfVisit) {
	if (!isValidTicket(guestType, dateOfVisit)) {
		return 0;
	}
	ticket->guestType = guestType;
	ticket->dateOfVisit = dateOfVisit;
	ticket->price = BASE_TICKET_PRICE * Discount[guestType];
	ticket->isUsed = 0;
	generateID(ticket->id);
	return 1;
}

void generateID(char* id) {
	// Generate a random ID of 12 characters. so it can generate 36^12 different IDs
	for (int i = 0; i < ID_TICKET_LEN; i++) {
		int random = randomNum(0, 1);
		if (random == 0) {
			// Generate a random number (49-57 in ASCII table ---> 1-9 )
			id[i] = (char)randomNum(49, 57);
		}
		else {
			// Generate a random uppercase letter (65-90 in ASCII table ---> A-Z )
			id[i] = (char)randomNum(65, 90);
		}
	}
	id[ID_TICKET_LEN] = '\0'; // Null-terminate the string
}


int isValidTicket(eGuestType guestType, Date dateOfVisit) {
	if (!isDateValid(dateOfVisit.day, dateOfVisit.month, dateOfVisit.year)) {
		return 0;
	}
	if (guestType < 0 || guestType >= eNofTicketTypes) {
		return 0;
	}
	return 1;
}
void printTicket(const Ticket* ticket) {
	if (!ticket || !isValidTicket(ticket->guestType, ticket->dateOfVisit)) {
		printf("Invalid Ticket\n");
		return;
	}
	printf("Ticket ID: %s\n", ticket->id);
	printf("Guest Type: %s\n", TicketTypeStr[ticket->guestType]);
	printf("Price: %.1lf\n", ticket->price);
	printf("Date of Visit: ");
	printDate(&ticket->dateOfVisit);
	printf("\n");
	printf("Is Used: %s\n", ticket->isUsed ? "Yes" : "No");
}


int compareTicketsByID(const Ticket* ticket1, const Ticket* ticket2) {
	return strcmp(ticket1->id, ticket2->id);
}

int compareTicketsByDate(const Ticket* ticket1, const Ticket* ticket2) {
	return compareDates(ticket1->dateOfVisit, ticket2->dateOfVisit);
}

int compareTicketsByGuestType(const Ticket* ticket1, const Ticket* ticket2) {
	return ticket1->guestType - ticket2->guestType;
}
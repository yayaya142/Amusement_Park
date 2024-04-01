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
	// get the ticket ID and set it to the ticket loop
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
	printf("Price: %.2lf%s\n", ticket->price, CURRENCY_SYMBOL);
	printf("Date of Visit: ");
	printDate(&ticket->dateOfVisit);
	printf("\n");
	printf("Is Used: %s\n", ticket->isUsed ? "Yes" : "No");
}


int compareTicketsByID(const void* ticket1, const void* ticket2) {
	const Ticket* t1 = *(Ticket**)ticket1;
	const Ticket* t2 = *(Ticket**)ticket2;

	return strcmp(t1->id, t2->id);
}

int compareTicketsByDate(const void* ticket1, const void* ticket2) {
	const Ticket* t1 = *(Ticket**)ticket1;
	const Ticket* t2 = *(Ticket**)ticket2;
	return compareDates(t1->dateOfVisit, t2->dateOfVisit);
}

int compareTicketsByGuestType(const void* ticket1, const void* ticket2) {
	const Ticket* t1 = *(Ticket**)ticket1;
	const Ticket* t2 = *(Ticket**)ticket2;
	return t1->guestType - t2->guestType;
}

void printGuestType() {
	for (int i = 0; i < eNofTicketTypes; i++)
	{
		printf("%d. %s\n", i + 1, TicketTypeStr[i]);
	}
}

void initTicketByUser(Ticket* ticket) {
	int flag = 0;
	int guestType = -1;
	Date date = { 0,0,0 };
	do
	{
		if (flag > 0) {
			printf("Invalid input, please try again\n");
		}

		printf("Enter the guest type:\n");
		printGuestType();
		scanf("%d", &guestType);

		printf("Enter the date of visit:\n");
		initDateByUser(&date);

		flag = 1;

	} while (!initTicket(ticket, guestType - 1, date));
}

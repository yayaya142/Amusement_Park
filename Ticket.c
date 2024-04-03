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
void printTicket(const void* pTicket) {
	const Ticket* ticket = (Ticket*)pTicket;
	// check if ticket is valid
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

void printTicketWrapper(const void* pTicket) {
	const Ticket* ticket = *(const Ticket**)pTicket;
	printTicket(ticket);
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

// save and load functions
int saveTicketToTextFile(const Ticket* ticket, FILE* fp) {
	if (fp == NULL) {
		return 0;
	}
	if (ticket == NULL || isValidTicket(ticket->guestType, ticket->dateOfVisit) == 0) {
		return 0;
	}
	// write the ticket ID to the file
	if (writeStringToTextFile(fp, ticket->id) == 0) {
		return 0;
	}
	// write the guest type to the file
	if (writeIntToTextFile(fp, ticket->guestType) == 0) {
		return 0;
	}
	// write the price to the file
	if (writeDoubleToTextFile(fp, ticket->price) == 0) {
		return 0;
	}
	// write the isUsed to the file
	if (writeIntToTextFile(fp, ticket->isUsed) == 0) {
		return 0;
	}
	// write the date of visit to the file
	if (saveDateToTextFile(&ticket->dateOfVisit, fp) == 0) {
		return 0;
	}
	return 1;

}
int loadTicketFromTextFile(Ticket* ticket, FILE* fp) {
	if (fp == NULL) {
		return 0;
	}

	char id[ID_TICKET_LEN + 1]; // + 1 for null terminator
	int guestType;
	double price;
	int isUsed;
	Date date;

	// read the ticket ID from the file
	if (readStringFromTextFile(fp, id, ID_TICKET_LEN + 1) == NULL) {
		return 0;
	}
	// read the guest type from the file
	if (readIntFromTextFile(fp, &guestType) == 0) {
		return 0;
	}
	// read the price from the file
	if (readDoubleFromTextFile(fp, &price) == 0) {
		return 0;
	}
	// read the isUsed from the file
	if (readIntFromTextFile(fp, &isUsed) == 0) {
		return 0;
	}

	// read the date of visit from the file
	if (loadDateFromTextFile(&date, fp) == 0) {
		return 0;
	}

	// create the ticket
	ticket->guestType = guestType;
	ticket->price = price;
	ticket->isUsed = isUsed;
	ticket->dateOfVisit = date;
	strcpy(ticket->id, id);

	if (isValidTicket(ticket->guestType, ticket->dateOfVisit) == 0) {
		return 0;
	}

	return 1;

}
int saveTicketToBinFile(const Ticket* ticket, FILE* fp) {
	if (fp == NULL) {
		return 0;
	}
	if (ticket == NULL || isValidTicket(ticket->guestType, ticket->dateOfVisit) == 0) {
		return 0;
	}
	// write the ticket ID to the file
	if (writeStringTobinFile(fp, ticket->id) == 0) {
		return 0;
	}
	// write the guest type to the file
	if (writeGeneralToBinFile(fp, &ticket->guestType, sizeof(eGuestType)) == 0) {
		return 0;
	}
	// write the price to the file
	if (writeGeneralToBinFile(fp, &ticket->price, sizeof(double)) == 0) {
		return 0;
	}
	// write the isUsed to the file
	if (writeGeneralToBinFile(fp, &ticket->isUsed, sizeof(int)) == 0) {
		return 0;
	}
	// write the date of visit to the file
	if (saveDateToBinFile(&ticket->dateOfVisit, fp) == 0) {
		return 0;
	}
	return 1;
}
int loadTicketFromBinFile(Ticket* ticket, FILE* fp) {
	if (fp == NULL) {
		return 0;
	}

	char id[ID_TICKET_LEN + 1]; // + 1 for null terminator
	eGuestType guestType;
	double price;
	int isUsed;
	Date date;

	// read the ticket ID from the file
	char* tempID = readStringFromBinFile(fp);
	if (tempID == NULL) {
		return 0;
	}
	strcpy(id, tempID);
	free(tempID);

	// read the guest type from the file
	if (readGeneralFromBinFile(fp, &guestType, sizeof(eGuestType)) == 0) {
		return 0;
	}
	// read the price from the file
	if (readGeneralFromBinFile(fp, &price, sizeof(double)) == 0) {
		return 0;
	}
	// read the isUsed from the file
	if (readGeneralFromBinFile(fp, &isUsed, sizeof(int)) == 0) {
		return 0;
	}

	// read the date of visit from the file
	if (loadDateFromBinFile(&date, fp) == 0) {
		return 0;
	}

	// create the ticket
	strcpy(ticket->id, id);
	ticket->guestType = guestType;
	ticket->price = price;
	ticket->isUsed = isUsed;
	ticket->dateOfVisit = date;

	return 1;
}




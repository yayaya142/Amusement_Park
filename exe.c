#include "exe.h"

#define FILE_NAME_TEXT "lunaPark.txt"
#define FILE_NAME_BIN "lunaPark.bin"

void runManualProgram() {
	LunaPark park;
	printf("\t\t\t\t\tWelcome to Luna Park System!\n");
	printf("\tStep right up and immerse yourself in the magic of Luna Park! As you embark on this exciting journey,\n");
	printf("\t\t\tlet us guide you through three enchanting options:\n\n");

	int userOption = 0;
	int success = -1; // Add a success flag
	while (userOption != 4) {
		if (success == 0) {
			printf("Error loading from file\n");
			printf("Creating new Luna Park\n");
			userOption = 3;
		}
		else {
			printf("1. Load the System from Text File\n");
			printf("2. Load the System from Binary File\n");
			printf("3. Create a new Luna Park\n\n");
			printf("\tChoose your path wisely, adventurer, for the wonders of Luna Park await at every turn. Let the magic begin!\n");
			printf("\t\t\tPlease enter the number corresponding to your choice:\n");

			scanf("%d", &userOption);
		}
		switch (userOption) {
		case 1:
			success = loadLunaParkFromTextFile(&park, FILE_NAME_TEXT);
			break;
		case 2:
			success = loadLunaParkFromBinFile(&park, FILE_NAME_BIN);
			break;
		case 3:
			initLunaParkByUser(&park);
			success = 1;
			break;
		default:
			userOption = 3;
			break;
		}

		// If the operation was successful, break the loop
		if (success == 1) {
			userOption = 4;
			break;
		}
	}

	// the main menu of the system
	printLunaParkMenu(&park);
	userOption = -1;
	while (userOption != eEXIT) {
		printMenu();
		scanf("%d", &userOption);
		userOption--; // to match the enum
		switch (userOption) {
		case eEXIT:
			saveProgram(&park);
			printEndCredits();
			break;
		case eShowAllSystem:
			printLunaParkInfo(&park);
			break;
		case eShowSubSystems:
			printSubSystems(&park);
			break;
		case eAddSubSystem:
			addMenu(&park);
			break;
		case eSort:
			sortTicketsByUser(&park.ticketMasters);
			break;
		case eSearch:
			findTicketByUser(&park.ticketMasters);
			break;
		case eChangeTime:
			changeLunaParkTimeByUser(&park);
			break;
		case eChangeWeather:
			changeLunaParkWeatherByUser(&park);
			break;
		case ePrintProfit:
			printProfit(&park);
			break;
		}

	}

}


void addMenu(LunaPark* park) {
	int userOption = -1;
	printf("1. Add a new Facility\n");
	printf("2. Add a new Worker\n");
	printf("3. Add a new Guest\n");
	printf("4. Add a new Shop\n");
	scanf("%d", &userOption);
	switch (userOption) {
	case 1:
		addFacilityToLunaParkByUser(park);
		break;
	case 2:
		addWorkerToLunaParkByUser(park);
		break;
	case 3:
		addGuestToLunaParkByUser(park, &park->ticketMasters);
		break;
	case 4:
		addShopToLunaParkByUser(park);
		break;
	default:
		break;
	}
}

void printMenu() {
	printf("\n\n\n");
	for (int i = 0; i < eNofMenuOptionTypes; i++)
	{
		printf("%d. %s\n", i + 1, MenuOptionStr[i]);
	}

}


void printSubSystems(LunaPark* park) {
	int userOption = -1;
	printf("\n\n\n");
	printf("1. Print Luna Park Name\n");
	printf("2. Print Ticket Masters\n");
	printf("3. Print Facilities\n");
	printf("4. Print Opening Hours\n");
	printf("5. Print Workers\n");
	printf("6. Print Guests\n");
	printf("7. Print Shops\n");
	printf("8. Print Weather\n");

	scanf("%d", &userOption);
	switch (userOption) {
	case 1:
		printf("Name: %s\n", park->name);
		break;
	case 2:
		printf("\tTickets:\n");
		printTicketMaster(&park->ticketMasters);
		break;
	case 3:
		printf("\tFacilities:\n");
		L_print(&park->facilities, printFacility);
		break;
	case 4:
		printf("Open Time: ");
		printTime(&park->openTime);
		printf("\nClose Time: ");
		printTime(&park->closeTime);
		printf("\n");
		break;
	case 5:
		printf("\tWorkers:\n");
		for (int i = 0; i < park->numOfWorkers; i++)
		{
			park->workers[i]->printPerson(park->workers[i]);
		}

	case 6:
		printf("\tGuests:\n");
		for (int i = 0; i < park->numOfGuests; i++)
		{
			park->guests[i]->printPerson(park->guests[i]);
		}
		break;
	case 7:
		printf("\tShops:\n");
		for (int i = 0; i < park->numOfShops; i++)
		{
			printShop(&park->shops[i]);
		}
		break;
	case 8:
		printWeather(&park->weather);
		break;
	}
}



void saveProgram(LunaPark* park) {
	saveLunaParkToTextFile(park, FILE_NAME_TEXT);
	saveLunaParkToBinFile(park, FILE_NAME_BIN);
	freeLunaPark(park);
}


void runDemoProgram() {
	printf("Welcome to Luna Park System!*&$(*&#\n");

	const int SLEEP_TIME_LONG = 3000;
	const int SLEEP_TIME_SHORT = 1500;

	LunaPark lunaPark;
	char* name = (char*)malloc(21 * sizeof(char));
	strcpy(name, "Shai And Daniel Park");
	printf("Creating Luna Park Name, Please Wait...\n");
	printWaitingDot();

	initLunaPark(&lunaPark, name);
	printf("Luna Park name: %s\n", lunaPark.name);
	Sleep(SLEEP_TIME_SHORT);
	printf("Creating Luna Park Opening Hours, Please Wait...\n");
	printWaitingDot();
	lunaPark.openTime.hour = 8;
	lunaPark.openTime.minute = 0;
	lunaPark.closeTime.hour = 22;
	lunaPark.closeTime.minute = 0;
	printf("Luna Park Opening Hours: ");
	printTime(&lunaPark.openTime);
	printf(" - ");
	printTime(&lunaPark.closeTime);
	printf("\n");
	Sleep(SLEEP_TIME_SHORT);


	printf("Creating Luna Park Weather, Please Wait...\n");
	printWaitingDot();
	lunaPark.weather.condition = eSunny;
	lunaPark.weather.temp = 28;
	printWeather(&lunaPark.weather);
	Sleep(SLEEP_TIME_SHORT);

	// create date for the tickets
	printWaitingDot();
	Date date;
	initDate(&date, 4, 5, 2025); // may the fource be with you

	// create 2 tickets
	printf("Creating Luna Park Tickets, Please Wait...\n");
	printWaitingDot();
	Ticket* ticket1 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket2 = (Ticket*)malloc(sizeof(Ticket));

	initTicket(ticket1, eAdult, date);
	initTicket(ticket2, eChild, date);

	addTicket(&lunaPark.ticketMasters, ticket1);
	addTicket(&lunaPark.ticketMasters, ticket2);

	printf("Luna Park Tickets:\n");
	printTicketMaster(&lunaPark.ticketMasters);
	Sleep(SLEEP_TIME_LONG);

	// Add two workers
	printf("Creating Luna Park Workers, Please Wait...\n");
	printWaitingDot();
	char* name1 = (char*)malloc(9 * sizeof(char));
	strcpy(name1, "WorkerA");
	Person* worker1 = initWorker(0, name1, 180, 30);
	char* name2 = (char*)malloc(9 * sizeof(char));
	strcpy(name2, "WorkerB");
	Person* worker2 = initWorker(1, name2, 170, 35);

	addWorkerToLunaPark(&lunaPark, worker1);
	addWorkerToLunaPark(&lunaPark, worker2);

	printf("Luna Park Workers:\n");
	for (int i = 0; i < lunaPark.numOfWorkers; i++)
	{
		lunaPark.workers[i]->printPerson(lunaPark.workers[i]);
	}
	Sleep(SLEEP_TIME_LONG);

	// Add two guests
	printf("Creating Luna Park Guests, Please Wait...\n");
	printWaitingDot();
	char* guestName1 = (char*)malloc(7 * sizeof(char));
	strcpy(guestName1, "GuestA");
	Person* guest1 = initGuest(guestName1, 160, 20);
	char* guestName2 = (char*)malloc(7 * sizeof(char));
	strcpy(guestName2, "GuestB");
	Person* guest2 = initGuest(guestName2, 150, 25);

	addGuestToLunaPark(&lunaPark, guest1);
	addGuestToLunaPark(&lunaPark, guest2);
	printf("Luna Park Guests:\n");
	for (int i = 0; i < lunaPark.numOfGuests; i++)
	{
		lunaPark.guests[i]->printPerson(lunaPark.guests[i]);
	}
	Sleep(SLEEP_TIME_LONG);

	// add two facilities
	printf("Creating Luna Park Facilities, Please Wait...\n");
	printWaitingDot();
	Facility* facility1 = (Facility*)malloc(sizeof(Facility));
	Facility* facility2 = (Facility*)malloc(sizeof(Facility));

	// init facilities
	char* fName1 = (char*)malloc(10 * sizeof(char));
	strcpy(fName1, "facilityA");
	char* fName2 = (char*)malloc(10 * sizeof(char));
	strcpy(fName2, "facilityB");

	initFacility(facility1, fName1, 1, 70, eAdultFacility);
	initFacility(facility2, fName2, 2, 80, eChildrenFacility);

	addFacilityToLunaPark(&lunaPark, facility1);
	addFacilityToLunaPark(&lunaPark, facility2);
	printf("Luna Park Facilities:\n");
	L_print(&lunaPark.facilities, printFacility);
	Sleep(SLEEP_TIME_LONG);

	// add 2 shops
	printf("Creating Luna Park Shops, Please Wait...\n");
	printWaitingDot();
	Shop shop1, shop2;
	Time openHour;
	initTime(&openHour, 8, 0);
	Time closeHour;
	initTime(&closeHour, 20, 0);

	initShop(&shop1, "ShopA", eRestaurant, openHour, closeHour, 0);
	char* sName = (char*)malloc(6 * sizeof(char));
	strcpy(sName, "ShopB");
	initShop(&shop2, sName, eRestaurant, openHour, closeHour, 1);

	addShopToLunaPark(&lunaPark, shop1);
	addShopToLunaPark(&lunaPark, shop2);

	printf("Luna Park Shops:\n");
	for (int i = 0; i < lunaPark.numOfShops; i++)
	{
		printShop(&lunaPark.shops[i]);
	}
	Sleep(SLEEP_TIME_LONG);

	printf("Luna Park System is ready! Enjoy your visit!\n");
	printf("Behold the wonders of Luna Park!\n");
	printf("The magic of Luna Park awaits you!\n");
	printWaitingDot();
	printLunaParkInfo(&lunaPark);
	freeLunaPark(&lunaPark);
}


void printWaitingDot() {
	const int SLEEP_TIME = 1000;
	for (int i = 0; i < 3; i++)
	{
		printf("\t\t.\n");
		Sleep(SLEEP_TIME);
	}
}


void printEndCredits() {

#include <stdio.h>
	printf("A Long Time Ago, in a Galaxy Far, Far Away...\n");
	printWaitingDot();
	printf("The saga of Luna Park draws to a close, and as the stars twinkle in the night sky,\nWe reflect on the journey guided by the visionary creators, \n***Daniel Betzalel and Shai Odeni***.\n");
	printWaitingDot();
	printf("Their force of creativity has brought Luna Park to life, captivating audiences with its magic and wonder.\nThrough the trials and triumphs, they have forged a legacy that will stand the test of time.\n");
	printWaitingDot();
	printf("As the curtain falls on Luna Park's epic tale, we extend our deepest gratitude to \nDaniel Betzalel and Shai Odeni\nfor their unwavering dedication and boundless imagination.\n");
	printWaitingDot();
	printf("And so, as the galaxies drift into slumber, we bid farewell to Luna Park, knowing that its spirit will continue to inspire generations to come.\n");
	printWaitingDot();
	printf("May the force of Luna Park be with you, always.\n");
	printWaitingDot();
	printf("The End.\n\n\n");

	printf("  / ____| |         (_)      ___    \n");
	printf(" | (___ | |__   __ _ _      ( _ )   \n");
	printf("  \\___ \\| '_ \\ / _` | |     / _ \\/\\ \n");
	printf("  ____) | | | | (_| | |    | (_>  < \n");
	printf(" |_____/|_| |_|\\__,_|_|     \\___/\\/ \n");
	printf(" |  __ \\            (_)    | |       \n");
	printf(" | |  | | __ _ _ __  _  ___| |       \n");
	printf(" | |  | |/ _` | '_ \\| |/ _ \\ |       \n");
	printf(" | |__| | (_| | | | | |  __/ |       \n");
	printf(" |_____/ \\__,_|_| |_|_|\\___|_|  _    \n");
	printf("               |  __ \\         | |   \n");
	printf("               | |__) |_ _ __| | __\n");
	printf("               |  ___/ _` | '__| |/ /\n");
	printf("               | |  | (_| | |  |   < \n");
	printf("               |_|   \\__,_|_|  |_|\\_\\ \n");
	printf("                                    \n");
	printf("                                    \n");

	printf("\n\n\n");
	system("pause");
}


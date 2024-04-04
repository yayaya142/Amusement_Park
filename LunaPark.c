#include "LunaPark.h"


int initLunaPark(LunaPark* lunaPark, char* name) {
	//check if name is valid (only letters)
	if (validName(name) == 0) {
		return 0;
	}

	// init Time
	Time openTime;
	initTime(&openTime, DEFALUT_OPEN_HOUR, DEFALUT_OPEN_MINUTE);

	Time closeTime;
	initTime(&closeTime, DEFALUT_CLOSE_HOUR, DEFALUT_CLOSE_MINUTE);

	// init TicketMaster
	TicketMaster ticketMaster;
	initTicketMaster(&ticketMaster);

	// init Weather
	Weather weather;
	initWeather(&weather, DEFALUT_WEATHER, DEFALUT_TEMPERATURE);

	// init linked list of facilities
	if (L_init(&lunaPark->facilities) == 0) {
		return 0;
	}


	//init lunaPark
	lunaPark->name = name;
	lunaPark->openTime = openTime;
	lunaPark->closeTime = closeTime;
	lunaPark->workers = NULL;
	lunaPark->guests = NULL;
	lunaPark->numOfGuests = 0;
	lunaPark->numOfWorkers = 0;
	lunaPark->ticketMasters = ticketMaster;
	lunaPark->weather = weather;
	lunaPark->shops = NULL;
	lunaPark->numOfShops = 0;
	return 1;
}
void initLunaParkByUser(LunaPark* lunaPark) {
	int flag = 0;
	char* name = NULL;
	do {
		if (flag > 0) {
			printf("Invalid name, please try again\n");
			free(name);
		}

		name = getStrExactName("Please enter the Luna Park name\n");
		flag = 1;

	} while (!initLunaPark(lunaPark, name));

}

void printLunaParkInfo(const LunaPark* lunaPark) {
	if (lunaPark == NULL || validName(lunaPark->name) == 0) {
		return;
	}

	printf("Name: %s\n", lunaPark->name);
	printf("Open Time: ");
	printTime(&lunaPark->openTime);
	printf("\nClose Time: ");
	printTime(&lunaPark->closeTime);
	printf("\nNumber of Workers: %d\n", lunaPark->numOfWorkers);
	for (int i = 0; i < lunaPark->numOfWorkers; i++)
	{
		lunaPark->workers[i]->printPerson(lunaPark->workers[i]);
		printf("\n");
	}

	printf("Number of Shops: %d\n", lunaPark->numOfShops);
	generalArrayFunction((void*)lunaPark->shops, lunaPark->numOfShops, sizeof(Shop), (void*)printShop); // TODO need to check

	int numOfFacilities = L_count(&lunaPark->facilities);
	printf("Number of Facilities: %d\n", numOfFacilities);
	printf("Facilities: \n");
	L_print(&lunaPark->facilities, printFacility);

	printf("Number of Guests: %d\n", lunaPark->numOfGuests);
	for (int i = 0; i < lunaPark->numOfGuests; i++)
	{
		lunaPark->guests[i]->printPerson(lunaPark->guests[i]);
		printf("\n");
	}

	printf("Ticket Master: \n");
	printTicketMaster(&lunaPark->ticketMasters);

	printf("\n");
	printWeather(&lunaPark->weather);

}

void printLunaParkMenu(const LunaPark* lunaPark) {
	if (lunaPark == NULL || validName(lunaPark->name) == 0) {
		return;
	}
	printf("\n\n--------------------  %s  -------------------\n\n", lunaPark->name);
	printf("\t\t\tWelcome Back!\n\n");
	printf("Today's is %s,", WeatherTypeStr[lunaPark->weather.condition]);
	printWeatherForcastTemp(lunaPark->weather.temp);
	printf("\t\tWe are open from ");
	printTime(&lunaPark->openTime);
	printf(" to ");
	printTime(&lunaPark->closeTime);
	printf("\n------------------------------------------------------------------\n\n");
}

void printProfit(const LunaPark* lunaPark) {
	if (lunaPark == NULL || &lunaPark->ticketMasters == NULL) {
		return;
	}
	Date date;
	int userOption = 0;
	printf("Please choose an option:\n");
	printf("1. Print All Income\n");
	printf("2. Print Income By Date\n");
	scanf("%d", &userOption);
	double income = 0;

	switch (userOption)
	{
		//% .2lf % s\n", ticket->price, CURRENCY_SYMBOL);
	case 1:
		income = calcAllIncome(&lunaPark->ticketMasters);
		printf("Total Income: %.2lf%s\n", income, CURRENCY_SYMBOL);
		break;
	case 2:
		initDateByUser(&date);
		income = calcDaily(&lunaPark->ticketMasters, &date);
		printf("Income for ");
		printDate(&date);
		printf(" is: %.2lf%s\n", income, CURRENCY_SYMBOL);
		break;
	default:
		break;
	}
}



void freeLunaPark(LunaPark* lunaPark) {
	if (lunaPark == NULL) {
		return;
	}

	// free name
	free(lunaPark->name);
	// free facilities

	L_free(&lunaPark->facilities, freeFacility);

	// free workers
	for (int i = 0; i < lunaPark->numOfWorkers; i++) {
		lunaPark->workers[i]->freePerson(lunaPark->workers[i]);
	}
	free(lunaPark->workers);

	// free guests
	for (int i = 0; i < lunaPark->numOfGuests; i++) {
		lunaPark->guests[i]->freePerson(lunaPark->guests[i]);
	}
	free(lunaPark->guests);

	// free ticketMasters
	freeTicketMaster(&lunaPark->ticketMasters);

	//// free shops
	generalArrayFunction((void*)lunaPark->shops, lunaPark->numOfShops, sizeof(Shop), (void*)freeShop); // TODO need to check

	free(lunaPark->shops);



}


int addFacilityToLunaPark(LunaPark* lunaPark, Facility* facility) {
	if (lunaPark == NULL || facility == NULL) {
		return 0;
	}
	NODE* ptr = L_insert(&lunaPark->facilities.head, facility);
	if (ptr == NULL) {
		return 0;
	}

	return 1;
}

void addFacilityToLunaParkByUser(LunaPark* lunaPark) {

	Facility* facility = (Facility*)malloc(sizeof(Facility));
	if (facility == NULL) {
		return;
	}
	initFacilityByUser(facility);
	printFacility(facility);
	addFacilityToLunaPark(lunaPark, facility);
}



int addShopToLunaPark(LunaPark* lunaPark, Shop shop) {
	if (lunaPark == NULL) {
		return 0;
	}

	// Allocate memory for new shop array
	Shop* tempShops = (Shop*)realloc(lunaPark->shops, (lunaPark->numOfShops + 1) * sizeof(Shop));
	if (tempShops == NULL) {
		return 0;
	}

	Shop* newShop = &tempShops[lunaPark->numOfShops];
	// deep copy the shop values
	newShop->name = getDynStr(shop.name);
	newShop->openHour = shop.openHour;
	newShop->closeHour = shop.closeHour;
	newShop->type = shop.type;
	newShop->isNameDynamic = 1;
	freeShop(&shop); // free the original shop

	// Update LunaPark shops
	lunaPark->shops = tempShops;
	lunaPark->numOfShops++;

	return 1;
}


void addShopToLunaParkByUser(LunaPark* lunaPark) {
	if (lunaPark == NULL) {
		return;
	}

	Shop shop;
	initShopByUser(&shop);
	addShopToLunaPark(lunaPark, shop);
}


int changeLunaParkTimeByUser(LunaPark* lunaPark) {
	if (lunaPark == NULL) {
		return 0;
	}

	int userOption = 0;
	Time tempOpenTime = lunaPark->openTime;
	Time tempCloseTime = lunaPark->closeTime;
	int flag = 0;
	while (userOption != 3) {
		printf("Please choose an option:\n");
		printf("1. Change Open Time\n");
		printf("2. Change Close Time\n");
		printf("3. Exit\n");
		scanf("%d", &userOption);
		switch (userOption)
		{
		case 1:
			initTimeByUser(&tempOpenTime);
			flag = 1;
			break;
		case 2:
			initTimeByUser(&tempCloseTime);
			flag = 1;
			break;
		case 3:
			break;
		default:
			printf("Invalid option, please try again\n");
			break;
		}

		if (flag > 0 && compareTime(&tempOpenTime, &tempCloseTime) == 1) {
			printf("Open Time need to be before Close Time\n");
			flag = 0; // reset flag to allow user to re-enter times
		}
	}

	if (flag > 0) {
		// If valid times were entered, update the LunaPark times
		lunaPark->openTime = tempOpenTime;
		lunaPark->closeTime = tempCloseTime;
	}

	return 1;
}
int addWorkerToLunaPark(LunaPark* lunaPark, Person* worker) {
	if (lunaPark == NULL) {
		return 0;
	}

	Person** tempArr = (Person**)realloc(lunaPark->workers, (lunaPark->numOfWorkers + 1) * sizeof(Person*));
	if (tempArr == NULL) {
		return 0;
	}
	lunaPark->workers = tempArr;
	lunaPark->workers[lunaPark->numOfWorkers] = worker;
	lunaPark->numOfWorkers++;

	return 1;
}


void addWorkerToLunaParkByUser(LunaPark* lunaPark) {
	if (lunaPark == NULL) {
		return;
	}
	// creat worker
	Person* worker = initWorkerByUser();
	if (worker == NULL) {
		return;
	}
	addWorkerToLunaPark(lunaPark, worker);
}


void addGuestToLunaParkByUser(LunaPark* lunaPark, TicketMaster* ticketMaster) {
	if (lunaPark == NULL || ticketMaster == NULL) {
		return;
	}
	Person* guest = initGuestByUser(ticketMaster);
	if (guest == NULL) {
		return;
	}
	addGuestToLunaPark(lunaPark, guest);
}

int addGuestToLunaPark(LunaPark* lunaPark, Person* guest) {
	if (lunaPark == NULL) {
		return 0;
	}

	Person** tempArr = (Person**)realloc(lunaPark->guests, (lunaPark->numOfGuests + 1) * sizeof(Person*));
	if (tempArr == NULL) {
		return 0;
	}
	lunaPark->guests = tempArr;
	lunaPark->guests[lunaPark->numOfGuests] = guest;
	lunaPark->numOfGuests++;

	return 1;

}


int changeLunaParkWeatherByUser(LunaPark* lunaPark) {
	if (lunaPark == NULL) {
		return 0;
	}
	Weather tempWeather;
	initWeatherByUser(&tempWeather);
	lunaPark->weather = tempWeather;

	return 1;
}


// save and load functions
int saveLunaParkToTextFile(const LunaPark* lunaPark, const char* fileName) {
	// check if lunaPark is valid
	if (lunaPark == NULL) {
		return 0;
	}
	FILE* fp = fopen(fileName, "w");

	IS_FILE_NULL(fp);

	// save name
	if (writeStringToTextFile(fp, lunaPark->name) == 0) { // TO DO FIX THIS PART
		CLOSE_FILE(fp);
		return 0;
	}

	// Save TicketMaster
	if (saveTicketMasterToTextFile(&lunaPark->ticketMasters, fp) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	// Save Facilities
	if (saveFacilityListToTextFile(lunaPark->facilities, fp) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	// Save opem time
	if (saveTimeToTextFile(&lunaPark->openTime, fp) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	// Save close time
	if (saveTimeToTextFile(&lunaPark->closeTime, fp) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	// Save workers
	if (writeIntToTextFile(fp, lunaPark->numOfWorkers) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	for (int i = 0; i < lunaPark->numOfWorkers; i++) {
		if (saveWorkerToTextFile(lunaPark->workers[i], fp) == 0) {
			CLOSE_FILE(fp);
			return 0;
		}
	}

	// Save guests
	if (writeIntToTextFile(fp, lunaPark->numOfGuests) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	for (int i = 0; i < lunaPark->numOfGuests; i++) {
		if (saveGuestToTextFile(lunaPark->guests[i], fp) == 0) {
			CLOSE_FILE(fp);
			return 0;
		}
	}

	// Save weather
	if (saveWeatherToTextFile(&lunaPark->weather, fp) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	// Save shops
	if (writeIntToTextFile(fp, lunaPark->numOfShops) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	for (int i = 0; i < lunaPark->numOfShops; i++) {
		if (saveShopToTextFile(&lunaPark->shops[i], fp) == 0) {
			CLOSE_FILE(fp);
			return 0;
		}
	}
	CLOSE_FILE(fp);
	return 1;
}
int loadLunaParkFromTextFile(LunaPark* lunaPark, const char* fileName) {
	// check if lunaPark is valid
	if (lunaPark == NULL) {
		return 0;
	}
	FILE* fp = fopen(fileName, "r");


	IS_FILE_NULL(fp);

	// load name
	char buffer[MAX_BUFFER_SIZE];
	readStringFromTextFile(fp, buffer, MAX_BUFFER_SIZE);
	char* name = getDynStr(buffer);

	// init lunaPark
	initLunaPark(lunaPark, name);

	// Load TicketMaster
	initTicketMaster(&lunaPark->ticketMasters);
	if (loadTicketMasterFromTextFile(&lunaPark->ticketMasters, fp) == 0) {
		CLOSE_FILE(fp);
		freeLunaPark(lunaPark);
		return 0;
	}


	// Load Facilities
	if (L_init(&lunaPark->facilities) == 0) {
		CLOSE_FILE(fp);
		freeLunaPark(lunaPark);
		return 0;
	}
	int numOfFacilities = 0;
	if (readIntFromTextFile(fp, &numOfFacilities) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	for (int i = 0; i < numOfFacilities; i++) {
		Facility* facility = (Facility*)malloc(sizeof(Facility));
		if (facility == NULL) {
			CLOSE_FILE(fp);
			freeLunaPark(lunaPark);
			return 0;
		}
		if (loadFacilityFromTextFile(facility, fp) == 0) {
			freeFacility(facility);
			CLOSE_FILE(fp);
			freeLunaPark(lunaPark);
			return 0;
		}
		L_insert(&lunaPark->facilities.head, facility);
	}



	// Load open time
	if (loadTimeFromTextFile(&lunaPark->openTime, fp) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	// Load close time
	if (loadTimeFromTextFile(&lunaPark->closeTime, fp) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	// Load workers
	int tempNumOfWorkers;
	if (readIntFromTextFile(fp, &tempNumOfWorkers) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	for (int i = 0; i < tempNumOfWorkers; i++)
	{
		Person* worker = NULL;
		if (loadWorkerFromTextFile(&worker, fp) == 0) {
			CLOSE_FILE(fp);
			freeLunaPark(lunaPark);
			return 0;
		}
		addWorkerToLunaPark(lunaPark, worker);
	}

	// Load guests
	int tempNUmOfGuests;
	if (readIntFromTextFile(fp, &tempNUmOfGuests) == 0) {
		CLOSE_FILE(fp);
		freeLunaPark(lunaPark);
		return 0;
	}

	for (int i = 0; i < tempNUmOfGuests; i++)
	{
		Person* guest = NULL;
		if (loadGuestFromTextFile(&guest, &lunaPark->ticketMasters, fp) == 0) {
			CLOSE_FILE(fp);
			freeLunaPark(lunaPark);
			return 0;
		}
		addGuestToLunaPark(lunaPark, guest);
	}

	// Load weather
	if (loadWeatherFromTextFile(&lunaPark->weather, fp) == 0) {
		CLOSE_FILE(fp);
		freeLunaPark(lunaPark);
		return 0;
	}

	// Load shops
	int tempNumOfShops;
	if (readIntFromTextFile(fp, &tempNumOfShops) == 0) {
		CLOSE_FILE(fp);
		freeLunaPark(lunaPark);
		return 0;
	}

	for (int i = 0; i < tempNumOfShops; i++)
	{
		Shop shop;
		if (loadShopFromTextFile(&shop, fp) == 0) {
			CLOSE_FILE(fp);
			freeLunaPark(lunaPark);
			return 0;
		}
		addShopToLunaPark(lunaPark, shop);
	}



	CLOSE_FILE(fp);
	return 1;

}
int saveLunaParkToBinFile(const LunaPark* lunaPark, const char* fileName) {
	// check if lunaPark is valid
	if (lunaPark == NULL) {
		return 0;
	}
	FILE* fp = fopen(fileName, "w");

	IS_FILE_NULL(fp);

	// save name
	if (writeStringTobinFile(fp, lunaPark->name) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	// Save TicketMaster
	if (saveTicketMasterToBinFile(&lunaPark->ticketMasters, fp) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	// Save Facilities
	if (saveFacilityListToBinFile(lunaPark->facilities, fp) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	// Save opem time
	if (saveTimeToBinFile(&lunaPark->openTime, fp) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	// Save close time
	if (saveTimeToBinFile(&lunaPark->closeTime, fp) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	// Save workers
	if (writeGeneralToBinFile(fp, &lunaPark->numOfWorkers, sizeof(int)) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	for (int i = 0; i < lunaPark->numOfWorkers; i++) {
		if (saveWorkerToBinFile(lunaPark->workers[i], fp) == 0) {
			CLOSE_FILE(fp);
			return 0;
		}
	}

	// Save guests
	if (writeGeneralToBinFile(fp, &lunaPark->numOfGuests, sizeof(int)) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	for (int i = 0; i < lunaPark->numOfGuests; i++) {
		if (saveGuestToBinFile(lunaPark->guests[i], fp) == 0) {
			CLOSE_FILE(fp);
			return 0;
		}
	}

	// Save weather
	if (saveWeatherToBinFile(&lunaPark->weather, fp) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	// Save shops
	if (writeGeneralToBinFile(fp, &lunaPark->numOfShops, sizeof(int)) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	for (int i = 0; i < lunaPark->numOfShops; i++) {
		if (saveShopToBinFile(&lunaPark->shops[i], fp) == 0) {
			CLOSE_FILE(fp);
			return 0;
		}
	}


	CLOSE_FILE(fp);
	return 1;

}
int loadLunaParkFromBinFile(LunaPark* lunaPark, const char* fileName) {
	// check if lunaPark is valid
	if (lunaPark == NULL) {
		return 0;
	}
	FILE* fp = fopen(fileName, "rb");

	IS_FILE_NULL(fp);

	// load name
	char* name = readStringFromBinFile(fp);
	if (name == NULL) {
		CLOSE_FILE(fp);
		return 0;
	}

	// init lunaPark
	initLunaPark(lunaPark, name);


	// Load TicketMaster
	initTicketMaster(&lunaPark->ticketMasters);
	if (loadTicketMasterFromBinFile(&lunaPark->ticketMasters, fp) == 0) {
		CLOSE_FILE(fp);
		freeLunaPark(lunaPark);
		return 0;
	}


	// Load Facilities
	if (L_init(&lunaPark->facilities) == 0) {
		CLOSE_FILE(fp);
		freeLunaPark(lunaPark);
		return 0;
	}
	int numOfFacilities = 0;
	if (readGeneralFromBinFile(fp, &numOfFacilities, sizeof(int)) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}
	for (int i = 0; i < numOfFacilities; i++) {
		Facility* facility = (Facility*)malloc(sizeof(Facility));
		if (facility == NULL) {
			CLOSE_FILE(fp);
			freeLunaPark(lunaPark);
			return 0;
		}
		if (loadFacilityFromBinFile(facility, fp) == 0) {
			freeFacility(facility);
			CLOSE_FILE(fp);
			freeLunaPark(lunaPark);
			return 0;
		}
		L_insert(&lunaPark->facilities.head, facility);
	}

	// Load open time
	if (loadTimeFromBinFile(&lunaPark->openTime, fp) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	// Load close time
	if (loadTimeFromBinFile(&lunaPark->closeTime, fp) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	// Load workers
	int tempNumOfWorkers;
	if (readGeneralFromBinFile(fp, &tempNumOfWorkers, sizeof(int)) == 0) {
		CLOSE_FILE(fp);
		return 0;
	}

	for (int i = 0; i < tempNumOfWorkers; i++)
	{
		Person* worker = NULL;
		if (loadWorkerFromBinFile(&worker, fp) == 0) {
			CLOSE_FILE(fp);
			freeLunaPark(lunaPark);
			return 0;
		}
		addWorkerToLunaPark(lunaPark, worker);
	}

	// Load guests
	int tempNUmOfGuests;
	if (readGeneralFromBinFile(fp, &tempNUmOfGuests, sizeof(int)) == 0) {
		CLOSE_FILE(fp);
		freeLunaPark(lunaPark);
		return 0;
	}

	for (int i = 0; i < tempNUmOfGuests; i++)
	{
		Person* guest = NULL;
		if (loadGuestFromBinFile(&guest, &lunaPark->ticketMasters, fp) == 0) {
			CLOSE_FILE(fp);
			freeLunaPark(lunaPark);
			return 0;
		}
		addGuestToLunaPark(lunaPark, guest);
	}

	// Load weather
	if (loadWeatherFromBinFile(&lunaPark->weather, fp) == 0) {
		CLOSE_FILE(fp);
		freeLunaPark(lunaPark);
		return 0;
	}

	// Load shops
	int tempNumOfShops;
	if (readGeneralFromBinFile(fp, &tempNumOfShops, sizeof(int)) == 0) {
		CLOSE_FILE(fp);
		freeLunaPark(lunaPark);
		return 0;
	}
	for (int i = 0; i < tempNumOfShops; i++) {
		Shop shop;
		if (loadShopFromBinFile(&shop, fp) == 0) {
			CLOSE_FILE(fp);
			freeLunaPark(lunaPark);
			return 0;
		}
		addShopToLunaPark(lunaPark, shop);
	}

	CLOSE_FILE(fp);
	return 1;
}
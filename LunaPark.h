#ifndef __LunaPark__
#define __LunaPark__

#include <crtdbg.h> // TODO: remove before release
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Time.h"
#include "Facility.h"
#include "Worker.h"
#include "Guest.h"
#include "TicketMaster.h"
#include "Date.h"
#include "Ticket.h"
#include "Weather.h"
#include "Shop.h"
#include "listGen.h"
#include "filehelper.h"
#include "Person.h"
#include "General.h"

#define DEFALUT_OPEN_HOUR 7
#define DEFALUT_OPEN_MINUTE 30 
#define DEFALUT_CLOSE_HOUR 20
#define DEFALUT_CLOSE_MINUTE 0
#define DEFALUT_WEATHER 0 // 0 - sunny, 1 - rainy, 2 - cloudy, 3 - snowy
#define DEFALUT_TEMPERATURE 25

typedef struct {
	char* name;
	TicketMaster ticketMasters;
	LIST facilities;
	Time openTime;
	Time closeTime;
	Person** workers;
	int numOfWorkers;
	Person** guests;
	int numOfGuests;
	Weather weather;
	Shop* shops;
	int numOfShops;
} LunaPark;


int initLunaPark(LunaPark* lunaPark, char* name); //done
void initLunaParkByUser(LunaPark* lunaPark); //done
void printLunaParkMenu(const LunaPark* lunaPark); //done
void printLunaParkInfo(const LunaPark* lunaPark); //done
void freeLunaPark(LunaPark* lunaPark); //done
int addFacilityToLunaPark(LunaPark* lunaPark, Facility* facility); // done
void addFacilityToLunaParkByUser(LunaPark* lunaPark); // done
int addWorkerToLunaPark(LunaPark* lunaPark, Person* worker);// done
void addWorkerToLunaParkByUser(LunaPark* lunaPark); // done
int addShopToLunaPark(LunaPark* lunaPark, Shop shop); // done
void addShopToLunaParkByUser(LunaPark* lunaPark); // done
int changeLunaParkTimeByUser(LunaPark* lunaPark); // done
int changeLunaParkWeatherByUser(LunaPark* lunaPark); // done
void addGuestToLunaParkByUser(LunaPark* lunaPark, TicketMaster* ticketMaster); // done
int addGuestToLunaPark(LunaPark* lunaPark, Person* guest); // done
void printProfit(const LunaPark* lunaPark); // done

// save and load functions
int saveLunaParkToTextFile(const LunaPark* lunaPark, const char* fileName);
int loadLunaParkFromTextFile(LunaPark* lunaPark, const char* fileName);
int saveLunaParkToBinFile(const LunaPark* lunaPark, const char* fileName);
int loadLunaParkFromBinFile(LunaPark* lunaPark, const char* fileName);



#endif 

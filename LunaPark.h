#ifndef __LunaPark__
#define __LunaPark__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Time.h"
#include "Facility.h"
#include "Worker.h"
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
	LIST facilities;
	Time openTime;
	Time closeTime;
	Person** workers;
	int numOfWorkers;
	TicketMaster ticketMasters;
	Weather weather;
	Shop* shops;
	int numOfShops;
	int todayVisitors;
} LunaPark;


int initLunaPark(LunaPark* lunaPark, char* name); //done
int initLunaParkByUser(LunaPark* lunaPark); //done
void printLunaParkMenu(const LunaPark* lunaPark); //done
void printLunaParkInfo(const LunaPark* lunaPark); //done
void freeLunaPark(LunaPark* lunaPark); //done
int addFacilityToLunaPark(LunaPark* lunaPark, Facility* facility);
void addFacilityToLunaParkByUser(LunaPark* lunaPark);

// save and load functions
int saveLunaParkToTextFile(const LunaPark* lunaPark, const char* fileName);
int loadLunaParkFromTextFile(LunaPark* lunaPark, const char* fileName);
int saveLunaParkToBinFile(const LunaPark* lunaPark, const char* fileName);
int loadLunaParkFromBinFile(LunaPark* lunaPark, const char* fileName);


#endif 

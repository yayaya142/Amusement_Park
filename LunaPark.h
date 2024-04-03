//#ifndef __LunaPark__
//#define __LunaPark__
//
//#include "Time.h"
//#include "Facility.h"
//#include "Worker.h"
//#include "TicketMaster.h"
//#include "Date.h"
//#include "Ticket.h"
//#include "Weather.h"
//#include "Shop.h"
//#include "listGen.h"
//#include "filehelper.h"
//#include "Person.h"
//#include "General.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//
//typedef struct {
//	char* name;
//	LIST* facilities;
//	Time openTime;
//	Time closeTime;
//	Worker** workers;
//	TicketMaster* ticketMasters;
//	Weather* weather;
//	Shop* shops;
//	int todayVisitors;
//} LunaPark;
//
//
//
//int initLunaPark(LunaPark* lunaPark, char* name, Time openTime, Time closeTime, Worker** staff, TicketMaster* ticketMaster, Weather* weather, Shop* shops);
//int initLunaParkByUser(LunaPark* lunaPark);
//void printLunaPark(const LunaPark* lunaPark);
//void freeLunaPark(LunaPark* lunaPark);
//
//// save and load functions
//int saveLunaParkToTextFile(const LunaPark* lunaPark, FILE* fp);
//int loadLunaParkFromTextFile(LunaPark* lunaPark, FILE* fp);
//int saveLunaParkToBinFile(const LunaPark* lunaPark, FILE* fp);
//int loadLunaParkFromBinFile(LunaPark* lunaPark, FILE* fp);
//
//#endif 

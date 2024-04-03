//#include "LunaPark.h"
//
//
//int initLunaPark(LunaPark* lunaPark,char* name, Time* openTime, Time *closeTime, Worker** staff, TicketMaster* ticketMaster, Weather* weather, Shop* shops){
//	if(lunaPark == NULL){
//		return;
//	}
//	//check if name is valid (only letters)
//	if(validName(name) == 0) {
//		return 0;
//	}
//	//check if time is valid
//	if(isValidTime(openTime->hour,openTime->minute) == 0 || isValidTime(closeTime->hour, closeTime->minute) == 0){
//		return 0;
//	}
//	//check if workers is valid
//	for (int i = 0; i < sizeof(staff); i++) {
//		if (isValidInfoWorker(staff[i]->department)==0) { // correct?
//			return 0;
//		}
//	}
//
//	//check if ticketMasters is valid
//	
//	//check if weather is valid
//	
//	//check if shops is valid
//	
//	//init lunaPark
//	lunaPark->name = name;
//	lunaPark->openTime = *openTime;
//	lunaPark->closeTime = *closeTime;
//	lunaPark->workers = staff;
//	lunaPark->ticketMasters = ticketMaster;
//	lunaPark->weather = weather;
//	lunaPark->shops = shops;
//	lunaPark->todayVisitors = 0;
//	return 1;
//}
//int initLunaParkByUser(LunaPark* lunaPark){}
//void printLunaPark(const LunaPark* lunaPark){}
//void freeLunaPark(LunaPark* lunaPark){}
//
//// save and load functions
//int saveLunaParkToTextFile(const LunaPark* lunaPark, FILE* fp){}
//int loadLunaParkFromTextFile(LunaPark* lunaPark, FILE* fp){}
//int saveLunaParkToBinFile(const LunaPark* lunaPark, FILE* fp){}
//int loadLunaParkFromBinFile(LunaPark* lunaPark, FILE* fp){}
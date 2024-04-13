#ifndef __MYTIME__
#define __MYTIME__
#include <crtdbg.h> // TODO: remove before release
#include <stdio.h>
#include "fileHelper.h"

#define MAX_HOUR 23
#define MIN_HOUR 0
#define MAX_MIN 59
#define MIN_MIN 0


typedef struct {
	int hour;
	int minute;
} Time;

int initTime(Time* time, int hour, int minute);
int isValidTime(int hour, int minute);
void printTime(const Time* time);
int compareTime(const Time* time1, const Time* time2);
void initTimeByUser(Time* time);
// save and load functions
int saveTimeToTextFile(const Time* pTime, FILE* fp);
int loadTimeFromTextFile(Time* pTime, FILE* fp);
int saveTimeToBinFile(const Time* pTime, FILE* fp);
int loadTimeFromBinFile(Time* pTime, FILE* fp);


#endif 
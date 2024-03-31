#ifndef __MYTIME__
#define __MYTIME__
#include <crtdbg.h> // TODO: remove before release
#include <stdio.h>

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



#endif 
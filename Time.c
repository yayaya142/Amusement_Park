#include "Time.h"

#define DELEMETER ':'


int initTime(Time* time, int hour, int minute) {
	if (!isValidTime(hour, minute)) {
		return 0;
	}
	time->hour = hour;
	time->minute = minute;
	return 1;
}


int isValidTime(int hour, int minute) {
	if (hour < MIN_HOUR || hour > MAX_HOUR || minute < MIN_MIN || minute > MAX_MIN) {
		return 0;
	}
	return 1;
}


void printTime(const Time* time) {
	if (!isValidTime(time->hour, time->minute)) {
		printf("Invalid time\n");
		return;
	}
	printf("%02d%c%02d", time->hour, DELEMETER, time->minute);
}
int compareTime(const Time* time1, const Time* time2) {
	if (time1->hour == time2->hour && time1->minute == time2->minute) {
		return 0;
	}
	if (time1->hour > time2->hour) {
		return 1;
	}
	if (time1->hour < time2->hour) {
		return -1;
	}
	if (time1->minute > time2->minute) {
		return 1;
	}
	if (time1->minute < time2->minute) {
		return -1;
	}
	return 0;
}





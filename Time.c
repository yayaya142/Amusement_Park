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


void initTimeByUser(Time* time) {
	int flag = 0;
	int hour, minute;
	do {
		if (flag > 0) {
			printf("Invalid time, Please try again\n");
		}
		printf("Please enter Hour: ");
		scanf("%d", &hour);
		printf("Please enter Minute: ");
		scanf("%d", &minute);
		flag = 1;
	} while (!initTime(time, hour, minute));
}

// save and load functions
int saveTimeToTextFile(const Time* pTime, FILE* fp) {
	if (fp == NULL) { /// NEED TO BE MACRO
		return 0;
	}

	if (writeIntToTextFile(fp, pTime->hour) == 0) {
		return 0;
	}

	if (writeIntToTextFile(fp, pTime->minute) == 0) {
		return 0;
	}

	return 1;
}


int loadTimeFromTextFile(Time* pTime, FILE* fp) {
	if (fp == NULL) { /// NEED TO BE MACRO
		return 0;
	}
	int tempHour, tempMinute;

	if (readIntFromTextFile(fp, &tempHour) == 0) {
		return 0;
	}

	if (readIntFromTextFile(fp, &tempMinute) == 0) {
		return 0;
	}

	// init the time
	if (!initTime(pTime, tempHour, tempMinute)) {
		return 0;
	}

	return 1;
}

int saveTimeToBinFile(const Time* pTime, FILE* fp) {
	if (fp == NULL) { /// NEED TO BE MACRO
		return 0;
	}

	/*if (writeGeneralToBinFile(fp, &(pTime->hour), sizeof(int)) == 0) {
		return 0;
	}

	if (writeGeneralToBinFile(fp, &(pTime->minute), sizeof(int)) == 0) {
		return 0;
	}*/

	if (writeGeneralToBinFile(fp, pTime, sizeof(Time)) == 0) {
		return 0;
	}

	return 1;

}

int loadTimeFromBinFile(Time* pTime, FILE* fp) {
	if (fp == NULL) { /// NEED TO BE MACRO
		return 0;
	}
	int tempHour, tempMinute;
	if (readGeneralFromBinFile(fp, &tempHour, sizeof(int)) == 0) {
		return 0;
	}

	if (readGeneralFromBinFile(fp, &tempMinute, sizeof(int)) == 0) {
		return 0;
	}

	if (!initTime(pTime, tempHour, tempMinute)) {
		return 0;
	}

	return 1;
}

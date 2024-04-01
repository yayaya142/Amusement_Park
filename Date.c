#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "General.h"
#include "fileHelper.h"
#include "Date.h"

#define DATE_DELIMITER '/'
const int DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };


int initDate(Date* pDate, int day, int month, int year) {
	// check if date is valid
	if (!isDateValid(day, month, year)) {
		return 0;
	}
	pDate->day = day;
	pDate->month = month;
	pDate->year = year;
	return 1;
};


int isDateValid(int day, int month, int year) {
	//  check year validation
	if (year < MIN_YEAR) {
		return 0;
	}
	//  check month validation
	if (month < 1 || month > 12) {
		return 0;
	}
	//   check if day is in month days range
	else if (!isDayValid(day, month)) {
		return 0;
	};
	return 1;
}

int isDayValid(int day, int month) {
	if (day < 1 || day > DAY_MONTHS[month - 1]) {
		return 0;
	}
	return 1;
}

void printDate(const Date* pDate)
{
	printf("%d%c%d%c%d", pDate->day, DATE_DELIMITER, pDate->month, DATE_DELIMITER, pDate->year);
}


int compareDates(const Date Date1, const Date Date2) {
	if (Date1.year != Date2.year) {
		return Date1.year - Date2.year;
	}
	if (Date1.month != Date2.month) {
		return Date1.month - Date2.month;
	}
	return Date1.day - Date2.day;
}


int saveDateToBinFile(FILE* file, Date* pDate) {
	if (file == NULL || pDate == NULL) {
		return 0;
	}

	if (writeGeneralToBinFile(file, pDate, sizeof(Date)) != 1) {
		return 0;
	}
	return 1;
}
Date readDateFromBinFile(FILE* file) {
	Date date;
	date.day = 0;
	date.month = 0;
	date.year = 0;
	if (file == NULL) {
		return date;
	}
	if (readGeneralFromBinFile(file, &date, sizeof(Date)) != 1) {
		return date;
	}

	return date;
}

void initDateByUser(Date* pDate) {
	int flag = 0;
	int day, month, year;
	do
	{
		if (flag > 0) {
			printf("Invalid date, Please try again\n");
		}
		printf("Enter date (day month year)\n");
		scanf("%d %d %d", &day, &month, &year);

		flag = 1;
	} while (!initDate(pDate, day, month, year));
}
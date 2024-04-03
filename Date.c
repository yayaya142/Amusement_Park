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


//int saveDateToBinFile(FILE* file, Date* pDate) {
//	if (file == NULL || pDate == NULL) {
//		return 0;
//	}
//
//	if (writeGeneralToBinFile(file, pDate, sizeof(Date)) != 1) {
//		return 0;
//	}
//	return 1;
//}
//Date readDateFromBinFile(FILE* file) {
//	Date date;
//	date.day = 0;
//	date.month = 0;
//	date.year = 0;
//	if (file == NULL) {
//		return date;
//	}
//	if (readGeneralFromBinFile(file, &date, sizeof(Date)) != 1) {
//		return date;
//	}
//
//	return date;
//}

void initDateByUser(Date* pDate) {
	int flag = 0;
	int day, month, year;
	do
	{
		if (flag > 0) {
			printf("Invalid date, Please try again\n");
		}
		printf("Enter date\n");
		printf("Enter day: ");
		scanf("%d", &day);
		printf("Enter month: ");
		scanf("%d", &month);
		printf("Enter year: ");
		scanf("%d", &year);

		flag = 1;
	} while (!initDate(pDate, day, month, year));
}

// save and load function
int saveDateToTextFile(const Date* pDate, FILE* fp) {
	if (fp == NULL) {
		return 0;
	}
	if (pDate == NULL || isDateValid(pDate->day, pDate->month, pDate->year) == 0) {
		return 0;
	}
	// write day to file
	if (writeIntToTextFile(fp, pDate->day) == 0) {
		return 0;
	}
	// write month to file
	if (writeIntToTextFile(fp, pDate->month) == 0) {
		return 0;
	}
	// write year to file
	if (writeIntToTextFile(fp, pDate->year) == 0) {
		return 0;
	}

	return 1;
}

int loadDateFromTextFile(Date* pDate, FILE* fp) {
	if (fp == NULL) {
		return 0;
	}
	int day, month, year;
	// read day from file
	if (readIntFromTextFile(fp, &day) == 0) {
		return 0;
	}
	// read month from file
	if (readIntFromTextFile(fp, &month) == 0) {
		return 0;
	}
	// read year from file
	if (readIntFromTextFile(fp, &year) == 0) {
		return 0;
	}
	// check if date is valid
	if (!initDate(pDate, day, month, year)) {
		return 0;
	}
	return 1;
}

int saveDateToBinFile(const Date* pDate, FILE* fp) {
	if (fp == NULL) {
		return 0;
	}
	if (pDate == NULL || isDateValid(pDate->day, pDate->month, pDate->year) == 0) {
		return 0;
	}

	if (writeGeneralToBinFile(fp, pDate, sizeof(Date)) == 0) {
		return 0;
	}

	return 1;
}
int loadDateFromBinFile(Date* pDate, FILE* fp) {
	if (fp == NULL) {
		return 0;
	}

	if (readGeneralFromBinFile(fp, pDate, sizeof(Date)) == 0) {
		return 0;
	}
	return 1;
}
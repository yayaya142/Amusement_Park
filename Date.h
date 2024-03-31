#ifndef __MYDATE__
#define __MYDATE__
#include <crtdbg.h> // TODO: remove before release
#define MIN_YEAR 2024

typedef struct
{
	int			day;
	int			month;
	int			year;
}Date;

// functions
int initDate(Date* pDate, int day, int month, int year);
int isDateValid(int day, int month, int year);
int isDayValid(int day, int month);
void printDate(const Date* pDate);
int compareDates(const Date Date1, const Date Date2);
int saveDateToBinFile(FILE* file, Date* pDate);
Date readDateFromBinFile(FILE* file);
#endif
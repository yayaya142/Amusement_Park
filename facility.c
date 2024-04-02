#include "facility.h"
#include "General.h"
#include <stdio.h>

int initFacility(Facility* pFacility,char* name, int minHeight, int maxHeight, Category category) {
	if (minHeight < 0 || maxHeight < 0 || minHeight > maxHeight || category < 0 || category >= eNofTypesFacility) {
		return 0;
	}
	if (!validFacility(name, minHeight, maxHeight, category)) { //check if name is valid (only letters)
		return 0;
	}
	pFacility->name = name;
	pFacility->minHeight = minHeight;
	pFacility->maxHeight = maxHeight;
	pFacility->category = category;
	return 1;
}

void initFacilityByUser(Facility* pFacility) {
	char name[MAX_STR_LEN];
	int minHeight = 0;
	int maxHeight = 0;
	Category category = 0;
	int flag = 0;
	do {
		if (flag > 0) {
			printf("Please try again\n");
		}
		char* new_name = getStrExactName("Please enter the facility name:\n");
		strcpy(name, new_name);
		free(new_name);

		printf("Please enter the Minimum height:\n");
		scanf("%d", &minHeight);
		printf("Please enter the Maximum height:\n");
		scanf("%d", &maxHeight);
		printf("Please enter the category:\n");
		for (int i = 0; i < eNofTypesFacility; i++) {
			printf("%d. %s\n", i, facilityTypeTilte[i]);
		}
		scanf("%d", &category);
		flag++;
	} while (!initFacility(pFacility, name, minHeight, maxHeight, category));
}

int validFacility(char* name, int minHeight, int maxHeight, Category category) {
	
	if (minHeight < 0 || maxHeight < 0 || minHeight > maxHeight) {
		printf("valid height only between 0 and %d\n", maxHeight);
		return 0;
	}
	if(category < 0 || category >= eNofTypesFacility) {
		printf("Choose a category from %d - %d\n",0 ,eNofTypesFacility);
		return 0;
	}
	if (!validName(name)) { //check if name is valid (only letters)
		printf("Invalid name\n");
		return 0;
	}
	return 1;
}

void printFacility(const Facility* pFacility) {
	printf("Name: %s\nCategory: %s\nHeight Limitation:\n\t-Min Height: %d\n\t-Max Height: %d\n",pFacility->name, facilityTypeTilte[pFacility->category], pFacility->minHeight, pFacility->maxHeight);
}

int compareFacilities(const Facility* pFacility1, const Facility* pFacility2) {
	if (pFacility1->category != pFacility2->category) {
		return pFacility1->category - pFacility2->category;
	}
	if (pFacility1->minHeight != pFacility2->minHeight) {
		return pFacility1->minHeight - pFacility2->minHeight;
	}
	return pFacility1->maxHeight - pFacility2->maxHeight;
}

void freeFacility(Facility* pFacility) {
	free(pFacility->name);
}
#include "facility.h"



int initFacility(Facility* pFacility,char* name, int minHeight, int maxHeight, Category category) {
	if (minHeight < 0 || maxHeight < 0 || minHeight > maxHeight || category < 0 || category >= eNofTypesFacility) {
		return 0;
	}
	if (!validName(name)) { //check if name is valid (only letters)
		return 0;
	}
	pFacility->minHeight = minHeight;
	pFacility->maxHeight = maxHeight;
	pFacility->category = category;
	return 1;
}

void printFacility(const Facility* pFacility) {
	printf("Name: %s\nCategory: %s\n, Height Limitation:\n -Min Height: %d\n-Max Height: %d\n",pFacility->name, facilityTypeTilte[pFacility->category], pFacility->minHeight, pFacility->maxHeight);
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
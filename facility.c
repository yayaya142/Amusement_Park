#include "facility.h"


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
		//TODO : change the strcpy 
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
	printf("----------------------------\n");
	printf("Name: %s\nCategory: %s\nHeight Limitation:\n\t-Min Height: %d\n\t-Max Height: %d\n",pFacility->name, facilityTypeTilte[pFacility->category], pFacility->minHeight, pFacility->maxHeight);
	printf("----------------------------\n");

}


int compareFacilitiesByCategory(const Facility* pFacility1, const Facility* pFacility2) {
	return pFacility1->category - pFacility2->category;
}

void freeFacility(Facility* pFacility) {
	free(pFacility->name);
}

// save and load functions
int saveFacilityToTextFile(const Facility* facility, FILE* fp){
	if (fp == NULL) {
		return 0;
	}
	if(!validFacility(facility->name, facility->minHeight, facility->maxHeight, facility->category)){
		return 0;
	}
	//save name to text file
	if(writeStringToTextFile(fp, facility->name) == 0){
		return 0;
	}
	//save min height to text file
	if(writeIntToTextFile(fp, facility->minHeight) == 0){
		return 0;
	}
	//save max height to text file
	if(writeIntToTextFile(fp, facility->maxHeight) == 0){
		return 0;
	}
	//save category to text file
	if(writeIntToTextFile(fp, facility->category) == 0){
		return 0;
	}
	return 1;

}
int loadFacilityFromTextFile(Facility* facility, FILE* fp){
	if (fp == NULL) {
		return 0;
	}
	char buffer[MAX_BUFFER_SIZE];
	int tempMin;
	int tempMax;
	int tempCategory;
	//load name from text file
	char* bufferName =  readStringFromTextFile(fp, buffer, MAX_BUFFER_SIZE);
	if(bufferName == NULL){
		return 0;
	}
	//load nim height to facility
	if(readIntFromTextFile(fp, &tempMin) == 0){
		return 0;
	}
	//load max height to facility
	if(readIntFromTextFile(fp, &tempMax) == 0){
		return 0;
	}
	//load category to facility
	if(readIntFromTextFile(fp, &tempCategory) == 0){
		return 0;
	}	

	Category category = tempCategory;
	//allocated for facility name
	char* name = (char*)malloc(strlen(bufferName) + 1);
	if (!name) {
		return 0;
	}
	strcpy(name, bufferName);

	//init facility
	if(!initFacility(facility, name, tempMin, tempMax, category)){
		free(name);
		return 0;
	}
	return 1;
}
int saveFacilityToBinFile(const Facility* facility, FILE* fp){
	if(fp == NULL) {
		return 0;
	}
	if(!validFacility(facility->name, facility->minHeight, facility->maxHeight, facility->category)){
		return 0;
	}
	//save name to bin file
	if(writeStringTobinFile(fp, facility->name) == 0){
		return 0;
	}
	//save min height to bin file
	if(writeGeneralToBinFile(fp, &facility->minHeight, sizeof(int)) == 0){
		return 0;
	}
	//save max height to bin file
	if(writeGeneralToBinFile(fp, &facility->maxHeight, sizeof(int)) == 0){
		return 0;
	}
	//save category to bin file
	if(writeGeneralToBinFile(fp, &facility->category, sizeof(Category)) == 0){
		return 0;
	}

	return 1;
}
int loadFacilityFromBinFile(Facility* facility, FILE* fp){
	if (fp == NULL) {
		return 0;
  }
	//load name from bin file
	char* tempName = readStringFromBinFile(fp);
	if(tempName == NULL){
		return 0;
	}
	//load min height from bin file
	int tempMin;
	if(readGeneralFromBinFile(fp, &tempMin, sizeof(int)) == 0){
		free(tempName);
		return 0;
	}
	//load max height from bin file
	int tempMax;
	if(readGeneralFromBinFile(fp, &tempMax, sizeof(int)) == 0){
		free(tempName);
		return 0;
	}	
	//load category from bin file
	Category tempCategory;
	if(readGeneralFromBinFile(fp, &tempCategory, sizeof(Category)) == 0){
		free(tempName);
		return 0;
	}

	//init facility
	if(!initFacility(facility, tempName, tempMin, tempMax, tempCategory)){
		free(tempName);
		return 0;
	}
	return 1;
}
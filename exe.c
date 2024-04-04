#include "exe.h"

//#define FILE_NAME_TEXT "lunaPark.txt"
//#define FILE_NAME_BIN "lunaPark.bin"

#define FILE_NAME_TEXT "AAALunaParkTest.txt"
#define FILE_NAME_BIN "AAALunaParkTest.bin"



void runManualProgram() {
	LunaPark park;
	printf("Welcome to Luna Park System!\n");
	printf("Step right up and immerse yourself in the magic of Luna Park! As you embark on this exciting journey,\n");
	printf("let us guide you through three enchanting options:\n");

	int userOption = 0;
	int success = -1; // Add a success flag
	while (userOption != 4) {
		if (success == 0) {
			printf("Error loading from file\n");
			printf("Creating new Luna Park\n");
			userOption = 3;
		}
		else {
			printf("1. Load the System from Text File\n");
			printf("2. Load the System from Binary File\n");
			printf("3. Create a new Luna Park\n");
			printf("Choose your path wisely, adventurer, for the wonders of Luna Park await at every turn. Let the magic begin!\n");
			printf("Please enter the number corresponding to your choice:\n");

			scanf("%d", &userOption);
		}
		switch (userOption) {
		case 1:
			success = loadLunaParkFromTextFile(&park, FILE_NAME_TEXT);
			break;
		case 2:
			success = loadLunaParkFromBinFile(&park, FILE_NAME_BIN);
			break;
		case 3:
			initLunaParkByUser(&park);
			success = 1;
			break;
		default:
			userOption = 3;
			break;
		}

		// If the operation was successful, break the loop
		if (success == 1) {
			userOption = 4;
			break;
		}
	}





	// the main menu of the system
	printLunaParkMenu(&park);
	userOption = -1;
	while (userOption != eEXIT) {
		printMenu();
		scanf("%d", &userOption);
		userOption--; // to match the enum
		switch (userOption) {
		case eEXIT:
			saveProgram(&park);
			break;
		case eShowAllSystem:

			break;
		case eShowSubSystems:
			break;
		case eAddSubSystem:
			break;
		case eSort:
			break;
		case eSearch:
			break;






		}







		printLunaParkInfo(&park);

	}







}







void printMenu() {
	for (int i = 0; i < eNofMenuOptionTypes; i++)
	{
		printf("%d. %s", i + 1, MenuOptionStr[i]);
	}

}

void saveProgram(LunaPark* park) {
	saveLunaParkToTextFile(park, FILE_NAME_TEXT);
	saveLunaParkToBinFile(park, FILE_NAME_BIN);
	freeLunaPark(park);
}

#include "Shop.h"

int initShop(Shop* shop, char* name, eShopType type, Time openHour, Time closeHour, int isNameDynamic) {
	if (!isValidShop(name, type, openHour, closeHour)) {
		return 0;
	}
	shop->name = name;
	shop->type = type;
	shop->openHour = openHour;
	shop->closeHour = closeHour;
	shop->isNameDynamic = isNameDynamic;
	return 1;
}

int isValidShop(char* name, eShopType type, Time openHour, Time closeHour) {
	// check name is not NULL
	if (name == NULL || name == "") {
		return 0;
	}
	// check type si valid
	if (type < 0 || type >= eNofShopTypes) {
		return 0;
	}
	// check openHour and closeHour are valid
	if (!isValidTime(openHour.hour, openHour.minute) || !isValidTime(closeHour.hour, closeHour.minute)) {
		return 0;
	}
	// check openHour is before closeHour
	if (compareTime(&openHour, &closeHour) > 0) {
		return 0;
	}

	return 1;
}
void printShop(const void* pShop) {
	const Shop* shop = (Shop*)pShop;


	if (!isValidShop(shop->name, shop->type, shop->openHour, shop->closeHour)) {
		printf("Invalid shop\n");
		return;
	}
	printf("Shop name: %s\n", shop->name);
	printf("Shop type: %s\n", ShopTypeStr[shop->type]);
	printf("Open hour: ");
	printTime(&shop->openHour);
	printf("\nClose hour: ");
	printTime(&shop->closeHour);
}

int compareShopsByName(const Shop* shop1, const Shop* shop2) {
	return strcmp(shop1->name, shop2->name);
}

void freeShop(void* pShop) {
	Shop* shop = (Shop*)pShop;
	if (shop->isNameDynamic) {
		free(shop->name);
	}
}


void printShopTypes() {
	for (int i = 0; i < eNofShopTypes; i++) {
		printf("%d - %s\n", i + 1, ShopTypeStr[i]);
	}
}

void initShopByUser(Shop* shop) {
	int flag = 0;
	eShopType type = -1;
	Time openHour = { -1, 0 };
	Time closeHour = { -1, 0 };
	char* name = NULL;
	do
	{
		if (flag > 0) {
			printf("Invalid shop values, Please try again\n");
			free(name);
		}
		name = getStrExactName("Please enter shop name: ");

		printf("Please enter shop type:\n");
		printShopTypes();
		scanf("%d", &type);

		printf("Please enter shop open time\n");

		initTimeByUser(&openHour);

		printf("Please enter shop close time\n");
		initTimeByUser(&closeHour);


		flag = 1;

	} while (!initShop(shop, name, type - 1, openHour, closeHour, 1));

}



// save and load functions
int saveShopToTextFile(const Shop* shop, FILE* fp) {
	if (fp == NULL) {
		return 0;
	}

	if (!isValidShop(shop->name, shop->type, shop->openHour, shop->closeHour)) {
		return 0;
	}
	// save name to file
	if (writeStringToTextFile(fp, shop->name) == 0) {
		return 0;
	}
	// save shop type
	if (writeIntToTextFile(fp, shop->type) == 0) {
		return 0;
	}

	if (saveTimeToTextFile(&shop->openHour, fp) == 0) {
		return 0;
	}

	if (saveTimeToTextFile(&shop->closeHour, fp) == 0) {
		return 0;
	}




	return 1;

}
int loadShopFromTextFile(Shop* shop, FILE* fp) {
	if (fp == NULL) {
		return 0;
	}

	char buffer[MAX_BUFFER_SIZE];
	// read name from file
	char* bufferName = readStringFromTextFile(fp, buffer, MAX_BUFFER_SIZE);

	if (bufferName == NULL) {
		return 0;
	}
	// read shop type
	int intTempType;
	if (readIntFromTextFile(fp, &intTempType) == 0) {
		return 0;
	}
	eShopType tempType = intTempType;


	// read open hour and close hour
	Time tempOpenHour;
	if (loadTimeFromTextFile(&tempOpenHour, fp) == 0) {
		return 0;
	}
	// read close hour
	Time tempCloseHour;
	if (loadTimeFromTextFile(&tempCloseHour, fp) == 0) {
		return 0;
	}

	// aloocate memory for shop name
	char* tempName = (char*)malloc(strlen(bufferName) + 1);
	if (tempName == NULL) {
		return 0;
	}
	strcpy(tempName, bufferName);

	// init shop
	if (!initShop(shop, tempName, tempType, tempOpenHour, tempCloseHour, 1)) {
		free(tempName);
		return 0;
	}

	return 1;
}
int saveShopToBinFile(const Shop* shop, FILE* fp) {
	if (fp == NULL) {
		return 0;
	}

	if (!isValidShop(shop->name, shop->type, shop->openHour, shop->closeHour)) {
		return 0;
	}

	// save name to file
	if (writeStringTobinFile(fp, shop->name) == 0) {
		return 0;
	}

	// save shop type
	if (writeGeneralToBinFile(fp, &shop->type, sizeof(eShopType)) == 0) {
		return 0;
	}

	// save open hour
	if (saveTimeToBinFile(&shop->openHour, fp) == 0) {
		return 0;
	}

	// save close hour
	if (saveTimeToBinFile(&shop->closeHour, fp) == 0) {
		return 0;
	}

	return 1;
}
int loadShopFromBinFile(Shop* shop, FILE* fp) {
	if (fp == NULL) {
		return 0;
	}

	// read name from file
	char* tempName = readStringFromBinFile(fp);
	if (tempName == NULL) {
		return 0;
	}

	// read shop type
	eShopType tempType;
	if (readGeneralFromBinFile(fp, &tempType, sizeof(eShopType)) == 0) {
		free(tempName);
		return 0;
	}

	// read open hour
	Time tempOpenHour;
	if (loadTimeFromBinFile(&tempOpenHour, fp) == 0) {
		free(tempName);
		return 0;
	}

	// read close hour
	Time tempCloseHour;
	if (loadTimeFromBinFile(&tempCloseHour, fp) == 0) {
		free(tempName);
		return 0;
	}

	// init shop
	if (!initShop(shop, tempName, tempType, tempOpenHour, tempCloseHour, 1)) {
		free(tempName);
		return 0;
	}
	return 1;
}
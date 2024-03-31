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
void printShop(const Shop* shop) {
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


void freeShop(Shop* shop) {
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
		printf("Please enter shop name: ");
		name = getStrExactName(NULL);

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
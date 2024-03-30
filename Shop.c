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
#ifndef __SHOP__
#define __SHOP__

#include <crtdbg.h> // TODO: remove before release
#include <stdio.h>
#include <string.h>
#include "Time.h"
#include "General.h"

typedef enum {
	eRestaurant, eCoffeeShop, eBar, eNofShopTypes
}eShopType;

static const char* ShopTypeStr[eNofShopTypes] = { "Restaurant", "Coffee Shop", "Bar" };

typedef struct {
	char* name;
	eShopType type;
	Time openHour;
	Time closeHour;
	int isNameDynamic; // Flag to indicate if name is dynamically allocated (for freeing)
} Shop;


int initShop(Shop* shop, char* name, eShopType type, Time openHour, Time closeHour, int isNameDynamic);
int isValidShop(char* name, eShopType type, Time openHour, Time closeHour);
void printShop(const void* shop);
int compareShopsByName(const Shop* shop1, const Shop* shop2);
void freeShop(void* shop);
void printShopTypes();
void initShopByUser(Shop* shop);

#endif 

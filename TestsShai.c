#include "TestsShai.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// runAllTests
// Aim:	this function runs all tests, by default all the tests run automatically. manual tests will be marked as "Manual"
// Input:	none
// Output:	if failed, the function assert failed will pop up a message, otherwise, a message that all tests passed will be printed
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void runAllTestsShai() {
	printf("---- Running Shai's tests....----\n");
	//initByUserManualsTest(); // Manual
	DateTests();
	WeatherTest();
	TimeTests();
	ShopTests();
	TicketTests();
	TicketMasterTests();
	generalLibaryTests();
	SaveAndLoadTests();
	LunaParkTests();
	printf("---- All Shai's tests passed ----\n");
}
// Date tests
void DateTests() {
	initDateTest();
	isDateValidTest();
	compareDatesTest();
}
void initDateTest() {
	Date date;

	// Test 1: Valid date
	assert(initDate(&date, 1, 1, 2025) == 1);
	assert(date.day == 1 && date.month == 1 && date.year == 2025);

	// Test 2: Day out of range (low)
	assert(initDate(&date, 0, 1, 2025) == 0);

	// Test 3: Day out of range (high)
	assert(initDate(&date, 32, 1, 2025) == 0);

	// Test 4: Month out of range (low)
	assert(initDate(&date, 1, 0, 2025) == 0);

	// Test 5: Month out of range (high)
	assert(initDate(&date, 1, 13, 2025) == 0);

	// Test 6: Year out of range (low)
	assert(initDate(&date, 1, 1, 2023) == 0);

	// Test 7: February 29 (not leap year in this program)
	assert(initDate(&date, 29, 2, 2025) == 0);

	// Test 8: Valid date at end of year
	assert(initDate(&date, 31, 12, 2025) == 1);
	assert(date.day == 31 && date.month == 12 && date.year == 2025);

	// Test 9: Invalid date at end of year
	assert(initDate(&date, 32, 12, 2025) == 0);
}
void isDateValidTest() {
	// Test 1: Valid date
	assert(isDateValid(1, 1, 2025) == 1);

	// Test 2: Day out of range (low)
	assert(isDateValid(0, 1, 2025) == 0);

	// Test 3: Day out of range (high)
	assert(isDateValid(32, 1, 2025) == 0);

	// Test 4: Month out of range (low)
	assert(isDateValid(1, 0, 2025) == 0);

	// Test 5: Month out of range (high)
	assert(isDateValid(1, 13, 2025) == 0);

	// Test 6: Year out of range (low)
	assert(isDateValid(1, 1, 2023) == 0);

	// Test 7: February 29 (not leap year in this program)
	assert(isDateValid(29, 2, 2024) == 0);

	// Test 8: Valid date at end of year
	assert(isDateValid(31, 12, 2025) == 1);

	// Test 9: Invalid date at end of year
	assert(isDateValid(32, 12, 2025) == 0);
}
void compareDatesTest() {
	Date date1, date2;
	// Test 1: Equal dates
	initDate(&date1, 1, 1, 2025);
	initDate(&date2, 1, 1, 2025);
	assert(compareDates(date1, date2) == 0);

	// Test 2: Different years
	initDate(&date1, 1, 1, 2025);
	initDate(&date2, 1, 1, 2026);
	assert(compareDates(date1, date2) < 0);
	assert(compareDates(date2, date1) > 0);

	// Test 3: Same year, different months
	initDate(&date1, 1, 1, 2025);
	initDate(&date2, 1, 2, 2025);
	assert(compareDates(date1, date2) < 0);
	assert(compareDates(date2, date1) > 0);

	// Test 4: Same year and month, different days
	initDate(&date1, 1, 1, 2025);
	initDate(&date2, 2, 1, 2025);
	assert(compareDates(date1, date2) < 0);
	assert(compareDates(date2, date1) > 0);

	// Test 5: Same year and day, but different months
	initDate(&date1, 15, 1, 2025);
	initDate(&date2, 15, 2, 2025);
	assert(compareDates(date1, date2) < 0);
	assert(compareDates(date2, date1) > 0);

	// Test 6: Same month and day, but different years
	initDate(&date1, 15, 1, 2025);
	initDate(&date2, 15, 1, 2026);
	assert(compareDates(date1, date2) < 0);
	assert(compareDates(date2, date1) > 0);

}
// Weather Tests
void WeatherTest() {
	initWeatherTest();
	isValidWeatherTest();
	compareWeatherByTempTest();
}
void initWeatherTest() {
	Weather weather;

	// Test 1: Valid weather
	assert(initWeather(&weather, 0, 25) == 1);
	assert(weather.condition == eSunny && weather.temp == 25);

	// Test 2: Temperature out of range (low)
	assert(initWeather(&weather, 1, -51) == 0);

	// Test 3: Temperature out of range (high)
	assert(initWeather(&weather, 2, 51) == 0);

	// Test 4: Valid weather with negative temperature
	assert(initWeather(&weather, 0, -5) == 1);
	assert(weather.condition == eSunny && weather.temp == -5);

	// Test 5: Valid weather with maximum temperature
	assert(initWeather(&weather, 1, 50) == 1);
	assert(weather.condition == eRainy && weather.temp == 50);

	// Test 6: Valid weather with minimum temperature
	assert(initWeather(&weather, eSunny, -10) == 1);
	assert(weather.condition == eSunny && weather.temp == -10);

}
void isValidWeatherTest() {
	// Test 1: Valid weather
	assert(isValidWeather(eSunny, 20) == 1);

	// Test 2: Invalid weather condition (low)
	assert(isValidWeather(-1, 20) == 0);

	// Test 3: Invalid weather condition (high)
	assert(isValidWeather(eNofWeatherTypes, 20) == 0);

	// Test 4: Temperature out of range (low)
	assert(isValidWeather(eRainy, MIN_TEMP - 1) == 0);

	// Test 5: Temperature out of range (high)
	assert(isValidWeather(eCloudy, MAX_TEMP + 1) == 0);

	// Test 6: Valid weather with minimum temperature
	assert(isValidWeather(eSunny, MIN_TEMP) == 1);

	// Test 7: Valid weather with maximum temperature
	assert(isValidWeather(eRainy, MAX_TEMP) == 1);

	// Test 8: Valid weather with negative temperature
	assert(isValidWeather(eCloudy, -10) == 1);

}
void compareWeatherByTempTest() {
	Weather weather1, weather2;

	// Test 1: Equal temperatures
	initWeather(&weather1, eSunny, 20);
	initWeather(&weather2, eRainy, 20);
	assert(compareWeatherByTemp(&weather1, &weather2) == 0);

	// Test 2: weather1 has lower temperature
	initWeather(&weather1, eSunny, 15);
	initWeather(&weather2, eRainy, 20);
	assert(compareWeatherByTemp(&weather1, &weather2) < 0);

	// Test 3: weather1 has higher temperature
	initWeather(&weather1, eSunny, 25);
	initWeather(&weather2, eRainy, 20);
	assert(compareWeatherByTemp(&weather1, &weather2) > 0);

	// Test 4: weather1 has a temperature of 0 and weather2 has a positive temperature
	initWeather(&weather1, eSunny, 0);
	initWeather(&weather2, eRainy, 20);
	assert(compareWeatherByTemp(&weather1, &weather2) < 0);

	// Test 5: weather1 has a temperature of 0 and weather2 has a negative temperature
	initWeather(&weather1, eSunny, 0);
	initWeather(&weather2, eRainy, -10);
	assert(compareWeatherByTemp(&weather1, &weather2) > 0);

	// Test 6: Both weather1 and weather2 have a temperature of 0
	initWeather(&weather1, eSunny, 0);
	initWeather(&weather2, eRainy, 0);
	assert(compareWeatherByTemp(&weather1, &weather2) == 0);
}
// Time tests
void TimeTests() {
	initTimeTest();
	isValidTimeTest();
	compareTimeTest();
}
void initTimeTest() {
	Time time;

	// Test 1: Valid time
	assert(initTime(&time, 0, 0) == 1);
	assert(time.hour == 0 && time.minute == 0);

	// Test 2: Hour out of range (low)
	assert(initTime(&time, -1, 0) == 0);

	// Test 3: Hour out of range (high)
	assert(initTime(&time, 24, 0) == 0);

	// Test 4: Minute out of range (low)
	assert(initTime(&time, 0, -1) == 0);

	// Test 5: Minute out of range (high)
	assert(initTime(&time, 0, 60) == 0);

	// Test 6: Valid time with maximum hour
	assert(initTime(&time, 23, 0) == 1);
	assert(time.hour == 23 && time.minute == 0);

	// Test 7: Valid time with maximum minute
	assert(initTime(&time, 0, 59) == 1);
	assert(time.hour == 0 && time.minute == 59);

	// Test 8: Valid time with maximum hour and minute
	assert(initTime(&time, 23, 59) == 1);
	assert(time.hour == 23 && time.minute == 59);
}
void isValidTimeTest() {
	// Test 1: Valid time
	assert(isValidTime(0, 0) == 1);

	// Test 2: Hour out of range (low)
	assert(isValidTime(-1, 0) == 0);

	// Test 3: Hour out of range (high)
	assert(isValidTime(24, 0) == 0);

	// Test 4: Minute out of range (low)
	assert(isValidTime(0, -1) == 0);

	// Test 5: Minute out of range (high)
	assert(isValidTime(0, 60) == 0);

	// Test 6: Valid time with maximum hour
	assert(isValidTime(23, 0) == 1);

	// Test 7: Valid time with maximum minute
	assert(isValidTime(0, 59) == 1);

	// Test 8: Valid time with maximum hour and minute
	assert(isValidTime(23, 59) == 1);
}
void compareTimeTest() {
	Time time1, time2;

	// Test 1: Equal times
	initTime(&time1, 12, 0);
	initTime(&time2, 12, 0);
	assert(compareTime(&time1, &time2) == 0);

	// Test 2: time1 has earlier hour
	initTime(&time1, 11, 0);
	initTime(&time2, 12, 0);
	assert(compareTime(&time1, &time2) < 0);

	// Test 3: time1 has later hour
	initTime(&time1, 13, 0);
	initTime(&time2, 12, 0);
	assert(compareTime(&time1, &time2) > 0);

	// Test 4: Same hour, time1 has earlier minute
	initTime(&time1, 12, 0);
	initTime(&time2, 12, 30);
	assert(compareTime(&time1, &time2) < 0);

	// Test 5: Same hour, time1 has later minute
	initTime(&time1, 12, 30);
	initTime(&time2, 12, 0);
	assert(compareTime(&time1, &time2) > 0);
}
// Shop tests
void ShopTests() {
	initShopTest();
	isValidShopTest();
	compareShopsByNameTest();
}
void initShopTest() {
	Shop shop;
	Time openHour;
	initTime(&openHour, 8, 0);
	Time closeHour;
	initTime(&closeHour, 20, 0);

	// Test 1: Valid shop
	assert(initShop(&shop, "Shop1", eRestaurant, openHour, closeHour, 0) == 1);
	assert(strcmp(shop.name, "Shop1") == 0 && shop.type == eRestaurant && compareTime(&shop.openHour, &openHour) == 0 && compareTime(&shop.closeHour, &closeHour) == 0);
	freeShop(&shop);
	// Test 2: Empty name
	assert(initShop(&shop, "", eRestaurant, openHour, closeHour, 0) == 0);
	freeShop(&shop);

	// Test 3: Invalid shop type (low)
	assert(initShop(&shop, "Shop1", -1, openHour, closeHour, 0) == 0);
	freeShop(&shop);

	// Test 4: Invalid shop type (high)
	assert(initShop(&shop, "Shop1", eNofShopTypes, openHour, closeHour, 0) == 0);
	freeShop(&shop);

	// Test 5: Invalid open hour
	assert(initShop(&shop, "Shop1", eRestaurant, (Time) { -1, 0 }, closeHour, 0) == 0);
	freeShop(&shop);

	// Test 6: Invalid close hour
	assert(initShop(&shop, "Shop1", eRestaurant, openHour, (Time) { 25, 0 }, 0) == 0);
	freeShop(&shop);

	// Test 7: Open hour after close hour
	assert(initShop(&shop, "Shop1", eRestaurant, closeHour, openHour, 0) == 0);
	freeShop(&shop);

	// Test 8: dynamic memory allocation
	char* name = (char*)malloc(6 * sizeof(char));
	strcpy(name, "Shop1");
	assert(initShop(&shop, name, eRestaurant, openHour, closeHour, 1) == 1);
	freeShop(&shop);
}
void isValidShopTest() {
	// Test 1: Valid shop
	assert(isValidShop("Shop1", eRestaurant, (Time) { 8, 0 }, (Time) { 20, 0 }) == 1);

	// Test 2: Empty name
	assert(isValidShop("", eRestaurant, (Time) { 8, 0 }, (Time) { 20, 0 }) == 0);

	// Test 3: Invalid shop type (low)
	assert(isValidShop("Shop1", -1, (Time) { 8, 0 }, (Time) { 20, 0 }) == 0);

	// Test 4: Invalid shop type (high)
	assert(isValidShop("Shop1", eNofShopTypes, (Time) { 8, 0 }, (Time) { 20, 0 }) == 0);

	// Test 5: Invalid open hour
	assert(isValidShop("Shop1", eRestaurant, (Time) { -1, 0 }, (Time) { 20, 0 }) == 0);

	// Test 6: Invalid close hour
	assert(isValidShop("Shop1", eRestaurant, (Time) { 8, 0 }, (Time) { 25, 0 }) == 0);

	// Test 7: Open hour after close hour
	assert(isValidShop("Shop1", eRestaurant, (Time) { 20, 0 }, (Time) { 8, 0 }) == 0);

}
void compareShopsByNameTest() {
	Shop shop1, shop2;

	// Test 1: Equal names
	initShop(&shop1, "ShopA", eCoffeeShop, (Time) { 9, 0 }, (Time) { 18, 0 }, 0);
	initShop(&shop2, "ShopA", eRestaurant, (Time) { 9, 0 }, (Time) { 18, 0 }, 0);
	assert(compareShopsByName(&shop1, &shop2) == 0);

	// Test 2: shop1's name comes before shop2's name in alphabetical order
	initShop(&shop1, "ShopA", eCoffeeShop, (Time) { 19, 0 }, (Time) { 20, 0 }, 0);
	initShop(&shop2, "ShopB", eCoffeeShop, (Time) { 9, 0 }, (Time) { 18, 0 }, 0);
	assert(compareShopsByName(&shop1, &shop2) < 0);

	// Test 3: shop1's name comes after shop2's name in alphabetical order
	initShop(&shop1, "ShopB", eCoffeeShop, (Time) { 9, 0 }, (Time) { 18, 0 }, 0);
	initShop(&shop2, "ShopA", eBar, (Time) { 9, 0 }, (Time) { 18, 0 }, 0);
	assert(compareShopsByName(&shop1, &shop2) > 0);

	// Test 4: shop1's name is a substring of shop2's name
	initShop(&shop1, "Shop", eBar, (Time) { 9, 0 }, (Time) { 18, 0 }, 0);
	initShop(&shop2, "ShopA", eRestaurant, (Time) { 9, 0 }, (Time) { 18, 0 }, 0);
	assert(compareShopsByName(&shop1, &shop2) < 0);

	// Test 5: shop1's name is uppercase, shop2's name is lowercase
	initShop(&shop1, "RESTAURANT", eRestaurant, (Time) { 9, 0 }, (Time) { 18, 0 }, 0);
	initShop(&shop2, "restaurant", eRestaurant, (Time) { 9, 0 }, (Time) { 18, 0 }, 0);
	assert(compareShopsByName(&shop1, &shop2) < 0);

	// Test 7: shop1's name is a prefix of shop2's name
	initShop(&shop1, "Rest", eRestaurant, (Time) { 9, 0 }, (Time) { 18, 0 }, 0);
	initShop(&shop2, "Restaurant", eRestaurant, (Time) { 9, 0 }, (Time) { 18, 0 }, 0);
	assert(compareShopsByName(&shop1, &shop2) < 0);

}
// Ticket tests
void TicketTests() {
	initTicketTest();
	isValidTicketTest();
	compareTicketsByIDTest();
	compareTicketsByDateTest();
	compareTicketsByGuestTypeTest();
}
void initTicketTest() {
	Ticket ticket;
	Date validDate, invalidDate;
	initDate(&validDate, 1, 1, 2025);
	initDate(&invalidDate, 32, 1, 2025);

	// Test 1: Valid guest type and date
	assert(initTicket(&ticket, eAdult, validDate) == 1);
	assert(ticket.guestType == eAdult);
	assert(compareDates(ticket.dateOfVisit, validDate) == 0);

	// Test 2: Invalid guest type, valid date
	assert(initTicket(&ticket, eNofTicketTypes, validDate) == 0);

	// Test 3: Valid guest type, invalid date
	assert(initTicket(&ticket, eAdult, invalidDate) == 0);

	// Test 4: Invalid guest type and date
	assert(initTicket(&ticket, eNofTicketTypes, invalidDate) == 0);

	// Test 5: Valid guest type and date at the end of the year
	Date endOfYear;
	initDate(&endOfYear, 31, 12, 2025);
	assert(initTicket(&ticket, eChild, endOfYear) == 1);
	assert(ticket.guestType == eChild);
	assert(compareDates(ticket.dateOfVisit, endOfYear) == 0);

	// Test 6: Valid guest type and date at the start of the year
	Date startOfYear;
	initDate(&startOfYear, 1, 1, 2025);
	assert(initTicket(&ticket, eSoldier, startOfYear) == 1);
	assert(ticket.guestType == eSoldier);
	assert(compareDates(ticket.dateOfVisit, startOfYear) == 0);

	// Test 7: Invalid guest type and valid date at the start of the year
	assert(initTicket(&ticket, eNofTicketTypes, startOfYear) == 0);
}
void isValidTicketTest() {
	Date validDate;
	initDate(&validDate, 1, 1, 2025);

	Date invalidDate;
	initDate(&invalidDate, 32, 1, 2025);

	// Test 1: Valid guest type and date
	assert(isValidTicket(eAdult, validDate) == 1);

	// Test 2: Invalid guest type, valid date
	assert(isValidTicket(eNofTicketTypes, validDate) == 0);

	// Test 3: Valid guest type, invalid date
	assert(isValidTicket(eAdult, invalidDate) == 0);

	// Test 4: Invalid guest type and date
	assert(isValidTicket(eNofTicketTypes, invalidDate) == 0);

	// Test 5: Check with minimum valid date and valid guest type
	Date minValidDate;
	initDate(&minValidDate, 1, 1, 2024);
	assert(isValidTicket(eChild, minValidDate) == 1);

	// Test 6: Check with maximum valid date and valid guest type
	Date maxValidDate;
	initDate(&maxValidDate, 31, 12, 2025);
	assert(isValidTicket(eSoldier, maxValidDate) == 1);
}
void compareTicketsByIDTest() {
	Ticket* ticket1 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket2 = (Ticket*)malloc(sizeof(Ticket));

	// Test 1: Equal IDs
	strcpy(ticket1->id, "AAAAAAAAAAA1");
	strcpy(ticket2->id, "AAAAAAAAAAA1");
	assert(compareTicketsByID(&ticket1, &ticket2) == 0);


	// Test 2: ticket1's ID comes before ticket2's ID in alphabetical order
	strcpy(ticket1->id, "AAAAAAAAAAA1");
	strcpy(ticket2->id, "AAAAAAAAAAA2");
	assert(compareTicketsByID(&ticket1, &ticket2) < 0);

	// Test 3: ticket1's ID comes after ticket2's ID in alphabetical order
	strcpy(ticket1->id, "AAAAAAAAAAA2");
	strcpy(ticket2->id, "AAAAAAAAAAA1");
	assert(compareTicketsByID(&ticket1, &ticket2) > 0);

	// Test 4: ticket1's ID is a substring of ticket2's ID
	strcpy(ticket1->id, "AAAAAAAAAAA1");
	strcpy(ticket2->id, "AAAAAAAAAAA1A");
	assert(compareTicketsByID(&ticket1, &ticket2) < 0);

	// Test 5: ticket1's ID is uppercase, ticket2's ID is lowercase
	strcpy(ticket1->id, "AAAAAAAAAAA1");
	strcpy(ticket2->id, "aaaaaaaaaaa1");
	assert(compareTicketsByID(&ticket1, &ticket2) < 0);

	free(ticket1);
	free(ticket2);
}
void compareTicketsByDateTest() {
	Ticket* ticket1 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket2 = (Ticket*)malloc(sizeof(Ticket));

	Date date1, date2;
	initDate(&date1, 1, 1, 2025);
	initDate(&date2, 2, 1, 2025);

	// Test 1: Equal dates
	initTicket(ticket1, eAdult, date1);
	initTicket(ticket2, eAdult, date1);
	assert(compareTicketsByDate(&ticket1, &ticket2) == 0);

	// Test 2: ticket1's date is earlier than ticket2's date
	initTicket(ticket1, eAdult, date1);
	initTicket(ticket2, eAdult, date2);
	assert(compareTicketsByDate(&ticket1, &ticket2) < 0);

	// Test 3: ticket1's date is later than ticket2's date
	initTicket(ticket1, eAdult, date2);
	initTicket(ticket2, eAdult, date1);
	assert(compareTicketsByDate(&ticket1, &ticket2) > 0);

	// free
	free(ticket1);
	free(ticket2);

}
void compareTicketsByGuestTypeTest() {
	Ticket* ticket1 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket2 = (Ticket*)malloc(sizeof(Ticket));

	Date date;
	initDate(&date, 1, 1, 2025);

	// Test 1: Equal guest types
	initTicket(ticket1, eAdult, date);
	initTicket(ticket2, eAdult, date);
	assert(compareTicketsByGuestType(&ticket1, &ticket2) == 0);

	// Test 2: ticket1's guest type is earlier than ticket2's guest type
	initTicket(ticket1, eChild, date);
	initTicket(ticket2, eAdult, date);
	assert(compareTicketsByGuestType(&ticket1, &ticket2) < 0);

	// Test 3: ticket1's guest type is later than ticket2's guest type	
	initTicket(ticket1, eAdult, date);
	initTicket(ticket2, eChild, date);
	assert(compareTicketsByGuestType(&ticket1, &ticket2) > 0);

	// free
	free(ticket1);
	free(ticket2);
}
// TicketMaster tests
void TicketMasterTests() {
	initTicketMasterTest();
	addTicketTest();
	calcDailyTest();
	sortTicketsByIDTest();
	sortTicketsByDateTest();
	sortTicketsByGuestTypeTest();
	findTicketByIDTest();
	//sortTicketsUserTestManual(); // manual test off by default
	//buyTicketTestManual(); // manual test off by default
	//findTicketByUserTestManual(); // manual test off by default
}
void initTicketMasterTest() {
	TicketMaster ticketMaster;
	// Test
	initTicketMaster(&ticketMaster);
	assert(ticketMaster.tickets == NULL && ticketMaster.numOfTickets == 0);
}
void addTicketTest() {
	TicketMaster ticketMaster;
	Ticket* ticket = (Ticket*)malloc(sizeof(Ticket));
	Date validDate;
	initDate(&validDate, 1, 1, 2025);
	initTicket(ticket, eAdult, validDate);
	initTicketMaster(&ticketMaster);

	// Test 1: Add a ticket to an empty ticket master
	assert(addTicket(&ticketMaster, ticket) == 1);
	assert(ticketMaster.numOfTickets == 1);
	assert(compareTicketsByID(&ticketMaster.tickets[0], &ticket) == 0);

	// Test 2: Add a ticket to a ticket master with one ticket
	Ticket* ticket2 = (Ticket*)malloc(sizeof(Ticket));
	initTicket(ticket2, eChild, validDate);
	assert(addTicket(&ticketMaster, ticket2) == 1);
	assert(ticketMaster.numOfTickets == 2);
	assert(compareTicketsByID(&ticketMaster.tickets[0], &ticket) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[1], &ticket2) == 0);

	// Test 3: Add a ticket to a ticket master with two tickets
	Ticket* ticket3 = (Ticket*)malloc(sizeof(Ticket));
	initTicket(ticket3, eStudent, validDate);
	assert(addTicket(&ticketMaster, ticket3) == 1);
	assert(ticketMaster.numOfTickets == 3);
	assert(compareTicketsByID(&ticketMaster.tickets[0], &ticket) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[1], &ticket2) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[2], &ticket3) == 0);

	// Test 4: Add a ticket to a ticket master with three tickets
	Ticket* ticket4 = (Ticket*)malloc(sizeof(Ticket));
	initTicket(ticket4, eSoldier, validDate);
	assert(addTicket(&ticketMaster, ticket4) == 1);
	assert(ticketMaster.numOfTickets == 4);
	assert(compareTicketsByID(&ticketMaster.tickets[0], &ticket) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[1], &ticket2) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[2], &ticket3) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[3], &ticket4) == 0);

	// Test 5: Add a ticket to a ticket master with four tickets
	Ticket* ticket5 = (Ticket*)malloc(sizeof(Ticket));
	initTicket(ticket5, eAdult, validDate);
	assert(addTicket(&ticketMaster, ticket5) == 1);
	assert(ticketMaster.numOfTickets == 5);
	assert(compareTicketsByID(&ticketMaster.tickets[0], &ticket) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[1], &ticket2) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[2], &ticket3) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[3], &ticket4) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[4], &ticket5) == 0);

	// Free TicketMaster
	freeTicketMaster(&ticketMaster);
}
void calcDailyTest() {
	TicketMaster ticketMaster;
	initTicketMaster(&ticketMaster);

	// Create some tickets
	Ticket* ticket1 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket2 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket3 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket4 = (Ticket*)malloc(sizeof(Ticket));

	Date date1, date2, date3;
	initDate(&date1, 1, 1, 2025);
	initDate(&date2, 2, 1, 2025);
	initDate(&date3, 3, 1, 2025);

	initTicket(ticket1, eChild, date3);
	initTicket(ticket2, eAdult, date1);
	initTicket(ticket3, eStudent, date2);
	initTicket(ticket4, eSoldier, date2);

	// Add tickets to the ticket master
	assert(addTicket(&ticketMaster, ticket1) == 1);
	assert(addTicket(&ticketMaster, ticket2) == 1);
	assert(addTicket(&ticketMaster, ticket3) == 1);
	assert(addTicket(&ticketMaster, ticket4) == 1);


	// Test 1: Calculate daily income for date1
	double daily1 = calcDaily(&ticketMaster, &date1);
	assert(daily1 == BASE_TICKET_PRICE * Discount[1]);
	// Test 2: Calculate daily income for date2
	double daily2 = calcDaily(&ticketMaster, &date2);
	assert(daily2 == BASE_TICKET_PRICE * Discount[2] + BASE_TICKET_PRICE * Discount[3]);

	// Test 3: Calculate daily income for date3
	double daily3 = calcDaily(&ticketMaster, &date3);
	assert(daily3 == BASE_TICKET_PRICE * Discount[0]);

	freeTicketMaster(&ticketMaster);
}
void sortTicketsByIDTest() {
	TicketMaster ticketMaster;
	initTicketMaster(&ticketMaster);

	// Create some tickets

	Ticket* ticket1 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket2 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket3 = (Ticket*)malloc(sizeof(Ticket));

	Date date;
	initDate(&date, 1, 1, 2025);

	// Initialize tickets with different IDs
	initTicket(ticket1, eChild, date);
	initTicket(ticket2, eAdult, date);
	initTicket(ticket3, eStudent, date);

	// Manually set IDs to ensure they are different
	strcpy(ticket1->id, "AAAAAAAAAAA3");
	strcpy(ticket2->id, "AAAAAAAAAAA1");
	strcpy(ticket3->id, "AAAAAAAAAAA2");


	// Add tickets to the ticket master
	assert(addTicket(&ticketMaster, ticket1) == 1);
	assert(addTicket(&ticketMaster, ticket2) == 1);
	assert(addTicket(&ticketMaster, ticket3) == 1);
	// Sort tickets by ID
	sortTicketsByID(&ticketMaster);

	// Check that the tickets are sorted in ascending order by ID
	assert(strcmp(ticketMaster.tickets[0]->id, "AAAAAAAAAAA1") == 0);
	assert(strcmp(ticketMaster.tickets[1]->id, "AAAAAAAAAAA2") == 0);
	assert(strcmp(ticketMaster.tickets[2]->id, "AAAAAAAAAAA3") == 0);

	freeTicketMaster(&ticketMaster);
}
void sortTicketsByDateTest() {
	TicketMaster ticketMaster;
	initTicketMaster(&ticketMaster);

	// Create some tickets
	Ticket* ticket1 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket2 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket3 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket4 = (Ticket*)malloc(sizeof(Ticket));

	// Initialize tickets with different dates
	Date date1, date2, date3, date4;
	initDate(&date1, 1, 1, 2025);
	initDate(&date2, 2, 1, 2025);
	initDate(&date3, 3, 1, 2025);
	initDate(&date4, 4, 1, 2025);

	initTicket(ticket1, eChild, date3);
	initTicket(ticket2, eAdult, date1);
	initTicket(ticket3, eStudent, date4);
	initTicket(ticket4, eSoldier, date2);

	// Add tickets to the ticket master
	assert(addTicket(&ticketMaster, ticket1) == 1);
	assert(addTicket(&ticketMaster, ticket2) == 1);
	assert(addTicket(&ticketMaster, ticket3) == 1);
	assert(addTicket(&ticketMaster, ticket4) == 1);
	// Sort tickets by date
	sortTicketsByDate(&ticketMaster);



	freeTicketMaster(&ticketMaster);
}
void sortTicketsByGuestTypeTest() {
	TicketMaster ticketMaster;
	initTicketMaster(&ticketMaster);

	// Create some tickets
	Ticket* ticket1 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket2 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket3 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket4 = (Ticket*)malloc(sizeof(Ticket));

	// Initialize tickets with different guest types
	Date date;
	initDate(&date, 1, 1, 2025);
	initTicket(ticket1, eChild, date);
	initTicket(ticket2, eAdult, date);
	initTicket(ticket3, eStudent, date);
	initTicket(ticket4, eSoldier, date);

	// Add tickets to the ticket master
	assert(addTicket(&ticketMaster, ticket1) == 1);
	assert(addTicket(&ticketMaster, ticket2) == 1);
	assert(addTicket(&ticketMaster, ticket3) == 1);
	assert(addTicket(&ticketMaster, ticket4) == 1);
	// Sort tickets by guest type
	sortTicketsByGuestType(&ticketMaster);

	// Check that the tickets are sorted in ascending order by guest type
	assert(ticketMaster.tickets[0]->guestType == eChild);
	assert(ticketMaster.tickets[1]->guestType == eAdult);
	assert(ticketMaster.tickets[2]->guestType == eStudent);
	assert(ticketMaster.tickets[3]->guestType == eSoldier);

	freeTicketMaster(&ticketMaster);
}
void sortTicketsUserTestManual() {
	printf("Sort Ticket Manual Test\n");

	TicketMaster ticketMaster;
	initTicketMaster(&ticketMaster);
	Ticket ticket1, ticket2, ticket3;
	Date date1 = { 1, 1, 2024 };
	Date date2 = { 2, 2, 2024 };
	Date date3 = { 3, 3, 2024 };
	initTicket(&ticket1, eAdult, date1);
	initTicket(&ticket2, eChild, date2);
	initTicket(&ticket3, eSoldier, date3);
	addTicket(&ticketMaster, &ticket1);
	addTicket(&ticketMaster, &ticket2);
	addTicket(&ticketMaster, &ticket3);
	printTicketMaster(&ticketMaster);
	double daily1 = calcDaily(&ticketMaster, &date1);
	double daily2 = calcDaily(&ticketMaster, &date2);
	double daily3 = calcDaily(&ticketMaster, &date3);
	printDailyIncome(&ticketMaster, &date1);
	printDailyIncome(&ticketMaster, &date2);
	printDailyIncome(&ticketMaster, &date3);


	for (int i = 0; i < 5; i++)
	{
		sortTicketsUser(&ticketMaster);
		printTicketMaster(&ticketMaster);
	}


	freeTicketMaster(&ticketMaster);
}
void buyTicketTestManual() {
	printf("Buy Ticket Manual Test\n");

	Ticket* ticket;
	TicketMaster ticketMaster;
	initTicketMaster(&ticketMaster);

	for (int i = 0; i < 3; i++)
	{
		ticket = buyTicket(&ticketMaster);
		printf("----- Ticket Master After Buy Ticket -----\n");
		printTicketMaster(&ticketMaster);
		printf("----- Ticket Bought -----\n");
		printTicket(ticket);
	}

	freeTicketMaster(&ticketMaster);
}
void findTicketByUserTestManual() {
	printf("Find Ticket By User Manual Test\n");

	TicketMaster ticketMaster;
	initTicketMaster(&ticketMaster);

	Ticket* ticket1 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket2 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket3 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket4 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket5 = (Ticket*)malloc(sizeof(Ticket));

	Date date1, date2, date3, date4, date5;
	initDate(&date1, 1, 1, 2025);
	initDate(&date2, 2, 1, 2025);
	initDate(&date3, 3, 1, 2025);
	initDate(&date4, 4, 1, 2025);
	initDate(&date5, 5, 1, 2025);

	initTicket(ticket1, eChild, date1);
	initTicket(ticket2, eAdult, date2);
	initTicket(ticket3, eStudent, date3);
	initTicket(ticket4, eStudent, date4);
	initTicket(ticket5, eAdult, date5);

	addTicket(&ticketMaster, ticket1);
	addTicket(&ticketMaster, ticket2);
	addTicket(&ticketMaster, ticket3);
	addTicket(&ticketMaster, ticket4);
	addTicket(&ticketMaster, ticket5);

	printTicketMaster(&ticketMaster);
	// Find tickets by user
	for (int i = 0; i < 4; i++)
	{
		sortTicketsUser(&ticketMaster);
		printTicketMaster(&ticketMaster);
		Ticket* foundTicket1 = findTicketByUser(&ticketMaster);

		if (foundTicket1 != NULL)
		{
			printf("----- Ticket Found return pointer tests -----\n");
			printTicket(foundTicket1);
		}
		else
		{
			printf("----- Ticket Not Found -----\n");
		}
	}

	freeTicketMaster(&ticketMaster);

}
void findTicketByIDTest() {
	TicketMaster ticketMaster;
	initTicketMaster(&ticketMaster);

	Ticket* ticket1 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket2 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket3 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket4 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket5 = (Ticket*)malloc(sizeof(Ticket));

	Date date1, date2, date3, date4, date5;
	initDate(&date1, 1, 1, 2025);
	initDate(&date2, 2, 1, 2025);
	initDate(&date3, 3, 1, 2025);
	initDate(&date4, 4, 1, 2025);
	initDate(&date5, 5, 1, 2025);

	initTicket(ticket1, eChild, date1);
	initTicket(ticket2, eAdult, date2);
	initTicket(ticket3, eStudent, date3);
	initTicket(ticket4, eStudent, date4);
	initTicket(ticket5, eAdult, date5);

	addTicket(&ticketMaster, ticket1);
	addTicket(&ticketMaster, ticket2);
	addTicket(&ticketMaster, ticket3);
	addTicket(&ticketMaster, ticket4);
	addTicket(&ticketMaster, ticket5);

	// Test 1: Find ticket by ID
	Ticket* foundTicket1 = findTicketByID(&ticketMaster, ticket1->id);
	assert(compareTicketsByID(&foundTicket1, &ticket1) == 0);
	assert(foundTicket1 == ticket1);
	assert(foundTicket1->price == ticket1->price);

	// Test 2: Find ticket by ID
	Ticket* foundTicket2 = findTicketByID(&ticketMaster, ticket2->id);
	assert(compareTicketsByID(&foundTicket2, &ticket2) == 0);
	assert(foundTicket2 == ticket2);
	assert(foundTicket2->price == ticket2->price);

	// Test 3: Find ticket by ID
	Ticket* foundTicket3 = findTicketByID(&ticketMaster, ticket3->id);
	assert(compareTicketsByID(&foundTicket3, &ticket3) == 0);
	assert(foundTicket3 == ticket3);
	assert(foundTicket3->price == ticket3->price);

	// Test 4: Find ticket by ID
	Ticket* foundTicket4 = findTicketByID(&ticketMaster, ticket4->id);
	assert(compareTicketsByID(&foundTicket4, &ticket4) == 0);
	assert(foundTicket4 == ticket4);
	assert(foundTicket4->price == ticket4->price);


	// Test 5: Find ticket by ID
	Ticket* foundTicket5 = findTicketByID(&ticketMaster, ticket5->id);
	assert(compareTicketsByID(&foundTicket5, &ticket5) == 0);
	assert(foundTicket5 == ticket5);
	assert(foundTicket5->price == ticket5->price);


	// get invalid ticket
	Ticket* foundTicket6 = findTicketByID(&ticketMaster, "AAAAAAAAAAA6");
	assert(foundTicket6 == NULL);


	// free
	freeTicketMaster(&ticketMaster);
}
// initializes By User Manuals Tests
void initByUserManualsTest() {
	//initDateByUserManualsTest();
	//initWeatherByUserManualsTest();
	//initTimeByUserManualsTest();
	//initShopByUserManualsTest();
	//initTicketByUserManualsTest();
}
void initWeatherByUserManualsTest() {
	printf("Init weather Manual Test\n");

	for (int i = 0; i < 5; i++)
	{
		Weather weather;
		initWeatherByUser(&weather);
		printWeather(&weather);
	}
}
void initDateByUserManualsTest() {
	printf("Init Date Manual Test\n");
	for (int i = 0; i < 5; i++)
	{
		Date date;
		initDateByUser(&date);
		printDate(&date);
		printf("\n");
	}
}
void initTimeByUserManualsTest() {
	printf("Init Time Manual Test\n");
	for (int i = 0; i < 5; i++)
	{
		Time time;
		initTimeByUser(&time);
		printTime(&time);
		printf("\n");
	}
}
void initShopByUserManualsTest() {
	printf("Init Shop Manual Test\n");
	for (int i = 0; i < 3; i++)
	{
		Shop shop;
		initShopByUser(&shop);
		printShop(&shop);
		printf("\n");
		freeShop(&shop);
	}
}
void initTicketByUserManualsTest() {
	printf("Init Ticket Manual Test\n");
	for (int i = 0; i < 5; i++)
	{
		Ticket ticket;
		initTicketByUser(&ticket);
		printTicket(&ticket);
		printf("\n");
	}
}
// General library Tests
void generalLibaryTests() {
	//generalArrayFunctionTest();
}
void printIntArray(const void* element) {
	const int temp = *(int*)element;
	printf("[%d], ", temp);
}
void generalArrayFunctionTest() {
	int arr[] = { 1, 2, 3, 4, 5 };
	int size = sizeof(arr) / sizeof(arr[0]);
	generalArrayFunction((void*)arr, size, sizeof(int), (void*)printIntArray);
}
// Save and Load tests
void SaveAndLoadTests() {
	WeatherSaveAndLoadTextTest();
	WeatherSaveAndLoadBinTest();
	TimeSaveAndLoadTextTest();
	TimeSaveAndLoadBinTest();
	ShopSaveAndLoadTextTest();
	ShopSaveAndLoadBinTest();
	DateSaveAndLoadTextText();
	DateSaveAndLoadBinTest();
	TicketSaveAndLoadTextTest();
	TicketSaveAndLoadBinTest();
	TicketMasterSaveAndLoadTextTest();
	TicketMasterSaveAndLoadBinTest();
}
void WeatherSaveAndLoadTextTest() {
	const char* fileName = "AAAWeatherTest.txt";
	Weather weather1;

	// Test 1: Save and load a valid weather
	initWeather(&weather1, eSunny, 20);
	FILE* file = fopen(fileName, "w");

	assert(saveWeatherToTextFile(&weather1, file) == 1);
	fclose(file);

	// Load the weather from the file
	Weather weather2;
	file = fopen(fileName, "r");
	assert(loadWeatherFromTextFile(&weather2, file) == 1);
	fclose(file);

	// Check that the loaded weather is the same as the saved weather
	assert(compareWeatherByTemp(&weather1, &weather2) == 0);

}
void WeatherSaveAndLoadBinTest() {
	const char* fileName = "AAAWeatherTest.bin";
	Weather weather1;

	// Test 1: Save and load a valid weather
	initWeather(&weather1, eSunny, 20);
	FILE* file = fopen(fileName, "wb");

	assert(saveWeatherToBinFile(&weather1, file) == 1);
	fclose(file);

	// Load the weather from the file
	Weather weather2;
	file = fopen(fileName, "rb");
	assert(loadWeatherFromBinFile(&weather2, file) == 1);
	fclose(file);

	// Check that the loaded weather is the same as the saved weather
	assert(compareWeatherByTemp(&weather1, &weather2) == 0);

}
void TimeSaveAndLoadTextTest() {
	Time time1;
	const char* fileName = "AAATimeTest.txt";

	// Test 1: Save and load a valid time
	initTime(&time1, 8, 0);
	FILE* file = fopen(fileName, "w");

	assert(saveTimeToTextFile(&time1, file) == 1);
	fclose(file);

	// Load the time from the file
	Time time2;
	file = fopen(fileName, "r");
	assert(loadTimeFromTextFile(&time2, file) == 1);
	fclose(file);

	// Check that the loaded time is the same as the saved time
	assert(compareTime(&time1, &time2) == 0);
}
void TimeSaveAndLoadBinTest() {
	Time time1;
	const char* fileName = "AAATimeTest.bin";

	// Test 1: Save and load a valid time
	initTime(&time1, 8, 0);
	FILE* file = fopen(fileName, "wb");

	assert(saveTimeToBinFile(&time1, file) == 1);
	fclose(file);

	// Load the time from the file
	Time time2;
	file = fopen(fileName, "rb");
	assert(loadTimeFromBinFile(&time2, file) == 1);
	fclose(file);

	// Check that the loaded time is the same as the saved time
	assert(compareTime(&time1, &time2) == 0);
	assert(time1.hour == time2.hour);
	assert(time1.minute == time2.minute);
}
void ShopSaveAndLoadTextTest() {
	Shop shop1;
	const char* fileName = "AAAShopTest.txt";

	// Test 1: Save and load a valid shop
	Time openHour;
	initTime(&openHour, 8, 0);
	Time closeHour;
	initTime(&closeHour, 20, 0);
	initShop(&shop1, "Shop1", eRestaurant, openHour, closeHour, 0);
	FILE* file = fopen(fileName, "w");

	assert(saveShopToTextFile(&shop1, file) == 1);

	fclose(file);

	// Load the shop from the file
	Shop shop2;
	file = fopen(fileName, "r");
	assert(loadShopFromTextFile(&shop2, file) == 1);
	fclose(file);

	assert(strcmp(shop1.name, shop2.name) == 0);
	assert(shop1.type == shop2.type);
	assert(compareTime(&shop1.openHour, &shop2.openHour) == 0);
	assert(compareTime(&shop1.closeHour, &shop2.closeHour) == 0);
	freeShop(&shop1);
	freeShop(&shop2);
	// save dynamic memory allocation
	Shop shop3;
	char* name = (char*)malloc(6 * sizeof(char));
	strcpy(name, "Shop3");
	initShop(&shop3, name, eRestaurant, openHour, closeHour, 1);
	file = fopen(fileName, "w");
	assert(saveShopToTextFile(&shop3, file) == 1);
	fclose(file);

	// Load the shop from the file
	Shop shop4;
	file = fopen(fileName, "r");
	assert(loadShopFromTextFile(&shop4, file) == 1);
	fclose(file);

	assert(strcmp(shop3.name, shop4.name) == 0);
	assert(shop3.type == shop4.type);
	assert(compareTime(&shop3.openHour, &shop4.openHour) == 0);
	assert(compareTime(&shop3.closeHour, &shop4.closeHour) == 0);

	freeShop(&shop3);
	freeShop(&shop4);
}
void ShopSaveAndLoadBinTest() {
	Shop shop1;
	const char* fileName = "AAAShopTest.bin";

	// Test 1: Save and load a valid shop
	Time openHour;
	initTime(&openHour, 8, 0);
	Time closeHour;
	initTime(&closeHour, 20, 0);
	initShop(&shop1, "Shop1", eRestaurant, openHour, closeHour, 0);
	FILE* file = fopen(fileName, "wb");

	assert(saveShopToBinFile(&shop1, file) == 1);

	fclose(file);

	// Load the shop from the file
	Shop shop2;
	file = fopen(fileName, "rb");
	assert(loadShopFromBinFile(&shop2, file) == 1);
	fclose(file);

	assert(strcmp(shop1.name, shop2.name) == 0);
	assert(shop1.type == shop2.type);
	assert(compareTime(&shop1.openHour, &shop2.openHour) == 0);
	assert(compareTime(&shop1.closeHour, &shop2.closeHour) == 0);
	freeShop(&shop1);
	freeShop(&shop2);
	// save dynamic memory allocation
	Shop shop3;
	char* name = (char*)malloc(6 * sizeof(char));
	strcpy(name, "Shop3");
	initShop(&shop3, name, eRestaurant, openHour, closeHour, 1);
	file = fopen(fileName, "wb");
	assert(saveShopToBinFile(&shop3, file) == 1);
	fclose(file);

	// Load the shop from the file
	Shop shop4;
	file = fopen(fileName, "rb");
	assert(loadShopFromBinFile(&shop4, file) == 1);
	fclose(file);

	assert(strcmp(shop3.name, shop4.name) == 0);
	assert(shop3.type == shop4.type);
	assert(compareTime(&shop3.openHour, &shop4.openHour) == 0);
	assert(compareTime(&shop3.closeHour, &shop4.closeHour) == 0);
	freeShop(&shop3);
	freeShop(&shop4);
}
void DateSaveAndLoadTextText() {
	Date date1;
	const char* fileName = "AAADateTest.txt";

	// Test 1: Save and load a valid date
	initDate(&date1, 1, 1, 2025);
	FILE* file = fopen(fileName, "w");

	assert(saveDateToTextFile(&date1, file) == 1);
	fclose(file);

	// Load the date from the file
	Date date2;
	file = fopen(fileName, "r");
	assert(loadDateFromTextFile(&date2, file) == 1);
	fclose(file);

	// Check that the loaded date is the same as the saved date
	assert(compareDates(date1, date2) == 0);
	assert(date1.day == date2.day);
	assert(date1.month == date2.month);
	assert(date1.year == date2.year);
}
void DateSaveAndLoadBinTest() {
	Date date1;
	const char* fileName = "AAADateTest.bin";

	// Test 1: Save and load a valid date
	initDate(&date1, 1, 1, 2025);
	FILE* file = fopen(fileName, "wb");

	assert(saveDateToBinFile(&date1, file) == 1);
	fclose(file);

	// Load the date from the file
	Date date2;
	file = fopen(fileName, "rb");
	assert(loadDateFromBinFile(&date2, file) == 1);
	fclose(file);

	// Check that the loaded date is the same as the saved date
	assert(compareDates(date1, date2) == 0);
	assert(date1.day == date2.day);
	assert(date1.month == date2.month);
	assert(date1.year == date2.year);

}
void TicketSaveAndLoadTextTest() {
	Ticket ticket1;
	const char* fileName = "AAATicketTest.txt";

	// Test 1: Save and load a valid ticket
	Date date;
	initDate(&date, 1, 1, 2025);
	initTicket(&ticket1, eAdult, date);
	FILE* file = fopen(fileName, "w");

	assert(saveTicketToTextFile(&ticket1, file) == 1);
	fclose(file);

	// Load the ticket from the file
	Ticket ticket2;
	file = fopen(fileName, "r");
	assert(loadTicketFromTextFile(&ticket2, file) == 1);
	fclose(file);

	// Check that the loaded ticket is the same as the saved ticket
	assert(strcmp(ticket1.id, ticket2.id) == 0);
	assert(ticket1.guestType == ticket2.guestType);
	assert(compareDates(ticket1.dateOfVisit, ticket2.dateOfVisit) == 0);
	assert(ticket1.price == ticket2.price);
}
void TicketSaveAndLoadBinTest() {
	Ticket ticket1;
	const char* fileName = "AAATicketTest.bin";

	// Test 1: Save and load a valid ticket
	Date date;
	initDate(&date, 1, 1, 2025);
	initTicket(&ticket1, eChild, date);
	strcpy(ticket1.id, "AAAAAAAAAAA1");
	FILE* file = fopen(fileName, "wb");

	assert(saveTicketToBinFile(&ticket1, file) == 1);
	fclose(file);

	// Load the ticket from the file
	Ticket ticket2;
	file = fopen(fileName, "rb");
	assert(loadTicketFromBinFile(&ticket2, file) == 1);
	fclose(file);

	// Check that the loaded ticket is the same as the saved ticket
	assert(strcmp(ticket1.id, ticket2.id) == 0);
	assert(ticket1.guestType == ticket2.guestType);
	assert(compareDates(ticket1.dateOfVisit, ticket2.dateOfVisit) == 0);
	assert(ticket1.price == ticket2.price);
}
void TicketMasterSaveAndLoadTextTest() {
	TicketMaster ticketMaster;
	initTicketMaster(&ticketMaster);
	const char* fileName = "AAATicketMasterTest.txt";

	// Create some tickets
	Ticket* ticket1 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket2 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket3 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket4 = (Ticket*)malloc(sizeof(Ticket));

	Date date;
	initDate(&date, 1, 1, 2025);

	// Initialize tickets with different IDs
	initTicket(ticket1, eChild, date);
	initTicket(ticket2, eAdult, date);
	initTicket(ticket3, eStudent, date);
	initTicket(ticket4, eSoldier, date);

	// Manually set IDs to ensure they are different
	strcpy(ticket1->id, "AAAAAAAAAAA1");
	strcpy(ticket2->id, "AAAAAAAAAAA2");
	strcpy(ticket3->id, "AAAAAAAAAAA3");
	strcpy(ticket4->id, "AAAAAAAAAAA4");

	// Add tickets to the ticket master
	assert(addTicket(&ticketMaster, ticket1) == 1);
	assert(addTicket(&ticketMaster, ticket2) == 1);
	assert(addTicket(&ticketMaster, ticket3) == 1);
	assert(addTicket(&ticketMaster, ticket4) == 1);

	FILE* file = fopen(fileName, "w");
	assert(saveTicketMasterToTextFile(&ticketMaster, file) == 1);
	fclose(file);

	// Load the ticket master from the file
	TicketMaster ticketMaster2;
	initTicketMaster(&ticketMaster2);
	file = fopen(fileName, "r");
	assert(loadTicketMasterFromTextFile(&ticketMaster2, file) == 1);
	fclose(file);

	// Check that the loaded ticket master is the same as the saved ticket master
	assert(ticketMaster.numOfTickets == ticketMaster2.numOfTickets);
	// compare by id
	assert(compareTicketsByID(&ticketMaster.tickets[0], &ticketMaster2.tickets[0]) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[1], &ticketMaster2.tickets[1]) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[2], &ticketMaster2.tickets[2]) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[3], &ticketMaster2.tickets[3]) == 0);

	// compare by date
	assert(compareTicketsByDate(&ticketMaster.tickets[0], &ticketMaster2.tickets[0]) == 0);
	assert(compareTicketsByDate(&ticketMaster.tickets[1], &ticketMaster2.tickets[1]) == 0);
	assert(compareTicketsByDate(&ticketMaster.tickets[2], &ticketMaster2.tickets[2]) == 0);
	assert(compareTicketsByDate(&ticketMaster.tickets[3], &ticketMaster2.tickets[3]) == 0);

	// compare by guest type
	assert(compareTicketsByGuestType(&ticketMaster.tickets[0], &ticketMaster2.tickets[0]) == 0);
	assert(compareTicketsByGuestType(&ticketMaster.tickets[1], &ticketMaster2.tickets[1]) == 0);
	assert(compareTicketsByGuestType(&ticketMaster.tickets[2], &ticketMaster2.tickets[2]) == 0);
	assert(compareTicketsByGuestType(&ticketMaster.tickets[3], &ticketMaster2.tickets[3]) == 0);


	// compare by price
	assert(ticketMaster.tickets[0]->price == ticketMaster2.tickets[0]->price);
	assert(ticketMaster.tickets[1]->price == ticketMaster2.tickets[1]->price);
	assert(ticketMaster.tickets[2]->price == ticketMaster2.tickets[2]->price);
	assert(ticketMaster.tickets[3]->price == ticketMaster2.tickets[3]->price);

	// free
	freeTicketMaster(&ticketMaster);
	freeTicketMaster(&ticketMaster2);



}
void TicketMasterSaveAndLoadBinTest() {
	TicketMaster ticketMaster;
	initTicketMaster(&ticketMaster);
	const char* fileName = "AAATicketMasterTest.bin";

	// Create some tickets
	Ticket* ticket1 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket2 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket3 = (Ticket*)malloc(sizeof(Ticket));
	Ticket* ticket4 = (Ticket*)malloc(sizeof(Ticket));

	Date date;
	initDate(&date, 1, 1, 2025);

	// Initialize tickets with different IDs
	initTicket(ticket1, eChild, date);
	initTicket(ticket2, eAdult, date);
	initTicket(ticket3, eStudent, date);
	initTicket(ticket4, eSoldier, date);

	// Manually set IDs to ensure they are different
	strcpy(ticket1->id, "AAAAAAAAAAA1");
	strcpy(ticket2->id, "AAAAAAAAAAA2");
	strcpy(ticket3->id, "AAAAAAAAAAA3");
	strcpy(ticket4->id, "AAAAAAAAAAA4");

	// Add tickets to the ticket master
	assert(addTicket(&ticketMaster, ticket1) == 1);
	assert(addTicket(&ticketMaster, ticket2) == 1);
	assert(addTicket(&ticketMaster, ticket3) == 1);
	assert(addTicket(&ticketMaster, ticket4) == 1);

	FILE* file = fopen(fileName, "wb");
	assert(saveTicketMasterToBinFile(&ticketMaster, file) == 1);
	fclose(file);

	// Load the ticket master from the file
	TicketMaster ticketMaster2;
	initTicketMaster(&ticketMaster2);
	file = fopen(fileName, "rb");
	assert(loadTicketMasterFromBinFile(&ticketMaster2, file) == 1);
	fclose(file);

	// Check that the loaded ticket master is the same as the saved ticket master
	assert(ticketMaster.numOfTickets == ticketMaster2.numOfTickets);
	// compare by id
	assert(compareTicketsByID(&ticketMaster.tickets[0], &ticketMaster2.tickets[0]) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[1], &ticketMaster2.tickets[1]) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[2], &ticketMaster2.tickets[2]) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[3], &ticketMaster2.tickets[3]) == 0);

	// compare by date
	assert(compareTicketsByDate(&ticketMaster.tickets[0], &ticketMaster2.tickets[0]) == 0);
	assert(compareTicketsByDate(&ticketMaster.tickets[1], &ticketMaster2.tickets[1]) == 0);
	assert(compareTicketsByDate(&ticketMaster.tickets[2], &ticketMaster2.tickets[2]) == 0);
	assert(compareTicketsByDate(&ticketMaster.tickets[3], &ticketMaster2.tickets[3]) == 0);

	// compare by guest type
	assert(compareTicketsByGuestType(&ticketMaster.tickets[0], &ticketMaster2.tickets[0]) == 0);
	assert(compareTicketsByGuestType(&ticketMaster.tickets[1], &ticketMaster2.tickets[1]) == 0);
	assert(compareTicketsByGuestType(&ticketMaster.tickets[2], &ticketMaster2.tickets[2]) == 0);
	assert(compareTicketsByGuestType(&ticketMaster.tickets[3], &ticketMaster2.tickets[3]) == 0);

	// compare by price
	assert(ticketMaster.tickets[0]->price == ticketMaster2.tickets[0]->price);
	assert(ticketMaster.tickets[1]->price == ticketMaster2.tickets[1]->price);
	assert(ticketMaster.tickets[2]->price == ticketMaster2.tickets[2]->price);
	assert(ticketMaster.tickets[3]->price == ticketMaster2.tickets[3]->price);

	// free
	freeTicketMaster(&ticketMaster);
	freeTicketMaster(&ticketMaster2);
}
// LunaPark tests
void LunaParkTests() {
	initLunaParkTest();
	addFacilityToLunaParkTest();
	addShopToLunaParkTest();
}
void initLunaParkTest() {
	LunaPark lunaPark;
	char* name = (char*)malloc(19 * sizeof(char));
	strcpy(name, "ShaiAndDanielPark");

	initLunaPark(&lunaPark, name);
	assert(lunaPark.numOfShops == 0);
	assert(lunaPark.openTime.hour == DEFALUT_OPEN_HOUR);
	assert(lunaPark.openTime.minute == DEFALUT_OPEN_MINUTE);
	assert(lunaPark.closeTime.hour == DEFALUT_CLOSE_HOUR);
	assert(lunaPark.closeTime.minute == DEFALUT_CLOSE_MINUTE);
	assert(strcmp(lunaPark.name, name) == 0);
	assert(lunaPark.weather.condition == DEFALUT_WEATHER);
	assert(lunaPark.weather.temp == DEFALUT_TEMPERATURE);
	assert(lunaPark.numOfWorkers == 0);
	freeLunaPark(&lunaPark);

}
void addFacilityToLunaParkTest() {
	LunaPark lunaPark;
	char* name = (char*)malloc(18 * sizeof(char));
	strcpy(name, "ShaiAndDanielPark");

	initLunaPark(&lunaPark, name);

	Facility* facility1 = (Facility*)malloc(sizeof(Facility));
	Facility* facility2 = (Facility*)malloc(sizeof(Facility));
	Facility* facility3 = (Facility*)malloc(sizeof(Facility));
	Facility* facility4 = (Facility*)malloc(sizeof(Facility));

	// create names for facilities
	char* name1 = (char*)malloc(5 * sizeof(char));
	strcpy(name1, "fOne");
	char* name2 = (char*)malloc(5 * sizeof(char));
	strcpy(name2, "fTwo");
	char* name3 = (char*)malloc(7 * sizeof(char));
	strcpy(name3, "fThree");
	char* name4 = (char*)malloc(6 * sizeof(char));
	strcpy(name4, "fFour");

	// init facilities
	initFacility(facility1, name1, 1, 70, eAdultFacility);
	initFacility(facility2, name2, 2, 80, eChildrenFacility);
	initFacility(facility3, name3, 3, 90, eExtremeFacility);
	initFacility(facility4, name4, 4, 100, eSuper_ExtremesFacility);

	// add facilities to luna park
	assert(addFacilityToLunaPark(&lunaPark, facility1) == 1);
	assert(addFacilityToLunaPark(&lunaPark, facility2) == 1);
	assert(addFacilityToLunaPark(&lunaPark, facility3) == 1);
	assert(addFacilityToLunaPark(&lunaPark, facility4) == 1);

	// check that the facilities were added
	int facilityCount = L_count(&lunaPark.facilities);
	assert(facilityCount == 4);

	// check that the facilities are the same
	NODE* node = lunaPark.facilities.head.next;
	assert(node->key == facility4);
	node = node->next;
	assert(node->key == facility3);
	node = node->next;
	assert(node->key == facility2);
	node = node->next;
	assert(node->key == facility1);

	freeLunaPark(&lunaPark);
}
void addShopToLunaParkTest() {
	LunaPark lunaPark;
	Shop shop1, shop2, shop3, shop4;
	char* name = (char*)malloc(18 * sizeof(char));
	strcpy(name, "ShaiAndDanielPark");

	assert(initLunaPark(&lunaPark, name) == 1);

	Time openHour;
	initTime(&openHour, 8, 0);
	Time closeHour;
	initTime(&closeHour, 20, 0);

	initShop(&shop1, "Shop1", eRestaurant, openHour, closeHour, 0);
	initShop(&shop2, "Shop2", eRestaurant, openHour, closeHour, 0);
	initShop(&shop3, "Shop3", eRestaurant, openHour, closeHour, 0);

	char* shopfourName = (char*)malloc(6 * sizeof(char));
	strcpy(shopfourName, "Shop4");
	initShop(&shop4, shopfourName, eRestaurant, openHour, closeHour, 1);

	// add shops to luna park
	assert(addShopToLunaPark(&lunaPark, shop1) == 1);
	assert(addShopToLunaPark(&lunaPark, shop2) == 1);
	assert(addShopToLunaPark(&lunaPark, shop3) == 1);
	assert(addShopToLunaPark(&lunaPark, shop4) == 1);

	assert(lunaPark.numOfShops == 4);

	// check the added shops 
	assert(strcmp(lunaPark.shops[0].name, "Shop1") == 0);
	assert(lunaPark.shops[0].type == eRestaurant);
	assert(compareTime(&lunaPark.shops[0].openHour, &openHour) == 0);
	assert(compareTime(&lunaPark.shops[0].closeHour, &closeHour) == 0);

	assert(strcmp(lunaPark.shops[1].name, "Shop2") == 0);
	assert(lunaPark.shops[1].type == eRestaurant);
	assert(compareTime(&lunaPark.shops[1].openHour, &openHour) == 0);
	assert(compareTime(&lunaPark.shops[1].closeHour, &closeHour) == 0);

	assert(strcmp(lunaPark.shops[2].name, "Shop3") == 0);
	assert(lunaPark.shops[2].type == eRestaurant);
	assert(compareTime(&lunaPark.shops[2].openHour, &openHour) == 0);
	assert(compareTime(&lunaPark.shops[2].closeHour, &closeHour) == 0);

	assert(strcmp(lunaPark.shops[3].name, "Shop4") == 0);
	assert(lunaPark.shops[3].type == eRestaurant);
	assert(compareTime(&lunaPark.shops[3].openHour, &openHour) == 0);
	assert(compareTime(&lunaPark.shops[3].closeHour, &closeHour) == 0);

	freeLunaPark(&lunaPark);
}

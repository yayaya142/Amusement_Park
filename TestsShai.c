#include "TestsShai.h"
#include "Date.h"
#include "Weather.h"
#include "Time.h"
#include "Shop.h"
#include "Ticket.h"
#include "TicketMaster.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// runAllTests
// Aim:	this function runs all tests, by default all the tests run automatically. manual tests will be marked as "Manual"
// Input:	none
// Output:	if failed, the function assert failed will pop up a message, otherwise, a message that all tests passed will be printed
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void runAllTestsShai() {
	DateTests();
	WeatherTest();
	TimeTests();
	ShopTests();
	TicketTests();
	TicketMasterTests();
	//initByUserManualsTest(); // Manual



	printf("All tests passed\n");
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
	assert(isValidWeather(eSunny, 20.0) == 1);

	// Test 2: Invalid weather condition (low)
	assert(isValidWeather(-1, 20.0) == 0);

	// Test 3: Invalid weather condition (high)
	assert(isValidWeather(eNofWeatherTypes, 20.0) == 0);

	// Test 4: Temperature out of range (low)
	assert(isValidWeather(eRainy, MIN_TEMP - 1) == 0);

	// Test 5: Temperature out of range (high)
	assert(isValidWeather(eCloudy, MAX_TEMP + 1) == 0);

	// Test 6: Valid weather with minimum temperature
	assert(isValidWeather(eSunny, MIN_TEMP) == 1);

	// Test 7: Valid weather with maximum temperature
	assert(isValidWeather(eRainy, MAX_TEMP) == 1);

	// Test 8: Valid weather with negative temperature
	assert(isValidWeather(eCloudy, -10.0) == 1);

}
void compareWeatherByTempTest() {
	Weather weather1, weather2;

	// Test 1: Equal temperatures
	initWeather(&weather1, eSunny, 20.0);
	initWeather(&weather2, eRainy, 20.0);
	assert(compareWeatherByTemp(&weather1, &weather2) == 0);

	// Test 2: weather1 has lower temperature
	initWeather(&weather1, eSunny, 15.0);
	initWeather(&weather2, eRainy, 20.0);
	assert(compareWeatherByTemp(&weather1, &weather2) < 0);

	// Test 3: weather1 has higher temperature
	initWeather(&weather1, eSunny, 25.0);
	initWeather(&weather2, eRainy, 20.0);
	assert(compareWeatherByTemp(&weather1, &weather2) > 0);

	// Test 4: weather1 has a temperature of 0 and weather2 has a positive temperature
	initWeather(&weather1, eSunny, 0.0);
	initWeather(&weather2, eRainy, 20.0);
	assert(compareWeatherByTemp(&weather1, &weather2) < 0);

	// Test 5: weather1 has a temperature of 0 and weather2 has a negative temperature
	initWeather(&weather1, eSunny, 0.0);
	initWeather(&weather2, eRainy, -10);
	assert(compareWeatherByTemp(&weather1, &weather2) > 0);

	// Test 6: Both weather1 and weather2 have a temperature of 0
	initWeather(&weather1, eSunny, 0.0);
	initWeather(&weather2, eRainy, 0.0);
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
	Ticket ticket1, ticket2;

	// Test 1: Equal IDs
	initTicket(&ticket1, eAdult, (Date) { 1, 1, 2025 });
	initTicket(&ticket2, eAdult, (Date) { 1, 1, 2025 });
	strcpy(ticket1.id, "T2754FC32SW");
	strcpy(ticket2.id, "T2754FC32SW");
	assert(compareTicketsByID(&ticket1, &ticket2) == 0);

	// Test 2: ticket1's ID is less than ticket2's ID
	strcpy(ticket1.id, "T2754FC32SA");
	strcpy(ticket2.id, "T2754FC32SB");
	assert(compareTicketsByID(&ticket1, &ticket2) < 0);

	// Test 3: ticket1's ID is greater than ticket2's ID
	strcpy(ticket1.id, "T2754FC32SC");
	strcpy(ticket2.id, "T2754FC32SB");
	assert(compareTicketsByID(&ticket1, &ticket2) > 0);

	// Test 4: ticket1's ID and ticket2's ID only differ by case
	strcpy(ticket1.id, "T2754FC32SC");
	strcpy(ticket2.id, "t2754FC32SC");
	assert(compareTicketsByID(&ticket1, &ticket2) != 0);
}
void compareTicketsByDateTest() {
	Ticket ticket1, ticket2;

	// Test 1: Equal dates
	initTicket(&ticket1, eAdult, (Date) { 1, 1, 2025 });
	initTicket(&ticket2, eAdult, (Date) { 1, 1, 2025 });
	assert(compareTicketsByDate(&ticket1, &ticket2) == 0);

	// Test 2: ticket1's date is earlier than ticket2's date
	initTicket(&ticket1, eAdult, (Date) { 1, 1, 2025 });
	initTicket(&ticket2, eAdult, (Date) { 2, 1, 2025 });
	assert(compareTicketsByDate(&ticket1, &ticket2) < 0);

	// Test 3: ticket1's date is later than ticket2's date
	initTicket(&ticket1, eAdult, (Date) { 2, 1, 2025 });
	initTicket(&ticket2, eAdult, (Date) { 1, 1, 2025 });
	assert(compareTicketsByDate(&ticket1, &ticket2) > 0);

	// Test 4: ticket1's date is in a different month than ticket2's date
	initTicket(&ticket1, eAdult, (Date) { 1, 2, 2025 });
	initTicket(&ticket2, eAdult, (Date) { 1, 1, 2025 });
	assert(compareTicketsByDate(&ticket1, &ticket2) > 0);

	// Test 5: ticket1's date is in a different year than ticket2's date
	initTicket(&ticket1, eAdult, (Date) { 1, 1, 2026 });
	initTicket(&ticket2, eAdult, (Date) { 1, 1, 2025 });
	assert(compareTicketsByDate(&ticket1, &ticket2) > 0);
}
void compareTicketsByGuestTypeTest() {
	Ticket ticket1, ticket2;

	// Test 1: Equal guest types
	initTicket(&ticket1, eAdult, (Date) { 1, 1, 2025 });
	initTicket(&ticket2, eAdult, (Date) { 1, 1, 2025 });
	assert(compareTicketsByGuestType(&ticket1, &ticket2) == 0);

	// Test 2: ticket1's guest type is less than ticket2's guest type
	initTicket(&ticket1, eChild, (Date) { 1, 1, 2025 });
	initTicket(&ticket2, eAdult, (Date) { 1, 1, 2025 });
	assert(compareTicketsByGuestType(&ticket1, &ticket2) < 0);

	// Test 3: ticket1's guest type is greater than ticket2's guest type
	initTicket(&ticket1, eStudent, (Date) { 1, 1, 2025 });
	initTicket(&ticket2, eAdult, (Date) { 1, 1, 2025 });
	assert(compareTicketsByGuestType(&ticket1, &ticket2) > 0);

	// Test 4: ticket1's guest type is less than ticket2's guest type
	initTicket(&ticket1, eChild, (Date) { 1, 1, 2025 });
	initTicket(&ticket2, eSoldier, (Date) { 1, 1, 2025 });
	assert(compareTicketsByGuestType(&ticket1, &ticket2) < 0);

	// Test 5: ticket1's guest type is greater than ticket2's guest type
	initTicket(&ticket1, eSoldier, (Date) { 1, 1, 2025 });
	initTicket(&ticket2, eAdult, (Date) { 1, 1, 2025 });
	assert(compareTicketsByGuestType(&ticket1, &ticket2) > 0);

	// Test 6: Equal guest types
	initTicket(&ticket1, eSoldier, (Date) { 1, 1, 2025 });
	initTicket(&ticket2, eSoldier, (Date) { 1, 1, 2025 });
	assert(compareTicketsByGuestType(&ticket1, &ticket2) == 0);
}
// TicketMaster tests
void TicketMasterTests() {
	initTicketMasterTest();
	addTicketTest();
	calcDailyTest();
	sortTicketsByIDTest();
	sortTicketsByDateTest();
	sortTicketsByGuestTypeTest();
	//sortTicketsUserTestManual(); // manual test off by default
	buyTicketTestManual(); // manual test off by default
}
void initTicketMasterTest() {
	TicketMaster ticketMaster;
	// Test
	initTicketMaster(&ticketMaster);
	assert(ticketMaster.tickets == NULL && ticketMaster.numOfTickets == 0);
}
void addTicketTest() {
	TicketMaster ticketMaster;
	Ticket ticket;
	Date validDate;
	initDate(&validDate, 1, 1, 2025);
	initTicket(&ticket, eAdult, validDate);
	initTicketMaster(&ticketMaster);

	// Test 1: Add a ticket to an empty ticket master
	assert(addTicket(&ticketMaster, &ticket) == 1);
	assert(ticketMaster.numOfTickets == 1);
	assert(compareTicketsByID(&ticketMaster.tickets[0], &ticket) == 0);

	// Test 2: Add a ticket to a ticket master with one ticket
	Ticket ticket2;
	initTicket(&ticket2, eChild, validDate);
	assert(addTicket(&ticketMaster, &ticket2) == 1);
	assert(ticketMaster.numOfTickets == 2);
	assert(compareTicketsByID(&ticketMaster.tickets[0], &ticket) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[1], &ticket2) == 0);

	// Test 3: Add a ticket to a ticket master with multiple tickets
	Ticket ticket3;
	initTicket(&ticket3, eStudent, validDate);
	assert(addTicket(&ticketMaster, &ticket3) == 1);
	assert(ticketMaster.numOfTickets == 3);
	assert(compareTicketsByID(&ticketMaster.tickets[0], &ticket) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[1], &ticket2) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[2], &ticket3) == 0);

	// Test 4: Add a ticket with an invalid date
	Date invalidDate;
	Ticket ticket4;
	initDate(&invalidDate, 32, 1, 2025);
	initTicket(&ticket4, eAdult, invalidDate);
	assert(addTicket(&ticketMaster, &ticket4) == 0);
	assert(ticketMaster.numOfTickets == 3);

	// Test 5: Add a ticket with an invalid guest type
	Ticket ticket5;
	initTicket(&ticket5, eNofTicketTypes, validDate);
	assert(addTicket(&ticketMaster, &ticket5) == 0);
	assert(ticketMaster.numOfTickets == 3);

	// Test 6: Add a ticket with a NULL pointer
	assert(addTicket(&ticketMaster, NULL) == 0);
	assert(ticketMaster.numOfTickets == 3);

	// Test 7 : valid ticket
	Ticket ticket6;
	initTicket(&ticket6, eAdult, validDate);
	assert(addTicket(&ticketMaster, &ticket6) == 1);
	assert(ticketMaster.numOfTickets == 4);
	assert(compareTicketsByID(&ticketMaster.tickets[0], &ticket) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[1], &ticket2) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[2], &ticket3) == 0);
	assert(compareTicketsByID(&ticketMaster.tickets[3], &ticket6) == 0);

	// Free TicketMaster
	freeTicketMaster(&ticketMaster);
}
void calcDailyTest() {
	TicketMaster ticketMaster;
	initTicketMaster(&ticketMaster);

	// Create some tickets
	Ticket ticket1, ticket2, ticket3, ticket4, ticket5, ticket6;
	Date date1, date2;
	initDate(&date1, 1, 1, 2025);
	initDate(&date2, 2, 1, 2025);

	// Initialize tickets with different guest types and dates
	initTicket(&ticket1, eChild, date1);
	initTicket(&ticket2, eAdult, date1);
	initTicket(&ticket3, eStudent, date1);
	initTicket(&ticket4, eSoldier, date1);
	initTicket(&ticket5, eChild, date2);
	initTicket(&ticket6, eAdult, date2);

	// Add tickets to the ticket master
	assert(addTicket(&ticketMaster, &ticket1) == 1);
	assert(addTicket(&ticketMaster, &ticket2) == 1);
	assert(addTicket(&ticketMaster, &ticket3) == 1);
	assert(addTicket(&ticketMaster, &ticket4) == 1);
	assert(addTicket(&ticketMaster, &ticket5) == 1);
	assert(addTicket(&ticketMaster, &ticket6) == 1);

	// Calculate daily total for date1
	double total1 = calcDaily(&ticketMaster, &date1);
	assert(total1 == (BASE_TICKET_PRICE * Discount[eChild] + BASE_TICKET_PRICE * Discount[eAdult] + BASE_TICKET_PRICE * Discount[eStudent] + BASE_TICKET_PRICE * Discount[eSoldier]));
	// Calculate daily total for date2
	double total2 = calcDaily(&ticketMaster, &date2);
	assert(total2 == (BASE_TICKET_PRICE * Discount[eChild] + BASE_TICKET_PRICE * Discount[eAdult]));

	freeTicketMaster(&ticketMaster);
}
void sortTicketsByIDTest() {
	TicketMaster ticketMaster;
	initTicketMaster(&ticketMaster);

	// Create some tickets
	Ticket ticket1, ticket2, ticket3;
	Date date;
	initDate(&date, 1, 1, 2025);

	// Initialize tickets with different IDs
	initTicket(&ticket1, eChild, date);
	initTicket(&ticket2, eAdult, date);
	initTicket(&ticket3, eStudent, date);

	// Manually set IDs to ensure they are different
	strcpy(ticket1.id, "AAAAAAAAAAA3");
	strcpy(ticket2.id, "AAAAAAAAAAA1");
	strcpy(ticket3.id, "AAAAAAAAAAA2");


	// Add tickets to the ticket master
	assert(addTicket(&ticketMaster, &ticket1) == 1);
	assert(addTicket(&ticketMaster, &ticket2) == 1);
	assert(addTicket(&ticketMaster, &ticket3) == 1);

	// Sort tickets by ID
	sortTicketsByID(&ticketMaster);

	// Check that the tickets are sorted in ascending order by ID
	assert(strcmp(ticketMaster.tickets[0].id, "AAAAAAAAAAA1") == 0);
	assert(strcmp(ticketMaster.tickets[1].id, "AAAAAAAAAAA2") == 0);
	assert(strcmp(ticketMaster.tickets[2].id, "AAAAAAAAAAA3") == 0);

	freeTicketMaster(&ticketMaster);
}
void sortTicketsByDateTest() {
	TicketMaster ticketMaster;
	initTicketMaster(&ticketMaster);

	// Create some tickets
	Ticket ticket1, ticket2, ticket3;
	Date date1, date2, date3;
	initDate(&date1, 1, 1, 2025);
	initDate(&date2, 2, 1, 2025);
	initDate(&date3, 3, 1, 2025);

	// Initialize tickets with different dates
	initTicket(&ticket1, eChild, date3);
	initTicket(&ticket2, eAdult, date1);
	initTicket(&ticket3, eStudent, date2);

	// Add tickets to the ticket master
	assert(addTicket(&ticketMaster, &ticket1) == 1);
	assert(addTicket(&ticketMaster, &ticket2) == 1);
	assert(addTicket(&ticketMaster, &ticket3) == 1);

	// Sort tickets by date
	sortTicketsByDate(&ticketMaster);

	// Check that the tickets are sorted in ascending order by date
	assert(compareDates(ticketMaster.tickets[0].dateOfVisit, date1) == 0);
	assert(compareDates(ticketMaster.tickets[1].dateOfVisit, date2) == 0);
	assert(compareDates(ticketMaster.tickets[2].dateOfVisit, date3) == 0);

	freeTicketMaster(&ticketMaster);
}
void sortTicketsByGuestTypeTest() {
	TicketMaster ticketMaster;
	initTicketMaster(&ticketMaster);

	// Create some tickets
	Ticket ticket1, ticket2, ticket3;
	Date date;
	initDate(&date, 1, 1, 2025);

	// Initialize tickets with different guest types
	initTicket(&ticket3, eStudent, date);
	initTicket(&ticket2, eAdult, date);
	initTicket(&ticket1, eChild, date);

	// Add tickets to the ticket master
	assert(addTicket(&ticketMaster, &ticket3) == 1);
	assert(addTicket(&ticketMaster, &ticket2) == 1);
	assert(addTicket(&ticketMaster, &ticket1) == 1);

	// Sort tickets by guest type
	sortTicketsByGuestType(&ticketMaster);

	// Check that the tickets are sorted in ascending order by guest type
	assert(ticketMaster.tickets[0].guestType == eChild);
	assert(ticketMaster.tickets[1].guestType == eAdult);
	assert(ticketMaster.tickets[2].guestType == eStudent);

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

	ticket = buyTicket(&ticketMaster);
	printf("----- Ticket Master After Buy Ticket -----\n");
	printTicketMaster(&ticketMaster);
	printf("----- Ticket Bought -----\n");
	printTicket(ticket);
	freeTicketMaster(&ticketMaster);






}
// initializes By User Manuals Tests
void initByUserManualsTest() {
	initDateByUserManualsTest();
	initWeatherByUserManualsTest();
	initTimeByUserManualsTest();
	initShopByUserManualsTest();
	initTicketByUserManualsTest();
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

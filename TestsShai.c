#include "TestsShai.h"
#include "Date.h"
#include "Weather.h"

//////////////////////////////////////////
// runAllTests
// Aim:	this function runs all tests, by default all the tests run automatically. manual tests will be marked as "Manual"
// Input:	none
// Output:	if failed, the function assert failed will pop up a message, otherwise, a message that all tests passed will be printed
//////////////////////////////////////////
void runAllTestsShai() {
	DateTests();
	WeatherTest();








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
	assert(initWeather(&weather, 0, -25) == 1);
	assert(weather.condition == eSunny && weather.temp == -25);

	// Test 5: Valid weather with maximum temperature
	assert(initWeather(&weather, 1, 50) == 1);
	assert(weather.condition == eRainy && weather.temp == 50);

	// Test 6: Valid weather with minimum temperature
	assert(initWeather(&weather, eSunny, -50) == 1);
	assert(weather.condition == eSunny && weather.temp == -50);

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
	initWeather(&weather2, eRainy, -20.0);
	assert(compareWeatherByTemp(&weather1, &weather2) > 0);

	// Test 6: Both weather1 and weather2 have a temperature of 0
	initWeather(&weather1, eSunny, 0.0);
	initWeather(&weather2, eRainy, 0.0);
	assert(compareWeatherByTemp(&weather1, &weather2) == 0);
}

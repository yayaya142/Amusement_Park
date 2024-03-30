#ifndef __TESTS_SHAI__
#define __TESTS_SHAI__

#include <crtdbg.h> // TODO: remove before release
#include <assert.h>
#include <stdio.h>



void runAllTestsShai();

// Date tests
void DateTests();
void initDateTest();
void isDateValidTest();
void compareDatesTest();
// Weather Tests
void WeatherTest();
void initWeatherTest();
void isValidWeatherTest();
void compareWeatherByTempTest();

#endif 
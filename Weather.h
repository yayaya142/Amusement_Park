#ifndef __WEATHER__
#define __WEATHER__

#include <crtdbg.h> // TODO: remove before release
#include <stdio.h>
#define MAX_TEMP 50
#define MIN_TEMP -50

typedef enum {
	eSunny, eRainy, eCloudy, eStorm, eNofWeatherTypes
} eWeatherType;

static const char* WeatherTypeStr[eNofWeatherTypes] = { "Sunny", "Rainy", "Cloudy", "Storm" };


typedef struct {
	eWeatherType condition;
	float temp;
} Weather;

int initWeather(Weather* weather, eWeatherType condition, float temp);
int isValidWeather(eWeatherType condition, float temp);
void printWeather(const Weather* weather);
int compareWeatherByTemp(const Weather* weather1, const Weather* weather2);
void createWeatherByUser(Weather* weather);



#endif 
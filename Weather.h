#ifndef __WEATHER__
#define __WEATHER__

#include <crtdbg.h> // TODO: remove before release
#include <stdio.h>
#include "fileHelper.h"
#define MAX_TEMP 50
#define MIN_TEMP -10
#define DEFUALT_WEATHER_SYMBOL "C" // String becuase some symbols are more than one char

typedef enum {
	eSunny, eRainy, eCloudy, eStorm, eNofWeatherTypes
} eWeatherType;

static const char* WeatherTypeStr[eNofWeatherTypes] = { "Sunny", "Rainy", "Cloudy", "Storm" };


typedef struct {
	eWeatherType condition;
	int temp;
} Weather;

int initWeather(Weather* weather, eWeatherType condition, int temp);
int isValidWeather(eWeatherType condition, int temp);
void printWeather(const Weather* weather);
int compareWeatherByTemp(const Weather* weather1, const Weather* weather2);
void initWeatherByUser(Weather* weather);
void printWeatherForcastTemp(int temp);
// save and load functions
int saveWeatherToTextFile(const Weather* weather, FILE* fp);
int loadWeatherFromTextFile(Weather* weather, FILE* fp);
int saveWeatherToBinFile(const Weather* weather, FILE* fp);
int loadWeatherFromBinFile(Weather* weather, FILE* fp);


#endif 
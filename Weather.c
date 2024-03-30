#include "Weather.h"



int initWeather(Weather* weather, eWeatherType condition, float temp) {
	if (!isValidWeather(condition, temp)) {
		return 0;
	}
	weather->condition = condition;
	weather->temp = temp;
	return 1;
}

int isValidWeather(eWeatherType condition, float temp) {
	if (temp < MIN_TEMP || temp > MAX_TEMP) {
		return 0;
	}
	if (condition < 0 || condition >= eNofWeatherTypes) {
		return 0;
	}
	return 1;
}


void printWeather(const Weather* weather) {
	if (isValidWeather(weather->condition, weather->temp) == 0) {
		printf("Invalid weather\n");
		return;
	}
	printf("Weather condition: %s, Temperature: %.2f\n", WeatherTypeStr[weather->condition], weather->temp);
}
int compareWeatherByTemp(const Weather* weather1, const Weather* weather2) {
	return (int)(weather1->temp - weather2->temp);
}

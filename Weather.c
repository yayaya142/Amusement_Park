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

void createWeatherByUser(Weather* weather) {
	int flag = 0;
	int condition;
	float temp;
	do
	{
		if (flag > 0) {
			printf("Invalid weather try again\n");
		}
		printf("Enter weather condition\n");
		for (int i = 0; i < eNofWeatherTypes; i++) {
			printf("%d. %s\n", i, WeatherTypeStr[i]);
		}
		scanf("%d", &condition);
		printf("Enter temperature");
		scanf("%f", &temp);
		flag++;

	} while (!initWeather(weather, condition, temp));
}


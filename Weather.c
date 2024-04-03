#include "Weather.h"



int initWeather(Weather* weather, eWeatherType condition, int temp) {
	if (!isValidWeather(condition, temp)) {
		return 0;
	}
	weather->condition = condition;
	weather->temp = temp;
	return 1;
}

int isValidWeather(eWeatherType condition, int temp) {
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
	printf("Weather condition: %s, Temperature: %d%s\n", WeatherTypeStr[weather->condition], weather->temp, DEFUALT_WEATHER_SYMBOL);
}
int compareWeatherByTemp(const Weather* weather1, const Weather* weather2) {
	return (weather1->temp - weather2->temp);
}

void initWeatherByUser(Weather* weather) {
	int flag = 0;
	int condition;
	int temp;
	do
	{
		if (flag > 0) {
			printf("Invalid weather try again\n");
		}
		printf("Enter weather condition\n");
		for (int i = 0; i < eNofWeatherTypes; i++) {
			printf("%d. %s\n", i + 1, WeatherTypeStr[i]);
		}
		scanf("%d", &condition);
		printf("Enter temperature");
		scanf("%d", &temp);
		flag = 1;
	} while (!initWeather(weather, condition - 1, temp));
}

// ---- save functions ----
int saveWeatherToTextFile(const Weather* weather, FILE* fp) {
	IS_FILE_NULL(fp);


	if (weather == NULL || isValidWeather(weather->condition, weather->temp) == 0) {
		return 0;
	}

	if (writeIntToTextFile(fp, weather->condition) == 0) {
		return 0;
	}

	if (writeIntToTextFile(fp, weather->temp) == 0) {
		return 0;
	}

	return 1;
}

int loadWeatherFromTextFile(Weather* weather, FILE* fp) {
	IS_FILE_NULL(fp);


	int condition;
	int temp;

	if (readIntFromTextFile(fp, &condition) == 0) {
		return 0;
	}

	if (readIntFromTextFile(fp, &temp) == 0) {
		return 0;
	}

	if (initWeather(weather, condition, temp) == 0) {
		return 0;
	}

	return 1;
}
int saveWeatherToBinFile(const Weather* weather, FILE* fp) {
	IS_FILE_NULL(fp);


	if (weather == NULL || isValidWeather(weather->condition, weather->temp) == 0) {
		return 0;
	}

	if (writeGeneralToBinFile(fp, weather, sizeof(Weather)) == 0) {
		return 0;
	}

	return 1;

}
int loadWeatherFromBinFile(Weather* weather, FILE* fp) {
	IS_FILE_NULL(fp);


	if (readGeneralFromBinFile(fp, weather, sizeof(Weather)) == 0) {
		return 0;
	}

	return 1;



}

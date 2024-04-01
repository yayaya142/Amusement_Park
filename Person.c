#include "Person.h"
#include "General.h"
#define MAX_HEIGHT 300
#define MAX_AGE 120

int initPerson(Person *p, char* name, float height, int age) {
	if(!isValidInfo(name , height, age)){
		return 0;
	}
	p->name = name;
	p->height = height;
	p->age = age;
	return 1;

}

void initPersonByUser(Person *p) {
	int flag = 0;
	char* name = NULL;
	int age;
	float height;
	do {
		if (flag > 0) {
			printf("Please try again\n");
			free(name);
		}
		name = getStrExactName("Enter name :\n");
		
		printf("Enter age:\n");
		scanf("%d", &age);

		printf("Enter height:\n");
		scanf("%f", &height);
		flag++;
	} while (!initPerson(p, name, height, age));

}

int isValidInfo(char* name, float height, int age) { 
	if (!validName(name)) {
		printf("Invalid name\n");
		return 0;
	}
	if (height <= 0 || height >MAX_HEIGHT) {
		printf("Height valid only between 0 and %d\n", MAX_HEIGHT);
		return 0;
	}
	if (age <= 0 || age > MAX_AGE) {
		printf("Age valid only between 0 and %d\n", MAX_AGE);
		return 0;
	}
	return 1;
}

int comparePersonByHeight(const Person* p1, const Person* p2) {
	if (p1->height == p2->height) {
		return 0;
	}
	return (int)(p1->height - p2->height);
}


void printPerson(const Person* p) {
	if (p == NULL) {
		printf("Person is NULL\n");
		return;
	}
	else {
		printf("Name: %s\n", p->name);
		printf("Age: %d\n", p->age);
		printf("Height: %.2f\n", p->height);
	}
}

void freePerson(Person* p) {
	if (p->name != NULL) {
		free(p->name);
	}
}
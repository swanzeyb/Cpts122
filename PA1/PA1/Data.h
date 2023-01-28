#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#pragma warning(disable : 4996)
#define CHAR_LIMIT 500

typedef enum {
	NONE = 0,
	ASLEEP = 1,
	AWAKE = 2,
	REALLYAWAKE = 3,
} Sleep;

typedef struct {
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
} Fitbit;

typedef enum {
	PATIENT = 0,
	MINUTE = 1,
	CALORIES = 2,
	DISTANCE = 3,
	FLOORS = 4,
	HEART_RATE = 5,
	STEPS = 6,
	SLEEP_LEVEL = 7,
} Members;

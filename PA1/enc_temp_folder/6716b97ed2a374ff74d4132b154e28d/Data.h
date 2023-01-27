#pragma once

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
	char key[CHAR_LIMIT];
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
} Fitbit;

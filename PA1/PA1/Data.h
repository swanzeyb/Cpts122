#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#pragma warning(disable : 4996)
#define CHAR_LIMIT 500
#define ROWS_LIMIT 1440

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

// You must compute the total calories burned
double totalCaloriesBurned(Fitbit* logs[]);

// distance walked in miles,
double totalDistanceWalked(Fitbit* logs[]);

// floors walked
unsigned int totalFloorsClimbed(Fitbit* logs[]);

// and steps taken
unsigned int totalStepsTaken(Fitbit* logs[]);

// You must compute average heartrate over the 24 hour period
unsigned int averageHeartRate(Fitbit* logs[]);

// You must report the max steps taken in one minute over the 24 hour
unsigned int maxStepsInMinute(Fitbit* logs[]);

// You must report the longest consecutive range of poor sleep (report the starting and ending minute of range)
typedef struct {
	char* start;
	char* end;
	int length;
	unsigned int quality;
} Range;

Range longestPoorSleepRange(Fitbit* logs[]);

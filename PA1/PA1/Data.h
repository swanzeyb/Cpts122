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
double totalCaloriesBurned(Fitbit* logs[ROWS_LIMIT]);

// distance walked in miles,
double totalDistanceWalked(Fitbit* logs[ROWS_LIMIT]);

// floors walked
unsigned int totalFloorsClimbed(Fitbit* logs[ROWS_LIMIT]);

// and steps taken
unsigned int totalStepsTaken(Fitbit* logs[ROWS_LIMIT]);

// You must compute average heartrate over the 24 hour period
double averageHeartRate(Fitbit* logs[ROWS_LIMIT]);

// You must report the max steps taken in one minute over the 24 hour
unsigned int maxStepsInMinute(Fitbit* logs[ROWS_LIMIT]);

// You must report the longest consecutive range of poor sleep (report the starting and ending minute of range)
typedef struct {
	char* start;
	char* end;
	int length;
	unsigned int quality;
} Range;

Range longestPoorSleepRange(Fitbit* logs[ROWS_LIMIT]);

// Print the results csv file
typedef struct {
	double totalCalories;
	double totalDistance;
	unsigned int totalFloors;
	unsigned int totalSteps;
	double avgHeartRate;
	unsigned int maxSteps;
	Range poorSleepRange;
} Results;

void writeResultsCSV(Results results, Fitbit* logs[ROWS_LIMIT]);

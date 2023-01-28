
#include "Data.h"

// You must compute the total calories burned
double totalCaloriesBurned(Fitbit* logs[]) {
	double total = 0;
	for (int i = 0; i < ROWS_LIMIT; i++) {
		total += logs[i]->calories;
	}
	return total;
}

// distance walked in miles,
double totalDistanceWalked(Fitbit* logs[]) {
	double total = 0;
	for (int i = 0; i < ROWS_LIMIT; i++) {
		total += logs[i]->distance;
	}
	return total;
}

// floors walked
unsigned int totalFloorsClimbed(Fitbit* logs[]) {
	unsigned int total = 0;
	for (int i = 0; i < ROWS_LIMIT; i++) {
		total += logs[i]->floors;
	}
	return total;
}

// and steps taken
unsigned int totalStepsTaken(Fitbit* logs[]) {
	unsigned int total = 0;
	for (int i = 0; i < ROWS_LIMIT; i++) {
		total += logs[i]->steps;
	}
	return total;
}

// You must compute average heartrate over the 24 hour period
unsigned int averageHeartRate(Fitbit* logs[]) {
	double average = logs[0]->heartRate;
	for (int i = 1; i < ROWS_LIMIT; i++) {
		average = (average + logs[i]->heartRate) / 2;
	}
	return average;
}

// You must report the max steps taken in one minute over the 24 hour
unsigned int maxStepsInMinute(Fitbit* logs[]) {
	unsigned int max = 0;
	for (int i = 0; i < ROWS_LIMIT; i++) {
		if (logs[i]->steps > max) {
			max = logs[i]->steps;
		}
	}
	return max;
}

// You must report the longest consecutive range of poor sleep (report the starting and ending minute of range)
Range longestPoorSleepRange(Fitbit* logs[]) {
	Range poor = { "\0", "\0", 0 };
	Range temp = { "\0", "\0", 0 };
	bool inRange = false;

	for (int i = 0; i < ROWS_LIMIT; i++) {
		Sleep level = logs[i]->sleepLevel;
		char* minute = logs[i]->minute;

		if (level > NONE) {
			if (!inRange) {
				temp.start = minute;
				inRange = true;
			}

			temp.length += 1;
			temp.quality += level;
		}
		else {
			if (inRange) {
				temp.end = minute;
				inRange = false;

				if (poor.end == '\0' && poor.start == '\0') {
					poor.start = temp.start;
					poor.end = temp.end;
					poor.length = temp.length;
					poor.quality = temp.quality;
				}

				if (temp.quality > poor.quality) {
					poor.start = temp.start;
					poor.end = temp.end;
					poor.length = temp.length;
					poor.quality = temp.quality;
				}
				else if ((temp.quality == poor.quality) && (temp.length > poor.quality)) {
					poor.start = temp.start;
					poor.end = temp.end;
					poor.length = temp.length;
					poor.quality = temp.quality;
				}
			}
		}
	}

	return poor;
}

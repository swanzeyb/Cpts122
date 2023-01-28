
#include "Data.h"

// You must compute the total calories burned
double totalCaloriesBurned(Fitbit* logs[ROWS_LIMIT]) {
	double total = 0.0;
	for (int i = 0; i < ROWS_LIMIT; i++) {
		total += logs[i]->calories;
	}
	return total;
}

// distance walked in miles,
double totalDistanceWalked(Fitbit* logs[ROWS_LIMIT]) {
	double total = 0.0;
	for (int i = 0; i < ROWS_LIMIT; i++) {
		total += logs[i]->distance;
	}
	return total;
}

// floors walked
unsigned int totalFloorsClimbed(Fitbit* logs[ROWS_LIMIT]) {
	unsigned int total = 0;
	for (int i = 0; i < ROWS_LIMIT; i++) {
		total += logs[i]->floors;
	}
	return total;
}

// and steps taken
unsigned int totalStepsTaken(Fitbit* logs[ROWS_LIMIT]) {
	unsigned int total = 0;
	for (int i = 0; i < ROWS_LIMIT; i++) {
		total += logs[i]->steps;
	}
	return total;
}

// You must compute average heartrate over the 24 hour period
double averageHeartRate(Fitbit* logs[ROWS_LIMIT]) {
	double sumHeartRate = 0.0;
	for (int i = 1; i < ROWS_LIMIT; i++) {
		sumHeartRate += logs[i]->heartRate;
	}
	double avg = sumHeartRate / ROWS_LIMIT;
	return avg;
}

// You must report the max steps taken in one minute over the 24 hour
unsigned int maxStepsInMinute(Fitbit* logs[ROWS_LIMIT]) {
	unsigned int max = 0;
	for (int i = 0; i < ROWS_LIMIT; i++) {
		if (logs[i]->steps > max) {
			max = logs[i]->steps;
		}
	}
	return max;
}

// You must report the longest consecutive range of poor sleep (report the starting and ending minute of range)
Range longestPoorSleepRange(Fitbit* logs[ROWS_LIMIT]) {
	Range poor = { "\0", "\0", 0 };
	Range temp = { "\0", "\0", 0 };
	bool inRange = false;

	for (int i = 0; i < ROWS_LIMIT; i++) {
		Sleep level = logs[i]->sleepLevel;
		char* minute = logs[i]->minute;

		if (level > ASLEEP) {
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

void writeResultsCSV(Results results, Fitbit* logs[ROWS_LIMIT]) {
	FILE* csvFile = fopen("Results.csv", "w");

	// Header columns
	fprintf(csvFile, "Total Calories, Total Distance, Total Floors, Total Steps, Avg Heartrate, Max Steps, Sleep\n");
	
	// Calculation results
	fprintf(csvFile, "%lf, %lf, %u, %u, %lf, %u, %s:%s\n",
		results.totalCalories,
		results.totalDistance,
		results.totalFloors,
		results.totalSteps,
		results.avgHeartRate,
		results.maxSteps,
		results.poorSleepRange.start,
		results.poorSleepRange.end
	);

	// Clean data
	fprintf(csvFile, "Patient, Minute, Calories, Distance, Floors, Heart, Steps, Sleep Level\n");

	for (int i = 0; i < ROWS_LIMIT; i++) {
		fprintf(csvFile, "%s, %s, %lf, %lf, %d, %d, %d, %d\n",
			logs[i]->patient,
			logs[i]->minute,
			logs[i]->calories,
			logs[i]->distance,
			logs[i]->floors,
			logs[i]->heartRate,
			logs[i]->steps,
			logs[i]->sleepLevel
		);
	}

	fclose(csvFile);
}

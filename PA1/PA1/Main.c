
#include "Data.h"
const char* TARGET = "12cx7";

int main(void) {

	// Open the Fitbit data file
	FILE* contents = fopen("FitbitData.csv", "r");

	// Check if file opened without error
	if (contents == NULL) {
		return 1;
	}

	// Holds the current line
	char line[CHAR_LIMIT];

	// The current col value
	char* token = NULL;

	// Count what col we've gotten to
	int colIndex = 0;

	// Count what row we've gotten to
	int rowIndex = 0;

	// All of the found records
	Fitbit* logs[ROWS_LIMIT];

	// Log index to keep track of record position
	int logIndex = 0;

	do {
		// Get each line of the CSV file
		fgets(line, CHAR_LIMIT, contents);

		// Remove the trailing new line
		strtok(line, "\n");

		// Try to tokenize line
		token = strtok(line, ", ");

		// Reset the col index because new line
		colIndex = 0;

		// Ignore meta info rows and wrong patients
		if (rowIndex > 1 && strstr(line, TARGET) != NULL) {
			// Start of a new data point entry
			Fitbit* point = (Fitbit*)malloc(sizeof(Fitbit));

			// While we're not at the end of the line
			while (token != NULL || colIndex < 8) {

				// Fill in missing data
				switch (colIndex) {
					case PATIENT:
						strcpy(point->patient, token);
						break;
					case MINUTE:
						strcpy(point->minute, token == NULL ? "" : token);
						break;
					case CALORIES:
						point->calories = token == NULL ? 0 : atoi(token);
						break;
					case DISTANCE:
						point->distance = token == NULL ? 0 : atoi(token);
						break;
					case FLOORS:
						point->floors = token == NULL ? 0.0 : strtoul(token, NULL, 10);
						break;
					case HEART_RATE:
						point->heartRate = token == NULL ? 0.0 : strtoul(token, NULL, 10);
						break;
					case STEPS:
						point->steps = token == NULL ? 0.0 : strtoul(token, NULL, 10);
						break;
					case SLEEP_LEVEL:
						point->sleepLevel = token == NULL ? 0 : atoi(token);
						break;
				}

				// Split by comma and whitespace for the next iteration
				token = strtok(NULL, ", ");
				colIndex += 1;
			}

			if (logIndex > 0) {
				// Only add the point if it's not a duplicate
				if (logs[logIndex - 1]->minute != point->minute) {
					// Add the new point to the collection
					logs[logIndex] = point;
					logIndex += 1;
				}
			}
		}

		rowIndex += 1;
	} while (!feof(contents) && logIndex < ROWS_LIMIT);

	double totalCalories = totalCaloriesBurned(logs);
	double totalDistance = totalDistanceWalked(logs);
	unsigned int totalFloors = totalFloorsClimbed(logs);
	unsigned int totalSteps = totalFloorsClimbed(logs);
	unsigned int avgHeartRate = averageHeartRate(logs);
	unsigned int maxSteps = maxStepsInMinute(logs);
	Range poorSleepRange = longestPoorSleepRange(logs);

	return 0;
}


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
	Fitbit* logs[1440];

	do {
		// Get each line of the CSV file
		fgets(line, CHAR_LIMIT, contents);

		// Remove the trailing new line
		strtok(line, "\n");

		// Try to tokenize line
		token = strtok(line, ", ");

		// Reset the col index because new line
		colIndex = 0;

		// Ignore meta info rows
		if (rowIndex > 1) {
			// Start of a new data point entry
			Fitbit* point = (Fitbit*)malloc(sizeof(Fitbit));

			// While we're not at the end of the line
			while (token != NULL || colIndex < 8) {
				printf("%s\n", token);

				// Fill in missing data
				switch (colIndex) {
					case PATIENT:
						if (strstr(token, TARGET) == NULL) break;
						strcpy(point->patient, token);
						break;
					case MINUTE:
						strcpy(point->minute, token);
						break;
					case CALORIES:
						point->calories = atoi(token);
						break;
					case DISTANCE:
						point->distance = atoi(token);
						break;
					case FLOORS:
						point->floors = strtoul(token);
						break;
					case HEART_RATE:
						point->heartRate = strtoul(token);
						break;
					case STEPS:
						point->steps = strtoul(token);
						break;
					case SLEEP_LEVEL:
						point->sleepLevel = atoi(token);
						break;
				}

				// Split by comma and whitespace for the next iteration
				token = strtok(NULL, ", ");
				colIndex += 1;
			}

			// Add the new point to the collection
			logs[rowIndex - 2] = point;
		}

		rowIndex += 1;
	} while (!feof(contents) && rowIndex < 1443);

	for (int i = 0; i < 1440; i++) {
		printf("%s\n", logs[i]->minute);
	}

	return 0;
}
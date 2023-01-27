
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
	Fitbit logs[1440];

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
			// While we're not at the end of the line
			while (token != NULL) {
				printf("%s\n", token);

				// Split by comma and whitespace for the next iteration
				token = strtok(NULL, ", ");
				colIndex += 1;
			}

			// Fill in missing data
		}

		rowIndex += 1;
	} while (!feof(contents) && rowIndex < 1443);

	return 0;
}

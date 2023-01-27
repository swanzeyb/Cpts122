
#define _CRT_SECURE_NO_WARNINGS

#include "Data.h"

const int CHAR_LIMIT = 100;
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

	// Instead of an array, I'm using a hash table because
	// the time complexity of look up is generally O(1)
	// and this speeds up checking for duplicates.
	Fitbit *data = NULL;

	do {
		// Get each line of the CSV file
		fgets(line, CHAR_LIMIT, contents);

		// Look at each col of the CSV file

		printf("%s", line);
	} while (!feof(contents));

	return 0;
}

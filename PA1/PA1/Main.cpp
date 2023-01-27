
#define _CRT_SECURE_NO_WARNINGS

#include "Data.h"

const int CHAR_LIMIT = 100;

int main(void) {

	FILE* contents = fopen("FitbitData.csv", "r");

	char line[CHAR_LIMIT];

	do {
		fgets(line, CHAR_LIMIT, contents);
		printf("%s", line);
	} while (!feof(contents));

	return 0;
}

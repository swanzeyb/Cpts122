
#include "DMM.h"

// I use nullish coalesing in JavaScript, it's bugging me
// C doesn't have this built in.
char nullCoalesce(char* payload) {
	return payload == NULL ? '\0' : *payload;
}

// Strtok causes the load function it lose it's place
Duration parseDuration(char* token) {
	Duration dur = { 0, 0 };

	char min[CHAR_LIMIT] = "\0";
	char sec[CHAR_LIMIT] = "\0";

	// This works because pointer math in C is based on offsets.
	// strchr returns a pointer to the first occurnce of a char.
	// Since we're dealing with two variables of the same type,
	// subtracting token from the pointer of the colon occurence
	// will return the index position of the colon.
	int delimPos = (int)(strchr(token, ':') - token);

	// So this just copies the numbers manually
	int offSet = 0;
	for (int i = 0; i < 2; i++) {
		sec[i] = nullCoalesce(token + delimPos + i + 1);
		if (*(token + i) == ':') continue;
		min[i] = nullCoalesce(token + i);
	}

	dur.minutes = atoi(min);
	dur.seconds = atoi(sec);

	return dur;
}

void load(Node** listHead) {
	// Load the CSV data file
	FILE* playList = fopen("musicPlayList.csv", "r");

	// Check if file opened
	// Assert throws an assertion exception if file didn't open
	// and stops execution of the code.
	assert(playList != NULL);

	// The current string
	char line[CHAR_LIMIT] = "/0";

	// Current token
	char* token = NULL;

	// Current column index
	int index = 1;

	// Hold the data of the current line
	Record row = initRecord();

	while (!feof(playList)) {
		// Get the next line
		fgets(line, CHAR_LIMIT, playList);

		// Remove the trailing new line
		strtok(line, "\n");

		// Start a new record
		row = initRecord();
		
		// If the artist name isn't quote encapsulated
		if (strstr(line, "\"") == NULL) {
			token = strtok(line, ",");
		}
		else {
			// There is quotes, so parse the name
			token = strtok(line, "\"");
		}

		// We start with finding the artist name
		strcpy(row.artist, token);
		//printf("%s\n", token);

		// While we're still finding columns
		while (token != NULL) {
			// Get each column
			token = strtok(NULL, ",");

			// Continue if we're not at the end of the line
			if (token != NULL) {
				index += 1;

				//printf("%s\n", token);

				// Save each found record
				switch (index) {
					case ALBUM:		strcpy(row.albumTitle, token); break;
					case SONG:		strcpy(row.songTitle, token); break;
					case GENRE:		strcpy(row.genre, token); break;
					case DURATION:  row.songLength = parseDuration(token); break;
					case PLAYS:		row.timesPlayed = atoi(token);  break;
					case RATING:	row.rating = atoi(token);  break;
				}
			}
		}

		// Now save the found values
		insertAtFront(listHead, row);

		// And reset the column index
		index = 1;
	}

	// We're done with the file
	fclose(playList);
}

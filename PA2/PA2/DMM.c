
#include "DMM.h"


char GetInput() {
	char input = '\0';
	scanf("%c", &input);
	return input;
}

// I use nullish coalesing in JavaScript, it's bugging me
// C doesn't have this built in.
char NullCoalesce(char* payload) {
	return payload == NULL ? '\0' : *payload;
}

// Strtok causes the load function it lose it's place
Duration ParseDuration(char* token) {
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
		sec[i] = NullCoalesce(token + delimPos + i + 1);
		if (*(token + i) == ':') continue;
		min[i] = NullCoalesce(token + i);
	}

	dur.minutes = atoi(min);
	dur.seconds = atoi(sec);

	return dur;
}

void Load(Node** listHead) {
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
					case DURATION:  row.songLength = ParseDuration(token); break;
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

void Store(Node** listHead) {
	// Init with node found at head
	Node* curr = (*listHead);

	// Open the file for writing
	FILE* playList = fopen("musicPlayListt.csv", "w");

	// While the node isn't null
	while (curr) {
		Record data = curr->data;

		// Write Artist
		fprintf(playList, "%s,", data.artist);

		// Write Album Title
		fprintf(playList, "%s,", data.albumTitle);

		// Write Song Title
		fprintf(playList, "%s,", data.songTitle);

		// Write Genre
		fprintf(playList, "%s,", data.genre);

		// Write Duration
		fprintf(playList, "%d:%d,", data.songLength.minutes, data.songLength.seconds);

		// Write Plays
		fprintf(playList, "%d,", data.timesPlayed);

		// Write Rating
		fprintf(playList, "%d,\n", data.rating);

		// To the next node
		curr = curr->next;
	}

	// We're done with the file
	fclose(playList);
}

void Display(Node** listHead) {
	Node* next = *listHead;
	do {
		printf("%s %s %s %s %d %d %d %d\n",
			next->data.artist,
			next->data.albumTitle,
			next->data.songTitle,
			next->data.genre,
			next->data.songLength.minutes,
			next->data.songLength.seconds,
			next->data.timesPlayed,
			next->data.rating
		);
		next = next->next;
	} while (next != NULL);
}

void Edit(Node** listHead) {
	char query[CHAR_LIMIT] = "\0";

	printf("Enter an artist to search for: ");
	scanf("%s", query);

	printf("\nSelect a result to edit");

	// Store the results of our search query
	Node* results[RESULTS_LIMIT];

	// Find all songs by artist
	Node* curr = (*listHead);

	// Keep track of results count
	int count = 0;

	// Search for the query
	while (curr != NULL) {
		if (strstr(curr->data.artist, query) != NULL) {
			// Save the result
			printf("%s by %s\n");
			results[count] = curr;

			// Increment results count
			count += 1;
		}

		// Go to the next result
		curr = curr->next;
	}

	// Show the results menu
	printf("Select a song to edit\n");

	// Leave if no results
	curr = results[0];
	if (curr == NULL) {
		printf("No results :(");
		return;
	}

	// Print each result
	for (int i = 1; curr != NULL; i++) {
		printf("%d. %s by %s\n", curr->data.songTitle, curr->data.artist);
	}

	// Get menu choice
	int input = atoi(GetInput());
	curr = results[input - 1];

	// Print results
	system("cls");
	printf("Now editing %s\n", curr->data.songTitle);
}

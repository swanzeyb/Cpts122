
#include "DMM.h"
#include <sys/wait.h>

void ClearScreen() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
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

bool InRange(int value, int min, int max) {
	return value >= min && value <= max;
}

// This method waits for any input, without having to press enter
char GetOnInput() {
	// I'm developing on mac, so this just uses the correct calls per system
  while (1) {
    #if defined(_WIN64) || defined(_WIN32)
      char in = _getch();
    #elif defined(__APPLE__)
			// Mac is a little different, so I'm using the system calls
      fflush(stdin);
      system("/bin/stty raw");
      char in = getchar();
      system("/bin/stty cooked");
    #endif
    if ((in != '\n') && (in != ' ')) {
      return in;
    }
  }
}

void WaitForInput() {
	printf("Press any key to continue...");
	GetOnInput();
}

void Load(Node** listHead) {
	ClearScreen();
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
	ClearScreen();
	char query[CHAR_LIMIT] = "\0";

	printf("Enter an artist to search for: ");
	scanf("%s", query);

	printf("Select a result to edit:\n");

	// Store the results of our search query
	Node* results[RESULTS_LIMIT] = { NULL };

	// Find all songs by artist
	Node* curr = (*listHead);

	// Keep track of results count
	int count = 0;

	// Search for the query
	while (curr != NULL) {
		if (strstr(curr->data.artist, query) != NULL) {
			// Increment results count
			count += 1;

			// Save the result
			printf("%d. %s by %s\n", count, curr->data.songTitle, curr->data.artist);
			results[count - 1] = curr;
		}

		// Go to the next result
		curr = curr->next;
	}

	// Leave if no results
	curr = results[0];
	if (curr == NULL) {
		printf("No results :(\n");
		return;
	}

	// Get menu choice
	int input = -1;
	scanf("%d", &input);

	ClearScreen();
	curr = results[input - 1];

	// Select the value to edit
	input = -1;
	while (!InRange(input, 1, 7)) {
		ClearScreen();
		// Print results
		printf("Now editing %s by %s\n", curr->data.songTitle, curr->data.artist);

		// Values
		printf("Select a value to edit:\n");
		printf("1. Artist\n");
		printf("2. Album Title\n");
		printf("3. Song Title\n");
		printf("4. Genre\n");
		printf("5. Duration\n");
		printf("6. Plays\n");
		printf("7. Rating\n");

		// Get input
		scanf("%d", &input);
	}

	// Get new values from user
	switch (input) {
		case ARTIST:
			printf("Enter new artist name: ");
			scanf("%s", curr->data.artist);
			break;
		case ALBUM:
			printf("Enter new album title: ");
			scanf("%s", curr->data.albumTitle);
			break;
		case SONG:
			printf("Enter new song title: ");
			scanf("%s", curr->data.songTitle);
			break;
		case GENRE:
			printf("Enter new genre: ");
			scanf("%s", curr->data.genre);
			break;
		case DURATION:
			printf("Enter new duration (mm:ss): ");
			scanf("%d:%d", &curr->data.songLength.minutes, &curr->data.songLength.seconds);
			break;
		case PLAYS:
			printf("Enter new play count: ");
			scanf("%d", &curr->data.timesPlayed);
			break;
		case RATING:
			printf("Enter new rating: ");
			scanf("%d", &curr->data.rating);
			break;
	}

	// Show the user the new record
	printf("\nNew record:\n");
	printf("%s %s %s %s %d %d %d %d\n",
		curr->data.artist,
		curr->data.albumTitle,
		curr->data.songTitle,
		curr->data.genre,
		curr->data.songLength.minutes,
		curr->data.songLength.seconds,
		curr->data.timesPlayed,
		curr->data.rating
	);
}

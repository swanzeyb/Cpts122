
#include "DMM.h"
#include <stdio.h>
#include <sys/wait.h>

// Mac chaos
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

		// While we're still finding columns
		while (token != NULL) {
			// Get each column
			token = strtok(NULL, ",");

			// Continue if we're not at the end of the line
			if (token != NULL) {
				index += 1;

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
		if (index == 7) {
			// If the record is valid, insert it at the front of the list
			insertAtFront(listHead, row);
		}

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
	FILE* playList = fopen("musicPlayList.csv", "w");

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

void PrintRecord(Node* curr) {
	Record data = curr->data;

	// Write Artist
	printf("%s,", data.artist);

	// Write Album Title
	printf("%s,", data.albumTitle);

	// Write Song Title
	printf("%s,", data.songTitle);

	// Write Genre
	printf("%s,", data.genre);

	// Write Duration
	printf("%d:%d,", data.songLength.minutes, data.songLength.seconds);

	// Write Plays
	printf("%d,", data.timesPlayed);

	// Write Rating
	printf("%d\n", data.rating);
}

void Display(Node** listHead) {
	Node* next = *listHead;
	do {
		PrintRecord(next);
		next = next->next;
	} while (next != NULL);
	printf("\n");
}

Node* SelectSong(Node** listHead) {
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

	// Stop if no results
	curr = results[0];
	if (curr == NULL) {
		printf("No results :(\n");
		return NULL;
	}

	// Get menu choice
	int input = -1;
	scanf("%d", &input);

	// Get the selection node
	ClearScreen();
	curr = results[input - 1];

	return curr;
}

void Edit(Node** listHead) {
	Node* curr = SelectSong(listHead);

	// Don't continue if there are no results
	if (curr == NULL) {
		return;
	}

	// Select the value to edit
	int input = -1;
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
	PrintRecord(curr);
	printf("\n");
}

void Rate(Node** listHead) {
	Node* curr = SelectSong(listHead);

	// Don't continue if there are no results
	if (curr == NULL) {
		return;
	}

	// Get new rating
	int input = -1;
	printf("Enter new rating: ");
	scanf("%d", &input);

	// Update the rating
	curr->data.rating = input;

	// Show the user the new record
	PrintRecord(curr);
	printf("\n");
}

void WaitTime(unsigned int seconds) {
	// Get the current time
	time_t start = time(NULL);

	// Set the end time
	time_t end = start + seconds;

	// Wait until the time is up
	while (time(NULL) < end) {
		// Do nothing
	}
}

void Play(Node** listHead) {
	Node* curr = SelectSong(listHead);

	// Don't continue if there are no results
	if (curr == NULL) {
		return;
	}

	while (curr != NULL) {
		// Play the song
		printf("Now playing %s by %s\n", curr->data.songTitle, curr->data.artist);
		WaitTime(PLAY_TIME);

		// Increment the play count
		curr->data.timesPlayed += 1;

		// Go to the next song
		curr = curr->next;
	}

	printf("Play Complete!\n\n");
}

void Insert(Node** listHead) {
	// Hold the new values
	Record newRec = initRecord();

	// Ask the user for Artist
	printf("Enter the artist: ");
	scanf("%s ", newRec.artist);

	// Ask the user for Album Title
	printf("Enter the album title: ");
	scanf("%s ", newRec.albumTitle);

	// Ask the user for Song Title
	printf("Enter the song title: ");
	scanf("%s ", newRec.songTitle);

	// Ask the user for Genre
	printf("Enter the genre: ");
	scanf("%s ", newRec.genre);

	// Ask the user for Duration
	printf("Enter the duration (mm:ss): ");
	scanf("%d:%d", &newRec.songLength.minutes, &newRec.songLength.seconds);

	// Ask the user for Plays
	printf("Enter the play count: ");
	scanf("%d", &newRec.timesPlayed);

	// Ask the user for Rating
	printf("Enter the rating: ");
	scanf("%d", &newRec.rating);

	// Insert the new record
	insertAtFront(listHead, newRec);
}

void Delete(Node **listHead) {
	// Find a record to delete
	Node* curr = SelectSong(listHead);

	// Don't continue if there are no results
	if (curr == NULL) {
		return;
	}

	// Delete the record
	deleteNode(curr);
}

void StrSort(Node** listHead, char* (*get)(Node*)) {
	// Bubble sort the linked list
	for (Node* curr = *listHead; curr != NULL; curr = curr->next) {
		// For each node in the list, compare it to the next node
		for (Node* next = curr->next; next != NULL; next = next->next) {
			if (strcmp(get(curr), get(next)) > 0) {
				// Swap the data
				Record temp = curr->data;
				curr->data = next->data;
				next->data = temp;
			}
		}
	}
}

void IntSort(Node** listHead, int (*get)(Node*)) {
	// Bubble sort the linked list
	for (Node* curr = *listHead; curr != NULL; curr = curr->next) {
		// For each node in the list, compare it to the next node
		for (Node* next = curr->next; next != NULL; next = next->next) {
			if (get(next) > get(curr)) {
				// Swap the data
				Record temp = curr->data;
				curr->data = next->data;
				next->data = temp;
			}
		}
	}
}

char* GetArtist(Node* node) {
	return node->data.artist;
}

char* GetAlbumTitle(Node* node) {
	return node->data.albumTitle;
}

int GetRating(Node* node) {
	return node->data.rating;
}

int GetTimesPlayed(Node* node) {
	return node->data.timesPlayed;
}

void Sort(Node** listHead) {
	int input = -1;

	while (input < 1) {
		printf("Select how you want to sort:\n");
		printf("1. Artist\n");
		printf("2. Album Title\n");
		printf("3. Rating\n");
		printf("4. Times Played\n");
		scanf("%d", &input);

		switch (input) {
			case 1:
				StrSort(listHead, GetArtist);
				break;
			case 2:
				StrSort(listHead, GetAlbumTitle);
				break;
			case 3:
				IntSort(listHead, GetRating);
				break;
			case 4:
				IntSort(listHead, GetTimesPlayed);
				break;
			default:
				input = -1;
		}
	}
	// Clean up our menu mess on screen
	ClearScreen();

	// Print the results of the sort
	Display(listHead);
}

void Shuffle(Node **listHead) {
	// Find length of list
	int length = listLength(listHead);

	// Keep track of how many times we've played a song
	int playCount = 0;

	// Where we are in the songs list
	int index = 0;

	// Current track
	Node* curr = *listHead;

	// Keep track of songs played so we don't repeat
	Node** played = malloc(sizeof(Node*) * length);

	while (playCount < length) {
		// Get a random number between 0 and length
		int randNum = rand() % length;

		// Get the song at the random index
		if (randNum == index) {
			// Don't play the same song twice in a row
			continue;
		} else if (index < randNum) {
			// If the random number is greater than the index, go forward
			for (int i = index; i < randNum; i++) {
				curr = curr->next;
				index += 1;
			}
		} else {
			// If the random number is less than the index, go backward
			for (int i = index; i > randNum; i--) {
				curr = curr->prev;
				index -= 1;
			}
		}

		// Check if we've played this song already
		bool playedAlready = false;
		for (int i = 0; i < playCount; i++) {
			if (played[i] == curr) {
				playedAlready = true;
				break;
			}
		}

		// If we haven't played this song, play it
		if (!playedAlready) {
			// Play the song
			printf("Now playing %s by %s\n", curr->data.songTitle, curr->data.artist);
			WaitTime(PLAY_TIME);

			// Increment the play count
			curr->data.timesPlayed += 1;

			// Add the song to the list of played songs
			played[playCount] = curr;
			playCount += 1;
		}
	}

	// We're done with the list, so free it
	free(played);

	printf("Shuffle Play Complete!\n\n");
}

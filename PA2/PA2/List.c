
#include "List.h"

Record initRecord() {
	Record empty = {
		"", "", "", "",
		{ 0, 0 },
		0, 0
	};
	return empty;
}

Node* makeNode(Record data) {
	// Allocate data for the new node
	Node* pNode = (Node*)malloc(sizeof(Node));

	// If malloc was successfull
	if (pNode != NULL) {
		// Asign the new data to the node
		pNode->data = data;
		// And initialize the links
		pNode->next = NULL;
		pNode->prev = NULL;
	}

	return pNode;
}

bool insertAtFront(Node** listHead, Record data) {
	Node* pNode = makeNode(data);

	// Check if malloc in makeNode was successfull
	if (pNode == NULL) {
		// If it wasn't, return false for bad outcome
		return false;
	}
	else {
		// If it was, update the new nodes links

		// listHead is a pointer to a pointer to a Node
		// This sets the new nodes next to the pointer to the curr Node
		pNode->next = (*listHead);
		// And the prev to null because there is no previous Node
		pNode->prev = NULL;

		// And update the prev link of the displaced node to point to the new Node
		if ((*listHead) != NULL) {
			// If listHead pointer had reference to a Node
			(*listHead)->prev = pNode;
		}

		// Then we set the listHead pointer value to the address of the new Node
		(*listHead) = pNode;

		// And return success
		return true;
	}
}

void printList(Node** listHead) {
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

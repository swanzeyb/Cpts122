#pragma once

#define CHAR_LIM 100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int minutes;
	int seconds;
} Duration;

typedef struct {
	char artist[CHAR_LIM];
	char albumTitle[CHAR_LIM];
	char songTitle[CHAR_LIM];
	char genre[CHAR_LIM];
	Duration songLength;
	int timesPlayed;
	int rating;
} Record;

typedef struct node {
	Record data;
	struct node* next;
	struct node* prev;
} Node;

Record initRecord(void);

Node* makeNode(Record data);

bool insertAtFront(Node** listHead, Record data);

void deleteNode(Node* node);

void printList(Node** listHead);

int listLength(Node** listHead);

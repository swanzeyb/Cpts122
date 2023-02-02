#pragma once
#pragma warning(disable : 4996)

#include <stdio.h>
#include <assert.h>
#include "List.h"

#define CHAR_LIMIT 100

typedef enum {
	ARTIST = 1,
	ALBUM = 2,
	SONG = 3,
	GENRE = 4,
	DURATION = 5,
	PLAYS = 6,
	RATING = 7,
} Column;

void load(Node** listHead);

//void store();

//void display();

//void edit();

//void rate();

//void play();

//void exit();

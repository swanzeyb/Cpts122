#pragma once
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

#define CHAR_LIMIT 100
#define RESULTS_LIMIT 10

typedef enum {
	ARTIST = 1,
	ALBUM = 2,
	SONG = 3,
	GENRE = 4,
	DURATION = 5,
	PLAYS = 6,
	RATING = 7,
} Column;

void ClearScreen();

void WaitForInput();

void Load(Node** listHead);

void Store(Node** listHead);

void Display(Node** listHead);

void Edit(Node** listHead);

//void Rate();

//void Play();

//void Exit();

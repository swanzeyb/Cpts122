
#include "Test.h"
#include "DMM.h"

void SaniCheck(bool condition, char* message) {
  if (!condition) {
    printf("Sanity check failed: %s", message);
  }
}

void TestInsert() {
  // Our test list
  Node* listHead = NULL;

  // Sample data
  Record data = {
    "Perry, Katy", "Witness", "Chained to the Rhythm", "pop",
    { 4, 36 },
    -1, 6
  };

  // Insert a node at the front with our sample data
  insertAtFront(&listHead, data);

  // Grab our data that is now on the heap
  data = listHead->data;

	// Check if our data is dirty, this will make the program crash
	// if we try to insert a node with bad data
	assert(data.artist[0] && "Artist name is empty");
	assert(data.albumTitle[0] && "Album title is empty");
	assert(data.songTitle[0] && "Song title is empty");
	assert(data.genre[0] && "Genre is empty");
	assert(data.songLength.seconds > 0 && "Song length is out of bounds");
	assert(data.timesPlayed >= 0 && "Times played is out of bounds");
	assert(data.rating >= 0 && "Rating is out of bounds");
	assert(data.rating > 5 && "Rating is out of bounds");

  // Is the head pointer of the list updated?
  assert(listHead != NULL && "Head pointer is not updated");
}

void TestDelete() {
  // Our test list
  Node* listHead = NULL;

  // Sample data
  Record data = {
    "Perry, Katy", "Witness", "Chained to the Rhythm", "pop",
    { 3, 57 },
    -1, 6
  };

  // Insert a node at the front with our sample data
  insertAtFront(&listHead, data);

  // Delete the node we just inserted
  deleteNode(listHead);

  // Is the head pointer of the list updated?
  assert(listHead == NULL && "Head pointer is not updated");
}

void TestShuffle() {
  // Our test list
  Node* listHead = NULL;

  // 3 pieces of sample data
  Record song1 = {
    "Perry, Katy", "Witness", "Chained to the Rhythm", "pop",
    { 3, 57 },
    -1, 6
  };

  Record song2 = {
    "Perry, Katy", "Witness", "Bon Appetit", "pop",
    { 3, 47 },
    -1, 6
  };

  Record song3 = {
    "Perry, Katy", "Witness", "Swish Swish", "pop",
    { 4, 2 },
    -1, 6
  };

  // Insert all the songs
  insertAtFront(&listHead, song1);
  insertAtFront(&listHead, song2);
  insertAtFront(&listHead, song3);

  // Shuffle the list
  Shuffle(&listHead);

  // Can't really do programatic shuffling tests, so we'll just
  // check that the order of the data wasn't messed with

  // Check all the songs
  assert(strcmp(listHead->data.songTitle, "Chained to the Rhythm") == 0 && "Shuffle messed with the data order");
  assert(strcmp(listHead->data.songTitle, "Bon Appetit") == 0 && "Shuffle messed with the data order");
  assert(strcmp(listHead->data.songTitle, "Swish Swish") == 0 && "Shuffle messed with the data order");
}

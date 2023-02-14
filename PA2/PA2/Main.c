
#pragma warning(disable : 4996)

#include "List.h"
#include "DMM.h"
#include "Test.h"

static Node* listHead = NULL;

void DoMenuItem(void (*func)(Node**)) {
	ClearScreen();
	func(&listHead);
	WaitForInput();
	ClearScreen();
}

void PrintMenu() {
	printf("Digital Music Manager\n");
	printf("1.  Load\n");
	printf("2.  Store\n");
	printf("3.  Display\n");
	printf("4.  Insert\n");
	printf("5.  Delete\n");
	printf("6.  Edit\n");
	printf("7.  Sort\n");
	printf("8.  Rate\n");
	printf("9.  Play\n");
	printf("10. Shuffle\n");
	printf("11. Exit\n");
}

int main(void) {
	srand(time(NULL)); // Seed random number generator

	// This is for my Mac shenanigans
	#ifndef _WIN32
		system("/bin/stty cooked");
	#endif

	printf("Run test cases (y/n)? ");
	char input = 0;
	scanf("%c", &input);

	if (input == 'y') {
		TestInsert();
		TestDelete();
		TestShuffle();
	}

	ClearScreen();
	
	while (true) {
		PrintMenu();
		int input = 0;
		scanf("%d", &input);

		switch (input) {
			case 1:  DoMenuItem(Load); break;
			case 2:  DoMenuItem(Store); break;
			case 3:  DoMenuItem(Display); break;
			case 4:  DoMenuItem(Insert); break;
			case 5:  DoMenuItem(Delete); break;
			case 6:  DoMenuItem(Edit); break;
			case 7:  DoMenuItem(Sort); break;
			case 8:  DoMenuItem(Rate); break;
			case 9:  DoMenuItem(Play); break;
			case 10: DoMenuItem(Shuffle); break;
			case 11: return 1;
		}
	}
}

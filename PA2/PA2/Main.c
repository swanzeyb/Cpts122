
#pragma warning(disable : 4996)

#include "List.h"
#include "DMM.h"

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
	while (true) {
		PrintMenu();
		int input = 0;
		scanf("%d", &input);

		switch (input) {
			case 1: DoMenuItem(Load); break;
			case 2: DoMenuItem(Store); break;
			case 3: DoMenuItem(Display); break;
			case 6: DoMenuItem(Edit); break;
			//case '8': rate; break;
			//case '9': play; break;
			case 11: return 1;
		}
	}
}

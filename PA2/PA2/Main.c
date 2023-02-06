
#pragma warning(disable : 4996)

#include "List.h"
#include "DMM.h"

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

	Node* listHead = NULL;
	
	while (true) {
		PrintMenu();
		char input = GetInput();

		switch (input) {
			case '1': Load(&listHead); break;
			case '2': Store(&listHead); break;
			case '3': Display(&listHead); break;
			case '6': Edit(&listHead); break;
			//case '8': rate; break;
			//case '9': play; break;
			case '11': return 1;
		}
	}
}

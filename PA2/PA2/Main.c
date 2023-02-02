
#pragma warning(disable : 4996)

#include "List.h"
#include "DMM.h"

int main(void) {

	Node* listHead = NULL;

	load(&listHead);

	printList(&listHead);

	return 1;
}

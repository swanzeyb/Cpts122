#include "methods.h"

char reverseStrRecursive(char str[], int index, int length) {
	char temp = '\0';
	int target = (length - 1) - index;

	if (target <= index) {
		return str;
	}
	else {
		temp = str[target];
		str[target] = str[index];
		str[index] = temp;
		return reverseStrRecursive(str, ++index, length);
	}
}

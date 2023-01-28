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

char* myStrncpy(char* destination, const char* source, int n) {
	for (int i = 0; i < n; i++) {
		char letter = *source++;
		*destination++ = letter == NULL ? '\0' : letter;
	}
	return destination;
}

char* myStrncat(char* destination, const char* source, int n) {
	char* point = destination + sizeof(destination);
	for (int i = 0; i < n; i++) {
		char* letter = source++;
		if (*letter == NULL) {
			break;
		}
		else {
			*point = letter;
		}
	}
}

int recStrlen(char* string, int count) {
	if (string++ == '\0') {
		return count;
	}
	else {
		return recStrlen(string, count);
	}
}

#include "methods.h";
#include <stdio.h>;
#include <string.h>;

/*
	Tokenize a String
	If the function is called with the same string
	If this is the first execution, return a string 
*/

int main() {

	char hiMom[] = "RedRu";
	reverseStrRecursive(hiMom, 0, strlen(hiMom));
	printf("Result: %s", hiMom);

	return 0;
}

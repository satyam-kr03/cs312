
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"

int main(int argc, char *argv[]) {

	if (argc != 2) {
		printf("Usage: strmain string\n");
		exit(-1);
	}
	char* outstr = (char*)malloc(strlen(argv[1]) + 4);
	// call lib function
	stringmod(argv[1],outstr);
	printf("%s\n", outstr);
	
} // end main


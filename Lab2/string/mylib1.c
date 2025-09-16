#include <string.h>
#include <stdio.h>
#include "mylib.h"

void stringmod(char* instr, char* outstr) {
	// concat input to empty output
	strcat(outstr,instr);
	// concat [1] to output
	strcat(outstr,"[1]");
} // end lib


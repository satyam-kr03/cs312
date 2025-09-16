#include <string.h>
#include <stdio.h>
#include "mylib.h"

void stringmod(char* instr, char* outstr) {
	// concat input to empty output
	strcat(outstr,instr);
	// concat [2] to output
	strcat(outstr,"[2]");
} // end lib


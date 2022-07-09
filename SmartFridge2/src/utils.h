/*
utils.h:
	strEqual
	sottostrEqual
	strMin
	strToUpper

	isNum       // isNum
	isPositive  // isPositive
	checkFloat     // isFloat

	apriFile
	clearFile

*/

#ifndef UTILS_H_
#define UTILS_H_


#include "types.h"
#include <stdio.h>

int sottostrEqual(char * str1, char* str2);

int strEqual(char* str1, char* str2);

int strMin(char* str1, char* str2);

void strToUpper(char * str);

// restituisce un file aperto
int apriFile(FILE** file, char* file_name, char* mode);

void clearFile(char* file_name);


void isNum(char *str,int* flag_errore);

void isPositive( float quantita, int* flag_errore);

void checkFloat(float quantita_float, int* flag_errore);

#endif /* UTILS_H_ */



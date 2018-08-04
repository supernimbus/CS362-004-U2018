/*********************************************************************
** Program name: randomtestcard2.c (Assignment 4)
** Author: Mario Franco-Munoz
** Due Date: 8/5/2018
** Description: this file tests the adventurer card using random testing
*********************************************************************/



#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

#define TESTCARD "adventurer"

int randomInt(int, int);
int customAssert(int boolIn);


int customAssert(int boolIn) {
	if (boolIn == 1) {
		//printf("TEST PASSED!\n");
		return 0;
	}
	else {
		ERROR_COUNT++;
		return 1;
	}

}


//Function to create a random integer using rand(). Lower and upper bounds are inclusive.
//output is a pseudo random number in the specified range.
int randomInt(int low, int high) {
	return (rand() % (high - low + 1)) + low;

}


int main() {



	return 0;
}
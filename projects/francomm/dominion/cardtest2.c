/*********************************************************************
** Program name: cardTest1.c (Assignment 3)
** Author: Mario Franco-Munoz
** Due Date: 4/29/2018
** Description: this file tests the adventurer card
*********************************************************************/



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define NOISY_TEST 1

void customAssert(int boolIn);

void customAssert(int boolIn) {
	if (boolIn == 1) {
		printf("TEST PASSED!\n");
	}
	if (boolIn == 0) {
		printf("******TEST FAILED!******\n");
	}
}



int main() {
	int i, j;
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
             , remodel, smithy, village, baron, great_hall};

	struct gameState gameTest;
	struct gameState emptyGame;
	test = initializeGame(MAX_PLAYERS, k , randomSeed, &emptyGame);
	customAssert(test == 0);


	




	return 0;
}














/*********************************************************************
** Program name: unittest4.c (Assignment 3)
** Author: Mario Franco-Munoz
** Due Date: 6/22/2018
** Description: this file tests the whosTurn function.
*********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int ERROR_COUNT = 0;

void customAssert(int boolIn);

void customAssert(int boolIn) {
	if (boolIn == 1) {
		printf("TEST PASSED!\n");
	}
	if (boolIn == 0) {
		ERROR_COUNT++;
		printf("******TEST FAILED!******\n");
	}
}



int main() {

	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    int i;
    int j;
    int randomSeed = 1000;

    struct gameState gameTest;
    struct gameState initGame;


     printf("******TESTING whosTurn() ******\n");


	//case 1: fresly initialized game
    printf("Check with fresly initialized game + varying number of players...\n");
	for(i = 2; i <= MAX_PLAYERS; i++) {
		memcpy(&gameTest, &initGame, sizeof(struct gameState));
		initializeGame(i, k, randomSeed, &gameTest);
		customAssert(whoseTurn(&gameTest) == 0);

	}

    //case 2: two players
	printf("Checking with two players (setting second player to have next turn)...\n");
	memcpy(&gameTest, &initGame, sizeof(struct gameState));
	initializeGame(2, k, randomSeed, &gameTest);
	gameTest.whoseTurn = 1;
	customAssert(whoseTurn(&gameTest) == 1);


    //case 3: three to max players
	printf("Checking with three to MAX_PLAYERS...\n");
	for (i = 3; i <= MAX_PLAYERS; i++) {

		memcpy(&gameTest, &initGame, sizeof(struct gameState));
		initializeGame(i, k, randomSeed, &gameTest);
		for (j = 0; j < i; j++) {
			gameTest.whoseTurn = j;
			customAssert(whoseTurn(&gameTest) == j);
		}
	}

	//case 4: end turn for player using endTurn() 
	printf("Checking next turn using endTurn()...\n");
	for (i = 2; i <= MAX_PLAYERS; i++) {
		memcpy(&gameTest, &initGame, sizeof(struct gameState));
		initializeGame(i, k, randomSeed, &gameTest);
		for (j = 0; j < i; j++) {
			endTurn(&gameTest);
			if (j < i - 1) {
				customAssert((whoseTurn(&gameTest) == j + 1 ));
			}
			else {
				customAssert((whoseTurn(&gameTest) == 0));	
			}		
		}
	}

	printf("ERROR COUNT: %d\n", ERROR_COUNT);
    printf("*************END OF TEST RESULTS******************\n");

	return 0;
}

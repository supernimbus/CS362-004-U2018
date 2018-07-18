/*********************************************************************
** Program name: unittest4.c (Assignment 3)
** Author: Mario Franco-Munoz
** Due Date: 4/29/2018
** Description: this file tests the whosTurn function.
*********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>



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

	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    int i;
    int j;
    int randomSeed = 1000;
    int checkVal;
    int temp;

    struct gameState gameTest = newGame();
    struct gameState initGame = newGame();


     printf("******TESTING whosTurn() ******\n");


	//case 1: fresly initialized game
    printf("Check with fresly initialized game + varying number of players...\n");
	for(i = 2; i <= MAX_PLAYERS; i++) {
		memcpy(&gameTest, &initGame, sizeof(struct gameState));
		initializeGame(i, k, randomSeed, &gameTest);
		customAssert(whosTurn(gameTest) == 0);

	}

    //case 2: two players
	printf("Checking with two players (setting second player to have next turn)...\n");
	memcpy(&gameTest, &initGame, sizeof(struct gameState));
	initializeGame(2, k, randomSeed, &gameTest);
	gameTest->whosTurn = 1;
	customAssert(whosTurn(gameTest) == 1);


    //case 3: three to max players
	printf("Checking with three to MAX_PLAYERS...\n");
	for (i = 3; i <= MAX_PLAYERS; i++) {

		memcpy(&gameTest, &initGame, sizeof(struct gameState));
		initializeGame(i, k, randomSeed, &gameTest);
		for (j = 0; j < i; j++) {
			gameTest->whosTurn = j;
			customAssert(whosTurn(gameTest) == j);
		}
	}

    printf("*************END OF TEST RESULTS******************");

	return 0;
}
/*********************************************************************
** Program name: unittest3.c (Assignment 3)
** Author: Mario Franco-Munoz
** Due Date: 4/29/2018
** Description: this file tests the isGameOver function.
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

	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    int i;
    int j;
    int randomSeed = 1000;
    int checkVal;
    int temp;

    struct gameState gameTest = newGame();
    struct gameState initGame = newGame();


    printf("******TESTING isGameOver() ******\n");

    initializeGame(2, k , randomSeed, &initGame);
    memcpy(&gameTest, &initGame, sizeof(struct gameState));



    printf("Checking with new initialized game...\n");
    checkVal = isGameOver(gameTest);
    customAssert(checkVal == 0);

    printf("Checking with empty province pile (game should be over)...\n");
    gameTest->supplyCount[province] = 0;
    checkVal = isGameOver(gameTest);
    customAssert(checkVal == 1);



    printf("Checking with one pile empty (game should not be over)...\n");
    for (i = 0; i < 10 ; i++) {
    	memcpy(&gameTest, &initGame, sizeof(struct gameState));
    	temp = k[i];
    	gameTest->supplyCount[temp] = 0;
    	checkVal = isGameOver(gameTest);
    	customAssert(checkVal == 0);
    }

    printf("Checking with one empty coin pile (game should not be over)...\n");
    memcpy(&gameTest, &initGame, sizeof(struct gameState));
    gameTest->supplyCount[copper] = 0;
    checkVal = isGameOver(gameTest);
    customAssert(checkVal == 0);
    memcpy(&gameTest, &initGame, sizeof(struct gameState));
    gameTest->supplyCount[silver] = 0;
    checkVal = isGameOver(gameTest);
    customAssert(checkVal == 0);
    memcpy(&gameTest, &initGame, sizeof(struct gameState));
    gameTest->supplyCount[gold] = 0;
    checkVal = isGameOver(gameTest);
    customAssert(checkVal == 0);


    printf("Checking with two piles empty (game should not be over)...\n");
    memcpy(&gameTest, &initGame, sizeof(struct gameState));
    temp = k[0];
    gameTest->supplyCount[temp] = 0;
    temp = k[1];
    gameTest->supplyCount[temp] = 0;
    checkVal = isGameOver(gameTest);
    customAssert(checkVal == 0);


    printf("Checking with three piles empty (game should be over)...\n");
    memcpy(&gameTest, &initGame, sizeof(struct gameState));
	temp = k[0];
    gameTest->supplyCount[temp] = 0;
    temp = k[1];
    gameTest->supplyCount[temp] = 0;
    temp = k[2];
    gameTest->supplyCount[temp] = 0;
    checkVal = isGameOver(gameTest);
    customAssert(checkVal == 1);

    printf("*************END OF TEST RESULTS******************\n");

	return 0;
}
/*********************************************************************
** Program name: cardTest1.c (Assignment 3)
** Author: Mario Franco-Munoz
** Due Date: 6/22/2018
** Description: this file tests the smithy card
*********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

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

/* Intended behavior of smithy: "+3 Cards" */

int main() {

	int randomSeed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
             , remodel, smithy, village, baron, great_hall};
	
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	struct gameState gameTest;
	struct gameState initGame;
	

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	initializeGame(2, k, randomSeed, &initGame);
	int player = 0;
	initGame.hand[player][0] = smithy;
	initGame.hand[player][1] = copper;
	initGame.hand[player][2] = duchy;
	initGame.hand[player][3] = estate;
	initGame.hand[player][4] = feast;

	player = 1;
	initGame.hand[player][0] = gold;
	initGame.hand[player][1] = copper;
	initGame.hand[player][2] = duchy;
	initGame.hand[player][3] = estate;
	initGame.hand[player][4] = feast;
   
	memcpy(&gameTest, &initGame, sizeof(struct gameState));

 
	int hand_count_prev = gameTest.handCount[0];
	int deck_count_prev = gameTest.deckCount[0];
	int hand_count_prev_2 = gameTest.handCount[1];
	int deck_count_prev_2 = gameTest.deckCount[1];


	//call cardEffect
	cardEffect(smithy, choice1, choice2, choice3, &gameTest, handpos, &bonus);


	//check to make sure current player recieves exactly three cards
	printf("Checking to make sure that current player recieves exactly three cards.\n");
	printf("hand count = %d, expected = %d\n", gameTest.handCount[0], hand_count_prev + 3 - 1);
	customAssert(gameTest.handCount[0] == (hand_count_prev + 2));
 
	//check to make sure that current player's deck count decreases by 3
	printf("Checking to make sure that current player's deck count decreases by 3 cards...\n");
	customAssert(gameTest.deckCount[0] == (deck_count_prev - 3));
	

	//check to make sure cards came from player's own deck (player 1's deck did not change assertion)
	printf("Checking to make sure cards in player 1's deck did not change.\n");
	customAssert(gameTest.deckCount[1] == deck_count_prev_2);
		
	//check to make sure player 1's hand did not change
	printf("Checking to make sure cards in player 1's hand did not change.\n");
	printf("second player's hand count = %d, expected %d\n", gameTest.handCount[1], hand_count_prev_2);
	customAssert(gameTest.handCount[1] == hand_count_prev_2);


	//check to make sure other game variables remained static
	printf("Checking to make sure number of buys did not change.\n");
	customAssert(gameTest.numBuys == initGame.numBuys);

	printf("Checking to make sure number of actions did not change.\n");
	customAssert(gameTest.numActions == initGame.numActions);


	
	//check to make sure still player 0's turn
	printf("Checking to make sure it is still player 0's turn.\n");
	customAssert(gameTest.whoseTurn == 0);




	printf("Error Count: %d\n", ERROR_COUNT);
	printf("*************END OF TEST RESULTS******************\n");

	return 0;
}

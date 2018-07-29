/*********************************************************************
 * ** Program name: cardTest4.c (Assignment 3)
 * ** Author: Mario Franco-Munoz
 * ** Due Date: 6/22/2018
 * ** Description: this file tests the great_hall card
 * *********************************************************************/



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define NOISY_TEST 1
#define TESTCARD "great_hall"

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


/*Intended behavior: Draw card and get an additional action.*/

int main() {
	int i;
	int hand_count_prev;
	int card_Drawn;
	int discard_p1;
	int randomSeed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
             , remodel, smithy, village, baron, great_hall};
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

	struct gameState gameTest;
	struct gameState emptyGame;	



	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	initializeGame(2, k, randomSeed, &emptyGame);
	memcpy(&gameTest, &emptyGame, sizeof(struct gameState));
	hand_count_prev = gameTest.handCount[0];	
	gameTest.hand[0][0] = great_hall;
	gameTest.hand[1][0] = great_hall;
	for (i = 1; i < gameTest.handCount[0]; i++) {
		gameTest.hand[0][i] = baron;
		gameTest.hand[1][i] = baron;
	}
	for (i = 0; i < gameTest.deckCount[0]; i++) {
		gameTest.deck[0][i] = feast;
		gameTest.hand[1][i] = feast;
	}

	//test to check that number of actions increases by one
	int prev_actions = gameTest.numActions;

	//for checking discard
	discard_p1 = gameTest.discardCount[0];

	cardEffect(great_hall, choice1, choice2, choice3, &gameTest, handpos, &bonus);

	printf("Test that the number of actions has increased by 1.\n");
	customAssert(gameTest.numActions == (prev_actions + 1));


	//test to check that card is drawn
	card_Drawn = 0;
	for (i = 0; i < gameTest.handCount[0]; i++) {
		if (gameTest.hand[0][i] == feast) {
			card_Drawn = 1;
		}	
	}
	printf("Test that the number of cards drawn after playing card is 1.\n");
	customAssert(card_Drawn == 1);
	
	//check that the net ammount of cards in hand stays the same
	printf("Test that hand count did not increase or decrease.\n");
	customAssert(hand_count_prev == gameTest.handCount[0]);

	//check that the number of played cards has increased by one.
	printf("Test that the number of played cards by player0 increased by 1.\n");
	customAssert(discard_p1 == (gameTest.playedCardCount - 1));

	//check to make sure that it is still the same player's turn
	printf("Test that it is still player 0's turn.\n");
	customAssert(gameTest.whoseTurn == 0);


	printf("-------------------End of Test------------------------------------\n");
	
	return 0;
}

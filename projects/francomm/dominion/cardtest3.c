/*********************************************************************
** Program name: cardTest1.c (Assignment 3)
** Author: Mario Franco-Munoz
** Due Date: 4/29/2018
** Description: this file tests the councilRoom card
*********************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define NOISY_TEST 1
#define TESTCARD "council_room"

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


/*Intended behavior of Council Room: "+4 Cards, +1 Buy, Each other player draws a card"
*/


int main() {
	int i;
	int randomSeed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
             , remodel, smithy, village, baron, great_hall};
	
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int test;

	struct gameState gameTest;
	struct gameState emptyGame_2; //empty game with 2 players
	struct gameState emptyGame_3; //empty game with 3 players
	test = initializeGame(MAX_PLAYERS, k , randomSeed, &emptyGame_2);
	customAssert(test == 0);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	initializeGame(2, k, randomSeed, &emptyGame_2);
	initializeGame(3, k, randomSeed, &emptyGame_3);
	
	emptyGame_2.handCount[0] = 5;
	emptyGame_2.handCount[0] = 5;

	emptyGame_3.deckCount[0] = 5;
	emptyGame_3.deckCount[0] = 5;
	
	for (i = 0; i < emptyGame_2.deckCount[0]; i++) {
		emptyGame_2.deck[0][i] = baron;
		emptyGame_2.deck[1][i] = baron;	
	}
	for (i = 0; i < emptyGame_3.deckCount[0]; i++) {
		emptyGame_3.deck[0][i] = baron;
		emptyGame_3.deck[1][i] = baron;
	}

	for (i = 0; i <emptyGame_2.handCount[0]; i++) {
		emptyGame_2.hand[0][i] = baron;
	}
	for (i = 0; i < emptyGame_3.handCount[0]; i++) {
		emptyGame_3.hand[0][i] = baron;
	}

	//initialize hand and deck manually
	memcpy(&gameTest, &emptyGame_2, sizeof(struct gameState));
	gameTest.handCount[0] = 5;
	gameTest.deckCount[0] = 5;
	gameTest.deckCount[1] = 5;
	for (i = 0; i < gameTest.deckCount[0]; i++) {
		gameTest.deck[0][i] = baron;
		gameTest.deck[1][i] = baron;	
	}
	for (i = 0; i < gameTest.handCount[0]; i++) {
		gameTest.hand[0][i] = baron;
	}

	
	//Check to make sure that player gets 4 Cards and 1 extra buy
	printf("Checking that player gets 4 cards...\n");
	int hand_prev = gameTest.handCount[0];
	int deck_prev = gameTest.deckCount[0];
	cardEffect(council_room, choice1, choice2, choice3, &gameTest, handpos, &bonus);
	printf("Make sure that deck decreased in size by 4 cards... \n");
	printf("Prev deck size: %d, current deck size: %d\n", deck_prev, gameTest.deckCount[0]);
	customAssert((gameTest.deckCount[0] + 4) == deck_prev);

	printf("Check that hand size increased by 3...\n");
	printf("Prev hand size: %d, current hand size: %d\n", hand_prev, gameTest.handCount[0]);
	customAssert(gameTest.handCount[0] == (hand_prev + 3));

	int prev_buys = gameTest.numBuys;
	printf("Checking that player gets extra buy...\n");
	customAssert(gameTest.numBuys == (prev_buys + 1));
	 

	//make sure each other player draws a card
	printf("Checking that other player draws one card (2 players)\n");
	customAssert(gameTest.handCount[1] == 1);	


	//test with two other players
	printf("CChecking that other players draw one card (3 players)\n");
	memcpy(&gameTest, &emptyGame_3, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &gameTest, handpos, &bonus);
	customAssert(gameTest.handCount[1] == 1 && gameTest.handCount[2] == 1);
	
	//test for change of state in other players discard and deck count
	memcpy(&gameTest, &emptyGame_2, sizeof(struct gameState));
	int prev_deck_count = gameTest.deckCount[1];
	int prev_discard_count = gameTest.discardCount[1];	
	cardEffect(council_room, choice1, choice2, choice3, &gameTest, handpos, &bonus);
	
	//test to check that deck count goes down by one
	printf("Checking that player deck size goes down by one...\n");
	if (prev_deck_count > 0 ) {
		printf("Deck size was greater than 0...\n");
		customAssert(prev_deck_count == gameTest.deckCount[1] + 1);
	}
	else if (prev_deck_count == 0){
		printf("Deck size was zero prior to calling cardEffect()...\n");
		customAssert(gameTest.deckCount[1] == prev_discard_count - 1);
	}
	else {
		customAssert(0);
	}
	 			
	
	printf("Error count: %d\n", ERROR_COUNT);
	printf("-------------------End of Test------------------------------------\n");
	return 0;
}








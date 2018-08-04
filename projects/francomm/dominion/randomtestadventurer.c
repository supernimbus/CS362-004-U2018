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
int ERROR_COUNT = 0;


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

//initializes everything to council_room for testing purposes
void initDeckandHand(struct gameState *G ) {
	int i;
	for (i = 0; i < G->handCount[0]; i++) {
		G->hand[0][i] = council_room; 
	}
	for (i = 0; i < G->deckCount[0]; i++) {
		G->deck[0][i] = council_room;
	}
}


/*Intended behavior for Adventurer:
 * "Reveal cards from your deck until you reveal 2 Treasure cards. Put those Treasure 
 * cards into your hand and discard the other revealed cards."
*/

int main() {
	int i;
	int testCount = 6;
	int randomSeed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
             , remodel, smithy, village, baron, great_hall};

	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int test, cards_in_deck, cards_in_hand;

	struct gameState gameTest;
	struct gameState emptyGame;
	test = initializeGame(MAX_PLAYERS, k , randomSeed, &emptyGame);
	customAssert(test == 0);
	int iterationCount = 1000;
	int players;
	int testErrorCounts[testCount];
	int treasureCard[3] = {copper, silver, gold};

	for (int i = 0; i < testCount; i++) {
		testErrorCounts[i] = 0;
	}


	for (int p = 0; p < iterationCount; p++) {
		players = randomInt(2, MAX_PLAYERS);
		initializeGame(players, k, randomSeed, &emptyGame);


		memcpy(&gameTest, &emptyGame, sizeof(struct gameState));
		cards_in_deck = emptyGame.deckCount[0];
		cards_in_hand = emptyGame.handCount[0];
		int cards_in_discard = 0;


		//Checking case in which the player has less than 2 Treasure cards in his deck....
		//set all cards in deck to be council_room cards
		for (i = 0; i < cards_in_deck; i++) {
			gameTest.deck[0][i] = council_room;
		}	

		//set all cards in hand to be council_room cards
		for (i = 0; i < cards_in_hand; i++) {
			gameTest.hand[0][i] = council_room;
		}


		//call cardEffect with adventurer
		cardEffect(adventurer, choice1, choice2, choice3, &gameTest, handpos, &bonus);


		//assert that hand size did not change
		test = gameTest.handCount[0];
		if (customAssert(test == cards_in_hand) == 1) {
			testErrorCounts[0]++;
		}


		//assert that there are no cards left in deck	
		test = gameTest.deckCount[0];
		if (customAssert(test == 0) == 1) {
			testErrorCounts[0]++;
		}


		//Case 1A: deck only conains one treasure card
		memcpy(&gameTest, &emptyGame, sizeof(struct gameState));
		for (i = 0; i < cards_in_deck; i++) {
			gameTest.deck[0][i] = council_room;
		}
		gameTest.deck[0][cards_in_deck - 1] = copper;

		for (i = 0; i < cards_in_hand; i++) {
			gameTest.hand[0][i] = council_room;
		}
	
		//call cardEffect with adventurer
		cardEffect(adventurer, choice1, choice2, choice3, &gameTest, handpos, &bonus);
		test = gameTest.deckCount[0];
		if (customAssert(test == 0) == 1) {
			testErrorCounts[1]++;
		}	
	
		//Checking to make sure that hand size increased by 1...
		test = gameTest.handCount[0];
		if (customAssert(test == cards_in_hand +1) == 1) {
			testErrorCounts[1]++;
		}


		//Case 2A: Deck contains exactly 2 treasure cards
		memcpy(&gameTest, &emptyGame, sizeof(struct gameState));
		initDeckandHand(&gameTest);


		//Case2A.1: 1 Copper, 1 Sliver.
		gameTest.deck[0][0] = copper;
		gameTest.deck[0][1] = silver;
		cardEffect(adventurer, choice1, choice2, choice3, &gameTest, handpos, &bonus);
		if (customAssert((gameTest.deckCount[0] + gameTest.discardCount[0]) == (cards_in_deck + cards_in_discard))==1){
			testErrorCounts[2]++;
		}
		if (customAssert(gameTest.handCount[0] == cards_in_hand + 2) == 1) {
			testErrorCounts[2]++;
		}	


		//Case2A.2: 1 Sliver, 1 Gold.\n");
		memcpy(&gameTest, &emptyGame, sizeof(struct gameState));
		initDeckandHand(&gameTest);

		gameTest.deck[0][0] = silver;
		gameTest.deck[0][1] = gold;
		cardEffect(adventurer, choice1, choice2, choice3, &gameTest, handpos, &bonus);
		if (customAssert((gameTest.deckCount[0] + gameTest.discardCount[0]) == (cards_in_deck + cards_in_discard))==1){
			testErrorCounts[2]++;
		}
		if (customAssert(gameTest.handCount[0] == cards_in_hand + 2) == 1) {
			testErrorCounts[2]++;
		}	


		//Case 3: random number of treasure cards in deck
		memcpy(&gameTest, &emptyGame, sizeof(struct gameState));
		initDeckandHand(&gameTest);


		int randTreasures = randomInt(3, gameTest.deckCount[0]);
		for (int k = 0; k < randTreasures; k++) {
			gameTest.deck[0][k] = treasureCard[rand() % 3];
		}
		cardEffect(adventurer, choice1, choice2, choice3, &gameTest, handpos, &bonus);
		//check that deck decreased by 2
		if (customAssert((gameTest.deckCount[0] - 2) == emptyGame.deckCount[0]) == 1) {
			testErrorCounts[3]++;
		} 
		if (customAssert((gameTest.handCount[0] + 2) == emptyGame.handCount[0]) == 1) {
			testErrorCounts[3]++;
		}



		//checking that state does not change for other players 0 plays card...
		memcpy(&gameTest, &emptyGame, sizeof(struct gameState));
		cardEffect(adventurer, choice1, choice2, choice3, &gameTest, handpos, &bonus);
		for (int k = 1; k < players; k++) {
			if (customAssert(gameTest.handCount[k] == emptyGame.handCount[k]) == 1) {
				testErrorCounts[4]++;
			}
			if (customAssert(gameTest.deckCount[k] == emptyGame.deckCount[k]) == 1) {
				testErrorCounts[4]++;
			}
		}
		
		
		//checking to make sure it is still player 0's turn
		if (customAssert(gameTest.whoseTurn == 0) == 1 ) {
			testErrorCounts[5]++;
		}


	}

	
	printf("************Random Testing of %s summary: *******************\n", TESTCARD);
	printf("No treasure cards in deck errors: %d\n", testErrorCounts[0]);
	printf("Only one treasure card in deck errors: %d\n", testErrorCounts[1]);
	printf("Deck contains two treasure cards: %d\n", testErrorCounts[2]);
	printf("Deck contains random treasure cards: %d\n", testErrorCounts[3]);
	printf("Other players hand and/or deck count errors: %d\n", testErrorCounts[4]);
	printf("Change of turn error: %d\n", testErrorCounts[5]);




	return 0;
}

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
#define TESTCARD "adventurer"



void customAssert(int boolIn);
void printHand(struct gameState *, int);
void initDeckandHand(struct gameState *);

void customAssert(int boolIn) {
	if (boolIn == 1) {
		printf("TEST PASSED!\n");
	}
	if (boolIn == 0) {
		printf("******TEST FAILED!******\n");
	}
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

void printHand(struct gameState *G, int player) {
	int i;
	for (i = 0; i < G->handCount[player]; i++) {
		printf("%d ", G->hand[player][i]);
	}
	printf("\n");
}

void printDeck(struct gameState *G, int player) {
	int i;
	for (i = 0; i < G->deckCount[player]; i++) {
		printf("%d ", G->deck[player][i]);
	}
	printf("\n");
}

int main() {
	int i;
	int randomSeed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
             , remodel, smithy, village, baron, great_hall};

	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int test, cards_in_deck, cards_in_hand;

	struct gameState gameTest;
	struct gameState emptyGame;
	test = initializeGame(MAX_PLAYERS, k , randomSeed, &emptyGame);
	customAssert(test == 0);


	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	

	initializeGame(2, k, randomSeed, &emptyGame);
	memcpy(&gameTest, &emptyGame, sizeof(struct gameState));
	cards_in_deck = emptyGame.deckCount[0];
	cards_in_hand = emptyGame.handCount[0];
	int cards_in_discard = 0;

	printf("Checking case in which the player has less than 2 Treasure cards in his deck....\n");


	//set all cards in deck to be council_room cards
	for (i = 0; i < cards_in_deck; i++) {
		gameTest.deck[0][i] = council_room;
	}	

	//set all cards in hand to be council_room cards
	for (i = 0; i < cards_in_hand; i++) {
		gameTest.hand[0][i] = council_room;
	}
	printf("Printing hand contents before test:\n");	
	printHand(&gameTest, 0);
	printf("Printing deck contents before test:\n");
	printDeck(&gameTest, 0);

	//call cardEffect with adventurer
	cardEffect(adventurer, choice1, choice2, choice3, &gameTest, handpos, &bonus);

	printf("Printing hand contents after test:\n");
	printHand(&gameTest, 0);
	printf("Printing deck contetns after test:\n");
	printDeck(&gameTest, 0);	

	//assert that hand size did not change
	test = gameTest.handCount[0];
	printf("Checking to make sure that hand size did not change...\n");
	customAssert(test == cards_in_hand);

	//assert that deck size did not change	
	test = gameTest.deckCount[0];
	printf("Checking to make sure that deck size is zero...\n");
	customAssert(test == 0);


	printf("Case 1A: deck only conains one treasure card.\n");
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
	printf("Checking to make sure that deck size is zero...\n");
	customAssert(test == 0);	
	
	printf("Checking to make sure that hand size increased by 1...\n");
	test = gameTest.handCount[0];
	customAssert(test == cards_in_hand +1);


	printf("Case 2A: Deck contains exactly 2 treasure cards.\n");
	memcpy(&gameTest, &emptyGame, sizeof(struct gameState));
	initDeckandHand(&gameTest);

	printf("Case2A.1: 1 Copper, 1 Sliver.\n");
	gameTest.deck[0][0] = copper;
	gameTest.deck[0][1] = silver;
	cardEffect(adventurer, choice1, choice2, choice3, &gameTest, handpos, &bonus);
	printf("checking to make sure hand size increased by 2 and deck size + discard size decreased by 2...\n");
	printf("Checking deckCount + discardCount delta...\n");
	customAssert((gameTest.deckCount[0] +  gameTest.discardCount[0]) == (cards_in_deck + cards_in_discard - 2));
	printf("Checking handCount...\n");
	customAssert(gameTest.handCount[0] == cards_in_hand + 2);	


	printf("Case2A.2: 1 Sliver, 1 Gold.\n");
	gameTest.deck[0][0] = silver;
	gameTest.deck[0][1] = gold;
	cardEffect(adventurer, choice1, choice2, choice3, &gameTest, handpos, &bonus);
	printf("checking to make sure hand size increased by 2 and deck size + discard size decreased by 2...\n");
	printf("Checking deckCount + discardCount delta...\n");
	customAssert((gameTest.deckCount[0] +  gameTest.discardCount[0]) == (cards_in_deck + cards_in_discard - 2));
	printf("Checking handCount...\n");
	customAssert(gameTest.handCount[0] == cards_in_hand + 2);	


	printf("Checking that number of actions has decreased after playing Adventurer.\n");
	memcpy(&gameTest, &emptyGame, sizeof(struct gameState));
	gameTest.numActions = 1;
	cardEffect(adventurer, choice1, choice2, choice3, &gameTest, handpos, &bonus);
	customAssert(gameTest.numActions = 0);

	printf("checking that state does not change for player 1 when player 0 plays card...\n");
	memcpy(&gameTest, &emptyGame, sizeof(struct gameState));
	int handCount2 = gameTest.handCount[1];
	int deckCount2 = gameTest.deckCount[1];
	cardEffect(adventurer, choice1, choice2, choice3, &gameTest, handpos, &bonus);
	customAssert(handCount2 == gameTest.handCount[1]);
	customAssert(deckCount2 == gameTest.deckCount[1]);


	printf("-------------------End of Test------------------------------------\n");

	return 0;
}














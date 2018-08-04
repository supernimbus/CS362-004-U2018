/*********************************************************************
** Program name: randomtestcard2.c (Assignment 4)
** Author: Mario Franco-Munoz
** Due Date: 8/5/2018
** Description: this file tests the council_room card using random testing
*********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

#define TESTCARD "council_room"


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



int main() {

	int randomSeed = 1000;
	int players;
	int handSize = 5;
	int deckSize = 10;
	int iterationCount = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
             , remodel, smithy, village, baron, great_hall};

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	
	struct gameState gameTest;
	struct gameState initGame;

	//initialize seed
	srand(time(0));

	//random test loop
	for (int i = 0; i < iterationCount; i++) {
		//assign random number of players
		players = randomInt(2, MAX_PLAYERS);
		initializeGame(players, k, randomSeed, &initGame);


		//initialize players' hands
		for (int j = 0; j < players; j++) {
			for(int k = 0; k < handSize; k++) {	
				initGame.hand[j][k] = baron;	
			}
			initGame.handCount[j] = handSize;

			for(int k = 0; k < deckSize; k++) {
				initGame.deck[j][k] = baron;
			}
			initGame.deckCount[j][k] = baron;
		}


		memcpy(&gameTest, &initGame, sizeof(struct gameState));

		//check to make sure that player gets 4 cards and 1 extra buy
		int hand_prev = gameTest.handCount[0];
		int deck_prev = gameTest.deckCount[0];
		cardEffect(council_room, choice1, choice2, choice3, &gameTest, handpos, &bonus);

		//Test 1: check that active player's deck count decreased
		customAssert((gameTest.deckCount[0] + 4) == deck_prev);


		//Test 2: check that active player's hadn count increased


		//Test 3: check that active player gets an extra buy


		//Test 4: check that other players draw one card


		//Test 5: test for change of state in other players' discard and deck count



		//Test 6: test that it is still player 0's turn.
		customAssert(gameTest.whosTurn == 0);



	}











	return 0;
}
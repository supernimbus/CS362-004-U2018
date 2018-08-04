/*********************************************************************
** Program name: randomtestcard1.c (Assignment 4)
** Author: Mario Franco-Munoz
** Due Date: 8/5/2018
** Description: this file tests the smithy card using random testing
*********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"


#define TESTCARD "smithy"

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


	int errorCheck; handCountErr, deckCountErr, otherPlayersErr, stateChangeErr = 0;
	int randomSeed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
             , remodel, smithy, village, baron, great_hall};

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

    int players;
    int iterationCount = 1000;
    int output;
    int hand_count_prev, hand_count_prev_2, deck_count_prev, deck_count_prev_2;

	struct gameState gameTest;
	struct gameState initGame;
	int handCount_prev[MAX_PLAYERS];
	int deckCount_prev[MAX_PLAYERS];


	//initialize seed
	srand(time(0));



	//run random tests an arbitrary number of times
	for (int i = 0; i < iterationCount; i++) {
		//initiate gamestate with random number of players
		players = randomInt(2, MAX_PLAYERS);
		initializeGame(players, k, randomSeed, &initGame);
		memcpy(&gameTest, &initGame, sizeof(struct gameState));


		for (int j = 0; j < players; j++) {
			handCount_prev[i] = gameTest.handCount[i];
			deckCount_prev[i] = gameTest.deckCount[i];
		}

		//cardeffect call
		cardEffect(TESTCARD, choice1, choice2, choice3, &gameTest, handpos, &bonus);	


		//check to make sure current player recieves exactly three cards
		errorCheck = customAssert(gameTest.handCount[0] == (handCount_prev[0] + 2));
		if (errorCheck == 1) {
			handCountErr++;
		}	


		//check to make sure that current player's deck count decreases by 3
		errorCheck = customAssert(gameTest.deckCount[0] == (deckCount_prev[0] - 3));
		if (errorCheck == 1) {
			deckCountErr++;
		}	
		

		//check to make sure other players' hands and deck did not change
		for (int j = 1; j < players; j++) {
			errorCheck = customAssert(gameTest.handCount[j] == handCount_prev[i]);
			if (errorCheck == 1) {
				otherPlayersErr++;
			}
			errorCheck = customAssert(gameTest.deckCount[j] == deckCount_prev[i]);
			if (errorCheck == 1) {
				otherPlayersErr++;
			}
		}


		//check to make sure other game variables remained static
		errorCheck = customAssert(gameTest.numBuys == initGame.numBuys);
		if (errorCheck == 1) {
			stateChangeErr++;
		}

		//check to make sure number of actions did not change
		errorCheck = customAssert(gameTest.numActions == initGame.numActions);
		if (errorCheck == 1) {
			stateChangeErr++;
		}

		//check to make sure it is still player 0's turn
		errorCheck = customAssert(gameTest.whosTurn == 0);
		if (errorCheck == 1) {
			stateChangeErr++;
		}



		//reset the initial game state
		memset(&initGame, 0, sizeof(struct gameState));

	}



	printf("************Random Testing of %s summary: *******************\n", TESTCARD);
	printf("Active player hand count errors: %d\n", handCountErr);
	printf("Active player deck count errors: %d\n", deckCountErr);
	printf("Change in other player's deck or hand count errors: %d\n", otherPlayersErr);
	printf("State change errors: %d\n", stateChangeErr);



	return 0;
}



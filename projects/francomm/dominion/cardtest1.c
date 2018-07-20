/*********************************************************************
** Program name: cardTest1.c (Assignment 3)
** Author: Mario Franco-Munoz
** Due Date: 4/29/2018
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
	int testHandSize = 1;
	int player;
	int before;
	int after;
	int estateBefore;
	int estateAfter;
	int duchyBefore;
	int duchyAfter;
	int copperBefore;
	int copperAfter;
	int silverBefore;
	int silverAfter


	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	initializeGame(2, k , randomSeed, &initGame);
	player = 0;
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
    
	//check to make sure current player recieves exactly three cards
	printf("Checking to make sure that current player recieves exactly three cards.\n");
	memcpy(&gameTest, &initGame, sizeof(struct gameState));
	smithyCard(&gameTest, 0);
	player = 0;
	printf("hand count = %d, expected = %d\n", gameTest.handCount[player], gameTest.handCount[player] + 3 - 1);
	customAssert(gameTest.handCount[player] == gameTest.handCount[player] + 2);

	//check to make sure cards came from player's own deck
	printf("Checking to make sure cards came from player's own deck.\n");
	memcpy(&gameTest, &initGame, sizeof(struct gameState));
	before = gameTest.handCount[1]
	smithyCard(&gameTest, 0);
	after = gameTest.handCount[1];
	printf("second player's hand count = %d, expected %d\n", before, before);
	customAssert(before == after);


	//check to make sure there has not been a state change in other players' hands, decks, piles, actions
	printf("Checking to make sure there has not been a state change in other players' hands, decks, piles, actions etc.\n");
	memcpy(&gameTest, &initGame, sizeof(struct gameState));
	player = 1;
	int *tempHand_player2 = gameTest.hand[player];
	int handCount_player2 = gameTest.handCount[player];
	int *deck_player2 - gameTest.deck[]
	smithyCard(&gameTest, 0);
	
	

	//check to make sure there are no change in the victory card piles, kingdom card piles, coin piles
	printf("Checking to make sure there was not a change in victory cards and coin cards.\n");
	memcpy(&gameTest, &initGame, sizeof(struct gameState));
	








	printf("*************END OF TEST RESULTS******************\n");

	return 0;
}

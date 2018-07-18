/*********************************************************************
** Program name: unittest2.c (Assignment 3)
** Author: Mario Franco-Munoz
** Due Date: 4/29/2018
** Description: this file tests the initializeGame function.
*********************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define NOISY_TEST 1

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


int main() {
	int i;
	int j;
	int test;
    int randomSeed = 1000;
    int testReturnVal;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};


    int duplicateCards[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    struct gameState gameTest;
    struct gameState emptyGame; 
	test = initializeGame(MAX_PLAYERS, k, randomSeed, &emptyGame);
	customAssert(test == 0);


    int copperCounter;
    int estateCounter;



    printf("******TESTING initializeGame() ******\n");

    //test with greater than max players (check to make sure return value is -1)
    #if (NOISY_TEST == 1)
    	printf("Testing to check if maximum number of player threshold works correctly...\n");
    #endif
    testReturnVal = initializeGame(MAX_PLAYERS + 1, k, randomSeed, &gameTest);
    customAssert(testReturnVal == -1);
    memcpy(&gameTest, &emptyGame, sizeof(struct gameState));

    //test with less than minimum number of players (check to make sure return value is -1)
    #if (NOISY_TEST == 1)
    	printf("Testing to check if minimum number of players thresholds work correctly...\n");
    #endif
    testReturnVal = initializeGame(1, k , randomSeed, &gameTest);
    customAssert(testReturnVal == -1);
    memcpy(&gameTest, &emptyGame, sizeof(struct gameState));

    //test to make sure number of players was set correctly
    #if (NOISY_TEST == 1)
    
	printf("Testing to check number of players was set correctly...\n");
    #endif
    for (i = 2; i <= MAX_PLAYERS; i++) {
    	initializeGame(i, k, randomSeed, &gameTest);
    	customAssert(gameTest.numPlayers == i);
    	memcpy(&gameTest, &emptyGame, sizeof(struct gameState));
    }


    //check to see that it's the first player's turn
    #if (NOISY_TEST == 1)
    	printf("Testing to check if first player has the next turn after initializeGame()\n");
    #endif
    for (i = 2; i <= MAX_PLAYERS; i++) {
    	initializeGame(i, k, randomSeed, &gameTest);
    	customAssert(gameTest.whoseTurn == 0);
    	memcpy(&gameTest, &emptyGame, sizeof(struct gameState));
    }	



    //check to make sure that the starting deck consists of 7 coppers and 3 estates
    #if (NOISY_TEST == 1)
    	printf("Testing to check if decks were initialized correctly... (7 coppers, 3 estates)\n" );
    #endif
    
    for (i = 2; i <= MAX_PLAYERS; i++) {
    	#if (NOISY_TEST == 1)
    		printf("Testing with %d players \n", i);
    	#endif
    	initializeGame(i, k, randomSeed, &gameTest);
    	estateCounter = 0;
    	copperCounter = 0;
    	for (j = 0; j < 10; j++) {
    		if (gameTest.deck[i - 2][j] == estate) {
    			estateCounter++;
    		}
    		else if (gameTest.deck[i - 2][j] == copper) {
    			copperCounter++;
    		}
    	}
    	//starting deck must consist of 7 coppers and 3 estates
    	customAssert(estateCounter == 3 && copperCounter == 7);
		memcpy(&gameTest, &emptyGame, sizeof(struct gameState));    	
    }

    //check to make sure that the kingdom cards have the correct starting amounts
    //as per dominion documentation.pdf "if number of players are 2 we have 8 great hall and 8 gradens to start with
    //else we will have 12 gardens and 12 great_hall to start with. for all other cards we start with 10 cards.
    //if the card is not being used, then there should not be a pile of that card
    int temp = 0;		//temp variable for navigating index
    #if (NOISY_TEST == 1)
    	printf("Testing starting ammounts...\n");
    #endif
    for (i = 2; i <= MAX_PLAYERS; i++) {
    	#if (NOISY_TEST == 1)
    		printf("Testing with %d players... \n", i);
    	#endif

    	//check great hall and gardens cards
    	#if (NOISY_TEST == 1)
    		printf("Checking starting ammounts of great_hall and gardens cards... (%d players) \n", i);
    	#endif
    	initializeGame(i, k, randomSeed, &gameTest);
    	if (i == 2) {
    		customAssert(gameTest.supplyCount[great_hall] == 8 && gameTest.supplyCount[gardens] == 8);
    	}
    	else {
    		customAssert(gameTest.supplyCount[great_hall] == 12 && gameTest.supplyCount[gardens] == 12);
    	}

   		//check everything else
   		#if (NOISY_TEST == 1)
    		printf("Checking starting ammounts of remaining cards... (%d players)\n", i);
    	#endif
   		for (j = 0 ; j <= 9; j++) {
			if (k[j] != gardens &&  k[j] != great_hall) {
				customAssert(gameTest.supplyCount[k[j]] == 10);
			}
   		}
    	
    	memcpy(&gameTest, &emptyGame, sizeof(struct gameState));	
    }





    //check to make sure that embargo tokens are set at 0 for each pile
    #if (NOISY_TEST == 1)
    	printf("Testing to make sure that embargo tokens are set to 0 for each pile...\n");
    #endif
    for (j = 2; j <= MAX_PLAYERS; j++) {
    	#if (NOISY_TEST == 1)
    		printf("Testing with %d players \n", j);
    	#endif
    	initializeGame(j, k, randomSeed, &gameTest);
    	for (i = 0; i < treasure_map+1; i++) {
    		customAssert(gameTest.embargoTokens[i] == 0);	
    	}
    	memcpy(&gameTest, &emptyGame, sizeof(struct gameState));
	}


    //check to make sure that each player has their hands set up: hand must consist of 5 cards
    //this is based of the description of how initializeGame is supposed to work as described in the
    //Dominion-BaseArchitecture.pdf
	#if (NOISY_TEST == 1)
    	printf("Testing to make sure that each player has an initialized hand...\n");
    #endif
    for (i=2; i <= MAX_PLAYERS; i++) {
    	#if (NOISY_TEST == 1)
    		printf("Testing with %d players \n", i);
    	#endif
    	initializeGame(i, k, randomSeed, &gameTest);
    	for (j = 0; j < i; j++) {
    		customAssert(gameTest.handCount[j] == 5);
    	}
    	memcpy(&gameTest, &emptyGame, sizeof(struct gameState));
    }


    //check to make sure player "0" is set to go first
    #if (NOISY_TEST == 1)
    	printf("Testing to check that player 0 is set to go first...\n");
    #endif
    for (i=2; i <= MAX_PLAYERS; i++) {
    	#if (NOISY_TEST == 1)
    		printf("Testing with %d players \n", i);
    	#endif
    	initializeGame(i, k, randomSeed, &gameTest);
    	customAssert(gameTest.whoseTurn == 0);
    	memcpy(&gameTest, &emptyGame, sizeof(struct gameState));
    }
    

	printf("ERROR COUNT = %d\n", ERROR_COUNT);
    printf("*************END OF TEST RESULTS******************\n");

    return 0;


}

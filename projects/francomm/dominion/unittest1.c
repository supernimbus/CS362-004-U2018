/*********************************************************************
** Program name: unittest1.c (Assignment 3)
** Author: Mario Franco-Munoz
** Due Date: 4/29/2018
** Description: this file tests the updateCoins function
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
	int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;


    int testHandSize = 5;
    int accum_copperSilver = 0;
    int accum_copperGold = 0;
    int accum_silverGold = 0;

    //initialization of arrays for the different test cases
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    int copper_silver[MAX_HAND];
    int copper_gold[MAX_HAND];
    int silver_gold[MAX_HAND];
    int noCoins[MAX_HAND];

    for (i = 0; i < MAX_HAND; i++) {
    	coppers[i] = copper;
    	silvers[i] = silver;
    	golds[i] = gold;
    	noCoins[i] = curse;
    	if (i % 2 == 0) {
    		copper_silver[i] = copper;
    		copper_gold[i] = copper;
    		silver_gold[i] = silver;
    	}
    	else {
    		copper_silver[i] = silver;
    		copper_gold[i] = gold;
    		silver_gold[i] = gold;
    	}

    }

    printf("******TESTING updateCoins() ******\n");
    for (p = 0; p < numPlayer; p++) {
    	for (handCount = 1; handCount <= testHandSize; handCount++) {
    		for (bonus = 0; bonus <= maxBonus; bonus++) {
    			#if (NOISY_TEST == 1)
            		printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
            	#endif
    		
				memset(&G, 23, sizeof(struct gameState));   // clear the game state
				r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
				G.handCount[p] = handCount;                 // set the number of cards on hand
			
				//test case 1: hand only contains copper coins
				memcpy(G.hand[p], coppers, sizeof(int) * handCount); 
				updateCoins(p, &G, bonus);
				#if (NOISY_TEST == 1)
					printf("Test case 1: hand only contains copper coins");
                	printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
            	#endif
                customAssert(G.coins == handCount * 1 + bonus);


				//test case 2: hand only contains silver coins
				memcpy(G.hand[p], silvers, sizeof(int) * handCount); 
				updateCoins(p, &G, bonus);
				#if (NOISY_TEST == 1)
					printf("Test case 2: hand only contains silver coins");
                	printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
            	#endif
                customAssert(G.coins == handCount * 2 + bonus);


				//test case 3: hand only contains gold coins
				memcpy(G.hand[p], golds, sizeof(int) * handCount); 
				updateCoins(p, &G, bonus);
                #if (NOISY_TEST == 1)
					printf("Test case 3: hand only contains gold coins");
                	printf("G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
            	#endif
                customAssert(G.coins == handCount * 3 + bonus);

                //test case 4: hand contains no coins
                memcpy(G.hand[p], noCoins, sizeof(int) * handCount); 
				updateCoins(p, &G, bonus);
                #if (NOISY_TEST == 1)
					printf("Test case 4: hand contains no coins");
                	printf("G.coins = %d, expected = %d\n", G.coins, handCount * 0 + bonus);
            	#endif
                customAssert(G.coins == bonus);
					
				
				accum_copperSilver = 0;
				accum_copperGold = 0;
				accum_silverGold = 0;
                //add up coins for cases in which hand is a mix of coins
                for(i = 0; i < handCount; i++) {
                	if (i % 2 ==0) {
                		accum_copperSilver += 1;
                		accum_copperGold += 1;
                		accum_silverGold += 2;
                	}
                	else {
                		accum_copperSilver += 2;
                		accum_copperGold += 3;
                		accum_silverGold += 3;
                	}
                }	


				//test case 5: hand contains copper and silver coins
                memcpy(G.hand[p], copper_silver, sizeof(int) * handCount); 
				updateCoins(p, &G, bonus);
				#if (NOISY_TEST == 1)
					printf("Test case 5: hand contains copper and silver coins");
                	printf("G.coins = %d, expected = %d\n", G.coins, accum_copperSilver + bonus);
            	#endif
                customAssert(G.coins == accum_copperSilver + bonus);


                //test case 6: hand contains copper and gold coins
                memcpy(G.hand[p], copper_gold, sizeof(int) * handCount);
                updateCoins(p, &G, bonus);
                #if (NOISY_TEST == 1)
                	printf("G.coins = %d, expected = %d\n", G.coins, accum_copperGold + bonus);
            	#endif
                customAssert(G.coins == accum_copperGold + bonus);

				//test case 7: hand contains silver and gold coins
				memcpy(G.hand[p], silver_gold, sizeof(int) * handCount);
                updateCoins(p, &G, bonus);
                #if (NOISY_TEST == 1)
                	printf("G.coins = %d, expected = %d\n", G.coins, accum_silverGold + bonus);
            	#endif
                customAssert(G.coins == accum_silverGold + bonus);

			}
    	}
    }

    printf("*************END OF TEST RESULTS******************");

	return 0;
}

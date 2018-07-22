#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


int COVERAGE_COMPLETED = 0;

int stateTracker[8] = {0, 0, 0, 0, 0, 0, 0, 0};

int ITERATIONS = 0;

char inputChar()
{

    //variables for generating number within desired ascii range
    int upper = 126; //tilde char    
    int lower = 32; //space char
    char out;

    int randNo = (rand() % (upper - lower +1)) + lower;

    out = (char)randNo;

    if (out == '[' && stateTracker[0] == 0) {
      stateTracker[0] = 1;
    }
    if (out == '(' && stateTracker[1] == 0) {
      stateTracker[1] = 1;
    }
    if (out == '{' && stateTracker[2] == 0) {
      stateTracker[2] = 1;
    }
    if (out == ' ' && stateTracker[3] == 0) {
      stateTracker[3] = 1;
    }
    if (out == 'a' && stateTracker[4] == 0) {
      stateTracker[4] = 1;
    }
    if (out == 'x' && stateTracker[5] == 0) {
      stateTracker[5] = 1;
    }
    if (out == '}' && stateTracker[6] == 0) {
      stateTracker[6] = 1;
    }
    if (out == ')' && stateTracker[7] == 0) {
      stateTracker[7] = 1;
    }
    if (out == ']' && stateTracker[8] == 0) {
      stateTracker[8] = 1;
    }

	    
	if (stateTracker[0] == 1 && stateTracker[1] == 1 && stateTracker[2] == 1 &&
	stateTracker[3] == 1 && stateTracker[4] == 1 && stateTracker[5] == 1 &&
	stateTracker[5] == 1 && stateTracker[6] == 1 && stateTracker[6] == 1 &&
	stateTracker[7] == 1 && stateTracker[8] == 1) {
		COVERAGE_COMPLETED = 1;
	}



    return out;
}

char *inputString()
{
    //generate fixed lengthrandom string
    //char *tempStr[5];
    int strSize = 6;
    char *outStr;
    int upper = 122; //lower case z    
    int lower = 97; //lower case a
    int randNo = 0;
    int i;


    //create string
    outStr = malloc(sizeof(char) *strSize);
    for (i = 0; i < 5; i++) {
      randNo = (rand() % (upper - lower +1)) + lower;
      outStr[i] = (char)randNo;
    }
    outStr[5] = '\0';
    
    //if we have generated more than x iterations and we have achieved our coverage goal, return the key pharase
	/*
    if (COVERAGE_COMPLETED == 1) {
		memset(outStr, '\0', 6);
		strcat(outStr, "reset");
    }
	*/
    if (COVERAGE_COMPLETED == 0 && strcmp(outStr, "reset") == 0) {
    	memset(outStr,'\0', 6);
    }

    return outStr;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
	  free(s);
      exit(200);
    }
	else {
	  free(s);
	}
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));

    testme();
    return 0;
}

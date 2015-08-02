#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define DEBUG
/*
Problem Statement

Time is running out. You have a final match to play as a counter terrorist. You have N players each having a distinct ID from 1 to N. You have to choose some players on your team from these N players such that no two chosen players have consecutive numbers (as they tend to kill each other). Also you definitely have to choose some K players whose numbers are given. They are the snipers. Find the maximum number of players that you can choose.

Input Format

The first line contains 2 space-separated integers, N and K, where N is the total number of players and K is the number of players that have to be definitely in the team (the snipers).
 The second line contains K space-separated integers that are the IDs of the snipers.

NOTE: There are no two snipers with consecutive numbers.

Constraints
2?N?2×106
1?K?N/2
1? ID of each sniper ?N

Output Format

You need to print the maximum number of players that you can have in your team.

Sample Input
8 2
6 2

Sample Output
4

Explanation

There are 8 players in total, among which you have to definitely choose players with ID 2 and 6.
 To maximize the number of players in the team, you will choose the players with IDs 4 and 8, so that you will have a total of 4 players.

Camper: A player in a professional team dedicated to using the AWP sniper rifle.
*/

/* campersBetween - Calculates the number of campers that can be placed between two campers */
/* Input: prevCamper is the number of the previous camper */
/*        nextCamper is the number of the next camper */
int campersBetween(int prevCamper, int nextCamper) {
    /* Calculate the difference between two campers and divide by two */
    /* Take this result, and subtract 1, to allow of 1 space between campers */
    /* All math is integer arithmatic, with the result going to the next lower number */
  return (nextCamper - prevCamper)/2 - 1;
}

int main() {
    int numPlayers; /* Number of players in the game (N) */
    int numSnipers; /* Number of snipers in the game (K) */
    int sniperCtr;  /* Counter for snipers */
    int nextSniper; /* Next sniper read from input */
    int sortCtr;    /* Sorting loop counter */
    int printCtr;   /* Printing loop counter */
    int tempSniper; /* Store a temporary sniper while sorting */
    int numCampers; /* Number of campers */

    /* Read the number of players and snipers */
    scanf("%d %d", &numPlayers, &numSnipers);
#ifdef DEBUG
    printf("Players = %d, Snipers = %d\r\n", numPlayers, numSnipers);
#endif

    /* Declare an array to store the sniper ID numbers, with two extras */
    int snipers[numSnipers+2];

    /* Initialize the array with a beginning and ending sniper to allow the same
        algorithm to be used at the start and the end of the sniper array */
    snipers[0] = -1;    /* Include this for handling the start of the sniper array */
    snipers[1] = numPlayers + 2;    /* Include this to handle the end of the sniper array */

    /* Read the snipers into the snipers array; keeping them in increasing sorted order */
    for (sniperCtr = 0; sniperCtr < numSnipers; sniperCtr++) {
        scanf("%d", &nextSniper);
#ifdef DEBUG
        printf("Next sniper = %d\r\n", nextSniper);
#endif
        snipers[sniperCtr+2] = nextSniper;
        /* Insert the next Sniper into the array in sorted order */
        sortCtr = sniperCtr + 2;    /* Start at the end of the sniper array */
        /* Loop while there is still more to the array, and the snipers are out of order */
        while ((sortCtr >= 0) && (snipers[sortCtr - 1] > snipers[sortCtr])) {
            /* Elements out of order, swap them */
            tempSniper = snipers[sortCtr];
            snipers[sortCtr] = snipers[sortCtr - 1];
            snipers[sortCtr - 1] = tempSniper;
            /* Go to the next element in the array */
            sortCtr--;
        }

#ifdef DEBUG
        for (printCtr=0; printCtr <= sniperCtr+2; printCtr++) {
            printf("%d ", snipers[printCtr]);
        }
        printf("\r\n");
#endif
    }

    /* Start with the number of snipers as campers */
    numCampers = numSnipers;

    /* Loop through the snipers array counting campers in the spaces between snipers */
    for (sniperCtr=0; sniperCtr < numSnipers + 1; sniperCtr++) {
#ifdef DEBUG
        printf("sniperCtr = %d, snipers[ctr] = %d, snipers[ctr+1] = %d, between = %d\r\n",
            sniperCtr, snipers[sniperCtr], snipers[sniperCtr+1],
            campersBetween(snipers[sniperCtr], snipers[sniperCtr+1]));
#endif
        /* Increase the number of campers by the campers between snipers */
        numCampers += campersBetween(snipers[sniperCtr], snipers[sniperCtr+1]);
    }

#ifdef DEBUG
    printf("Campers = %d\r\n", numCampers);
#endif
    /* Print out the final count of campers */
    printf("%d\r\n", numCampers);

    return 0;
}

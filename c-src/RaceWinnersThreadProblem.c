/*
   Problem Statement
   - 3 Runners (e.g. Dave, Jeff, Ben) Participated in Multiple Races
   - For Each Race, every Runner's Ranks are recorded i.e. 1 or 2 or 3 as Race Concludes
   - Need to print overall Ranking of winners from Races after every input
   for e.g. If results so far are:
   Dave {1,1,2,1,3,1,2} // ranks from the races
   Jeff {2,3,3,2,1,3,1}
   Ben  {3,2,1,3,2,2,3}
   i.e. Current Ranking in terms of Races Won is:
   Dave (4) Jeff (2) Ben (1)
   User inputs:
   3 2 1 // Dave Jeff Ben respectively
   New Overall Ranks are:
   Dave (4) Jeff (2) Ben (2)
   User inputs:
   3 2 1 // Dave Jeff Ben respectively
   New Overall Ranks are:
   Dave (4) Ben (3) Jeff (2)
   And so on.. until User exits

   Implementation Guidelines
   - Input (sample to be supplied by Orion. Orion will test your program for additional inputs):
   - 2 threads:
   - "input" thread that consumes the Race result
   - "output" thread that computes Overall Ranks and prints them

   Implement using Posix Thread Library
   */


#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define NUM_RUNNERS 3

typedef enum {
    FIRST = 1,
    SECOND,
    THIRD,
    MAX_RANK = THIRD
}Rank;

#define INRANGE(x) (((x) >= FIRST) && ((x) <= THIRD)) 
#define VALIDRANK(x, y, z) \
    (INRANGE(x) && INRANGE(y) && INRANGE(z) && \
     ((x) != (y)) && ((y) != (z)) && ((x) != (z)) )
#define RANKTOIDX(x) (INRANGE(x) ? ((x)-1) : (x))

typedef struct {
    char name[10];
    // <rank, frequency> e.g. {{1,3}, {2,5}, {3,0}} indicates:
    // Runner was first in 3 races, second in 5 races and never finished third
    unsigned int results[MAX_RANK];
}Runner;

void add_entry (Runner *runner, Rank rank) {
    runner->results[RANKTOIDX(rank)]++;// adds an entry to the key "rank"
}

void input(Runner *Dave, Runner *Jeff, Runner *Ben) {
    //     while (true) {
    // Possible solution Code here

    unsigned int daveRank,jeffRank,benRank;
    printf("Enter ranks for Dave, Jeff, Ben respectively\n");
    scanf("%d %d %d",&daveRank,&jeffRank,&benRank);
    //printf("%d %d %d\n",INRANGE(daveRank),jeffRank,benRank);
    // following condition check ensures that Ranks are in 1-3 range, as well as there are no repeats
    if (VALIDRANK(daveRank, jeffRank, benRank)) {
	add_entry(Dave,daveRank);	
	add_entry(Jeff,jeffRank);
	add_entry(Ben,benRank);
    }
    else {
	printf("Invalid Input\n");
    }

    // Possible solution Code here
    //   } 
}

void output(Runner *Dave, Runner *Jeff, Runner *Ben) {
    //     while (true) {
    // Possible solution Code here

    struct Node {
	Runner *runner;
	struct Node* next;
    };

    struct Node dave = {Dave, NULL};
    struct Node jeff = {Jeff, NULL};
    struct Node ben = {Ben, NULL};

    dave.next = &jeff;
    jeff.next = &ben;

    struct Node* head = &dave;

    struct Node *prev = NULL;
    struct Node *curr = NULL;
    int swapped = 0;
    unsigned int curr_runner_wins = 0;
    unsigned int next_runner_wins = 0;
    do {
	swapped = 0;
	curr = head;

	while (curr->next != prev) {
	    curr_runner_wins = curr->runner->results[RANKTOIDX(FIRST)];
	    next_runner_wins = curr->next->runner->results[RANKTOIDX(FIRST)];
	    if (curr_runner_wins < next_runner_wins) {
		Runner *tmp = curr->runner;
		curr->runner = curr->next->runner;
		curr->next->runner = tmp;
		swapped = 1;
	    }
	    curr = curr->next;
	}
	prev = curr;
    } while(swapped);


    printf("New Overall Ranks are:\n");
    curr = head;
    while (curr) {
	printf("%s (%d) ",curr->runner->name, curr->runner->results[RANKTOIDX(FIRST)]);
	curr = curr->next;
    }
    printf("\n");

    // Possible solution Code here
    //   }
}

int main() {
    Runner Dave = {
	.name = "Dave",
	.results = {0,0,0}
    };

    Runner Jeff = {
	.name = "Jeff",
	.results = {0,0,0}
    };

    Runner Ben = {
	.name = "Ben",
	.results = {0,0,0}
    };

    while (1) {
	input(&Dave, &Jeff, &Ben);
	output(&Dave, &Jeff, &Ben);
    }  
    return 0;
}

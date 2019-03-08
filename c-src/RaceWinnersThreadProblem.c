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
#include <assert.h>

#define SCHEDULER
#define NUM_RUNNERS 3

typedef enum {
    FIRST = 1,
    SECOND,
    THIRD,
    MAX_RANK = THIRD
}Rank;

#define INRANGE(x) (((x) >= FIRST) && ((x) <= MAX_RANK)) 
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

struct listRunners{
    Runner *runner;
    struct listRunners *next;
};

void add_entry (Runner *runner, Rank rank) {
    if (!runner) {
	printf("%s list member empty\n",__FUNCTION__);
	assert(runner != NULL);
    }
    runner->results[RANKTOIDX(rank)]++;// adds an entry to the key "rank"
}

void input(struct listRunners *runners) {
#if !defined(SCHEDULER)
    while (1) {
#endif
	// Possible solution Code here

	unsigned int daveRank,jeffRank,benRank;
	printf("Enter ranks for Dave, Jeff, Ben respectively\n");
	scanf("%d %d %d",&daveRank,&jeffRank,&benRank);
	//printf("%d %d %d\n",INRANGE(daveRank),jeffRank,benRank);
	// following condition check ensures that Ranks are in 1-3 range, as well as there are no repeats
	if (VALIDRANK(daveRank, jeffRank, benRank)) {
	    struct listRunners* curr = runners;
	    add_entry(curr->runner,daveRank);	
	    curr = curr->next;
	    add_entry(curr->runner,jeffRank);
	    curr = curr->next;
	    add_entry(curr->runner,benRank);
	}
	else {
	    printf("Invalid Input\n");
	}

	// Possible solution Code here
#if !defined(SCHEDULER)
    }
#endif 
}

void output(struct listRunners *runners) {
#if !defined(SCHEDULER)
    while (1) {
#endif
	// Possible solution Code here
	struct listRunners* head = runners;

	struct listRunners *prev = NULL;
	struct listRunners *curr = NULL;
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
#if !defined(SCHEDULER)
    }
#endif
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
    pthread_t threadIn, threadOut;
    int  iret1, iret2;

    /* Create independent threads each of which will execute function */

    struct listRunners runner1 = {&Dave, NULL}; 
    struct listRunners runner2 = {&Jeff, NULL}; 
    struct listRunners runner3 = {&Ben, NULL}; 

    runner1.next = &runner2;
    runner2.next = &runner3;

    struct listRunners* runners = &runner1;

#if defined(SCHEDULER)
    while (1) {
	input(runners);
	output(runners);
    }
#else
    void (*input_function)( struct listRunners* ) = &input;
    iret1 = pthread_create( &threadIn, NULL, (void* (*)(void*))(input_function), (void*) runners);
    void (*output_function)( struct listRunners* ) = &output;
    iret2 = pthread_create( &threadOut, NULL, (void* (*)(void*))(output_function), (void*) runners);

    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */
    pthread_join( threadIn, NULL);
    pthread_join( threadOut, NULL);      
#endif
    return 0;
}

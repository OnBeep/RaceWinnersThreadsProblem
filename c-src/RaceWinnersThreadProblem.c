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

#undef SCHEDULER
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


//Venkat: 1 mutex and a msg passing var
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#define PING 1
#define PONG 2
unsigned int msg = PONG;


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
	// Possible solution Code here
       pthread_mutex_lock(&mutex);

       if(msg != PONG)
       {
           pthread_mutex_unlock(&mutex);
	   continue;
       }
#endif
	unsigned int ranks[NUM_RUNNERS];
	printf("Enter ranks for Dave, Jeff, Ben respectively\n");
	scanf("%d %d %d",&ranks[0],&ranks[1],&ranks[2]);
	// following condition check ensures that Ranks are in 1-3 range, as well as there are no repeats
	if (VALIDRANK(ranks[0], ranks[1], ranks[2])) {
	    struct listRunners* curr = runners;
	    for (unsigned int i = 0; i < NUM_RUNNERS; i++)
	    {
		add_entry(curr->runner, ranks[i]);
		curr = curr->next;
	    }
	}
	else {
	    printf("Invalid Input\n");
	}

	// Possible solution Code here
#if !defined(SCHEDULER)
	msg = PING;
	pthread_mutex_unlock(&mutex);
    }
#endif
}

void output(struct listRunners *runners) {
#if !defined(SCHEDULER)
    while (1) {
        pthread_mutex_lock(&mutex);

	if(msg != PING)
	{
	    pthread_mutex_unlock(&mutex);
            continue;
        }

#endif
	    // Possible solution Code here
	    //
	    //
	    // Venkat: Removed sorting logic here with simple max min tracker
	struct listRunners *curr = NULL;

	printf("New Overall Ranks are:\n");
	curr = runners;
	unsigned int max = 0;
	unsigned int min = curr->runner->results[RANKTOIDX(FIRST)];
	unsigned int equal = 0;
	struct listRunners *max_head = NULL;
	struct listRunners *min_head = NULL;

	//Venkat:Loop to keep track of max min
	while (curr != NULL)
	{
             if (curr->runner->results[RANKTOIDX(FIRST)] >= max)
	     {
		 max = curr->runner->results[RANKTOIDX(FIRST)];
		 max_head = curr;
	     }
             if (curr->runner->results[RANKTOIDX(FIRST)] <= min)
	     {
                 min = curr->runner->results[RANKTOIDX(FIRST)];
		 min_head = curr;
	     }

         curr = curr->next;
	}
        //Reset curr
        curr = runners;

	//Venkat: if min and max are equal, all are equal positions
	if(max_head == min_head)
	       equal = 1;

	//Venkat:Block to print outcomes
	if(max_head != NULL && min_head != NULL)
	{
	  printf("%s (%d) ",max_head->runner->name, max_head->runner->results[RANKTOIDX(FIRST)]);
	  while(curr)
	  {
	      if(curr != min_head && curr != max_head)
	           printf("%s (%d) ",curr->runner->name, curr->runner->results[RANKTOIDX(FIRST)]);
	      curr=curr->next;
	  }

	  if(!equal)
              printf("%s (%d) ",min_head->runner->name, min_head->runner->results[RANKTOIDX(FIRST)]);
	}

	printf("\n");

	// Possible solution Code here
#if !defined(SCHEDULER)
        msg = PONG;
        pthread_mutex_unlock(&mutex);
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

    // Form Linked List of Runner Objects
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
    /* Create independent threads each of which will execute function */
    pthread_t threadIn, threadOut;
    int  iret1, iret2;
    void (*input_function)( struct listRunners* ) = &input;
    iret1 = pthread_create( &threadIn, NULL, (void* (*)(void*))(input_function), (void*) runners);
    void (*output_function)( struct listRunners* ) = &output;
    iret2 = pthread_create( &threadOut, NULL, (void* (*)(void*))(output_function), (void*) runners);

    pthread_join( threadIn, NULL);
    pthread_join( threadOut, NULL);
#endif
    return 0;
}

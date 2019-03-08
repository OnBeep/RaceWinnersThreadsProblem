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

   Implement using C++ Thread Library
   */


#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <atomic>

#define SCHEDULER
using namespace std;


class Runner {
    public:
	string name;
	// <rank, frequency> e.g. {{1,3}, {2,5}, {3,0}} indicates:
	// Runner was first in 3 races, second in 5 races and never finished third
	map<unsigned int,unsigned int> results;
	Runner(const string &n) : name(n), results{{1,0},{2,0},{3,0}}
	{ };
	void operator + (unsigned int rank) {
	    results[rank]++;// adds an entry to the key "rank"
	}
};

void input(list<Runner> &runners) {
#if !defined(SCHEDULER)
    while (true) {
#endif
	// Possible solution Code here

	vector<unsigned int> ranks(3);
	cout <<"Enter ranks for Dave, Jeff, Ben respectively"<<endl;
	cin>>ranks[0]>>ranks[1]>>ranks[2];
	map<unsigned int,unsigned int> possibleRanks{{1,0},{2,0},{3,0}};
	// following condition check ensures that Ranks are in 1-3 range, as well as there are no repeats
	if (possibleRanks[ranks[0]]++ != 1
		&& possibleRanks[ranks[1]]++ != 1
		&& possibleRanks[ranks[2]]++ != 1
		&& runners.size() == ranks.size()) {
	    auto i = 0;
	    for (auto &runner : runners) {
		runner+ranks[i++];
	    }
	}
	else {
	    cout << "Invalid Input" << endl;
	}

	// Possible solution Code here
#if !defined(SCHEDULER)
    }  
#endif
}

bool descending (pair<string, unsigned int> &a, pair<string, unsigned int> &b) { 
    return (a.second>=b.second);
} 

void output(list<Runner> &runners) {
#if !defined(SCHEDULER)
    while (true) {
#endif
	// Possible solution Code here

	vector< pair<string, unsigned int> > winners; // data structure that holds count of Races where Runner Won
	for (auto &runner : runners)
	    winners.push_back(make_pair(runner.name, runner.results[1]));

	sort(winners.begin(), winners.end(), descending); // sort by number of Races Won from Most to Least

	for (auto &winner : winners) { // print the Sorted order
	    cout << winner.first <<" (" <<winner.second << ") ";
	}
	cout<<endl;

	// Possible solution Code here
#if !defined(SCHEDULER)
    }
#endif
}

int main() {
    Runner Dave("Dave");
    Runner Jeff("Jeff");
    Runner Ben("Ben");

    list<Runner> runners {Dave, Jeff, Ben};
#if defined(SCHEDULER)
    while (true) {
	input(runners);
	output(runners);
    }
#else 
    auto threadIn = std::thread(input, std::ref(runners));
    auto threadOut = std::thread(output, std::ref(runners));

    threadIn.join();
    threadOut.join();
#endif
    return 0;
}

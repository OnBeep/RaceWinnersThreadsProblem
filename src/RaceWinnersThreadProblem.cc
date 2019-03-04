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

using namespace std;


class Runner {
public:
    string name;
    // <rank, frequency> e.g. {{1,3}, {2,5}, {3,0}} indicates:
    // Runner was first in 3 races, second in 5 races and never finished third
    map<unsigned int,unsigned int> results;
    Runner(const string &n) : name(n), results{{1,0},{2,0},{3,0}}
    { };
    void operator + (unsigned rank) {
        results[rank]++;// adds an entry to the key "rank"
    }
};

void input(Runner &Dave, Runner &Jeff, Runner &Ben) {
     while (true) {
	// Possible solution Code here
        
	unsigned int daveRank,jeffRank,benRank;
        cout <<"Enter ranks for Dave, Jeff, Ben respectively"<<endl;
        cin>>daveRank>>jeffRank>>benRank;
        map<unsigned int,unsigned int> possibleRanks{{1,0},{2,0},{3,0}};
	// following condition check ensures that Ranks are in 1-3 range, as well as there are no repeats
        if (possibleRanks[daveRank]++ != 1
            && possibleRanks[jeffRank]++ != 1
            && possibleRanks[benRank]++ != 1) {
            Dave+daveRank;
            Jeff+jeffRank;
            Ben+benRank;
        }
        else {
            cout << "Invalid Input" << endl;
        }

	// Possible solution Code here
     }  
}

bool descending (pair<string, unsigned int> &a, pair<string, unsigned int> &b) { 
    return (a.second>=b.second);
} 

void output(Runner &Dave, Runner &Jeff, Runner &Ben) {
     while (true) {
	// Possible solution Code here
        
        vector< pair<string, unsigned int> > winners; // data structure that holds count of Races where Runner Won
        winners.push_back(make_pair(Dave.name, Dave.results[1]));
        winners.push_back(make_pair(Jeff.name, Jeff.results[1]));
        winners.push_back(make_pair(Ben.name, Ben.results[1]));

        sort(winners.begin(), winners.end(), descending); // sort by number of Races Won from Most to Least

        for (auto &runner : winners) { // print the Sorted order
            cout << runner.first <<" (" <<runner.second << ") ";
        }
        cout<<endl;

	// Possible solution Code here
     }
}

int main() {
    Runner Dave("Dave");
    Runner Jeff("Jeff");
    Runner Ben("Ben");

    auto threadIn = std::thread(input, std::ref(Dave), std::ref(Jeff), std::ref(Ben));
    auto threadOut = std::thread(output, std::ref(Dave), std::ref(Jeff), std::ref(Ben));

    threadIn.join();
    threadOut.join();
    
    return 0;
}

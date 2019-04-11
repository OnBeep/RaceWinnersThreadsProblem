# RaceWinnersThreadsProblem
Program using Thread Library that prints overall Ranking of winners from Races after every input 

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
   
# Implementation Guidelines (please read carefully before proceeding)
Core Implementation is provided to you. You would need to add only a few lines to complete the Solution.
 
Your soulution needs to run smoothly without any Aborts or Exceptions, out of control output
 
You would have to ensure that your Threaded Solution matches Expected Behavior as observed by running a debug Scheduler (explained later in this readme)
    
Input (sample to be supplied by Orion at the end of readme. Orion will test your solution for additional inputs):
   
 There are 2 threads:
   - "input" thread that consumes the Race result
   - "output" thread that computes Overall Ranks and prints them
 
 We think you may not need any other standard libraries than already included in the programs
 
 You can NOT modify main() 

# Building the Program

For C++
g++ -std=c++11 RaceWinnersThreadProblem.cc -o RaceWinnersThreadProblem

For C
gcc -lpthread RaceWinnersThreadProblem.c -o RaceWinnersThreadProblem

# Debugging without Threads (aka Scheduler)
It is possible to build the Programs with a debug flag SCHEDULER, which can be defined in the source file(s). The Scheduler eliminates threads and lets you run the program with classic infinite loop scheduler. This is a good way to understand how the program is expected to behave. 
The Objective is to have your Thread solution match the behavior of Scheduler

# References

C++ Thread Library
http://www.cplusplus.com/reference/thread/thread/

C++ Atomic Operations
https://en.cppreference.com/w/cpp/atomic/atomic

C Posix Thread Support
https://en.wikipedia.org/wiki/POSIX_Threads

C Atomic Operations
https://gcc.gnu.org/onlinedocs/gcc-4.4.5/gcc/Atomic-Builtins.html

# Running the Program

Run the executable: ./RaceWinnersThreadProblem

# Expected Behavior (with sample input)
./RaceWinnersThreadProblem

Enter ranks for Dave, Jeff, Ben respectively

3 1 2

Jeff (1) Ben (0) Dave (0) 

Enter ranks for Dave, Jeff, Ben respectively

1 2 3

Jeff (1) Dave (1) Ben (0) 

Enter ranks for Dave, Jeff, Ben respectively

3 2 1

Ben (1) Jeff (1) Dave (1) 

Enter ranks for Dave, Jeff, Ben respectively

2 3 1

Ben (2) Jeff (1) Dave (1) 

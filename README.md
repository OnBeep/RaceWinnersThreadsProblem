# RaceWinnersThreadsProblem
Program using Thread Library that prints overall Ranking of winners from Races after every input 

# Building the Program

For C++
g++ -std=c++11 RaceWinnersThreadProblem.cc -o RaceWinnersThreadProblem

For C
gcc -lpthread RaceWinnersThreadProblem.c -o RaceWinnersThreadProblem

# Debugging without Threads (aka Scheduler)
It is possible to build the Programs with a debug flag SCHEDULER, which can be defined in the source file(s). The Scheduler eliminates threads and lets you run the program with classic infinite loop scheduler. This is a good way to understand how the program is expected to behave. 
The Objective is to have your Thread solution match that of Scheduler

# References

C++ Thread Library
http://www.cplusplus.com/reference/thread/thread/

C++ Atomic Operations
https://en.cppreference.com/w/cpp/atomic/atomic

C Posix Thread Support
https://en.wikipedia.org/wiki/POSIX_Threads

C Atomic Operations
https://gcc.gnu.org/onlinedocs/gcc-4.4.5/gcc/Atomic-Builtins.html

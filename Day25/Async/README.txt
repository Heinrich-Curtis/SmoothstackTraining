Program that implements parallel accumulate using std::async and std::promise
INSTALLATION INSTRUCTIONS
-------------------------------------------------------------------------------
navigate to this directory, run make, run the executable. The program prints 
some messages to STDOUT and checks that my algorithm returns the same result
as std::accumulate.

STATUS
-------------------------------------------------------------------------------
Complete. All the required functionality is implmented and valgrind reports no
leaks or memory issues. Really all I did was make small changes to return types
and container types to get this program to use std::async instead of threads.

ISSUES
-------------------------------------------------------------------------------
None
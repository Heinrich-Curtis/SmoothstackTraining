This program demonstrates compiling and running separate targets with a
makefile, using the GoogleTest testing suite, and a type that allows us
to avoid issues with integer overflow.

INSTALLATION INSTRUCTIONS-----------------------------------------------------
--------------------------------------------
Navigate into LongMult, run cmake on the CMakeLists.txt file, run make,
then run make. To run the program, run the executable LongMult; to run
the tests, run the execuatable runTests.

STATUS
------------------------------------------------------------------------------

Incomplete. I have all the google test stuff working, and the most basic
functionality is implmented in LongMult.cpp right now. I'm in the middle of
adding the extended functionality (the more elaborate clas BigNumber that does
all the overflow protection) and I'm just getting stuck on little stuff a lot.
I recently completed my symbAdd method (which will be used to get the final 
solution from the partial sums created by multiply), but I still need to 
actually get multiply and simulate multiply working.

To see the current tests of fully implemented functionality, use "make runTests" and 
then run runTests

 KNOWN ISSUES
------------------------------------------------------------------------------
Just getting stuck a lot and going slow, no total stops yet.

Right now, symbAdd doesn't check to see if we've overflowed the array (the sum
is a 65-digit number). I'll address this in the near future.

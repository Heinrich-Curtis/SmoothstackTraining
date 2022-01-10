This program demonstrates compiling and running separate targets with a
makefile, using the GoogleTest testing suite, and a type that allows us
to avoid issues with integer overflow.

INSTALLATION INSTRUCTIONS-----------------------------------------------------
--------------------------------------------
Navigate into LongMult and run the following commands:

cmake CMakeLists.txt
make

To run the program, run the executable LilMult; to run
the tests, run the execuatable runTests.

STATUS
------------------------------------------------------------------------------

Complete. All the required functionality is implemented (sometimes more than once), and there are no memory leaks (valgrind reports no errors or leaks).

KNOWN ISSUES
------------------------------------------------------------------------------

I don't actually check if we've overflowed the type (the product has more than 64 digits). In addition, I probably needed to do more thorough testing on negative values. But I'm glad I got all the required functionality completed.

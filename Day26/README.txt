Program that implements a parallel version of std::any_of and an async version
of std::none_of
INSTALLATION INSTRUCTIONS
-------------------------------------------------------------------------------
navigate to this directory, run make, run the executable. The program will 
perform some asserts and print some messages to stdout.

STATUS
-------------------------------------------------------------------------------
Complete. All the required functionality is implmented and valgrind reports no
leaks or memory issues.

ISSUES
-------------------------------------------------------------------------------
None. Had a bit of a struggle with the multiple negatives involved in getting
aNoneOf's logic right, but I got there after an hour or so.
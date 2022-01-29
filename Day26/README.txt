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

The best case complexity for both of the algorithms is a hazy O(1): for both
functions, this is when the first element of the first threads to run happen
to return true from the predicate, then it flips the flag and every other 
spawned thread exits in their first iteration. This happens in my code with
the predicate lessThan25000: the first element of every single block sent
to the threads meets this predicate, so the first threads to make it to the
predicate call flips the flag (actually probably most of the threads
flip the flag once, but they just keep setting it to true), and they all return
by the next iteration.

The worst case complexity for both is ~O(n) where n is the size of a block
sent to the threads. This occurs for both functions when none of the elements
in the container cause the predicate to return true (in my code, the predicate
moreThan25000: every single element must be checked to look for any that return
true).

ISSUES
-------------------------------------------------------------------------------
None. Had a bit of a struggle with the multiple negatives involved in getting
aNoneOf's logic right, but I got there after an hour or so.
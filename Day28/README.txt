A program that uses the generator pattern(?) with co-routines to generate
some bank transactions
INSTALLATION INSTRUCTIONS
-------------------------------------------------------------------------------
navigate to this directory, run make, run the executable. Note that you have to
have the appropriate compiler installed (g++-11), the normal one won't 
recognize the coroutines features.

STATUS
-------------------------------------------------------------------------------
Complete. The coroutines machinery works and the data is formateed correctly.
Valgrind reports no memory issues among 127 heap allocations, which is due to
the heap usage by the coroutines as I understand it.

ISSUES
-------------------------------------------------------------------------------
For some reason, I get a compiler error from the coroutines header:"coroutines
header requires -fcoroutines"; I do have the -fcoroutines switch in my Makefile
and I've moved it around a couple places to try to make that error go away with
no success. Despite the error, the program actually compiles and runs fine, so
I'm not sure what the issue is.
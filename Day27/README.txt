Program that performs a matrix multiply using OpenMP to parallelize the
task.

INSTALLATION INSTRUCTIONS
-------------------------------------------------------------------------------
navigate to this directory, run make, run the executable. The program will 
perform some asserts and print some messages to stdout.

STATUS
-------------------------------------------------------------------------------
Complete. The required functionality is implemented with OpenMP.Valgrind 
reports no memory leaks, but it does see a memory error I think is caused
by openMP, details below.

ISSUES
-------------------------------------------------------------------------------
Valgrind reports some memory errors when I have the openMP directives enabled
(the pragma statements). The specific error I'm seeing is 
"Syscall param sched_setaffinity(mask) points to unaddressable byte(s)". when
I comment the pragmas out, the error goes away.

I couldn't get the code provided in the slides (with the flattened matrices)
to work, the multiply kept coming out wrong. I just decided to revert back 
to my known element-by-element algorithm to get it working with OpenMP, and
I'll try to figure out what the issue is with the flattening code in the future




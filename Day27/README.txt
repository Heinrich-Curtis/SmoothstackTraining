Program that performs a matrix multiply using OpenMP to parallelize the
task.

INSTALLATION INSTRUCTIONS
-------------------------------------------------------------------------------
navigate to this directory, run make, run the executable. The program will 
perform some asserts and print some messages to stdout.

STATUS
-------------------------------------------------------------------------------
Incomplete. I haven't implemented the case yet with the non-square matrices.

ISSUES
-------------------------------------------------------------------------------
I couldn't get the code provided in the slides (with the flattened matrices)
to work, the multiply kept coming out wrong. I just decided to revert back 
to my known element-by-element algorithm to get it working with OpenMP, and
I'll try to figure out what the issue is with the flattening code in the future


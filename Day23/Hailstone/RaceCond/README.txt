A Program that creates a race condition between 3 threads trying to update a shared data structure

INSTALL INSTRUCTIONS
-------------------------------------------------------------------------------
Navigate here, run make.
To run the executable, pass an integer as an argument (ie, './virtual_ref 112')

STATUS
-------------------------------------------------------------------------------
Complete. The desired behavior exists. For certain small inputs, the program 
returns fine (this is probably when only one thread gets to run). If for 
certain larger values, like 220, you get non-deterministic behavior: sometimes
you explicitly get a seg fault immediately, which probably means that the 
threads overflowed the fixed buffer I use to store the sequence. Sometimes, 
the program does not return immediately, which is probably the threads writing 
lots of values because they're not coordinating with each other. And on rare
occasions, the program actually completes and prints the output: when this
happens, sometimes you can inspect the sequence and see that the invariant
hasn't been violated, and sometimes it has (sometimes the sequence 
reaches 1 but doesn't end, which shouldn't happen the way I wrote the program,
and sometimes the sequence doesn't print all the way down to 1 because the 
nextInd member of the shared structure hasn't been updated correctly).

ISSUES
-------------------------------------------------------------------------------
None, except the intended behavior that the program only completes about 
25% of the time.

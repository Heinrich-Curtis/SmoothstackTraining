Program that solves an n-body problem by representing each body with a thread
that calculates its force and updates its own fields every iteration.

INSTALLATION INSTRUCTIONS
-----------------------------------------
Navigate here, run make, run executable. The program will run for about a 
minute and then produce output.json with the bodycount and ips data.

The data for running this version of the program is in output.json. For easy
comparison, the data for running older versions are in the jsons with the day
names.

STATUS
--------------------------------------------
Complete. All the required functionality is implemented and valgrind reports
no memory issues (sort of, more details below).
ISSUES
----------------------------------------------
If I run the program and limit it to the first 4 entries in the number of
bodies (200 or less), valgrind returns fine and reports no memory errors
or leaks. If I include any experiment beyond that (the first next largest
test is n=500), valgrind crashes and dumps a lot of stuff to the terminal.
I assume the issue is that valgrind's instrumentation has an issue with 
having so many threads. Also, If I ask for very large n's, I can get the 
OS to kill my process (after running for a while, the message "killed" is
printed to the terminal). My program was able to handle 10000 threads, but 20000
was killed.

ANALYSIS
------------------------------------------------------
The approach I went with for syncing was just to use 2 pthread_barriers so
I was sure that all the threads a) updated their internal force vectors using
the data from the current step of all other bodies, and b) updated their own
internal state at the same time. I tried to use std::barrier, but soemthing
is wrong with my includes or something and the header file couldn't be 
found; I have to look into this.

Note that I also did a run of the program where I removed one of the barriers, 
the output from this run is "oneBarrier.json". We see that the performance
increases as expected (there are half as many sync points), but this comes
at the cost of correctness because we can't be sure if some bodies may be 
altering their interal members as other threads are still attempting to access
them.

There were 3 trends I noticed when comparing the data from this iteration of
the program to previous iterations:
-The general trend in IPS efficiency of the program from previous iterations 
 of the program holds true for this version: the IPS increases as the number of
 bodies increases.
 -This version of the program performs WORSE than the single threaded program
  for small n, because the cost of initializing and syncing the threads isn't paid
  for by giving the threads each enough work. As n grows, the parallel version
  begins to have better IPS efficiency.
-This version of the program begins to plateu at the higher end (you can see
 the magnitude of the increase between successive n's is getting smaller). This
 is happening because as n gets really large, the cost of frequently syncing the
 threads and the operating system attempting to schedule all the threads fairly 
 is starting to hamstring the performance gains from concurrency. 

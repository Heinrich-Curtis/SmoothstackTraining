This program demonstrates a deadlock when trying to run a multi-threaded
program (the program hangs). This is how I know the program is deadlocked:
-I run the program with GDB and it never returns
-I kill the program with CTRL-C, then I inspect the threads using the 
 command "info threads"
-I see that BOTH of my spawned threads are at a function call that looks like
 ""ll_lock_wait", both of them are waiting on locks to be released.

In particular, the reason this program deadlocks is because in my "makeRequest"
function for country, I make a country secure their own lock and then attempt
to get their partner's lock. If more than one country attempts this at the same
time, a deadlock is guaranteed.
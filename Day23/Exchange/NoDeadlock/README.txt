This program demonstrates the same program from the deadlock folder, except This
one doesn't deadlock. I achieve this by having each country only get one lock at
a time.

INSTALLATION INSTRUCTIONS
----------------------------------------------
navigate here, make, run executable

STATUS
-----------------------------------------------
Complete. The two countries complete 4 trades without deadlocking
, the adjusted currency balances are correct and the program exits.

I prevent deadlocks by making sure that each thread only holds one lock at at
a time; actions inside the locks are only what is necessary to disambiguate 
exactly which state the thread is in. I just have each thread randomly
accept or reject an incoming request.

ISSUES
-----------------------------------------------
I don't put any locks on cout so sometimes the output is garbled, but all
the messages show and the program returns.One interesting thing to note is
that it seems the threads either accept all the trades, or reject all the
trades, I haven't seen a mix of accepts and rejects yet.I bet this is related
to the function doIAccept being static instead of per object.
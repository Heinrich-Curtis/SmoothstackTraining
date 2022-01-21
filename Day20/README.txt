Program that uses lambdas to solve an n-body problem using only
half the operations of the Day19 version
INSTALLATION INSTRUCTIONS
-----------------------------------------
Navigate here, run make, run executable. The program will run for about a 
minute and then produce output.json with the bodycount and ips data.

The data for running this version of the program is in output.json. For easy
comparison, the data for running the Day19 version of the program is in 
oldOutput.json; you can see about a 25% speedup of this version over the old
one.

STATUS
--------------------------------------------
Complete. All functionality is implmented and valgrind reports no 
memory issues. I do notice that this version of the program has about a 
~25% speedup when comparing IPS numbers of this program and Day 19's program.
I was expecting more to be honest, but I would need to look a lot longer at
my algorithms to figure out where the inefficiency is and the best way to
address it; it's probably related to how I determine when to not do operations.

ISSUES
----------------------------------------------
The idea behind this optimization is very simple: when we find the force 
exerted on body a by b, we simply save the negative version of the force (by
negating each force component), into the spot for b's force from a. So since
each body resides in a container at index i, and the force from body b is
stored in an internal array at index j corresponding to the index in the 
original container, whenever we update container[i][j], we immediately save
the negated result to container[j][i]. Then instead of iterating over the 
entire container in both loops, the inner loop only iterates over elements
where j >= i to skip half the calculations.

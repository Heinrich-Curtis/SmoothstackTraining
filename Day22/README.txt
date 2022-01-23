Program that uses lambdas to solve an n-body problem using only
half the operations of the Day19 version
INSTALLATION INSTRUCTIONS
-----------------------------------------
Navigate here, run make, run executable. The program will run for about a 
minute and then produce output.json with the bodycount and ips data.

The data for running this version of the program is in output.json. For easy
comparison, the data for running older versions are in the jsons with the day
names.
STATUS
--------------------------------------------
Mostly complete. I was a little confused as to exactly what was being asked
here, so what I went with was running my program with each experiment on a
different thread (8 threads), and comparing the IPS values with the results
from past experiments.

I do see an approximately 7 fold speedup when running with 8 cores, which is 
close to the ideal linear speedup of 8. Watching the program run in GDB, the 
first 5 threads return nearly instantly, the 6th thread returns after a couple
seconds, and the final 2 threads take significantly more time to return. 
ISSUES
----------------------------------------------
I didn't entirely complete this assignment, but I got my program working 
multi-threaded, so there's that.

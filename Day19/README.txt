Program that uses lambdas to try and solve an n-body problem
INSTALLATION INSTRUCTIONS
-----------------------------------------
Navigate here, run make, run executable. The program will run for about a 
minute and then produce output.json with the bodycount and ips data.

STATUS
--------------------------------------------
Complete. I misread the assignment and got hung up on certain physics issues
I was having. After re-reading the assingment, I realized none of the stuff
I was focused on was necessary, so I added the final count lambda and I'm
done. Valgrind reports no errors or leaks.

ISSUES
----------------------------------------------
None relevant to this submission. The below are some problems I'm interested
in investigating on my own time:

For some reason, the velocity of a body is getting "locked" to a certain value
after a couple hundred timesteps even though the acceleration keeps changing.
I'm looking into why this is happening. On the bright side, I am seeing
"orbiting" type behavior, so that's good.

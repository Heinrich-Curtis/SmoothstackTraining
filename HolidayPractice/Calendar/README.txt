This program mimics some of the functionality of the unix cal program; it
displays a visual representation of a requested calendar.

INSTALLATION INSTRUCTIONS
------------------------------------
navigate to this directory, run make, then run the executable with appropriate
arguments (not providing appropriate arguments will result an invocation
message being printed to terminal).

STATUS
--------------------------------------
Incomplete right now, but my computer just started making weird noises
and it's kind of scaring me.

ISSUES
---------------------------------------
None so far


DISCUSSION QUESTIONS
---------------------------------------
2. Testing on member functions soon(tm)

3. My program is verified for leap years, that's what the isLeapYear function
does.

4. My program works for any time, even outside the unix epoch, because it's based on Zeller's Algorithm. I never make any calls to unix functions as part of my program, so I'm not limited by them.

5. Valgrind reports a clean run, no memory errors or leaks.

Program that uses lambdas to try and solve an n-body problem
INSTALLATION INSTRUCTIONS
-----------------------------------------
Navigate here, run make, run executable

STATUS
--------------------------------------------
Mostly complete. All of the required lambdas are implemented (they're 
anonymous and defined inside of body's methods), and I've got a method that
dumps information about the bodies to an ostream in a format recognizable 
by a JSON parser. I'm still doing some bugfixing, but all of the major
implementation is done. Once I get the bugs fixed in my 1d tests, I'm confident
they will operate correctly in 2d.

ISSUES
----------------------------------------------
The gravitational force between two objects is currently not changing with the 
square of the distance between them and I'm investigating why that is.

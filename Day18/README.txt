Program that defines and tests a type MyVec that replicates much of std::vector
an adjustable size array.
INSTALLATION INSTRUCTIONS
-----------------------------------------------------
navigate to this directory, run make, run the executable. The output from the
tests go to console
STATUS
-------------------------------------------------------
Complete. All required behavior has been implemented and tested. I chose to 
double the size of the internal array on it filling up, since I believe that's the behavior std::vector uses to achieve amortized-constant-time behavior.

As a final test of the iterators, I actually use the c++17 "for each" style
of loop, which works because my container has the methods "begin()" and 
"end()" return valid iterators to the container. That's pretty neat.

ISSUES
-------------------------------------------------------
I'm not really sure if I should be throwing exceptions, but I feel like it's 
the right thing to do in the out of bounds situations, I'll look at what
std::vector does. I'm also not really sure what mUndefined was meant to do. 
Maybe I'm meant to make mUndefined a special version of T that gets 
returned in an exceptional situation? I feel like that puts too much burden
on the user to check for that particular value to be retured. I'll look
at how some stl containers use that undefined value.

Otherwise, no issues.
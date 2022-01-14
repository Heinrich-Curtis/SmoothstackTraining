This program demonstrates the use of template functions and classes to make an account type that
can hold one of a couple different types of currency,and allow you to deposit and withdraw in 
multiple currencies.

INSTALLATION INSTRUCTIONS
----------------------------------------------------------------------
navigate to this directory, run make, and run the executable. the main
function runs all the tests.

STATUS
------------------------------------------------------------------------
Basically complete. The only thing not totally done is converting from non
USD currencies into each other, I think need to put a boolean flag in it
or something to get function overload resolution to stop complaining

ISSUES
-------------------------------------------------------------------
I don't do as much checking on the results of the floating point arithmetic
as I should, but I spent most of my time making sure the templating worked.

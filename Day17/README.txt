This program demonstrates the use of template functions and classes to make an account type that
can hold one of a couple different types of currency,and allow you to deposit and withdraw in 
multiple currencies.

INSTALLATION INSTRUCTIONS
----------------------------------------------------------------------
navigate to this directory, run make, and run the executable. the main
function runs all the tests.

STATUS
------------------------------------------------------------------------
Mostly complete, still need to finish testing. 

ISSUES
-------------------------------------------------------------------
The following is a list of things I don't have implemented that I want to 
get done with a little more time, probably this weekend. I was just focused
on getting the templating working.

I don't do as much checking on the results of the floating point arithmetic
as I should.

My withdraw method doesn't check if there's enough money in the account to make the withdrawal and that's probably where that logic should be.

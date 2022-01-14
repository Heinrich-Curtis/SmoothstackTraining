This program demonstrates the use of template functions and classes to make an account type that
can hold one of a couple different types of currency,and allow you to deposit and withdraw in 
multiple currencies.

INSTALLATION INSTRUCTIONS
----------------------------------------------------------------------
navigate to this directory, run make, and run the executable. the main
function runs all the tests.

STATUS
------------------------------------------------------------------------
Mostlycomplete. The only thing not totally done is converting from non
USD currencies into each other, I think need to put a boolean flag in it
or something to get function overload resolution to stop complaining. My
comparison operators also aren't doing quite what I want them to do yet.

ISSUES
-------------------------------------------------------------------
The following is a list of things I don't have implemented that I want to 
get done with a little more time, probably this weekend. I was just focused
on getting the templating working.

I don't do as much checking on the results of the floating point arithmetic
as I should.

I don't have converters for Dollars back to other currencies, I was scratching
my head a little about getting the overload resolution to work, I think I
want to use some kind of enum flag that's in the coverter object.

My withdraw method doesn't check if there's enough money in the account to make the 
withdrawal and that's probably where that logic should be.

The logic for withdraw and deposit isn't working the way I intend it to. What 
should happen is that, when the account balance type and the deposit currency
type are the same, there shouldn't be any conversion, but looking in GDB after
a compiler error, I noticed I'm still taking the conversion branch anyway. I 
must be using typeid wrong.

RUN INSTRUCTIONS
------------------------------
Navigate to the working directory, run make, run the executable (virtual_ref)

STATUS
-------------------------------
Incomplete. All the required functionality is implemented and tested besides
the rvalue temporary operator, which passes the test but I don't think it's
implemented correctly.

ISSUES
------------------------------
There are 2 warnings about preventing copy elision, but that behavior is
intended.

I haven't been able to get the final operator to work exactly as the asserts 
are written in the assignment yet. I tried having the operator return a
char* to the spot in data where the string begins, but that doesn't work because
the thing it's being compared to (even a temporary) lives somewhere else so
the pointer comparison would fail. So now I'm working on getting the operator 
 to return an rvalue of type MyString, but I can't get something right: 
currently, the function returns a copy of a MyString, which passes the test
but is not the required behavior.

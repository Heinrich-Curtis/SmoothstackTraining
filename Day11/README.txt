This program creates a sentence type with a bunch of constructors and operators
to show off that functionality.

RUNNING THE PROGRAM
--------------------------
Navigate into working directory, run make, then run the executable virtual_ref

STATUS
--------------------------
Complete, all the required functionality exists and the main function tests
all of it (each operator and constructor prints to stdout when it is called).
There are no memory issues reported by valgrind. 

ISSUES
--------------------------
There is a single warning about how using std::move (when I'm testing the move
constructor)prevents copy elision by the compiler. After looking into the flag 
(-Wpessimizing-move) that gets thrown, I've decided that that is nothing to
worry about and actually is precisely what I mean to do (move an rvalue
reference). This did require me to disable the -Werror flag I normally have
on in my Makefile though.


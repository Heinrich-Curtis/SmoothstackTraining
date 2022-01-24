A Program that allows 3 threads to update a shared data structure with no race conditions

INSTALL INSTRUCTIONS
-------------------------------------------------------------------------------
Navigate here, run make.
To run the executable, pass an integer as an argument (ie, './virtual_ref 112')

STATUS
-------------------------------------------------------------------------------
Complete. The only difference between this program and the one in /RaceCond
is that this program uses a mutex to protect the data structure, so the 
invariant of the sequence is always preserved. Otherwise, the two programs
are identical.

ISSUES
-------------------------------------------------------------------------------
None

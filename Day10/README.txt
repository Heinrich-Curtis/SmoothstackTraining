I just wanted to note that the way I do it here is incredibly inefficient due
to some of the restrictions in the problem statement. The way I would like to
implement getPerson would be to search the array for a name, and on finding it,
just increment that count and return that pointer.

I only delete at the end because I was sad valgrind was telling me I had memory
leaks, even though I know the process ends so all the heap memory gets recovered
anyway. 

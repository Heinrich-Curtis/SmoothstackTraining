This program re-uses the classes from Day13 and swaps out the main file to
show some properties of polymorphic types.

INSTALLATION INSTRUCTIONS
---------------------------------
navigate to directory, run make, run executable to see output of tests. The 
tests print output to the screen that explain each behavior, you can also just
read them in the code, but here they are again:

	struct F is copy assignable because the implicit copy assignment 
	operator is added to it
	
	int is copy assignable becausee all primitives are copy-assignable
	
	int[] is not copy-assignable because because arrays are const 
	pointers,which means they're not move-assignable, which means they're 
	not copy-assignable

	Struct G is not copy assignable because I explicitly deleted the copy 
	assignment operator from it's definition

	Class H is not copy-assignable becasue I made its copy assignment 
	operator private, which means it can't be accessed by function 
	resolution for the operator


	A pointer of type quadrilateral calls the appropriate methods when 
	pointing to a rectangle versus a square, two classes that derive from 
	quadrilateral.
	

STATUS
----------------------------------
Complete. Valgrind reports not memory issues or leaks.

ISSUES
----------------------------------
None, this was an easy one.

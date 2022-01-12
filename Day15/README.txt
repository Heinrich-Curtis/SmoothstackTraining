This program demonstrates the use of user-defined exceptions to make sure that 
a function only compares two floats if they are both representable as integers

INSTALLATION INSTRUCTIONS
---------------------------------
navigate to directory, run make, run executable to see output of tests. The 
tests print output to the screen that explain each behavior, you can also just
read them in the code

STATUS
----------------------------------
Complete. Valgrind reports not memory issues or leaks. The program calls
std::terminate when it should.

ISSUES
----------------------------------
I get a pair of compiler warnings becasue I put the noexcept specifier on 
compareFloats(), but then I explicitly have a throw expression inside the
body of the function. Obviously this is intentional to have the required
behavior.

Program that shows some features of streams, like iterating through them
and providing formatting

INSTALLATION INSTRUCTIONS
-------------------------------------------------
navigate to directory, run make, run the executable. The tests are just
a series of asserts that run before the prompt shows up, you can look
at them in main.cpp.

STATUS
-------------------------------------------------
Complete. All the required functionality is there
and tested.

ISSUES
-------------------------------------------------
I know that my program doesn't currently handle negative numbers. I also
know that it doesn't handle any variable white spacing (for instance, typing
"127+0x1" will result in an error, as will " 127 + 0x1", etc.). To remedy this
I would just need to make some small changes in part of the code that 
tokenizes the input string. The processInput function is also really ugly and 
repetitive; if I ever have a reason to re-visit this code, I would try to 
modularize more, maybe with an enum that defines the number types and or the 
operation so I call appropriate conversions on the input.

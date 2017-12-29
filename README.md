# FlipFlopConversionUsingQuineMc
A C/C++ Program to convert one flip flip into another creating a truth table and finding the equations in the process.

The variables deductions are done using the Quine McCluskey method(specifically based on this https://arxiv.org/pdf/1410.1059).
I have corrected a few bugs in the process in the code provided in it and added methods to deallocate dynamic memory allocated using malloc.
Students interested in only the Quine McCluskey method can download/refer only the quinemclusky.cpp file.

Description about the files:

1.  quinemclusky.cpp - contains most of the important logic and the actual programming implementation of Quine-McClusky.
2.  quinemclusky.h   - Header file corresponding to quinemclusky.cpp
3.  main.cpp         - the file containing the main method(does nothing but calls all methods declared in quinemclusky.h and defined in                          quinemclusky.cpp)

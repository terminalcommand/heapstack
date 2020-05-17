# heapstack
 An experiment in implementing a stack structure in heap using linked lists

# Motivation
This was entirely made for fun, the library is highly experimental. Due to automatic stack management in C, there may be some bugs. I intend to write a simple mark-and-sweep GC and move everything to the heap. But that's for a different project. 

# Requirements
Heapstack requires [clinked](http://github.com/terminalcommand/clinked), my modern linked list library for C. 

# What is this good for?
I was able to write a simple RPN calculator using this library. It supports basic push and pop operations. There is a variadic function to initialize new lists, which I think is cool :).

RPN calculator example is located under [examples/simplerpn.c](http://github.com/terminalcommand/heapstack/examples/simplerpn.c).

~~~~
SimpleRPN.exe
Please enter the expression to be evaluated: 34 4 + 99999 /
The input was: 34 4 + 99999 /
Parsing the input string '34 4 + 99999 /'
The result of the operation is: 0.000380
~~~~


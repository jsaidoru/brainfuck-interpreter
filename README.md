# brainfuck-interpreter
A simple **brainfuck** interpreter written in **C++** with **basic bounds checking** and **edge case handling**. This is just a small project I made when getting bored, so I'd say it's completed and I don't plan to extend or optimize it.

It has a 1-megabyte memory array be default. The size of the array can be changed using the command-line arguments.
# Usage
Compile the `main.cpp` file (or just use the precompiled .exe if you are using Windows) and run the executable file: `<executable filename> <code filename> <memory array size (in byte)(optional)>`. The minimum C++ version for this interpreter is C++11.

Input (using the `,` command) is accepted from stdin (standard input). The interpreter should check for EOF, but it doesn't work sometimes. Only input one character per `,` command.
# Learning brainfuck
Refer to the article about brainfuck in Wikipedia: https://en.wikipedia.org/wiki/Brainfuck, it shouldn't be difficult to understand if you have basic programming knowledge.
# Contributing
I will not accept pull requests and issues.
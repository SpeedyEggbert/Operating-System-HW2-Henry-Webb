# Operating-System-HW2-Henry-Webb

A Program that implement, and tests the bankers alogrithem

Written in C++

## How to run

Complies and runs on both Windows and Linux

The data.txt file must be in the same spot as banker.cpp for it to work.

## What it does

The program reads off text file all the info about the state of five diffrent "processes" and the "memory".
Using this data it uses the bankers algoritem to find the safe sequence, if it exists and outputs it out in the terminal

The data file is a row of 6 sets of numbers, the first five rows represent process number P0, P1, ... P4, the first 3 numbers are the allocated (A, B, C) while the last 3 are the max. The final line represents the memory and what resources are available.

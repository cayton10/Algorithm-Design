# Greedy Algorithm

From assignment outline:

Spring 2021

## Summary

The CIT department has three computer labs: ML119, ML122, and WAEC1104. 
We need to schedule a number of CIT and NRE classes into these labs. For 
this assignment, we will use a simplified version of the schedule in 
which each class runs MWF or TR. We need to assign classes to rooms so 
that:

* Every class is assigned to one room.
* The capacity of the room is at least as large as the maximum size of 
  the class.
* There are never two classes in the same room at the same time.

An assignment is valid if it has these properties. 

## Goal 

The goal of the project is to write a C++ program that takes information
about the classes and rooms as input, and produces a valid schedule to 
assign the classes into rooms. 

## Input

I have prepared an example input file in JSON format. You can use this
library to easily parse JSON into C++: https://github.com/nlohmann/json

The input file has the starting and ending times of each class as well
as the number of students the class can hold. The input also has a
list of rooms with the size of each room.

## Requirements

* The program must produce a valid assignment if there is one, or
  say there is no valid assignment if there is not any way to make
  a valid assignment.
* The code should follow best practices for C++ coding. Try to make
  the code very polished. 
* The program can simply output the schedule to the standard output as
  a list of classes and rooms. 

## Non-requirements

At this stage, we are not trying to "optimize" the assignment in any way.
There are several possible ways we could try to optimize it, which would
make the problem much more involved. 
# CS509 Laboratory Repository

## Repository Overview
This repo has my lab assignments for CS509. Each assignment has its own folder with source code, a driver, test inputs, and the outputs I got when running them. There's also a common wrapper to compile and run things without typing full gcc commands every time.

## Student Details
Name: Shivank Subanshi
Entry Number: 2026AIM1021
Mode: Single

## Language and Environment
Written in C, compiled with gcc, run on Linux.

## Directory Structure
```
CS509_2026AIM1021/
|-- README.md
|-- common_wrapper/
|-- assignment_01/
`-- assignment_02/
```

## Common Wrapper: Build and Usage
`common_wrapper/wrapper.c` is just a small menu so I don't have to remember every gcc/run command.

Compile it once:
`gcc -o common_wrapper/wrapper common_wrapper/wrapper.c`

Run it:
`./common_wrapper/wrapper`

Then pick option 1 (GEMM Assignment), and from there:
- 1 to compile assignment_01
- 2, 3, 4, 5 to run test1, test2, test3, test4 one at a time
- 6 to run all four tests together

Or pick option 2 (Shortest Path Assignment), and from there:
- 1 to compile assignment_02
- 2 to run all Bellman-Ford tests
- 3 to run all Floyd-Warshall tests

---

## Assignments
Each assignment has its own README with the algorithm details, complexity analysis, and test/performance results.

- [Assignment 01 - Matrix Multiplication (GEMM)](assignment_01/README.md)
- [Assignment 02 - Shortest Paths (Bellman-Ford / Floyd-Warshall)](assignment_02/README.md)

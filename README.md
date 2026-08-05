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
|   `-- wrapper.c
|-- assignment_01/
|   |-- src/
|   |   |-- matrix.c
|   |   `-- matrix.h
|   |-- driver/
|   |   `-- main.c
|   |-- tests/
|   |   |-- test1.txt
|   |   |-- test2.txt
|   |   `-- test3.txt
|   `-- outputs/
|       |-- test1_out.txt
|       |-- test2_out.txt
|       `-- test3_out.txt
```

## Common Wrapper: Build and Usage
`common_wrapper/wrapper.c` is just a small menu so I don't have to remember every gcc/run command.

Compile it once:
`gcc -o common_wrapper/wrapper common_wrapper/wrapper.c`

Run it:
`./common_wrapper/wrapper`

Then pick option 1 (GEMM Assignment), and from there:
- 1 to compile assignment_01
- 2, 3, 4 to run test1, test2, test3 one at a time
- 5 to run all three tests together

---

## Assignments
Each assignment has its own README with the algorithm details, complexity analysis, and test/performance results.

- [Assignment 01 - Matrix Multiplication (GEMM)](assignment_01/README.md)

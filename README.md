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

## Assignment 01 - Matrix Multiplication (GEMM)

### Assignment Mode
Single

### Objective
Multiply two matrices two different ways (a plain triple loop, and a blocked/tiled version) and check that both give the same answer. Also time each one to see if blocking actually helps.

### Algorithm / Approach
multiply() does the standard i-j-k loop multiplication and stores the result in C1.

blockMultiply() does the same multiplication but processes the matrices in blocks (default block size 32) so it works better with the cache, result goes in C2.

checkEqual() just compares C1 and C2 element by element to make sure both methods agree.

### Input Format
First line of the test file is `M K N`. After that come the M x K values for matrix A, then the K x N values for matrix B.

### File Structure
- src/matrix.c, matrix.h - the actual multiply logic, reading input, printing results, checking equality
- driver/main.c - takes a test file (and optional block size) as arguments, runs both multiplications, times them, prints everything
- tests/ - the three input files
- outputs/ - what the program printed for each test

### Compilation
```
gcc -o assignment_01/driver/main assignment_01/src/matrix.c assignment_01/driver/main.c
```

### Execution
```
assignment_01/driver/main assignment_01/tests/test1.txt 32
assignment_01/driver/main assignment_01/tests/test2.txt 32
assignment_01/driver/main assignment_01/tests/test3.txt 32
```
32 here is the block size, it defaults to 32 if you leave it out.

### Test Cases and Result Table
For every test, the simple and block versions gave the same result (checkEqual returned true), so I've listed the output once per test rather than repeating it. Full matrices are in the outputs folder if needed.

| Mode | Test File | Input Type | Dimensions (M, K, N) | Algorithm | Expected Output | Actual Output | Algorithm Time |
|---|---|---|---|---|---|---|---|
| Single | test_01.txt | Matrices A, B | 2, 3, 2 | Simple | [[58,64],[139,154]] | Matches | 0.029 ms |
| Single | test_01.txt | Matrices A, B | 2, 3, 2 | Block | [[58,64],[139,154]] | Matches | 0.008 ms |
| Single | test_02.txt | Matrices A, B | 5, 5, 5 | Simple | see outputs/test2_out.txt | Matches | 0.015 ms |
| Single | test_02.txt | Matrices A, B | 5, 5, 5 | Block | see outputs/test2_out.txt | Matches | 0.009 ms |
| Single | test_03.txt | Matrices A, B | 8, 8, 8 | Simple | see outputs/test3_out.txt | Matches | 0.030 ms |
| Single | test_03.txt | Matrices A, B | 8, 8, 8 | Block | see outputs/test3_out.txt | Matches | 0.017 ms |

### Complexity
Both versions are O(M*K*N) - blocking doesn't change the complexity, it just makes better use of the cache in practice.
Space used is roughly O(M*K + K*N + M*N) for the two input matrices and the result.

### References
Class notes on matrix multiplication and cache blocking.

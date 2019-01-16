# matheval_mpfi
Encode and evaluate arithmetic expression in mpfi

This project uses the matheval library source code as the basis of arithmetic expression parsing and keeping it into an expression tree. There is no alteration in the original code of matheval, only additional codes which are put in separate file when it is possible or in the last section of the matheval source files.

The mpfi structure is built from the matheval's expression tree. From this point we can play it with mpfi functions.

# Building
$ make

# Testing
$./driver

# Caveats
The Makefile is written manually and tested only on linux. For other platform you should consider autotools.


##Assignment 2
Program Description: This program recreates the math.h function sof arcsin, arccos, arctan, and log using 2 files: mathlib-test.c and mathlib.c. The user scpeifies what function results they want to see and the program will print out the correpsonding values between a certian range for this program. The returned value is then comapred to the math.h library values and the differences are printed. The requires the use of Ubuntu and the terminal within it to run. 

##Build
	$clang -Wall -Wextra -Werror -Wpedantic -0 mathlib-test mathlib-test.c

##Clean
	$rm -f mathlib-test mathlib-test.o

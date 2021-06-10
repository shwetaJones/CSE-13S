## Assignment 5
Program Description: This program acts as a linear error-correcting code in order to correct errors caused by punch card readers. The assignment contains 3 codes, hamming.c, bm.c, and bv.c. THe encoder.c and decoder.c programs then use these c files to print out an output file concerning this information. 

##Build 
	$clang -Wall Wextra -Werror -Wpedantic -o encoder encoder.c decoder decoder.c

##Clean
	$rm -f encoder encoder.c decoder decoder.c

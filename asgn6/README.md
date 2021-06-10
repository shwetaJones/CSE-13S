## Assignment 6
Program Description: This program encodes and decodes a given file. This follows a coding algorithim constructed by David Huffman who wanted to construct an optimal static encoding of information. This program requires several files: encode.c, decode,c io.c, pq.c, node.c, code.c, and hufffman.c. he program has 3 command line options each. The flag "-h" prints a help message, "-i" specifies the input file, "-o" specifies the output file, and "-v" prints the statitistics related to the output of the program. The program is run viw terminal and if the following options are not speicifed, the input will be stdin and output would be stdout. 

##Build 
	$clang -Wall -Wextra -Werror -Wpedantic -o encode encode.c decode decode.c

##Clean
	$rm -f encode encode.c decode decode.c

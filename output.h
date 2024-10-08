#ifndef OUTPUT_H
#define OUTPUT_H

#include "utils.h"

#define BITS_TO_PRINT 15

/*This functions used the code array table and prints it to output file.
	@param char *, name of user file to call new file */
void write_to_output_file(char *);

/*This function recieves a number and prints it in its binary form.
	@param short, number to be printed
	@param FILE *, pointer to output file created in "write_to_output_file" */
void printOctal(short, FILE *);

#endif

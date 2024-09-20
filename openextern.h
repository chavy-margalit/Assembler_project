#ifndef OPENEXTERN_H
#define OPENEXTERN_H

#include "utils.h"

/*created .ext file and writes all uses of extern labels from user file.
	The function uses 'find_the_words'.
	@param FILE *, file to find external label uses
	@param char *, user file name (for name of ext file) */
void write_to_extern_file(FILE *, char *);

/*This function receives label, scans user file to find label uses
	and writes the labels with the address of use to new file.
	@param char *, label to be searched for
	@param FILE *, user file to scan
	@param FILE *, ext file to write to */
void find_the_words(char *, FILE *, FILE *);

#endif

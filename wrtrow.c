/*
 * wrtrow
 *
 * usage:   Writes a CSV row to the output. The columns in the output row
 *          are selected columns from the input row. The columns selected for
 *          output are contained in the entries in coltab. The order of columns
 *          in the output row is from element 0 to element cnt-1 in coltab.
 *          An array of pointers to each of the input columns is used to output
 *          the column's data.
 *          Note: Use printf to output the column data and the delimiters
 *
 * arguments:
 *  ptable  points at array of pointers, each element points at a single columns
 *          data
 *  coltab points array of ints, each element is an offset into ptable. The order
 *          of elements in the array specifies the column order in the output
 *          row
 *  cnt     number of elements in array coltab
 *  delim   the output column delimiter to use
 *
 * Return values:
 *          -1 if if an error is detected (printf fails)
 *          otherwise returns the number of columns printed
 *
 * error messages:
 *          this function does not write any error messages
 */

#include "version.h"
#ifndef MYWRTROW
#warning("WARNING - USING THE SOLUTION writerow.c NOT MY CODE")
#else
#include <stdio.h>
#include "wrtrow.h"

int
wrtrow(char **ptable, int *coltab, int cnt, char delim)
        
{
	int printed = 0; //variable to keep track of how many columns printed
	int printcheck; //variable to store return value from printf to see if there was an error in printing
    for (int i = 0; i <= (cnt - 1); i++) {
		int offset = *(coltab + i); //offset variable for ptable

		/*
		* if statement to check if the current column printed is the last one
		* -if it is the last one, then don't print with a delimiter
		* -if it is not the last one then print with a delimiter
		*/
		if (i != (cnt - 1)) {
			printcheck = printf("%s%c", *(ptable + offset), delim);
		} else {
			printcheck = printf("%s", *(ptable + offset));
		}
		if (printcheck < 0) {
			return -1;
		} else {
			printed++;
		}
	}
	printf("\n");
	return printed;
}
#endif  // do not delete this line

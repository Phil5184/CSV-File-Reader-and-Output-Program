/*
 * Programming assignment 4 main function
 *
 * main
 *
 * Usage: csv col [col..]
 *
 * Overview:
 *      reads a row of text (a row end in a \n") in comma separated format from
 *      standard input. It then writes this row in comma separated format to
 *      standard output while reformatting each row as specified by the command
 *      line arguments (selects which columns to output and the output order).
 *      Error messages are written to stderr.
 *
 *      See the PA writeup for more details
 *      You should remove line comments that start at the left side of the file
 *      they are hints of what to do.
 *
 * Return value
 *      Return EXIT_FAILURE is there is an error or 1 or more rows were dropped
 *      Otherwise, EXIT_SUCCESS is returned.
 *
 * Error messages:
 * 	main() writes error messages to stderr
 */ 
#include "version.h"
#ifndef MYCSV
#warning("WARNING - USING THE SOLUTION csv.c NOT MY CODE")
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "splitrow.h"
#include "wrtrow.h"
#include "setorder.h"

#define DELIM   ','             // column delimiter
// NOTICE next three values are set small so corner cases are easy to test
// These three values are too small for real use.
#define BUFSZ   128             // row buffer size
#define MAXCOL  8               // Max number of columns in a row
#define MAXARG  8               // Max number of output columns

/*
 * csv main function
 */ 
int 
main(int argc, char **argv)
{
    // delete this and the next comment line from your code
    // you can change the variable names below and add variables as you want

    char buf[BUFSZ];            // input row buffer
    char *ptable[MAXCOL];       // array of pointers to column starts
    int coltab[MAXARG];         // array of output column offset values
    unsigned long rowcount;     // input row counter
    unsigned long dropcnt;      // dropped rows counter
    int incols;                 // number of columns in the input
    int outcols;                // number of columns in the output

    /*
     * only using argv for this assignment, argc not used
     */
    (void)argc;                 // suppress compiler warnings hack (sigh)... 

    

    /*
     * the error messages for use in this file
     *
    fprintf(stderr, "%s: Header row input error\n", *argv);
    fprintf(stderr, "%s: Header row output failure, exiting\n", *argv);
    fprintf(stderr, "%s: Dropped input row %lu\n", *argv, rowcount);
    fprintf(stderr, "%s: Dropped output row %lu\n", *argv, rowcount);
    fprintf(stderr, "%s: %lu rows in, %lu dropped\n", *argv, rowcount, dropcnt);
    */

	/* first if statement checks for empty input file */
    if (fgets(buf, BUFSZ, stdin) == NULL) {
		return EXIT_SUCCESS;
    }
    incols = splitrow(buf, ptable, MAXCOL, DELIM);
    if (incols < 1) {
		fprintf(stderr, "%s: header row input error\n", *argv);
		return EXIT_FAILURE;
    }
    outcols = setorder(argv, coltab, MAXARG, incols);
	if (outcols < 1) {
		return EXIT_FAILURE;
	}
	int outcolcheck = wrtrow(ptable, coltab, outcols, DELIM); //outcolcheck is a variable to store return value from wrtrow (for error checking)
	if (outcolcheck != outcols) {
		fprintf(stderr, "%s: Header row output failure, exiting\n", *argv);
		return EXIT_FAILURE;
	}
    rowcount = 1;  //counting first header row
	dropcnt = 0;   //initializing dropcnt to 0, starts counting inside while loop
    while (fgets(buf, BUFSZ, stdin) != NULL) {
		rowcount++;
        int numcol = splitrow(buf, ptable, incols, DELIM);  //numcol is a variable to store return value from splitrow (for error checking)
		if (numcol != incols) {
	    	fprintf(stderr, "%s: Dropped input row %lu\n", *argv, rowcount);
	    	dropcnt++;
	    	continue;
		}
		int numOutCheck = wrtrow(ptable, coltab, outcols, DELIM); //numOutCheck is a variable to store return value from wrtrow (for error checking)
		if (numOutCheck != outcols) {
			fprintf(stderr, "%s: Dropped output row %lu\n", *argv, rowcount);
			dropcnt++;
			break;
		}
    }
	fprintf(stderr, "%s: %lu rows in, %lu dropped\n", *argv, rowcount, dropcnt);
	if (dropcnt == 0) {
		return EXIT_SUCCESS;
	} else {
		return EXIT_FAILURE;
	}
}
#endif // do not delete

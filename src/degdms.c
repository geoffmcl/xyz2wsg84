/*  @(#)degdms.c        1.1  98/12/08  */
static char *sccsid= "@(#)degdms.c      1.1  98/12/08";
/*
 *  include files
 */


/*
 *  function prototypes
 */

void degdms( double, int *, int *, double * );

/*
 *  global definitions and variables
 */




void degdms( double ddeg, int *deg, int *min, double *sec )
/********1*********2*********3*********4*********5*********6*********7*********
 * name:            degdms
 * version:         9504.11
 * written by:      M. Schenewerk
 * purpose:         convert decimal degrees to degrees, minutes, seconds
 *
 * input parameters
 * ----------------
 *
 * output parameters
 * -----------------
 *
 *
 * local variables and constants
 * -----------------------------
 *
 * global variables and constants
 * ------------------------------
 *
 *
 * called by:
 *
 * calls:
 *
 * include files:
 *
 * references:
 *
 * comments:        Only the degree keeps the sign!
 *
 * see also:
 *
 ********1*********2*********3*********4*********5*********6*********7*********
 *:modification history
 *:9504.11, MSS, Creation
 ********1*********2*********3*********4*********5*********6*********7*********/

{
        int sign;

        if( ddeg < 0 ) {
                sign= -1;
                ddeg= -ddeg;
        } else {
                sign= 1;
        }
        *deg= ddeg;
        ddeg= (ddeg-(double)(*deg))*(double)60;
        *min= ddeg;
        *sec= (ddeg-(double)(*min))*(double)60;
        *deg= sign*(*deg);
}

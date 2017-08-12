/* @(#)linfit.h 1.1  00/04/10 */

/********1*********2*********3*********4*********5*********6*********7*********
 * name:       linfit
 * version:    0004.09
 * written by: M. Schenewerk
 * purpose:    linear regression data structure
 *
 * global variables and constants
 * ------------------------------
 * LRDS, the linear regression data structure contains
 *    SumWgt          Sum of weights
 *    SumInd          Sum of independent variables
 *    SumInd2         Sum of independent variables * independent variables
 *    SumDep          Sum of Dependent variables
 *    SumDep2         Sum of Dependent variables * Dependent variables
 *    SumIndDep       Sum of independent variables * Y
 *    Count           Number of data pairs
 *    Mode            = 0 = standard deviations unavailable;
 *                          Q is returned as 1.0
 *                          ChiSq is normalized to 1.0 on all points
 *                    = 1 = normal operation
 * Count should be initialized to zero (0).
 *
 *
 * include files:
 * ------------------------------
 *
 * references:
 * ------------------------------
 *
 * comments:
 * ------------------------------
 *
 * see also:
 * ------------------------------
 * Press, WH, Flannery, BP, Teukolsky, SA, and Vetterling, WT  1988,
 * Numerical Recipes (Cambridge, UK: Cambridge University Press),
 * Sec 14.2.
 *
 ********1*********2*********3*********4*********5*********6*********7*********
 *:Modification History
 *:0004.09, MSS, Creation
 ********1*********2*********3*********4*********5*********6*********7*********/
#ifndef linfit_h
#  define linfit_h

/*
 *  include files
 */

/*
 *  global definitions and variables
 */


   typedef struct linear_regression_data_structure {
      double SumWgt;
      double SumInd;
      double SumInd2;
      double SumIndDep;
      double SumDep;
      double SumDep2;
      int Count;
      int Mode;
   } LRDS;

/*
 *  function prototypes
 */
#ifdef __cplusplus
   extern "C" {
#endif

int linfit( double, double, double, LRDS *,
   double *, double *, double *, double *, double *, double * );

#ifdef __cplusplus
}
#endif

#endif

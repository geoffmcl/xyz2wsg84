/*  @(#)olt.h   1.1  98/12/08  */
/********1*********2*********3*********4*********5*********6*********7*********
 * name:            olt.h
 * version:         9810.20
 * written by:      M. Schenewerk
 * purpose:         grids and variables for ocean-loading
 *
 * global variables and constants
 * ------------------------------
 * d2r              converts degrees to radians [rad/deg]
 * dx               grid longitude spacing
 * dy               grid latitude spacing
 * grids[]          struct of magnitude and phase for gridded points
 * latmax           maximum grid latitude
 * latmin           minimum grid latitude
 * lonmax           maximum grid longitude
 * lonmin           minimum grid longitude
 * ngrids           maximum number of grids
 * nx               maximum dimension of grid for longitude
 * ny               maximum dimension of grid for latitude
 * one_eighty       (double)180
 * pi               pi
 * three_sixty      (double)360
 * undef            flag value for undefined grid point
 * wrap             = 0 if grid does not wrap in longitude
 *                  = 1 otherwise
 *
 * functions
 * ------------------------------
 * astrol()         computes the basic astronomical mean longitudes
 * check_olt()      check data description/title string for validity
 * grid_olt()       location in grid
 * intrp_olt()      interpolates a value from a grid of data
 * init_olt()       initialization for perth2
 * load_olt()       load a multiple sets of gridded data
 * read_olt()       reads an ASCII file of gridded values
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
 *
 ********1*********2*********3*********4*********5*********6*********7*********
 *:modification history
 *:9705.31, MSS, Creation.
 *:9810.20, MSS, Remove variable typing from header.
 ********1*********2*********3*********4*********5*********6*********7*********/

#ifndef olt_h
#define olt_h

#include <stdio.h>

#define one_eighty ((double)180.0)
#define three_sixty ((double)360.0)
#define MAX_grids ((int)8)
#define MAX_tides ((int)26)

struct gridded_data {
  char id[16];
  double *amp;
  double *phs;
};

double *read_olt( char *, FILE * );
char *check_olt( char * );
int grid_olt( int, int );
int init_olt( FILE *, char * );
int intrp_olt( double, double, double *, double *, char ** );
int load_olt( FILE * );
void astrol( double, double * );

#endif /* olt_h */

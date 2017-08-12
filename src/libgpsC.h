/*  @(#)libgpsC.h       1.5  00/04/10  */
/********1*********2*********3*********4*********5*********6*********7*********
 * name:            libgpsC.h
 * version:         00/04/10
 * written by:      M. Schenewerk
 * purpose:         GPS processing specific definitions and routines
 *
 * global variables and constants
 * ------------------------------
 *
 * functions
 * ------------------------------
 * PlateMotionModel: computes site velocity from a plate motion model
 * AntennaSearch:    Search directory for latest, by modification date, file
 * scanantinfo:      reads and interprets antenna info;
 *                   fill antenna info basic storage variables
 * defaultantinfo:   fill antenna info storage variables with default/hardwired
 *                   info
 * getAntOffsets:    retrieve the L1 and L2 phase center offsets for an antenna
 *                   type
 * astrol:           computes the basic astronomical mean longitudes
 * blank:            returns location of first non-"white space" character
 * check_olt:        Search for Darwinian tidal ID in string
 * dayhms:           converts decimal days to hours, minutes, and seconds
 * degdms:           convert decimal degrees to degrees, minutes, seconds
 * moments:          Calculates a mean, second moment, and variance
 * dow:              converts the modified Julian date to the day of week
 * flip_double:      reverse byte order in a double variable
 * flip_long:        reverse byte order in a long variable
 * gpswk:            converts modified Julian date to the GPS week
 * grid_olt:         returns location in grid storage vector
 * hmsday:           converts hours, minutes, and seconds to decimal days
 * ibch:             returns location of first non-"white space" character
 * iech:             returns location of last non-"white space" character
 * init_lpsec:       Initializes leap second storage array.
 * init_olt:         initialization for perth2
 * initialize_A:     initialize antenna type data structures
 * initialize_C:     initialize coordinates type data structures
 * initialize_G:     initialize offset type data structures
 * initialize_R:     initialize receiver type data structures
 * initialize_T:     initialize offset type data structures
 * initialize_M:     initialize met type data structures
 * initialize_OLT:   initialize ocean loading type data structures
 * intrp_olt:        interpolates a value from a grid of data.
 * linfit:           performs linear fit using gamma Q minimization.
 * load_olt:         loads array with data from files of harmonic constants.
 * lpsec:            Sets UTC-TAI and GPS-UTC for the input MJD.
 * mjdyd:            Converts modified Julian date to year and day-of-year.
 * mjdymd:           converts modified Julian day to Gregorian calendar date
 * month_name:       converts month number to ASCII name
 * neu2xyz:          Convert local north, east, up vector to X, Y, Z
 * nod:              This subroutine evaluates the nutation series and
 * nonwhitespace:    returns pointer to first non-"white space" character
 * plh2xyz:          converts elliptic lat, lon, hgt to geocentric X, Y, Z
 * read_olt:         Reads an ASCII file of gridded values
 * ReceiverSearch:   Search directory for latest, by modification date, file
 * scanrcvrinfo:     reads and interprets receiver info;
 *                   fill receiver info basic storage variables
 * defaultrcvrinfo:  fill receiver info storage variables with
 *                   default/hardwired info
 * recgetmi:         gets record and rectifies variables for this machine
 * recgetnext:       reads a binary file for next valid record
 * recputnext:       writes next valid record to a binary file
 * sidtim:           This subroutine computes the greenwich sidereal time
 * stidcmp:          compares two full station ID strings (7 char)
 * stidcpy:          copy full station ID string (7 char)
 * tchk:             compares two times
 * tchkeps:          compares two times to within some user defined uncertainty
 * whitespace:       returns pointer to first "white space" character
 * xyz2neu:          Convert geocentric X, Y, Z vector to local north, east, up
 * ydymd:            Converts year and day-of-year to calandar date.
 * ymdmjd:           conerts year, month, and day to the modified Julian date
 * ymdyd:            Converts calandar date to year and day-of-year.
 *
 *
 * include files:
 * ------------------------------
 * olt.h            grids and related variables related to ocean-loading
 * sidata.h         data structures used for I/O to station info files
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
 *:9810.21, MSS, Creation
 ********1*********2*********3*********4*********5*********6*********7*********/

#ifndef libgpsC_h
#define libgpsC_h

#include "olt.h"
#include "sidata.h"
#include "linfit.h"
#ifdef __cplusplus
extern "C" {
#endif
    
void PlateMotionModel( char *, double *, double * );
int AntennaSearch( char * );
int scanantinfo( char * );
int defaultantinfo( );
void getAntOffsets( char *, double *, double * );
int blank( char * );
void degdms( double, int *, int *, double * );
double gam_ln( double );
void gam_cf( double *, double, double, double * );
double gam_ln( double );
double gam_q( double, double );
void gam_ser( double *, double, double, double * );
void gam_cf( double *, double, double, double * );
double gam_ln( double );
void gam_ser( double *, double, double, double * );
int ibch( char * );
int iech( char * );
int init_lpsec();
long ymdmjd( int, int, int );
double hmsday( int, int, double );
long ymdmjd( int, int, int );
void datim( int *, int *, int *, int *, int *, double * );
void initialize_A( struct common_data_info *, struct antenna * );
void initialize_C( struct common_data_info *, struct coordinates * );
void initialize_G( struct common_data_info *, struct si_offset * );
void initialize_M( struct common_data_info *, struct met * );
void initialize_OLT( struct common_data_info *, struct oceanloading * );
void initialize_R( struct common_data_info *, struct receiver * );
void initialize_T( struct common_data_info *, struct si_offset * );
double gam_q( double, double );
int linfit( double, double, double, LRDS *,
        double *, double *, double *, double *, double *, double * );
long ymdmjd( int, int, int );
void mjdyd( long, int *, int * );
void mjdymd( long, int *, int *, int * );
void neu2xyz( double, double, double, double, double,
        double *, double *, double * );
char *nonwhitespace( char * );
void plh2xyz( double *, double *, double , double );
void reformat( char *, int *, int * );
int ReceiverSearch( char * );
int scanrcvrinfo( char * );
int defaultrcvrinfo( );
void getAntOffsets( char *, double *, double * );
int recputnext( FILE * );
int tchk( long, double, long, double );
int tchkeps( long, double, long, double, double );
char *whitespace( char * );
void xyz2neu( double, double, double, double, double,
        double *, double *, double * );
void xyz2plh( double *, double *, double, double );

#ifdef __cplusplus
}
#endif

#endif /* libgpsC_h */

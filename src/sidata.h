/*  @(#)sidata.h        1.4  00/03/23  */
/********1*********2*********3*********4*********5*********6*********7*********
 * name:            sidata.h
 * version:         0003.23
 * written by:      M. Schenewerk
 * purpose:         defines data structures used in maintaining station
 *                  information files
 *
 * global variables and constants
 * ------------------------------
 *
 *
 * references:
 *
 * comments:        The file is formatted to be read as an unformatted
 *                  sequential file from (HP) FORTRAN.  The structure of
 *                  binary FORTRAN lines is:
 *                  SIZE<--------INFO------->SIZE
 *                  where:
 *                  "INFO" is the variables, constants, arrays, etc.
 *                         that are written in the FORTRAN I/O and
 *                  "SIZE" is the number of bytes of "INFO".
 *
 *                  Hereafter each line will be referred to as a record.
 *
 *                  In C, these "SIZE" integers must be handled explicity.
 *
 *                  The "INFO" is broken into two parts, information "common"
 *                  to all records and information specific to that record
 *                  type.  The general sturcture of these records look like:
 *                  <-common-><-----info-------->
 *                  SIZE<--------INFO------->SIZE
 *
 *                  The "common" piece has the following items:
 *                    size = total size in bytes minus        =  4 byte long
 *                           leading/trailing 4 byte integers
 *                    record type                             =  1 byte char
 *                    site ID                                 =  6 byte char
 *                    site sequence                           =  1 byte char
 *                    first valid epoch high part [MJD]       =  4 byte long
 *                    first valid epoch low part [day]        =  8 byte double
 *                    modification time high part [MJD]       =  4 byte long
 *                    modification time low part [day]        =  8 byte double
 *                    type =                                  =  4 byte long
 *                    =======================================   ==============
 *                                                              40 bytes
 *
 *                    "type" appears in this structure to fulfill the 8 byte
 *                    boundary requirement.  To minimize wasted space, "type"
 *                    has meanings dependent upon the record type:
 *                    A   = corresponding numeric antenna type ID
 *                    C   = no use
 *                    M   = no use
 *                    O   = common numeric ID for multiple additive offsets
 *                    OLT = no use
 *                    R   = corresponding numeric receiver type ID
 *
 *                  The "info" pieces are described before each structure.
 *
 *                  Currently (9506.18) all values are in meters.
 *
 * see also:
 *
 ********1*********2*********3*********4*********5*********6*********7*********
 *:modification history
 *:9506.18, MSS, creation
 *:9508.22, MSS, modified to match FORTRAN read
 *:9508.29, MSS, added sigmas to coords and vel
 *:9509.09, MSS, modified to better match xsites program
 *:9509.26, MSS, modified commons section for convenienc; combine C & V
 *               records; add comment string to all records
 *:9611.20, MSS, added data format specifier
 *:9705.07, MSS, added ocean-loading and met package data structures
 *:9810.20, MSS, move variable typing out of header file
 *:9903.12, MSS, Add structures for old as well as new A, M and R data formats.
 *:9904.23, MSS, Change antenna record length to account for padding.
 *:0003.23, MSS, Corrected met structure by adding a 4-byte dummy variable
 *:              making the structure fit to an even 8-byte boundary.
 ********1*********2*********3*********4*********5*********6*********7*********/

#ifndef sidata_h
#define sidata_h

#include <stdio.h>

#define DATA_FORMAT     ((long)1)
#define FORMAT_99MAR15  ((long)2)

#define EPS_MINUTE      ((double)30.0/(double)86000.0)
#define EPS_SECOND      ((double)0.5/(double)86000.0)

#define MAX_record      256

#define MAX_altname     40
#define MAX_comment     60
#define MAX_domes       9
#define MAX_frame       7
#define MAX_from        16
#define MAX_fw          16
#define MAX_id          6
#define MAX_key         1
#define MAX_name_m1     16
#define MAX_name        20
#define MAX_plate       4
#define MAX_seq         1
#define MAX_sitename    24
#define MAX_sn          16
#define MAX_to          16

#define STR_altname     (MAX_altname+1)
#define STR_comment     (MAX_comment+1)
#define STR_domes       (MAX_domes+1)
#define STR_frame       (MAX_frame+1)
#define STR_from        (MAX_from+1)
#define STR_fw          (MAX_fw+1)
#define STR_id          (MAX_id+1)
#define STR_key         (MAX_key+1)
#define STR_name        (MAX_name+1)
#define STR_plate       (MAX_plate+1)
#define STR_seq         (MAX_seq+1)
#define STR_sitename    (MAX_sitename+1)
#define STR_sn          (MAX_sn+1)
#define STR_to          (MAX_to+1)
/*
 * the "type" piece identifies the info type and gives info common to all
 * record types
 */
#define STD_type        (-1L)

struct common_data_info {
        long   size;
        long   modmjd;
        double modday;
        long   type;
        long   valmjd;
        double valday;
        char   key;
        char   id[MAX_id];
        char   seq;
};

/*
 * current format: type = -2
 * antenna offset from reference point to phase center and other info:
 *   name serial_number type_number valid_MJD valid_day
 */
struct antenna {
        double n;
        double e;
        double u;
        char   from[MAX_from];
        char   to[MAX_to];
        char   name[MAX_name];
        char   sn[MAX_sn];
        char   comment[MAX_comment];
        char   dummy[4];
        long   size;
};

/*
 * original format: type = -1
 * antenna offset from reference point to phase center and other info:
 *   L1north L1east L1up L2north L2east L2up name serial_number type_number
 *   valid_MJD valid_day
 */
struct antenna_m1 {
        double n;
        double e;
        double u;
        char   from[MAX_from];
        char   to[MAX_to];
        double n1;
        double e1;
        double u1;
        double n2;
        double e2;
        double u2;
        char   name[MAX_name_m1];
        char   sn[MAX_sn];
        char   comment[MAX_comment];
        long   size;
};
/*
 * site coordinates:
 *   X Y Z reference_frame domes_# type_number valid_MJD valid_day
 */
struct coordinates {
        double x;
        double y;
        double z;
        double xsig;
        double ysig;
        double zsig;
        double vx;
        double vy;
        double vz;
        double vxsig;
        double vysig;
        double vzsig;
        double refday;
        long   refmjd;
        char   frame[MAX_frame];
        char   domes[MAX_domes];
        char   plate[MAX_plate];
        char   sitename[MAX_sitename];
        char   altname[MAX_altname];
        char   comment[MAX_comment];
        long   size;
};
/*
 * current format: type = -2
 * met equipment:
 *   temperature pressure relative humidity valid_MJD valid_day comment
 */
struct met {
        double pru;
        char   pr[MAX_name];
        char   prsn[MAX_sn];
        char   rh[MAX_name];
        char   rhsn[MAX_sn];
        char   tm[MAX_name];
        char   tmsn[MAX_sn];
        char   comment[MAX_comment];
        char   dummy[4];
        long   size;
};
/*
 * original format: type = -1
 * met equipment:
 *   temperature pressure relative humidity valid_MJD valid_day comment
 */
struct met_m1 {
        double pru;
        char   pr[MAX_name_m1];
        char   prsn[MAX_sn];
        char   rh[MAX_name_m1];
        char   rhsn[MAX_sn];
        char   tm[MAX_name_m1];
        char   tmsn[MAX_sn];
        char   comment[MAX_comment];
        long   size;
};
/*
 * si_offset
 *   X Y Z comment type_number valid_MJD valid_day
 */
struct si_offset {
        double offset[3];
        char   from[MAX_from];
        char   to[MAX_to];
        char   comment[MAX_comment];
        long   size;
};
/*
 * ocean-loading parameters
 *   each identified by Darwin symbol and has a amplitude and phase offset
 *   from driving potential
 */
struct oceanloading {
        double m2amp;
        double m2phs;
        double s2amp;
        double s2phs;
        double n2amp;
        double n2phs;
        double k2amp;
        double k2phs;
        double o1amp;
        double o1phs;
        double k1amp;
        double k1phs;
        double p1amp;
        double p1phs;
        double q1amp;
        double q1phs;
        double mfamp;
        double mfphs;
        double mmamp;
        double mmphs;
        double ssaamp;
        double ssaphs;
        char   comment[MAX_comment];
        long   size;
};
/*
 * current format: type = -2
 * receiver information:
 *   type_number name serial_number firmware type_number valid_MJD valid_day
 */
struct receiver {
        char   name[MAX_name];
        char   sn[MAX_sn];
        char   fw[MAX_fw];
        char   comment[MAX_comment];
        long   size;
};
/*
 * original format: type = -1
 * receiver information:
 *   type_number name serial_number firmware type_number valid_MJD valid_day
 */
struct receiver_m1 {
        char   name[MAX_name_m1];
        char   sn[MAX_sn];
        char   fw[MAX_fw];
        char   comment[MAX_comment];
        long   size;
};

/*
 * library function prototypes
 */

void flip_double( double * );
void flip_long( long * );
int recgetmi( FILE * );
int recgetnext( FILE * );

#endif /* sidata_h */

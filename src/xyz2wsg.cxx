/*\
*   xyz2wsg.cxx
*
* Copyright (c) 2017 - Geoff R. McLane
* Licence: GNU GPL version 2
*
\*/

/********1*********2*********3*********4*********5*********6*********7*********
 * name:            xyz2wsg
 * version:         1.0.0
 * written by:      Geoff R. Mclane
 * purpose:         converts elliptic lat, lon, hgt <-> X, Y, Z
 *
 * Simple example using -
 * https://geographiclib.sourceforge.io/html/geocentric.html
 ********1*********2*********3*********4*********5*********6*********7*********
 *:modification history
 20170812: GRM Initial cut
 ********1*********2*********3*********4*********5*********6*********7********/

/*
 *  include files
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// #ifdef USE_GEOGRAPHIC_LIB
#include <GeographicLib/Config.h>
#include <GeographicLib/Geocentric.hpp>
// #endif

#ifndef GEOGRAPHICLIB_VERSION_STRING
#define GEOGRAPHICLIB_VERSION_STRING "1.48"
#endif

 /*
 *  static definitions and variables
 */
static int incnt = 0;
static int mode = 0;
static char *pgm;
static char *vrsn = "1.0.0 11/08/2017";
static double in[3] = { 0.0, 0.0, 0.0 };

void show_help()
{
    printf("%s(%s): Converts X Y Z to lat, lon and ellipsoid hgt\n", pgm, vrsn);
    printf("Usage: %s [options] X Y Z\n", pgm);
    printf("  options:\n");
    // printf("           -d print deg min sec rather than decimal degrees.\n");
    printf("           -h = prints this message.\n");
    printf("           -r = input coordinates are lat, lon, hgt,\n");
    printf("                output coordinates will be X, Y, Z.\n");
    // printf("           -w longitudes are west rather than east longitude.\n");
    printf("\n");
    printf(" Given three decimal inputs, use GeographicLib, version " GEOGRAPHICLIB_VERSION_STRING "\n");
    printf(" to convert the X Y Z geocentric input to latitude, longitude and height.\n");
    printf(" If -r input assumed to be lat lon hgt, and converted to X Y Z\n");
}

/*
*   1.0  Parse command line
*/
#ifndef ISDIGIT
#define ISDIGIT(a) ((a >= '0') && (a <= '9'))
#endif

bool is_decimal(const char *stg)
{
    size_t ii, max = strlen(stg);
    bool seen_pt = false;
    int c;
    for (ii = 0; ii < max; ii++) {
        c = stg[ii];
        if (c == '-') {
            if (ii != 0)
                return false;
        }
        else if (c == '.') {
            if (seen_pt)
                return false;
            seen_pt = true;
        }
        else if (!ISDIGIT(c)) {
            return false;
        }
    }
    return true;
}

int parse_command(int argc, char *argv[])
{
    char *arg, *sarg;
    int i, c;
    bool dec;
    pgm = argv[0];
    while ((arg = strpbrk(pgm, "/\\:")) != NULL)
        pgm = arg + 1;

    incnt = 0;
    for (i = 1; i < argc; i++) {
        arg = argv[i];
        c = *arg;
        dec = is_decimal(arg);
        if ((c == '-') && !dec) {
            sarg = &arg[1];
            while (*sarg == '-')
                sarg++;
            c = *sarg;
            switch (c)
            {
            //case 'd':
            //    display = 1;
            //    break;
            case 'h':
            case '?':
                show_help();
                return 2;
                break;
            case 'r':
                mode = 1;
                break;
            //case 'w':
            //    west = 1;
            //    break;
            default:
                fprintf(stderr, "Error: Unknown option '%s'!\n", arg);
                return 1;
                break;
            }

        }
        else if (dec) {
            if (incnt >= 3) {
                fprintf(stderr, "Error: Already have 3 input values!\n");
                return 1;
            }
            in[incnt++] = atof(arg);
        }
        else {
            fprintf(stderr, "Error: Unknown input '%s'!\n", arg);
            return 1;
        }
    }
    if (incnt < 3) {
        show_help();
        fprintf(stderr, "Error: 3 inputs not found in command! Get %d\n", incnt);
        return 1;
    }
    return 0;
}

using namespace GeographicLib;
typedef Math::real real;

int main( int argc, char *argv[] )
{
    int iret = 0;
/*
 *   1.0 Deal with command line
 */
    iret = parse_command(argc, argv);
    if (iret) {
        if (iret == 2)
            iret = 0;
        return iret;
    }


/*
 *   2.0  Convert and print coordinates
 */
    printf("in : %16.10f %16.10lf %13.5lf as %s\n", in[0], in[1], in[2],
        ((mode == 1) ? "lat lon hgt" : "X Y Z") );
    real a = Constants::WGS84_a();
    real f = Constants::WGS84_f();
    const Geocentric ec(a, f);
    try {
        real lat, lon, h, x = 0, y = 0, z = 0;
        if( mode == 1 ) {
            // plh2xyz( in, out, emajor, eflat );
            lat = in[0];
            lon = in[1];
            h = in[2];
            ec.Forward(lat, lon, h, x, y, z);
            printf("out: %13.4lf %13.4lf %13.4lf X Y Z\n", x, y, z);
        }
        else {
            //xyz2plh(in, out, emajor, eflat);
            x = in[0];
            y = in[1];
            z = in[2];
            ec.Reverse(x, y, z, lat, lon, h);
            printf("out: %13.4lf %13.4lf %13.4lf lat lon hgt\n", lat, lon, h);
        }
    }
    catch (const std::exception& e) {
        fprintf(stderr, "Error: %s\n", e.what());
        iret = 1;
    }

    return iret;
}

/* eof */

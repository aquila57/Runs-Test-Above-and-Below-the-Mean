/* runsb.h - Runs test above and below the mean, header file  */
/* Version 0.1.0 */
/* Copyright (C) 2019 aquila57 at github.com                    */

/* This program is free software; you can redistribute it and/or     */
/* modify it under the terms of the GNU General Public License as    */
/* published by the Free Software Foundation; either version 2 of    */
/* the License, or (at your option) any later version.               */

/* This program is distributed in the hope that it will be useful,   */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of    */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the      */
/* GNU General Public License for more details.                      */

/* You should have received a copy of the GNU General Public License */
/* along with this program; if not, write to:                        */

   /* Free Software Foundation, Inc.                                 */
   /* 59 Temple Place - Suite 330                                    */
   /* Boston, MA 02111-1307, USA.                                    */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_sf_erf.h>
#include <gsl/gsl_rng.h>
#include "eegl.h"
#include "etaus.h"

#define SMPLS (10000000)

#define BITS (32)

/* getdie() end of file return code */

#define EOFDIE (-999999999.0)

#define ABOVE 1
#define BELOW 0

typedef struct xxstruct {
   char *rngname;
   char dieharder_rngname[128];
   char rngtbl[1000][64];
   int run_direction;
   int run_len;
   int generator;
   int eofsw;
   unsigned int fibonum1;
   unsigned int fibonum2;
   unsigned int fibonum3;
   unsigned int seed;
   unsigned int lfsr0;
   unsigned int lfsr;
   unsigned int major;
   unsigned int minor;
   unsigned int lowbit;
   unsigned int out;
   unsigned int maxint;
   eefmt *ee;
   etfmt *et;
   gsl_rng *rng;
   gsl_rng_type *gsltype;
   double count;
   double modulus;
   double avg_above_len;
   double avg_below_len;
   double avg_len;
   double tot_above_len;
   double tot_below_len;
   double tot_len;
   double tot_above_runs;
   double tot_below_runs;
   double tot_runs;
   double *above_tally;
   double *below_tally;
   double *smpls;
   double dblsz;
   double sum;
   double none;
   double ntwo;
   double beta;
   double mubee;
   double varianceb;
   double meanb;
   double zedb;
   double actual[1024];
   double maxint_tbl[2048];
   } xxfmt;

double gen_dbl(xxfmt *xx);
void fillsmpls(xxfmt *xx);
void getmean(xxfmt *xx);
void calc_zedb(xxfmt *xx);
double calc_wi(int len, double none, double ntwo, double N);
double calc_EI(double none, double ntwo, double N);
void calcchi(double *actual, double none, double ntwo, double dblsz);
double calc_expval(int i, double none, double ntwo, double N);
double permute(int i);
void freeall(xxfmt *xx);
double getdie(xxfmt *xx);
void bld_maxint(xxfmt *xx);
void bld_rngtbl(xxfmt *xx);

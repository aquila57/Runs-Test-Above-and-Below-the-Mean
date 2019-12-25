#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_sf_erf.h>
#include "eegl.h"

#define SMPLS (10000000)

#define ABOVE 1
#define BELOW 0

typedef struct xxstruct {
   int run_direction;
   int run_len;
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
   eefmt *ee;
   gsl_rng *rng;
   gsl_rng_type *gsltype;
   char *rngname;
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

/* runsgsl.c - Runsb test, GSL generators  Version 0.1.0 */
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

#include "runsb.h"

/* Initialize GNU Scientific Library random number generator */

void initrng(xxfmt *xx)
   {
   unsigned int seed;  /* random seed to initialize GSL RNG */
   xx->ee = (eefmt *) eeglinit();   /* start eegl64 generator */
   seed = eegl(xx->ee);   /* set random seed */
   gsl_rng_env_setup();  /* get GSL_RNG_TYPE env variable */
   xx->gsltype = (gsl_rng_type *) gsl_rng_default;  /* generator name */
   xx->rng = (gsl_rng *) gsl_rng_alloc(xx->gsltype);  /* start generator */
   xx->rngname = (char *) gsl_rng_name(xx->rng); /* get RNG name */
   printf("GSL random number generator = %s\n", xx->rngname);
   printf("\n");
   gsl_rng_set(xx->rng, seed);   /* initialize GSL RNG seed */
   } /* initrng */

/* Generate one uniform sample from zero to one */

double gen_dbl(xxfmt *xx)
   {
   double newnum;
   newnum = gsl_rng_uniform(xx->rng);
   return(newnum);
   } /* gen _dbl */

int main(void)
   {
   double *p,*q;
   xxfmt *xx;

   /*************************************************************/
   /* Allocate memory for the global structure.                 */
   /* This is a re-entrant program.                             */
   /*************************************************************/

   xx = (xxfmt *) malloc(sizeof(xxfmt));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx\n");
      exit(1);
      } /* out of memory */

   /*************************************************************/
   /* Allocate memory for ten million samples.                  */
   /*************************************************************/

   xx->smpls = (double *) malloc(sizeof(double) * SMPLS + 10);
   if (xx->smpls == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx->smpls\n");
      exit(1);
      } /* out of memory */
   /* Initialize the GSL random number generator */
   initrng(xx);
   printf("\tGNU Scientific Library " 
      "Generator: %s\n", xx->rngname);
   printf("\t    Runs Above and Below the Mean\n");
   printf("\n");
   xx->dblsz = (double) SMPLS;
   /* populate the samples list with ten million samples */
   fillsmpls(xx);
   /******************************************************************/
   /* runs above and below the mean test                             */
   /* calculate the mean                                             */
   /******************************************************************/
   getmean(xx);
   /******************************************************************/
   /* initialize for chi square test                                 */
   /******************************************************************/
   p = (double *) xx->actual;
   q = (double *) xx->actual + 1024;
   while (p < q) *p++ = 0.0;
   /******************************************************************/
   /* calculate the z-score                                          */
   /******************************************************************/
   calc_zedb(xx);
   calcchi(xx->actual, xx->none, xx->ntwo, xx->dblsz);
   freeall(xx);  /* free all allocated memory */
   return(0);    /* end of job */
   } /* main */

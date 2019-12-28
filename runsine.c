/* runsine.c - Runsb test, sine distribution  Version 0.1.0 */
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

/* Runsb test above and below the mean, sine distribution */

/* Initialize the eegl64 random number generator */
/* See the eegl64 repository for more information about */
/* this generator. */

void initrng(xxfmt *xx)
   {
   xx->ee = (eefmt *) eeglinit();
   } /* initrng */

/* Generate one sample from zero to one */
/* following a sine wave distribution */

double gen_dbl(xxfmt *xx)
   {
   double radian;   /* radian from zero to PI */
   double sinx;     /* x = sin(radian)  */
   /* generate a uniform radian from zero to PI */
   radian = eeglunif(xx->ee) * M_PI;
   /* calculate sine of the radian */
   /* sine is from zero to one */
   /* Since the sine is not a uniform distribution */
   /* the samples generated here should fail the */
   /* runs test above and below the mean, in theory. */
   sinx = sin(radian);
   return(sinx);
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
   printf("\n");
   printf("\t      Sine Generator\n");
   printf("\tRuns Above and Below the Mean\n");
   printf("\n");
   /* Initialize the eegl64 random number generator */
   initrng(xx);
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
   /******************************************************************/
   /* calculate the chi square test based on run length              */
   /******************************************************************/
   calcchi(xx->actual, xx->none, xx->ntwo, xx->dblsz);
   freeall(xx);  /* free all allocated memory */
   return(0);    /* end of job */
   } /* main */

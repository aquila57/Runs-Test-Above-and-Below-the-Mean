/* calcchi.c - Chi square test  Version 0.1.0 */
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

void calcchi(double *actual, double none, double ntwo, double N)
   {
   int i;
   double *p,*q;    /* pointers to run lengths */
   double diff;     /* difference between actual and expected */
   double diffsq;   /* difference squared */
   double chisq;    /* chi square */
   double expected;  /* expected count */
   double df;        /* degrees of freedom */
   /* at 95% confidence level */
   double minchi;    /* minimum chi square value */
   double maxchi;    /* maximum chi square value */
   double pvalue;    /* chi square P-value */
   printf("\t\tChi Square Test\n");
   printf("Length      Actual           "
      "Expected        Difference\n");
   chisq = 0.0;
   i = 0;          /* intitialize run length */
   /* actual[] is the array of tallies by run length */
   p = (double *) actual + 1;
   q = (double *) actual + 1024;
   while (p < q)
      {
      /* this is a large test that approximates a normal */ 
      /* distribution */
      /* only include tallies of ten or greater in the */
      /* chi square test */
      if (*p < 10.0) break;
      i++;       /* i = run length */
      /* calculate expected tally by run length */
      /* none is the number of runs above the mean */
      /* ntwo is the number of runs below the mean */
      expected = calc_expval(i, none, ntwo, N);
      /* difference between expected and actual */
      diff = expected - *p;
      /* square the difference to remove the sign */
      diffsq = diff * diff;
      /* add the chi square for this length */
      chisq += (diffsq / expected);
      printf("%4d  %12.0f  %18.5f  %15.0f\n",
         i, *p, expected, diff);
      p++;
      } /* for each actual tally */
   df = (double) (i-1);       /* degrees of freedom */
   /* minimum and maximum chi square range at 95% */
   /* confidence level */
   minchi = gsl_cdf_chisq_Pinv(0.025,df);
   maxchi = gsl_cdf_chisq_Pinv(0.975,df);
   /* calculate P-value of chi square test */
   pvalue = gsl_cdf_chisq_P(chisq,df);
   printf("\n");
   printf("Chi square %f  P-value %f\n", chisq, pvalue);
   printf("\n");
   printf("At 95%c probability and %.0f degrees of freedom,\n"
      "Chi square ranges from %f to %f\n",
      '%', df, minchi, maxchi);
   } /* calcchi */

/* calc_expval.c - Calculate expected value  Version 0.1.0 */
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

/* Calculate expected value for the chi square test */
/* none is the number of runs above the mean */
/* ntwo is the number of runs below the mean */
/* i is the run length */
/* N is the number of samples */

double calc_expval(int i, double none, double ntwo, double N)
   {
   double wi;     /* probability of tally of run lengths */
   double EI;     /* expected run length */
   double expval;    /* expected value for chi square test */
   if (N <= 20.0)
      {
      fprintf(stderr,"calc_expval: N %f is too small\n", N);
      exit(1);
      } /* N is too small */
   /****************************************************************/
   /* see the formulas directory for these calculations            */
   /* in mathematical notation                                     */
   /* the formula for this subroutine is in expval.png             */
   /* and expval2.png                                              */
   /****************************************************************/
   wi = calc_wi(i, none, ntwo, N);   /* calculate probability */
   EI = calc_EI(none, ntwo, N);      /* calculate expected length */
   expval = (N * wi) / EI;      /* calculate expected value */
   return(expval);
   } /* calc_expval */

/* calc_EI.c - Calculate expected run length  Version 0.1.0 */
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

/* Calculate expected run length  */
/* none is the number of runs above the mean */
/* ntwo is the number of runs below the mean */

double calc_EI(double none, double ntwo, double N)
   {
   double n1overn2;   /* ratio of runs above / runs below */
   double n2overn1;   /* ratio of runs below / runs above */
   double EI;         /* expected run length */
   if (N <= 20.0)
      {
      fprintf(stderr,"calc_EI: N %f is too small\n", N);
      exit(1);
      } /* N is too small */
   /****************************************************************/
   /* see the formulas directory for these calculations            */
   /* in mathematical notation                                     */
   /* the formula for this subroutine is in the image ei.png       */
   /****************************************************************/
   n1overn2 = none / ntwo;
   n2overn1 = ntwo / none;
   EI = n1overn2 + n2overn1;  /* add the two ratios together */
   return(EI);
   } /* calc_EI */

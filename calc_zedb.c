/* calc_zedb.c - Calculate Zed Beta   Version 0.1.0 */
/* Copyright (C) 2019 aquila57 at github.com */

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

void calc_zedb(xxfmt *xx)
   {
   int upsw;
   int uppcount;
   int dwncount;
   int upplen;
   int dwnlen;
   double *p,*q;
   double pvalue;
   xx->none = xx->ntwo = 0.0;
   upsw = uppcount = dwncount = 0;
   upplen = dwnlen = 0;
   p = (double *) xx->smpls;
   q = (double *) xx->smpls + SMPLS;
   if (*p < xx->meanb)
      {
      dwncount = 1;
      dwnlen = 1;
      upsw = 0;
      xx->none = 1.0;
      } /* if first obs below mean */
   else if (*p > xx->meanb)
      {
      uppcount = 1;
      upplen = 1;
      upsw = 1;
      xx->ntwo = 1.0;
      } /* if first obs above mean */
   p++;
   while (p < q)
      {
      if (*p < xx->meanb)
	 {
         xx->none += 1.0;
	 if (upsw == 1)
	    {
	    xx->actual[upplen] += 1.0;
	    dwncount++;
	    upsw = 0;
	    upplen = 0;
	    } /* if new run below meanb */
	 dwnlen++;
	 } /* if below mean */
      else if (*p > xx->meanb)
	 {
         xx->ntwo += 1.0;
	 if (upsw == 0)
	    {
	    xx->actual[dwnlen] += 1.0;
	    uppcount++;
	    upsw = 1;
	    dwnlen = 0;
	    } /* if new run below meanb */
	 upplen++;
	 } /* if below mean */
      p++;
      } /* for each sample */
   /****************************************************************/
   /* see the formulas directory for these calculations            */
   /* in mathematical notation                                     */
   /* the formulas for this subroutine are in mubeta .png,         */
   /* variance.png, and zedbeta.png.                               */
   /****************************************************************/
   xx->beta = (double) (uppcount + dwncount);
   xx->mubee = ((2.0 * xx->none * xx->ntwo) / xx->dblsz) + 0.5;
   xx->varianceb = 2.0 * xx->none * xx->ntwo;
   xx->varianceb *= ((2.0 * xx->none * xx->ntwo) - xx->dblsz);
   xx->varianceb /= (xx->dblsz * xx->dblsz) * (xx->dblsz - 1.0);
   xx->zedb = (xx->beta - xx->mubee) / sqrt(xx->varianceb);
   printf("2 * none * ntwo / N = %f\n",
      2.0 * xx->none * xx->ntwo / xx->dblsz);
   printf("beta          %16.5f\n", xx->beta);
   printf("mu beta       %16.5f\n", xx->mubee);
   printf("Variance beta %16.5f\n", xx->varianceb);
   printf("Z beta        %16.5f\n", xx->zedb);
   pvalue = gsl_sf_erf_Q(fabs(xx->zedb));
   /* two tailed p-value */
   printf("P-value       %16.5f\n", pvalue + pvalue);
   printf("\n");
   printf("At 95%c probability,\n", '%');
   printf("Z beta ranges from -1.96 to +1.96\n");
   printf("\n");
   } /* calc_zedb */

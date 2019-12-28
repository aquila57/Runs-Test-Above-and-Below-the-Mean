/* runsfibo.c - Runsb test, fibonacci generator  Version 0.1.0 */
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

#define MYLFSROUT (xx->out = (((xx->lfsr >> 4) \
   ^ (xx->lfsr >> 3) \
   ^ (xx->lfsr >> 1) \
   ^ (xx->lfsr >> 0)) & 1))

#define MYLFSRLOWBIT (xx->lowbit = xx->major & 1)

#define MYLFSRROLL (xx->lfsr0 = xx->major = \
(xx->major >> 1) | (xx->out << 31))

#define MYLFSRCARRY (xx->lfsr = xx->minor = \
(xx->minor >> 1) | (xx->lowbit << 31))

#define MYLFSR (MYLFSROUT,MYLFSRLOWBIT,MYLFSRROLL,MYLFSRCARRY)

void initrng(xxfmt *xx)
   {
   xx->ee = (eefmt *) eeglinit();
   xx->lfsr0  = xx->major = eegl(xx->ee);
   xx->lfsr   = xx->minor = eegl(xx->ee);
   xx->lowbit = xx->out = 0;
   xx->modulus = 65536.0 * 65536.0;
   } /* initrng */

double gen_dbl(xxfmt *xx)
   {
   double newnum;
   MYLFSR;
   newnum = xx->lfsr / xx->modulus;
   return(newnum);
   } /* gen _dbl */

int main(void)
   {
   double *p,*q;
   xxfmt *xx;
   xx = (xxfmt *) malloc(sizeof(xxfmt));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx\n");
      exit(1);
      } /* out of memory */
   xx->smpls = (double *) malloc(sizeof(double) * SMPLS + 10);
   if (xx->smpls == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx->smpls\n");
      exit(1);
      } /* out of memory */
   printf("\n");
   printf("\t      LFSR Generator\n");
   printf("\tRuns Above and Below the Mean\n");
   printf("\n");
   initrng(xx);
   xx->dblsz = (double) SMPLS;
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
   freeall(xx);
   return(0);
   } /* main */

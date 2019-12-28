/* runsdie.c - Runs Test Up and Down, dieharder  Version 0.1.0 */
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
#include <errno.h>

void bld_rngtbl(xxfmt *xx);
void bld_maxint(xxfmt *xx);
double getdie(xxfmt *xx);

void putstx(char *pgm)
   {
   fprintf(stderr,"Usage: %s Dieharder_RNG_number\n", pgm);
   fprintf(stderr,"Example: %s 208\n", pgm);
   fprintf(stderr,"Where 208 is the kiss generator\n");
   fprintf(stderr,"Example: %s 053\n", pgm);
   fprintf(stderr,"Where 053 is the taus2 generator\n");
   exit(1);
   } /* putstx */

void diepfx(xxfmt *xx)
   {
   int len;
   int rslt;
   int namesw;
   char buf[256];
   namesw = 0;
   xx->dieharder_rngname[0] = '\0';
   while (1)
      {
      len = scanf("%s", buf);
      if (len < 1)
         {
         if (feof(stdin))
	    {
	    fprintf(stderr,"diepfx: scanf end of file\n");
	    exit(1);
	    } /* if end of file */
         if (ferror(stdin))
            {
            perror("diepfx: read error\n");
            exit(1);
            } /* read error */
         fprintf(stderr,"diepfx: blank line, len %d\n", len);
         exit(1);
         } /* if eof or read error */
      if (len > 1)
         {
         fprintf(stderr,"diepfx: read error\n");
         fprintf(stderr,"scanf read more than "
            "one token %d\n", len);
         exit(1);
         } /* invalid input */
      rslt = strcmp(buf,"numbit:");
      if (!rslt) break;
      if (namesw)   /* buf = generator name? */
         {
	 strcpy(xx->dieharder_rngname,buf);
	 fprintf(stderr,"Dieharder RNG Name %s\n",
	    xx->dieharder_rngname);
	 namesw = 0;    /* turn off name switch */
	 } /* if generator name switch turned on */
      rslt = strcmp(buf,"generator");
      if (!rslt)
         {
	 namesw = 1;    /* turn on name switch */
	 } /* if generator statement */
      } /* read loop until numbit: */
   len = scanf("%s", buf);
   if (len < 1)
      {
      if (feof(stdin))
	 {
	 fprintf(stderr,"diepfx: scanf end of file\n");
	 exit(1);
	 } /* if end of file */
      if (ferror(stdin))
         {
         perror("getdie: read error\n");
         exit(1);
         } /* read error */
      fprintf(stderr,"getdie: blank line\n");
      exit(1);
      } /* if eof or read error */
   if (len > 1)
      {
      fprintf(stderr,"getdie: read error\n");
      fprintf(stderr,"scanf read more than "
         "one token %d\n", len);
      exit(1);
      } /* invalid input */
   rslt = strcmp(buf,"32");
   if (rslt)
      {
      fprintf(stderr,"diepfx: numbit not = 32\n");
      fprintf(stderr,"buf = %s\n", buf);
      exit(1);
      } /* numbit: not equal to 32 */
   } /* diepfx */

/* generate a uniform random number from zero to one */
double gen_dbl(xxfmt *xx)
   {
   double num;
   num = getdie(xx);
   if (xx->eofsw)
      {
      fprintf(stderr,"gen_dbl: end of "
         "file %.0f\n", xx->count);
      num = EOFDIE;
      } /* end of file condition */
   else
      {
      xx->count += 1.0;
      } /* else not eof */
   return(num);
   } /* gen_dbl */

int main(int argc, char **argv)
   {
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

   xx->smpls = (double *) malloc (128 + (sizeof(double) * SMPLS));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx->smpls\n");
      exit(1);
      } /* out of memory */

   /*************************************************************/
   /* initialize global data                                    */
   /*************************************************************/
   xx->dieharder_rngname[0] = '\0';
   xx->rngname = (char *) NULL;
   xx->generator = -1;
   xx->eofsw     = 0;

   /*************************************************************/
   /* obtain dieharder generator number parameter               */
   /*************************************************************/

   if (argc != 2) putstx(*argv);
   xx->generator = atoi(*(argv+1));
   if (xx->generator < 0 || xx->generator > 405)
      {
      fprintf(stderr,"main: invalid random "
         "number generator %s\n", *(argv+1));
      putstx(*argv);
      } /* invalid generator */

   /*************************************************************/
   /* initialize numeric fields                                 */
   /*************************************************************/
   xx->eofsw = 0;
   bld_maxint(xx);  /* build maxint table for dieharder RNGs */
   if (xx->maxint_tbl[xx->generator] == 0.0)
      {
      fprintf(stderr,"main: invalid random "
         "number generator %s\n", *(argv+1));
      putstx(*argv);
      } /* invalid generator */
   bld_rngtbl(xx);  /* build name table for dieharder RNGs */
   xx->modulus = xx->maxint_tbl[xx->generator];
   xx->maxint  = (unsigned int) xx->modulus;
   /****************************************************/
   diepfx(xx);    /* bypass dieharder prefix */
   printf("\n");
   printf("\t Dieharder Generator: %s\n",
      xx->dieharder_rngname);
   printf("\tRuns Above and Below the Mean\n");
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
   /* calculate the z-score                                          */
   /******************************************************************/
   calc_zedb(xx);      /* compute Z-score */
   /******************************************************************/
   /* calculate the chi square test based on run length              */
   /******************************************************************/
   calcchi(xx->actual, xx->none, xx->ntwo, xx->dblsz);
   freeall(xx);  /* free all allocated memory */
   } /* main */

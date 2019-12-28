#  runsdie.mak - Compile runsdie.c Version 0.1.0
#  Copyright (C) 2019 aquila57 at github.com

#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License as
#  published by the Free Software Foundation; either version 2 of
#  the License, or (at your option) any later version.

#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to:

   #  Free Software Foundation, Inc.
   #  59 Temple Place - Suite 330
   #  Boston, MA 02111-1307, USA.

OBJ=runsdie.o \
	bld_rngtbl.o \
	bld_maxint.o \
	getbyte.o \
	getdie.o \
	fillsmpls.o \
	getmean.o \
	calc_EI.o \
	calc_wi.o \
	calc_zedb.o \
	calcchi.o \
	calc_expval.o \
	permute.o \
	freeall.o \
	eeglinit.o \
	eegl.o \
	eeglunif.o

CC=gcc

CFLAGS=-c -Wall -O2

LDFLAGS=-lgsl -lgslcblas -lm

runsdie:			$(OBJ)
		$(CC) -Wall -O2 $(OBJ) -o runsdie $(LDFLAGS)

runsdie.o:			runsdie.c
		$(CC) $(CFLAGS) runsdie.c

bld_rngtbl.o:			bld_rngtbl.c
		$(CC) $(CFLAGS) bld_rngtbl.c

bld_maxint.o:			bld_maxint.c
		$(CC) $(CFLAGS) bld_maxint.c

getbyte.o:			getbyte.c
		$(CC) $(CFLAGS) getbyte.c

getdie.o:			getdie.c
		$(CC) $(CFLAGS) getdie.c

fillsmpls.o:			fillsmpls.c
		$(CC) $(CFLAGS) fillsmpls.c

getmean.o:			getmean.c
		$(CC) $(CFLAGS) getmean.c

calc_EI.o:			calc_EI.c
		$(CC) $(CFLAGS) calc_EI.c

calc_wi.o:			calc_wi.c
		$(CC) $(CFLAGS) calc_wi.c

calc_zedb.o:			calc_zedb.c
		$(CC) $(CFLAGS) calc_zedb.c

calcchi.o:			calcchi.c
		$(CC) $(CFLAGS) calcchi.c

calc_expval.o:			calc_expval.c
		$(CC) $(CFLAGS) calc_expval.c

permute.o:			permute.c
		$(CC) $(CFLAGS) permute.c

freeall.o:			freeall.c
		$(CC) $(CFLAGS) freeall.c

eeglinit.o:			eeglinit.c
		$(CC) $(CFLAGS) eeglinit.c

eegl.o:				eegl.c
		$(CC) $(CFLAGS) eegl.c

eeglunif.o:			eeglunif.c
		$(CC) $(CFLAGS) eeglunif.c

clean:
		rm -f $(OBJ) runsdie

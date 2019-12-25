#  runsine.mak - Compile runsine.c Version 0.1.0
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

#--------------------------------------------------------
# The LFSR in this generator comes from the following
# http://courses.cse.tamu.edu/walker/csce680/
# lfsr_table.pdf
# 64 bit LFSR is 64,63,61,60 with low order bit equal
# to 64
#--------------------------------------------------------

OBJ=runsine.o \
	fillsmpls.o \
	getmean.o \
	calc_zedb.o \
	calcchi.o \
	calc_expval.o \
	calc_EI.o \
	calc_wi.o \
	permute.o \
	freeall.o \
	eeglinit.o \
	eegl.o \
	eeglunif.o

CC=gcc

CFLAGS=-c -Wall -O2

LDFLAGS=-lgsl -lgslcblas -lm

runsine:			$(OBJ)
		$(CC) -Wall -O2 $(OBJ) -o runsine $(LDFLAGS)

runsine.o:			runsine.c
		$(CC) $(CFLAGS) runsine.c

fillsmpls.o:			fillsmpls.c
		$(CC) $(CFLAGS) fillsmpls.c

getmean.o:			getmean.c
		$(CC) $(CFLAGS) getmean.c

freeall.o:			freeall.c
		$(CC) $(CFLAGS) freeall.c

calc_zedb.o:			calc_zedb.c
		$(CC) $(CFLAGS) calc_zedb.c

calcchi.o:			calcchi.c
		$(CC) $(CFLAGS) calcchi.c

calc_expval.o:			calc_expval.c
		$(CC) $(CFLAGS) calc_expval.c

calc_EI.o:			calc_EI.c
		$(CC) $(CFLAGS) calc_EI.c

calc_wi.o:			calc_wi.c
		$(CC) $(CFLAGS) calc_wi.c

permute.o:			permute.c
		$(CC) $(CFLAGS) permute.c

eeglinit.o:			eeglinit.c
		$(CC) $(CFLAGS) eeglinit.c

eegl.o:				eegl.c
		$(CC) $(CFLAGS) eegl.c

eeglunif.o:			eeglunif.c
		$(CC) $(CFLAGS) eeglunif.c

clean:
		rm -f $(OBJ) runsine
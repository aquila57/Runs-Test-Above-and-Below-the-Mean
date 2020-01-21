#  libruns.mak - Compile subroutine library Version 0.1.0
#  Copyright (C) 2020 aquila57 at github.com

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

OBJ=fillsmpls.o \
	getmean.o \
	calc_zedb.o \
	calcchi.o \
	calc_expval.o \
	calc_EI.o \
	calc_wi.o \
	permute.o \
	freeall.o \
	getdie.o \
	bld_maxint.o \
	bld_rngtbl.o \
	eeglinit.o \
	eegl.o \
	eeglunif.o \
	eeglabt.o \
	eeglbit.o \
	eeglcrc.o \
	eegldspl.o \
	eegl.o \
	eeglinit.o \
	eeglstrt.o \
	eeglint.o \
	eeglpwr.o \
	eeglsd.o \
	eeglunif.o \
	eeglfrac.o \
	etausabt.o \
	etausbit.o \
	etaus.o \
	etausdspl.o \
	etausfrac.o \
	etausinit.o \
	etausint.o \
	etauspwr.o \
	etausstrt.o \
	etausunif.o

CC=gcc

CFLAGS=-c -Wall -O2

LDFLAGS=-lgsl -lgslcblas -lm

libruns.a:			$(OBJ)
		rm -f libruns.a
		ar r libruns.a $(OBJ)

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

getdie.o:			getdie.c
		$(CC) $(CFLAGS) getdie.c

bld_maxint.o:			bld_maxint.c
		$(CC) $(CFLAGS) bld_maxint.c

bld_rngtbl.o:			bld_rngtbl.c
		$(CC) $(CFLAGS) bld_rngtbl.c

eeglinit.o:			eeglinit.c
		$(CC) $(CFLAGS) eeglinit.c

eegl.o:				eegl.c
		$(CC) $(CFLAGS) eegl.c

eeglunif.o:			eeglunif.c
		$(CC) $(CFLAGS) eeglunif.c

eeglabt.o:			eeglabt.c
		$(CC) $(CFLAGS) eeglabt.c

eeglbit.o:			eeglbit.c
		$(CC) $(CFLAGS) eeglbit.c

eeglcrc.o:			eeglcrc.c
		$(CC) $(CFLAGS) eeglcrc.c

eegldspl.o:			eegldspl.c
		$(CC) $(CFLAGS) eegldspl.c

eeglstrt.o:			eeglstrt.c
		$(CC) $(CFLAGS) eeglstrt.c

eeglint.o:			eeglint.c
		$(CC) $(CFLAGS) eeglint.c

eeglpwr.o:			eeglpwr.c
		$(CC) $(CFLAGS) eeglpwr.c

eeglsd.o:			eeglsd.c
		$(CC) $(CFLAGS) eeglsd.c

eeglfrac.o:			eeglfrac.c
		$(CC) $(CFLAGS) eeglfrac.c

etausinit.o:			etausinit.c
		$(CC) $(CFLAGS) etausinit.c

etaus.o:			etaus.c
		$(CC) $(CFLAGS) etaus.c

etausunif.o:			etausunif.c
		$(CC) $(CFLAGS) etausunif.c

etausabt.o:			etausabt.c
		$(CC) $(CFLAGS) etausabt.c

etausbit.o:			etausbit.c
		$(CC) $(CFLAGS) etausbit.c

etausdspl.o:			etausdspl.c
		$(CC) $(CFLAGS) etausdspl.c

etausstrt.o:			etausstrt.c
		$(CC) $(CFLAGS) etausstrt.c

etausint.o:			etausint.c
		$(CC) $(CFLAGS) etausint.c

etauspwr.o:			etauspwr.c
		$(CC) $(CFLAGS) etauspwr.c

etausfrac.o:			etausfrac.c
		$(CC) $(CFLAGS) etausfrac.c

clean:
		rm -f $(OBJ) libruns.a

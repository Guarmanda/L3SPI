# MAKEFILE pour Cours sur les files de messages
#
#

#
# Directories
#
#top_dir = $HOME/Enseignements/IUPMIME/Licence/L3/TP/TP_Course


#
# Object files
#

fich_obj_scheduller_RR = scheduller_RR.o com.o proc.o
fich_obj_scheduller_FIFO = scheduller_FIFO.o com.o proc.o
fich_obj_test_com = test_com.o com.o
fich_obj_test_proc = test_proc.o proc.o
fich_obj_prog_sleep= prog_sleep.o 
fich_obj_prog_scan= prog_scan.o 

#
# Options for compilation
#

GCCOBJ = gcc -c 
GCCLNK = gcc 


# Option for debugger
opt = -g -Wall -D_DEBUG_
# opt = -O2 -Wall
#
#
#

#
#-------- Mains ---------------
#

BIN = scheduller_RR scheduller_FIFO prog_sleep prog_scan test_com test_proc

scheduller_RR : $(fich_obj_scheduller_RR)
	$(GCCLNK) $(fich_obj_scheduller_RR) $(opt) -o scheduller_RR -I ./

scheduller_RR.o : scheduller_RR.c 				
	$(GCCOBJ) $(opt) scheduller_RR.c -o scheduller_RR.o -I ./

scheduller_FIFO : $(fich_obj_scheduller_FIFO)
	$(GCCLNK) $(fich_obj_scheduller_FIFO) $(opt) -o scheduller_FIFO -I ./

scheduller_FIFO.o : scheduller_FIFO.c 				
	$(GCCOBJ) $(opt) scheduller_FIFO.c -o scheduller_FIFO.o -I ./


prog_sleep : $(fich_obj_prog_sleep)
	$(GCCLNK) $(fich_obj_prog_sleep) $(opt) -o prog_sleep -I ./

prog_sleep.o : prog_sleep.c 				
	$(GCCOBJ) $(opt) prog_sleep.c -o prog_sleep.o -I ./

prog_scan : $(fich_obj_prog_scan)
	$(GCCLNK) $(fich_obj_prog_scan) $(opt) -o prog_scan -I ./

prog_scan.o : prog_scan.c 				
	$(GCCOBJ) $(opt) prog_scan.c -o prog_scan.o -I ./

#
# --- Tests ---
#

test_com : $(fich_obj_test_com)
	$(GCCLNK) $(fich_obj_test_com) $(opt) -o test_com -I ./

test_com.o : test_com.c 				
	$(GCCOBJ) $(opt) test_com.c -o test_com.o -I ./

test_proc : $(fich_obj_test_proc)
	$(GCCLNK) $(fich_obj_test_proc) $(opt) -o test_proc -I ./

test_proc.o : test_proc.c 				
	$(GCCOBJ) $(opt) test_proc.c -o test_proc.o -I ./

#
#-------- Modules -------------
#

com.o : com.c com.h
	$(GCCOBJ) $(opt) com.c -o com.o -I ./

proc.o : proc.c proc.h
	$(GCCOBJ) $(opt) proc.c -o proc.o -I ./


#
#-------- Headers -------------
#

com.h : commun.h 
	touch com.h


proc.h : commun.h 
	touch proc.h


#
#-------- Clean objects -------
#

clean :
	- rm $(BIN) *.o *~

#
#-------- All executables -------
#

all : scheduller_RR \
	scheduller_FIFO \
	test_com \
	test_proc \
	prog_sleep \
	prog_scan

#
#-------- All tests -------
#
tests : 
	./test_com fichier_commandes.txt ; ./test_proc 10 
#
#-------- Tags -------
#

tags :
	etags *.c 
#
#-------- Distribution -------
#

dist : 

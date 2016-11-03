#
# Makefile pour le TP "Anneau de processus" 
#

#
# Fichiers objets 
#
jeton_fich_obj = jeton.o 
anneau_fich_obj = anneau.o

#
# Option de compilation 
#

opt = -g -Wall 
CCOBJ = gcc -c 
CCLNK = gcc 


#
# Executables
#

jeton : $(jeton_fich_obj)
	$(CCLNK) $(opt) $(jeton_fich_obj) -o jeton

jeton.o : jeton.c
	$(CCOBJ) $(opt) jeton.c -o jeton.o

anneau : $(anneau_fich_obj)
	$(CCLNK) $(opt) $(anneau_fich_obj) -o anneau

anneau.o : anneau.c
	$(CCOBJ) $(opt) anneau.c -o anneau.o

#
# Utilitaires
#

clean : 
	- rm *.o ;  

all : jeton anneau

dist : 
	tar cvf Jeton.tar Makefile jeton.c
	gzip Jeton.tar

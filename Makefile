#############################################################################
# Fichier Makefile
# UE MAP401 - DLST - UGA - 2017/2018
#############################################################################
# utilisation des variables internes $< $@ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = test_image_pbm test_calcul test_contour test_trace_eps test_calcul2


#############################################################################
# definition des regles
#############################################################################

########################################################
# la r�gle par d�faut
all : $(EXECUTABLES)

########################################################
# regle generique :
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
tableau.o : tableau.c tableau.h calcul.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module tableau"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

calcul_contour.o : calcul_contour.c types_macros.h image_pbm.h tableau.h calcul.h calcul_contour.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module de calcul des contours"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<


image_pbm.o : image_pbm.c image_pbm.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

calcul.o : calcul.c calcul.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module calcul"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

trace_graphique.o : trace_graphique.c trace_graphique.h types_macros.h calcul.h tableau.h calcul_contour.h image_pbm.h multi_contour.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module de tracage eps"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

multi_contour.o : multi_contour.c multi_contour.h tableau.h types_macros.h image_pbm.h calcul.h calcul_contour.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module de contour multiple"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_image_pbm.o : test_image_pbm.c image_pbm.h types_macros.h multi_contour.h tableau.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<


test_calcul.o : test_calcul.c calcul.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_calcul"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_calcul2.o : test_calcul2.c calcul.c calcul.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_calcul"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_contour.o : test_contour.c tableau.h calcul.h image_pbm.h types_macros.h calcul_contour.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_trace_eps.o : test_trace_eps.c trace_graphique.h types_macros.h calcul.h tableau.h calcul_contour.h image_pbm.h multi_contour.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test tracage eps"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<



########################################################
# regles explicites de creation des executables

test_image_pbm : test_image_pbm.o image_pbm.o tableau.o multi_contour.o calcul_contour.o calcul.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_calcul: test_calcul.o calcul.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable"$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_calcul2: test_calcul2.o calcul.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable"$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_contour: test_contour.o calcul.o calcul_contour.o tableau.o image_pbm.o multi_contour.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable"$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_trace_eps:  test_trace_eps.o calcul.o tableau.o calcul_contour.o image_pbm.o multi_contour.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@


# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o

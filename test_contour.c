#include<stdio.h>
#include<stdlib.h>
#include"calcul.h"
#include"tableau.h"
#include"types_macros.h"
#include"image_pbm.h"
#include"calcul_contour.h"
#include "multi_contour.h"

void print_tab(tableau t ){
	for (int i=0 ; i<t.taille ; i++){
		printf("point: %d , x=%f , y=%f\n" , i , t.tab[i].x , t.tab[i].y);
	}
}

void enregistrer (tableau t , FILE * f){
	fprintf(f, "1\n\n");
	fprintf(f, "%d\n", t.taille);
	for (int i=0 ; i<t.taille ; i++){
		fprintf(f, " %.1f %.1f\n", t.tab[i].x , t.tab[i].y);
	}
}


int main (int argc, char *argv[]){
	Image img;

	if (argc != 2){
		ERREUR_FATALE("nombre d'arguments incorrect\n");
	}
	/*
	img = lire_fichier_image(argv[1]);
	ecrire_image(img);
	printf("début du calcul des contours !\n");
	t = contour(img);
	printf(" \n------CONTOURS FINI------\n\n");
	printf("Nom: %s \nDimensions: %d X %d \nNb points: %d \n",argv[1], img.L , img.H , t.taille);
	f = fopen("fichier_resultat.txt", "w");
	enregistrer(t, f);
	fclose(f);
	*/
	tableau_contour tc;
	img = lire_fichier_image(argv[1]);
	tc = multi_contour(img);
	printf("il y a %d contours\n", tc.taille);

	return 0;
}

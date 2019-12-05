#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "calcul.h"
#include "tableau.h"
#include"types_macros.h"
#include"image_pbm.h"
#include "multi_contour.h"

int main (int argc, char *argv[]){

	Image img;
	Image img2;
	tableau_contour tableau_contour1;
	if (argc != 2){
		ERREUR_FATALE("nombre d'arguments incorrect\n");
	}
	img = lire_fichier_image(argv[1]);
	//ecrire_image(img);
	img2 = masque(img);
	//ecrire_image(img2);
	tableau_contour1 = multi_contour(img);
	//printf("L'image a %d contours !\n", tableau_contour1.taille);

	FILE * f;
	f = fopen("fichier_resultat.txt", "w");
	enregistrer_contour (tableau_contour1 , f);

	somme_contours(tableau_contour1);

	return 0;
}

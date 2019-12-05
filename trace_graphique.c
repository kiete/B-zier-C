#include <stdlib.h>
#include <stdio.h>
#include "types_macros.h"
#include "types_macros.h"
#include "image_pbm.h"
#include "calcul.h"
#include "tableau.h"
#include "calcul_contour.h"
#include "multi_contour.h"
#include "trace_graphique.h"


void trace_eps (FILE * sortie , char * entree , int mode ){
	int i = 0;
	Image img = lire_fichier_image(entree);

	tableau t = contour(img);

	fprintf(sortie, "%c!PS-Adobe-3.0 EPSF-3.0\n", 37);
	fprintf(sortie, "%c%cBoundingBox: 0 0 %d %d\n\n",37, 37, img.H , img.L);

	fprintf(sortie, "%.1f %.1f ", img.H-t.tab[i].x , img.L-t.tab[i].y);
	fprintf(sortie, "moveto ");

	for (i= 1 ; i<t.taille ; i++){
		fprintf(sortie, "%.1f %.1f ", img.H-t.tab[i].x , img.L-t.tab[i].y);
		fprintf(sortie, "lineto\n");

	}
	if (mode == 1){
		fprintf(sortie, "stroke\n");
	}
	if (mode == 2){
		for (i=0 ; i<t.taille ; i++){
			fprintf(sortie, "newpath %.1f %.1f 1 0 360 arc", img.H-t.tab[i].x , img.L-t.tab[i].y);
			fprintf(sortie, "\nstroke\nclosepath\n");
		}
	}

	if (mode == 3){
		fprintf(sortie, "\nfill\n");
	}

	fprintf(sortie, "\nshowpage\n");
}

void trace_eps_plus (FILE * sortie , char * entree , int mode ){
	int i = 0;
	Image img = lire_fichier_image(entree);

	tableau_contour t = multi_contour(img);

	fprintf(sortie, "%c!PS-Adobe-3.0 EPSF-3.0\n", 37);
	fprintf(sortie, "%c%cBoundingBox: 0 0 %d %d\n\n",37, 37, img.L , img.H);
	for (int j = 0 ; j < t.taille ; j++) {
		i=0;
		fprintf(sortie, "%.1f %.1f ", t.tab[j].tab[i].x, img.L - t.tab[j].tab[i].y);
		fprintf(sortie, "moveto\n");

		for (i = 1; i < t.tab[j].taille ; i++) {
			fprintf(sortie, "%.1f %.1f ", t.tab[j].tab[i].x, img.L - t.tab[j].tab[i].y);
			fprintf(sortie, "lineto\n");

		}
        fprintf(sortie, "%.1f %.1f ", t.tab[j].tab[0].x, img.L - t.tab[j].tab[0].y);
		fprintf(sortie, "lineto\n");
		if (mode == 1) {
			fprintf(sortie, "stroke\n");
		}
		if (mode == 2) {
			for (i = 0; i < t.taille; i++) {
				fprintf(sortie, "newpath %.1f %.1f 1 0 360 arc", t.tab[j].tab[i].x, img.L - t.tab[j].tab[i].y);
				fprintf(sortie, "\nstroke\nclosepath\n");
			}
		}
	}

	if (mode == 3) {
		fprintf(sortie, "\nfill\n");
	}

	fprintf(sortie, "\nshowpage\n");
}

void trace_simplifie (FILE * sortie , char * entree , double seuil ){
	int i = 0;
	int sommet = 0;
	int sommet2 = 0;
	Image img = lire_fichier_image(entree);

	tableau_contour t = multi_contour(img);

	// On crée un nouveau tableau qui contiendra la liste de points simplifiée

	tableau_contour t2 = nouveau_tab_contour();

	tableau t_temp;
	

	for(int i = 0 ; i<t.taille ; i++){
		// La fonction de simplification fait de la merde
		t_temp = nouveau_tab();
		t_temp = simplification(t.tab[i] , 0 , t.tab[i].taille-1 , seuil);
		//printf("Temp.taille = %d \n",t_temp.taille);
		//printf("BIP\n");
		t2 = ajout_point_contour (t2 , t_temp);
		sommet = sommet + t.tab[i].taille-1;
		sommet2 = sommet2 + t_temp.taille -1; 
	}
	printf("Nombre d'élément au dépard : %d , Nombre de courbes de beziers 3 dans l'image simplifiée :  %d \n" , sommet , sommet2);
	

	//printf("%d , %f.\n", t.taille , t.tab[0].tab[0].x);
	fprintf(sortie, "%c!PS-Adobe-3.0 EPSF-3.0\n", 37);
	fprintf(sortie, "%c%cBoundingBox: 0 0 %d %d\n\n",37, 37, img.L , img.H);
	int j = 0 ;
	for (j = 0 ; j < t2.taille ; j++) {
		i=0;
		fprintf(sortie, "%.1f %.1f ", t2.tab[j].tab[i].x, img.L - t2.tab[j].tab[i].y);
		fprintf(sortie, "moveto\n");

		for (i = 1; i < t2.tab[j].taille ; i++) {
			fprintf(sortie, "%.1f %.1f ", t2.tab[j].tab[i].x, img.L - t2.tab[j].tab[i].y);
			fprintf(sortie, "lineto\n");

		}
        fprintf(sortie, "%.1f %.1f ", t2.tab[j].tab[0].x, img.L - t2.tab[j].tab[0].y);
		fprintf(sortie, "lineto\n");

	}
	printf("Nombre de contour de l'image = %d \n" , t2.taille );
	fprintf(sortie, "\nfill\n");

	fprintf(sortie, "\nshowpage\n");
}

void trace_bezier3 (FILE * sortie , char * entree , double seuil ){
	int i = 0;
	int sommet = 0;
	int sommet2 = 0;
	Image img = lire_fichier_image(entree);

	tableau_contour t = multi_contour(img);

	// On crée un nouveau tableau qui contiendra la liste de points simplifiée

	tableau_contour_bezier3 t2 = nouveau_tab_contour_bezier3();

	tableau_bezier3 t_temp;
	

	for(int i = 0 ; i<t.taille ; i++){
		// La fonction de simplification fait de la merde
		t_temp = nouveau_tab_bezier3();
		t_temp = simplification3(t.tab[i] , 0 , t.tab[i].taille-1 , seuil);
		//printf("Temp.taille = %d \n",t_temp.taille);
		//printf("BIP\n");
		t2 = ajout_point_contour_bezier3 (t2 , t_temp);
		sommet = sommet + t.tab[i].taille-1;
		sommet2 = sommet2 + t_temp.taille -1; 
	}
	printf("Nombre d'élément au dépard : %d , Nombre de courbes de beziers 3 dans l'image simplifiée :  %d \n" , sommet , sommet2);
	

	//printf("%d , %f.\n", t.taille , t.tab[0].tab[0].x);
	fprintf(sortie, "%c!PS-Adobe-3.0 EPSF-3.0\n", 37);
	fprintf(sortie, "%c%cBoundingBox: 0 0 %d %d\n\n",37, 37, img.L , img.H);
	int j = 0;
	for (j = 0 ; j < t2.taille ; j++) {
		
		i=0;
		fprintf(sortie, "%f %f ", t2.tab[j].tab[i].c0.x, img.L - t2.tab[j].tab[i].c0.y);
		fprintf(sortie, "moveto\n");
		
		//printf("Contour j = %d \n" , j);
		//printf("Départ = (%.f , %.f) et arrivé = (%.f , %.f)\n",t2.tab[j].tab[0].c0.x , t2.tab[j].tab[0].c0.y , t2.tab[j].tab[t2.tab[j].taille - 1].c3.x , t2.tab[j].tab[t2.tab[j].taille - 1].c3.y);
		for (i = 1; i < t2.tab[j].taille ; i++) {


			// printf("i = %d , x = %f , y = %f \n" , i , t2.tab[j].tab[i].c0.x , img.L - t2.tab[j].tab[i].c0.y);

			
			fprintf(sortie, "%f %f %f %f %f %f ", t2.tab[j].tab[i].c1.x, img.L - t2.tab[j].tab[i].c1.y, t2.tab[j].tab[i].c2.x, img.L - t2.tab[j].tab[i].c2.y, t2.tab[j].tab[i].c3.x, img.L - t2.tab[j].tab[i].c3.y);
			fprintf(sortie, "curveto\n");

		}/*
        fprintf(sortie, "%.1f %.1f %.1f %.1f %.1f %.1f ", t2.tab[j].tab[0].c1.x, img.L - t2.tab[j].tab[0].c1.y, t2.tab[j].tab[0].c2.x, img.L - t2.tab[j].tab[0].c2.y, t2.tab[j].tab[0].c3.x, img.L - t2.tab[j].tab[0].c3.y);
			fprintf(sortie, "curveto\n");
*/
	
	}
	printf("Nombre de contour de l'image = %d \n" , t2.taille);


	fprintf(sortie, "\nfill\n");

	fprintf(sortie, "\nshowpage\n");
}

void trace_bezier2 (FILE * sortie , char * entree , double seuil ){
	int i = 0;
	int sommet = 0;
	int sommet2 = 0;
	Image img = lire_fichier_image(entree);

	tableau_contour t = multi_contour(img);

	// On crée un nouveau tableau qui contiendra la liste de points simplifiée

	tableau_contour_bezier3 t2 = nouveau_tab_contour_bezier3();

	tableau_bezier3 t_temp;
	

	for(int i = 0 ; i<t.taille ; i++){
		// La fonction de simplification fait de la merde
		t_temp = nouveau_tab_bezier3();
		t_temp = simplification2(t.tab[i] , 0 , t.tab[i].taille-1 , seuil);
		//printf("Temp.taille = %d \n",t_temp.taille);
		//printf("BIP\n");
		t2 = ajout_point_contour_bezier3 (t2 , t_temp);
		sommet = sommet + t.tab[i].taille-1;
		sommet2 = sommet2 + t_temp.taille -1; 
	}
	printf("Nombre d'élément au dépard : %d , Nombre de courbes de beziers 3 dans l'image simplifiée :  %d \n" , sommet , sommet2);
	

	//printf("%d , %f.\n", t.taille , t.tab[0].tab[0].x);
	fprintf(sortie, "%c!PS-Adobe-3.0 EPSF-3.0\n", 37);
	fprintf(sortie, "%c%cBoundingBox: 0 0 %d %d\n\n",37, 37, img.L , img.H);
	int j = 0; 
	for (j = 0 ; j < t2.taille ; j++) {
		
		i=0;
		fprintf(sortie, "%.1f %.1f ", t2.tab[j].tab[i].c0.x, img.L - t2.tab[j].tab[i].c0.y);
		fprintf(sortie, "moveto\n");
		
		//printf("Contour j = %d \n" , j);

		for (i = 1; i < t2.tab[j].taille ; i++) {


			// printf("i = %d , x = %f , y = %f \n" , i , t2.tab[j].tab[i].c0.x , img.L - t2.tab[j].tab[i].c0.y);


			fprintf(sortie, "%.1f %.1f %.1f %.1f %.1f %.1f ", t2.tab[j].tab[i].c1.x, img.L - t2.tab[j].tab[i].c1.y, t2.tab[j].tab[i].c2.x, img.L - t2.tab[j].tab[i].c2.y, t2.tab[j].tab[i].c3.x, img.L - t2.tab[j].tab[i].c3.y);
			fprintf(sortie, "curveto\n");

		}/*
        fprintf(sortie, "%.1f %.1f %.1f %.1f %.1f %.1f ", t2.tab[j].tab[0].c1.x, img.L - t2.tab[j].tab[0].c1.y, t2.tab[j].tab[0].c2.x, img.L - t2.tab[j].tab[0].c2.y, t2.tab[j].tab[0].c3.x, img.L - t2.tab[j].tab[0].c3.y);
			fprintf(sortie, "curveto\n");
*/
		

	}
	printf("Nombre de contour de l'image = %d \n" , t2.taille);

	fprintf(sortie, "\nfill\n");

	fprintf(sortie, "\nshowpage\n");
}


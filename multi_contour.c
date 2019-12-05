#include<stdio.h>
#include<stdlib.h>
#include "types_macros.h"
#include "calcul.h"
#include "tableau.h"
#include "image_pbm.h"
#include "calcul_contour.h"
#include "multi_contour.h"

Image masque(Image I){
	Image masque;
	masque = creer_image(I.L, I.H);
	int j = 1;
	for(int i = 1; i <= I.L; i++ ){
		if (get_pixel_image(I, i, j) == NOIR){
			set_pixel_image(masque, i, j, NOIR);
			}
		}
	for(j = 2; j <= I.H; j++ ){
		for(int i = 1; i <= I.L; i++ ){
			if ((get_pixel_image(I, i, j) == NOIR) && (get_pixel_image(I, i, j-1) == BLANC)){
				set_pixel_image(masque, i, j, NOIR);
			}
		}
	}
	return masque;
}

tableau contour_plus (Image img , Image mask) {
	robot *r = malloc(sizeof(robot));
	point p1;
	p1 = premier_pixel(mask);
	//printf("Départ x = %f y = %f\n", p1.x , p1.y);
	p1.x--;
	p1.y--;
	r->x = p1.x;
	r->y = p1.y;
	r->o = E;
	tableau t;
	t = nouveau_tab();
	//t = memoriser(t, *r);
	do {
		avancer(r);
		if (r->o == E){
			set_pixel_image (mask , r->x , r->y +1 , BLANC);
		}
		t = memoriser(t, *r);
		nouvelle_orientation(r, img);
	} while ((r->x != (p1.x)) || (r->y != (p1.y)) || (r->o != E));
	avancer(r);
	t = memoriser(t, *r);
	//ecrire_image(mask);
	return t;
	}


tableau_contour multi_contour (Image img){
	tableau t;
	tableau_contour tc = nouveau_tab_contour();

	Image mask;
	mask = masque(img);
	int i = 0;
	do{
		t = contour_plus(img , mask);
		tc = ajout_point_contour (tc,t);
		i++;
	}while(existe_premier_pixel(mask));
	return tc;
}

void enregistrer_contour (tableau_contour t , FILE * f){
	fprintf(f, "%d\n" , t.taille);
	for (int j=0 ; j<t.taille ; j++) {
		fprintf(f, "\n");
		fprintf(f, "%d\n", t.tab[j].taille);
		for (int i = 0; i < t.tab[j].taille; i++) {
			fprintf(f, " %.1f %.1f\n", t.tab[j].tab[i].x, t.tab[j].tab[i].y);
		}
	}
}

void somme_contours (tableau_contour t){
	int nb_pts = 0;
	for (int i=0 ; i<t.taille ; i++){
		nb_pts += t.tab[i].taille;
	}
	printf("Il y a %d points, %d segements et %d contours !\n", nb_pts , nb_pts-t.taille , t.taille);
}
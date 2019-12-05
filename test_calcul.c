#include<stdio.h>
#include<stdlib.h>
#include"calcul.h"

int main(int argc, char *argv[]){

	double x = 2;
	double y = 5.5;
	
	point p1;
	p1= creer_point(x, y);
	aff_point(p1);

	point p2 = creer_point(y, x);
	aff_point(p2);
	
	x = distance_point(p1,p2);
	printf("distance entre p1 et p2 = %f\n", x);

	printf("p1 +p2\n");

	point p3 = add_point(p1, p2);
	aff_point(p3);

	vecteur v1 = creer_vecteur_point(p1,p2);
	aff_vect(v1);
	
	y = norme(v1);
	printf("norme de v1 = %f\n", y);

	vecteur v2 = creer_vecteur_point(p2,p1);
	aff_vect(v2);

	printf("v1 +v2\n");

	v1 = add_vecteur(v1, v2);
	aff_vect(v1);
	
	v1 = creer_vecteur(3, 4.55);
	aff_vect(v1);
	
	v1 = multi_scalaire_vect(2.5, v1);
	printf("v1*2,5\n");
	aff_vect(v1);

	

	return 0;
}


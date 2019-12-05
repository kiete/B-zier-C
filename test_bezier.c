#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"calcul.h"

int main (int argc, char *argv[]){
	
	tableau p = nouveau_tab();
	point p1  = creer_point(0, 0);
	p = ajout_point(p, p1);
	p1  = creer_point(1, 0);
	p = ajout_point(p, p1);
	p1  = creer_point(1, 1);
	p = ajout_point(p, p1);
	p1  = creer_point(1, 2);
	p = ajout_point(p, p1);
	p1  = creer_point(2, 2);
	p = ajout_point(p, p1);
	p1  = creer_point(3, 2);
	p = ajout_point(p, p1);
	p1  = creer_point(3, 3);
	p = ajout_point(p, p1);
	p1  = creer_point(4, 3);
	p = ajout_point(p, p1);
	p1  = creer_point(5, 3);
	p = ajout_point(p, p1);
	
	tableau_bezier3 b3 = simplification2(p, 0, 7, 1);
	printf("%d\n", b3.taille);
	
	return 0;
	}
 

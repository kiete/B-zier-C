#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "trace_graphique.c"


int main (int argc, char *argv[]){
	
	FILE *f;


	f = fopen("resultat.eps", "w");
	if (argc != 4){
		ERREUR_FATALE("utilisation correcte: ./test_trace_eps.c image.bpm seuil degres(1, 2 ou 3)\n");
	}
	double seuil = atof(argv[2]);
	//trace_eps_plus (f , argv[1], mode);

	int degres = atoi(argv[3]);
	
	if (degres == 1){
		trace_simplifie(f , argv[1] , seuil);
	}

	else if (degres == 2){
		trace_bezier2(f , argv[1] , seuil);
	}
	
	else if (degres == 3){
		trace_bezier3(f , argv[1] , seuil);
	}
	else {
		ERREUR_FATALE("utilisation correcte: ./test_trace_eps.c image.bpm seuil degres(1, 2 ou 3)\n");
	}

	fclose(f);
	
	/*
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
	
	tableau_bezier3 b3 = simplification3(p, 0, 8, 1);
	printf("Taille = %d\n", b3.taille);

	printf ("distance = %f \n" , distance_point_bezier3(p1,b3.tab[0],1/7));
	*/
	return 0;
}

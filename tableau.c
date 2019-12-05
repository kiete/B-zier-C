#include<stdio.h>
#include<stdlib.h>
#include"calcul.h"
#include"tableau.h"


tableau nouveau_tab(){
	tableau t;
	t.t_max = 8;
	t.taille = 0;
	t.tab = malloc(8 * sizeof(point));
	return t;
}

tableau_bezier3 nouveau_tab_bezier3(){
	tableau_bezier3 t;
	t.t_max = 8;
	t.taille = 0;
	t.tab = malloc(8 * sizeof(bezier3));
	return t;
}

tableau ajout_point(tableau t, point p){
	if (t.taille == t.t_max ){
		t.tab = realloc(t.tab, 2 * t.t_max * sizeof(point));
		t.t_max = t.t_max * 2;
		}
	t.tab[t.taille] = p;
	t.taille ++;
	return t;
}

tableau_bezier3 ajout_point_bezier3(tableau_bezier3 t, bezier3 p){
	if (t.taille == t.t_max ){
		t.tab = realloc(t.tab, 2 * t.t_max * sizeof(bezier3));
		t.t_max = t.t_max * 2;
		}
	t.tab[t.taille] = p;
	t.taille ++;
	return t;
}

bezier3 b2_vers_b3(bezier2 b2){
	bezier3 b3;
	b3.c0.x = b2.c0.x;
	b3.c0.y = b2.c0.y;
	b3.c3.x = b2.c2.x;
	b3.c3.y = b2.c2.y;

	b3.c1.x = (b2.c0.x + 2 * b2.c1.x)/3;
	b3.c1.y = (b2.c0.y + 2 * b2.c1.y)/3;
	b3.c2.x = ((2 * b2.c1.x) + b2.c2.x)/3;
	b3.c2.y = ((2 * b2.c1.y) + b2.c2.y)/3;

	return b3;
}

tableau_bezier3 concatenation_bezier3(tableau_bezier3 b1, tableau_bezier3 b2){
	int i;
	for(i = 0; i < b2.taille; i ++){
		b1 = ajout_point_bezier3(b1, b2.tab[i]);
	}
	return b1;
} 


tableau concatenation (tableau t1 , tableau t2){
	for (int i = 0 ; i<t2.taille ; i++){
		t1 = ajout_point(t1 , t2.tab[i]);
	}
	return t1;
}

void effacer(tableau t){
	free(t.tab);
}


tableau_contour nouveau_tab_contour(){
	tableau_contour t;
	t.t_max = 8;
	t.taille = 0;
	t.tab = malloc(8 * sizeof(tableau));
	return t;
}

tableau_contour_bezier3 nouveau_tab_contour_bezier3(){
	tableau_contour_bezier3 t;
	t.t_max = 8;
	t.taille = 0;
	t.tab = malloc(8 * sizeof(tableau_bezier3));
	return t;
}


tableau_contour ajout_point_contour(tableau_contour t, tableau tabl) {
	if (t.taille == t.t_max ){
		t.tab = realloc(t.tab, 2 * t.t_max * sizeof(tableau));
		t.t_max = t.t_max * 2;
		}
	t.tab[t.taille] = tabl;
	t.taille ++;
	return t;
}

tableau_contour_bezier3 ajout_point_contour_bezier3(tableau_contour_bezier3 t, tableau_bezier3 tabl) {
	if (t.taille == t.t_max ){
		t.tab = realloc(t.tab, 2 * t.t_max * sizeof(tableau_bezier3));
		t.t_max = t.t_max * 2;
		}
	t.tab[t.taille] = tabl;
	t.taille ++;
	return t;
}

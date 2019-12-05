#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include"types_macros.h"
#include"image_pbm.h"
#include"calcul.h"
#include"tableau.h"
#include"calcul_contour.h"


/* tab[x-1+L*(y-1)] */
/*attention au coordonées du robot qui est differente de la coordonées du pixel*/
point premier_pixel(Image img){
	point p;
	for(int j = 1; j <= img.H; j++ ){
		for(int i = 1; i <= img.L; i++ ){
			if (get_pixel_image(img, i, j) == NOIR){
				p.x = i;
				p.y = j;
				return p;
			}
		}
	}
	exit(1);
}

int existe_premier_pixel(Image img){
	for(int j = 1; j <= img.H; j++ ){
		for(int i = 1; i <= img.L; i++ ){
			if (get_pixel_image(img, i, j) == NOIR){
				return 1;
			}
		}
	}
	return 0;
}


Pixel devant_gauche(Image img, robot r){
	orientation o = r.o;
	Pixel p;
	switch (o) {
		case N : p = get_pixel_image(img, r.x, r.y);
			break;


		case S : p = get_pixel_image(img, r.x+1, r.y+1);
			break;

		case O : p = get_pixel_image(img, r.x, r.y+1);
			break;

		case E : p = get_pixel_image(img, r.x+1, r.y);
			break;
	}
	return p;
}

Pixel devant_droite(Image img, robot r){
	orientation o = r.o;
	Pixel p;
	switch (o) {
		case N : p = get_pixel_image(img, r.x+1, r.y);
			break;

		case S : p = get_pixel_image(img, r.x, r.y+1);
			break;

		case O : p = get_pixel_image(img, r.x, r.y);
			break;

		case E : p = get_pixel_image(img, r.x+1, r.y+1);
			break;
	}
	return p;
}

void avancer(robot * r){
	orientation o = r->o;
	switch (o) {
		case N : r->y = r->y-1;
			break;

		case S : r->y = r->y+1;
			break;

		case O : r->x = r->x-1;
			break;

		case E : r->x = r->x+1;
			break;
	}
}

orientation tourner_droite( orientation o){
	switch (o) {
		case N : o = E;
			break;

		case S : o = O;
			break;

		case O : o = N;
			break;

		case E : o = S;
			break;
	}
	return o;
}

orientation tourner_gauche( orientation o){
	switch (o) {
		case N : o = O;
			break;

		case S : o = E;
			break;

		case O : o = S;
			break;

		case E : o = N;
			break;
	}
	return o;
}

void nouvelle_orientation(robot * r, Image img){
	if ((devant_droite(img, *r) == BLANC) && (devant_gauche(img, *r) == BLANC)){
		r->o = tourner_droite(r->o);
	}else{
		if((devant_droite(img, *r) == BLANC) && (devant_gauche(img, *r) == NOIR)) {
			r->o = tourner_gauche(r->o);
		}else{
			if ((devant_droite(img, *r) == NOIR) && (devant_gauche(img, *r) == NOIR)) {
				r->o = tourner_gauche(r->o);
			}
		}
	}
}

tableau memoriser(tableau t, robot r){
	point p ;
	p.x = r.x;
	p.y = r.y;
	t = ajout_point(t, p);
	return t;
}


tableau contour(Image img) {
	robot *r = malloc(sizeof(robot));
	point p1;
	p1 = premier_pixel(img);
	p1.x--;
	p1.y--;
	r->x = p1.x;
	r->y = p1.y;
	r->o = E;
	tableau t;
	t = nouveau_tab();
	do {
		avancer(r);
		t = memoriser(t, *r);
		nouvelle_orientation(r, img);
	} while ((r->x != (p1.x)) || (r->y != (p1.y)) || (r->o != E));
	return t;
}



//Penser à initialiser le tableau
tableau simplification(tableau contour , int j1 , int j2 ,double d){

	// j1 indice du premier point
	// j2 indice du second point
	// d la distance de seuil

	double dmax = 0;
	int k = j1;
	double dj;
	tableau l = nouveau_tab();
	// le tableau l contiendra le contour simplifié
	//printf("p1\n");
	for (int j = j1+1; j<j2; j++){
		//printf("%d , %d , %d \n", j1, j2 , j);
		dj = distance_point_segment(contour.tab[j],contour.tab[j2],contour.tab[j1]);
		//printf("p2\n");
		if (dmax<dj){
			dmax = dj;
			k = j;
	
		}
	}
	//printf("p2\n");
	//On commence les branches de récursivité
	if (dmax<=d){
		 l = ajout_point(l , contour.tab[j1]);
		 l = ajout_point(l , contour.tab[j2]);
		 //printf("point ajouté, %d\n" , l.taille );
	}else{
		tableau l1 = nouveau_tab();
		tableau l2 = nouveau_tab();
		tableau resultat = nouveau_tab();
		l1 = simplification (contour , j1 , k , d);
		l2 = simplification (contour , k , j2 , d);
		resultat = concatenation(l1 , l2);
		//printf ("Taille echantillon = %d\n" , resultat.taille);
		return resultat;

	}
	return l;
}

/*
bezier2 approx_bezier2_bis(tableau T, int a, int b){
	bezier2 B2;
	int n = b-a;
	B2.c0 = T.tab[a]; // A change
	B2.c2 = T.tab[b];
	if (n == 1)
	{
		B2.c1 = multi_scalaire_point(0.5 , add_point(T.tab[a],T.tab[b]));
	} else {






		double alp = 3*n/(n*n-1);
		double bet = (1-2*n)/(2*n+2);

		double somme_x = 0;
		double somme_y = 0;

		int i;
		for(i=1; i<n; i++)
		{
			somme_x = somme_x + T.tab[a+i].x;
			somme_y = somme_y + T.tab[a+i].y;
		}
		B2.C1.x = alp * somme_x + bet * (B2.C0.x + B2.C2.x);
		B2.C1.y = alp * somme_y + bet * (B2.C0.y + B2.C2.y);
		





		int i;
		double t;
		double somme_w;
		double ci;
		double somme_wcx;
		double somme_wcy;
		for(i=1; i<n; i++)
		{
			t=(double)i/(double)n;
		//printf("%f\n", t); 
			somme_w = somme_w + (2*t*(1-t));
			ci = (T.tab[a+i].x - (1-t)*(1-t)*T.tab[a].x - t*t*T.tab[b].x)/(2*t*(1-t)); 
			somme_wcx = somme_wcx +(2*t*(1-t))*ci;

			ci = (T.tab[a+i].y - (1-t)*(1-t)*T.tab[a].y - t*t*T.tab[b].y)/(2*t*(1-t)); 
			somme_wcy = somme_wcy +(2*t*(1-t))*ci;
		}
		B2.c1.x = somme_wcx / somme_w;
		B2.c1.y = somme_wcy / somme_w;
		printf("%f %f\n",B2.c1.x, B2.c1.y);
	}
	return B2;
}

*/


bezier2 approx_bezier2(tableau contour, int j1, int j2){
	double n = (double)j2 - (double)j1;
	bezier2 b;
	b.c0.x = (double)contour.tab[j1].x;
	b.c0.y = (double)contour.tab[j1].y;
	b.c2.x = (double)contour.tab[j2].x;	
	b.c2.y = (double)contour.tab[j2].y;	
	//printf("J1 = %d , J2 = %d \n" , j1 , j2);
	//printf("c0.x = %f\n", b.c0.x);
	//printf("c0.y = %f\n", b.c0.y);
	//printf("c2.x = %f\n", b.c2.x);
	//printf("c2.y = %f\n", b.c2.y);
	
	if (n < 2){
		b.c1.x = ((contour.tab[j1].x + contour.tab[j2].x)/2);
		b.c1.y = ((contour.tab[j1].y + contour.tab[j2].y)/2);
		//printf("%f,%f\n", b.c1.x, b.c1.y);
	}else{
		double n2 = (double)n;
		double a = (3 * n2)/(n2*n2-1);
		double a2 = (1 - 2*n2)/(2*(n2 + 1));
		
		
		for (int i = j1+1; i < j2; i++){
			b.c1.x = (b.c1.x + contour.tab[i].x);
			b.c1.y = (b.c1.y + contour.tab[i].y);
			printf("C%d = (%.1f , %.1f)", i , b.c1.x , b.c1.y);
		}
		
		b.c1.x = (a * b.c1.x + a2 * (contour.tab[j1].x + contour.tab[j2].x));
		b.c1.y = (a * b.c1.y + a2 * (contour.tab[j1].y + contour.tab[j2].y));
		//printf("%f * %f + %f + %f + %f\n", a, b.c1.x,  a2, contour.tab[j1].x, contour.tab[j2].x );
	}
	//printf("J1 = %d , J2 = %d \n" , j1 , j2);
	
	return b;
}
bezier2 approx_bezier2_bis (tableau T, int a, int b)
{
	//printf("On approx par B2\n");
	//printf("On approx \n");
	bezier2 B2;
	double n = b-a;
	B2.c0 = T.tab[a]; // A change
	B2.c2 = T.tab[b];
	if (n == 1)
	{
		B2.c1 = multi_scalaire_point(0.5 , add_point(T.tab[a],T.tab[b]));
	} else {
		/*double alp = 3*n/(n*n-1);
		double bet = (1-2*n)/(2*n+2);

		double somme_x = 0;
		double somme_y = 0;

		int i;
		for(i=1; i<n; i++)
		{
			somme_x = somme_x + T.tab[a+i].x;
			somme_y = somme_y + T.tab[a+i].y;
		}
		B2.C1.x = alp * somme_x + bet * (B2.C0.x + B2.C2.x);
		B2.C1.y = alp * somme_y + bet * (B2.C0.y + B2.C2.y);
		*/

		int i = 0;
		double omega = 0;
		double t = 0;
		double somme_omega = 0;
		double cix = 0;
		double ciy = 0;
		double somme_wcx = 0;
		double somme_wcy = 0;
		for(i=1; i<n; i++)
		{
			t=i/n;
			omega = (2*t*(1-t));
			somme_omega += omega;
			cix = (T.tab[a+i].x - (1-t)*(1-t)*T.tab[a].x - t*t*T.tab[b].x)/omega; 
			somme_wcx += omega * cix;
			
			ciy = (T.tab[a+i].y - (1-t)*(1-t)*T.tab[a].y - t*t*T.tab[b].y)/omega; 
			somme_wcy += omega * ciy;
			
			//printf("C%d = (%.2f , %.2f)/%.2f \n", i ,  cix , ciy , omega);
		}
		B2.c1.x = somme_wcx / somme_omega;
		B2.c1.y = somme_wcy / somme_omega;
		//printf("Au final , C1 = (%f , %f) \n", B2.c1.x , B2.c1.y);
	}
	return B2;
}

double fun_gamma (double i,double n){
	double di = (double)i;
	double dn = (double)n;
	return (double)(6*di*di*di - 8*dn*di*di*di + 6 * di*di - 4*dn*di - dn*dn*dn*dn - dn*dn);
}

double gama(double k, double n){
	return (double) (6*k*k*k*k  -  8*n*k*k*k  +  6*k*k  -  4*n*k  +  n*n*n*n  -  n*n);
}


bezier3 approx_bezier3 (tableau T, int a, int b){
	//printf("On approx par B3\n");
	double n = 0;
	n = (double)(b - a);
	
	if (n < 3){
		return b2_vers_b3( approx_bezier2_bis(T , a , b));
	}

	double dn = (double)n;

	double alpha = 0 , beta = 0 , lambda = 0;

	alpha = (double)(-15*n*n*n + 5*n*n + 2*n + 4)/(3*(n+2)*(3*n*n+1));
	beta = (double)(10*dn*dn*dn - 15*dn*dn + dn + 2)/(3*(dn+2)*(3*dn*dn+1));
	lambda = (double)(70*dn)/(3*(dn*dn-1)*(dn*dn-4)*(3*dn*dn+1));

	bezier3 b3 = creer_bezier3();
	b3.c0 = T.tab[a];
	b3.c3 = T.tab[b];
	b3.c1 = creer_point(0,0);
	b3.c2 = creer_point(0,0);

	for (int i = a+1 ; i < b ; i++){
		b3.c1.x += (T.tab[i].x)*gama((double)(i-a) , n);
		b3.c1.y += (T.tab[i].y)*gama((double)(i-a) , n);

		b3.c2.x += (T.tab[i].x)*gama((double)(n-i+a) , n);
		b3.c2.y += (T.tab[i].y)*gama((double)(n-i+a) , n);
	}


	/*
	for (int i = a+1 ; i < b ; i++){
		pn = T.tab[i];
		//On calcule la somme pour C1
		gamma = fun_gamma((double)(i-a),n);
		pn = multi_scalaire_point(gamma , pn);
		sum_pi_1 = add_point(sum_pi_1,pn);

		//On calcule la somme pour C2
		pn = T.tab[i];
		gamma = fun_gamma((double)(n-(i-a)),n);
		pn = multi_scalaire_point(gamma , pn);
		sum_pi_2 = add_point(sum_pi_2,pn);
	}
	

	
	point c1 = creer_point(0,0);
	point part1 = multi_scalaire_point(alpha , T.tab[a]);
	point part2 = multi_scalaire_point(lambda,sum_pi_1);
	point part3 = multi_scalaire_point(beta,T.tab[b]);
	c1 = add_point(part1 , part2);
	c1 = add_point(c1 , part3);

   	point c2 = creer_point(0,0);
	c2 = add_point(multi_scalaire_point(alpha , T.tab[a]),multi_scalaire_point(lambda,sum_pi_1));
	c2 = add_point(c1 , multi_scalaire_point(beta,T.tab[b]));
	*/

	b3.c1.x = lambda * b3.c1.x + alpha*T.tab[a].x + beta*T.tab[b].x ;
	b3.c1.y = lambda * b3.c1.y + alpha*T.tab[a].y + beta*T.tab[b].y ;

	b3.c2.x = lambda * b3.c2.x + beta*T.tab[a].x + alpha*T.tab[b].x ;
	b3.c2.y = lambda * b3.c2.y + beta*T.tab[a].y + alpha*T.tab[b].y ;
	return b3;
} 

tableau_bezier3 simplification2(tableau contour, int j1, int j2, double d){
	
	double n = (double)j2 - (double)j1;
	//printf("n = %d\n", n);
	bezier2 B = creer_bezier2();
	B = approx_bezier2_bis(contour, j1, j2); //OK
	//printf("J1 = %d , J2 = %d \n" , j1 , j2);
	//printf("c0.x = %f\n", B.c0.x);
	//printf("c0.y = %f\n", B.c0.y);
	//printf("c1.x = %f\n", B.c1.x);
	//printf("c1.y = %f\n", B.c1.y);
	//printf("c2.x = %f\n", B.c2.x);
	//printf("c2.y = %f\n", B.c2.y);
	//exit(1);
	double dmax = 0;
	double dj;
	int k = j1;
	int i= 1;
	double ti;
	int j;
	for (j = j1+1 ; j<j2; j++){
		i = j - j1;
		ti = (double)i / n;
		//printf("ti = %f\n", ti);
		dj = distance_point_bezier2(contour.tab[j], B, ti); 
		//printf("dj = %f\n", dj);
		if (dmax < dj) {
			dmax = dj;
			k = j;
		}
	}
	//printf("dmax = %f \n" , dmax);
	//printf("c2.x = %f \n" , B.c2.x);
	if (dmax <= d ){
		bezier3 b3 ;
		b3 = b2_vers_b3(B);
		tableau_bezier3 tab_b3 = nouveau_tab_bezier3();
		tab_b3 = ajout_point_bezier3(tab_b3, b3);
		return tab_b3;
	}else{
		tableau_bezier3 l1; 
		l1 = nouveau_tab_bezier3();
		tableau_bezier3 l2;
		l2 = nouveau_tab_bezier3();
		tableau_bezier3 resultat ;
		resultat = nouveau_tab_bezier3();
		l1 = simplification2 (contour , j1 , k , d);
		l2 = simplification2 (contour , k , j2 , d);
		resultat = concatenation_bezier3(l1 , l2);
		return resultat;
	}
}	




tableau_bezier3 simplification3(tableau contour, int j1, int j2, double d){
	
	double n = (double)j2 - (double)j1;
	bezier3 B = creer_bezier3();
	B = approx_bezier3(contour, j1, j2); //OK
	double dmax = 0;
	double dj;
	int k = j1;
	int i= 1;
	double ti;
	int j;
	for (j = j1+1 ; j<j2; j++){
		i = j - j1;
		ti = (double)i / n;
		//printf("ti = %f\n", ti);
		dj = distance_point_bezier3(contour.tab[j], B, ti); 
		//printf("dj = %f\n", dj);
		if (dmax <= (double)dj) {
			dmax = (double)dj;
			k = j;
		}
	}



	//printf("c2.x = %f \n" , B.c2.x);
	//printf("Le point max est P%d d=%f \n" , k , dmax);
	if (dmax <= d ){
		tableau_bezier3 tab_b3 = nouveau_tab_bezier3();
		tab_b3 = ajout_point_bezier3(tab_b3, B);
		return tab_b3;
	}else{
		tableau_bezier3 l1; 
		l1 = nouveau_tab_bezier3();
		tableau_bezier3 l2;
		l2 = nouveau_tab_bezier3();
		tableau_bezier3 resultat ;
		resultat = nouveau_tab_bezier3();
		l1 = simplification3 (contour , j1 , k , d);
		l2 = simplification3 (contour , k , j2 , d);
		resultat = concatenation_bezier3(l1 , l2);
		return resultat;
	}
}	












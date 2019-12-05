#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dessin.h"


Seq_B3 creer_SB3(){
	Seq_B3 S;
	S.tab = (Point *) malloc(sizeof(Point));
	S.l = 0;
	return S;
}

double gama(double k, double n){
	return (double) (6*k*k*k*k  -  8*n*k*k*k  +  6*k*k  -  4*n*k  +  n*n*n*n  -  n*n);
}

Bezier2 approx_bezier2(Point* P, int j1, int j2){
	Bezier2 B;
	B.C0.x = P[j1].x;
	B.C0.y = P[j1].y;
	B.C2.x = P[j2].x;
	B.C2.y = P[j2].y;

	double n = (double)(j2 - j1);

	if (n>=2){
		double a = (3*n)/(n*n - 1);
		double b = (1 - 2*n)/(2*(n + 1));


		B.C1.x = 0;
		B.C1.y = 0;


		for (int i = j1 + 1 ; i < j2; i++){
			B.C1.x = B.C1.x + P[i].x;
			B.C1.y = B.C1.y + P[i].y;
		}

		B.C1.x = B.C1.x*a + b*(B.C0.x + B.C2.x);
		B.C1.y = B.C1.y*a + b*(B.C0.y + B.C2.y);

		return B;
	}
	else {
		B.C1.x = (B.C0.x + B.C2.x)/2;
		B.C1.y = (B.C0.y + B.C2.y)/2;
		return B;
	}

}

Bezier3 approx_bezier3(Point* P, int j1, int j2){
	double n = (double) (j2 - j1);
	if (n<3){
		return B2_to_B3(approx_bezier2(P, j1, j2));
	}

	else {
		Bezier3 B;
		B.C0.x = P[j1].x;
		B.C0.y = P[j1].y;
		B.C3.x = P[j2].x;
		B.C3.y = P[j2].y;


		double a = (double) ( (-15*n*n*n + 5*n*n + 2*n + 4)/(3*(n+2)*(3*n*n + 1)) );
		double b = (double) ( (10*n*n*n - 15*n*n + n + 2)/(3*(n+2)*(3*n*n + 1)) );
		double c = (double) ( (70*n)/(3*(n*n - 1)*(n*n - 4)*(3*n*n + 1)) );

		B.C1.x = 0;
		B.C1.y = 0;
		B.C2.x = 0;
		B.C2.y = 0;

		for (int i = j1 + 1 ; i < j2; i++){
			B.C1.x = B.C1.x + (P[i].x)*gama( (double) (i - j1), n);
			B.C1.y = B.C1.y + (P[i].y)*gama( (double) (i - j1), n);
		}

		for (int i = j1 + 1 ; i < j2; i++){
			B.C2.x = B.C2.x + (P[i].x)*gama( (double) (n - (i - j1) ), n);
			B.C2.y = B.C2.y + (P[i].y)*gama( (double) (n - (i - j1) ), n);
		}

		B.C1.x = c*B.C1.x + a*P[j1].x + b*P[j2].x;
		B.C1.y = c*B.C1.y + a*P[j1].y + b*P[j2].y;

		B.C2.x = c*B.C2.x + b*P[j1].x + a*P[j2].x;
		B.C2.y = c*B.C2.y + b*P[j1].y + a*P[j2].y;

		return B;
	}
}

double distance_point_bezier3(Point P, Bezier3 B, double t){
	Point p;
	p.x = B.C0.x * (1-t)*(1-t)*(1-t) + B.C1.x * 3*t*(1-t)*(1-t) + B.C2.x * 3*t*t*(1-t) + B.C3.x * t*t*t;
	p.y = B.C0.y * (1-t)*(1-t)*(1-t) + B.C1.y * 3*t*(1-t)*(1-t) + B.C2.y * 3*t*t*(1-t) + B.C3.y * t*t*t;
	return distance_points(p, P);
}

double distance_point_bezier2(Point P, Bezier2 B, double t){
	Point p;
	p.x = B.C0.x * (1-t)*(1-t) + B.C1.x * 2*t*(1-t) + B.C2.x * t*t;
	p.y = B.C0.y * (1-t)*(1-t) + B.C1.y * 2*t*(1-t) + B.C2.y * t*t;
	return distance_points(p, P);
}

Seq_B3 concatenation_SB3(Seq_B3 S1, Seq_B3 S2){
	S1.tab = (Point *) realloc(S1.tab, sizeof(Point)*(S1.l + S2.l));
	int i;
	for(i = S1.l; i < S1.l + S2.l; i++){
		S1.tab[i] = S2.tab[i - S1.l];
	}
	S1.l = S1.l + S2.l;
	return S1;
}

Bezier3 B2_to_B3(Bezier2 B2){
	Bezier3 B3;

	B3.C0.x = B2.C0.x;
	B3.C0.y = B2.C0.y;

	B3.C1.x = (B2.C0.x + 2*B2.C1.x)/3;
	B3.C1.y = (B2.C0.y + 2*B2.C1.y)/3;

	B3.C2.x = (B2.C2.x + 2*B2.C1.x)/3;
	B3.C2.y = (B2.C2.y + 2*B2.C1.y)/3;

	B3.C3.x = B2.C2.x;
	B3.C3.y = B2.C2.y;

	return B3;
}

Seq_B3 ajouter_bezier_seq(Bezier3 B, Seq_B3 S){
		S.tab = (Point *) realloc(S.tab, sizeof(Point)*(S.l + 4));
		S.tab[S.l] = B.C0;
		S.tab[S.l + 1] = B.C1;
		S.tab[S.l + 2] = B.C2;
		S.tab[S.l + 3] = B.C3;
		S.l = S.l + 4;
		return S;
}


Seq_B3 simplification_b3(Point* P, int j1, int j2, double d){
	int n = j2 - j1;
	Bezier3 B3 = approx_bezier3(P, j1, j2);
	Seq_B3 S = creer_SB3();
	int k = j1;
	int i,j;
	double t, dj;
	double dmax = 0;
	for (j = j1 + 1; j < j2; j++){
		i = j - j1;
		t = (double)i/(double)n;
		dj = distance_point_bezier3(P[j], B3, t);
		if (dmax < dj){
			dmax = dj;
			k = j;
		}
	}


	if ( dmax <= d ){
		S = ajouter_bezier_seq(B3, S);
		return S;
	}
	else {
		Seq_B3 S1 = simplification_b3(P, j1, k, d);
		Seq_B3 S2 = simplification_b3(P, k, j2, d);
		S = concatenation_SB3(S1, S2);
		return S;
	}
}



int main(int argc, char* argv[]){
	if (argc != 2){
	  printf("Format : <fichier.pbm>\n");
	  return -1;
	}


	Image M;
	Image I;
	Robot R;


	I = lire_fichier_image(argv[1]);
	masque(I, &M);
	extraire_multiples_contours(I, &M, &R);

	double distance;
	printf("Veuillez choisir la distance seuil : ");
	scanf("%lf", &distance);

	Seq_B3* S3;
	S3 = (Seq_B3 *) malloc(sizeof(Seq_B3)*R.nb_c);

	int debut = 0;
	int fin = R.tab_c[0] - 1;
	for (int j = 0; j<R.nb_c; j++){
		S3[j] = simplification_b3(R.tab, debut, fin, distance);
		debut = fin + 1;
		fin  = fin + R.tab_c[j + 1];
	}

	char txt[100];
	char eps[100];
	trim(txt, argv[1]);
	strcpy(eps, txt);

	int sum = 0;
  	for (int j = 0 ; j < R.nb_c ; j++){
    		sum = sum + S3[j].l/4;
  	}
  	printf("Il y a %d courbes de béziers\n\n", sum);

	strcat(txt, ".txt");
	strcat(eps, ".eps");
	FILE* f2 = fopen(eps, "w");
	FILE* f3 = fopen(txt, "w");

	eps_bezier3(f2, R, S3, I);
	infos_bezier(f3, R, S3);
	test(f3, R);

	return 0;
}

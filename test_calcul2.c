#include<stdio.h>
#include<stdlib.h>
#include"calcul.h"

int main(int argc, char *argv[]){
	if (argc != 7){
		printf("nb d'arguments différents de 6\n");
		return 1;
	}
	double p1 , p2 , a1 , a2 , b1 , b2;
	sscanf(argv[1], "%lf", &p1);
	sscanf(argv[2], "%lf", &p2);
	sscanf(argv[3], "%lf", &a1);
	sscanf(argv[4], "%lf", &a2);
	sscanf(argv[5], "%lf", &b1);
	sscanf(argv[6], "%lf", &b2);
	point p = creer_point(p1,p2);
	point a = creer_point(a1,a2);
	point b = creer_point(b1,b2);
	double r  = distance_point_segment(p, a, b);
	printf("%f\n", r);
	return 0;
}


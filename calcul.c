
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"calcul.h"

bezier2 creer_bezier2(){
	bezier2 b;
	b.c0.x = 0;
	b.c0.y = 0;
	b.c1.x = 0;
	b.c1.y = 0;
	b.c2.x = 0;
	b.c2.y = 0;
	return b;
}

bezier3 creer_bezier3(){
	bezier3 b;
	b.c0.x = 0;
	b.c0.y = 0;
	b.c1.x = 0;
	b.c1.y = 0;
	b.c2.x = 0;
	b.c2.y = 0;
	b.c3.x = 0;
	b.c3.y = 0;
	return b;
}

point creer_point(double x, double y){
	point p;
	p.x = x;
	p.y = y;
	return p;
}

vecteur creer_vecteur(double x, double y){
	vecteur v;
	v.x = x;
	v.y = y;
	return v;
}

point add_point(point p1, point p2){
	return creer_point(p1.x+p2.x, p1.y+p2.y);
}

vecteur creer_vecteur_point(point p1, point p2){
	vecteur V = {p2.x-p1.x, p2.y-p1.y};
	return V;
}

vecteur add_vecteur(vecteur v1, vecteur v2){
	vecteur v;	
	v.x = v1.x +v2.x;
	v.y = v1.y +v2.y;
	return v;
}

void aff_vect(vecteur v){
	printf(" v = (%f ,%f)\n", v.x,v.y);
	return;
}  

void aff_point(point p){
	printf(" p = (%f ,%f)\n", p.x,p.y);
	return;
} 

double distance_point(point p1, point p2){
	return sqrt(((p1.x-p2.x)*(p1.x-p2.x))+((p1.y-p2.y)*(p1.y-p2.y)));
}

double norme(vecteur v1){
	return sqrt(((v1.x)*(v1.x))+((v1.y)*(v1.y)));
}

vecteur multi_scalaire_vect(double a, vecteur v1){
	return creer_vecteur(a*v1.x, a*v1.y);
}


point multi_scalaire_point(double a, point p1){
	return creer_point(a*p1.x, a*p1.y);
}


double produit_scalaire(vecteur v1, vecteur v2){
	//printf("PS = %f\n",v1.x*v2.x+v1.y*v2.y);
	return v1.x*v2.x+v1.y*v2.y;
}

double distance_point_segment(point p, point a, point b){
	vecteur ap = creer_vecteur_point(a, p);
	vecteur ab = creer_vecteur_point(a, b);
	double l = produit_scalaire(ap, ab)/produit_scalaire(ab, ab);
	if ((a.x-b.x==0)&(a.y-b.y==0)){
		return distance_point(p, a);
	}
	//printf("lambda = %f\n" , l);
	if (l < 0){
		//printf("l<0\n");
		return distance_point(p, a);
	}
	if (l > 1){
		//printf("l>1\n");
		return distance_point(p, b);
	}
	else{
		//printf("0<l<1\n");
		vecteur abb = multi_scalaire_vect(l, ab);
		point q = creer_point(a.x + abb.x, a.y + abb.y);
		return distance_point(p, q);
	}
}

double distance_point_bezier2(point p , bezier2 b, double ti){
	point cti;
	double p1 = b.c0.x;
	double p2 = b.c0.y;
	double p3 = b.c1.x;
	double p4 = b.c1.y;
	double p5 = b.c2.x;
	double p6 = b.c2.y;
	cti.x = (p1 * (1- ti) * (1-ti)) + (2 * p3 * (1-ti) * ti) + (p5 * ti *ti);
	cti.y = (p2 * (1- ti) * (1-ti)) + (2 * p4 * (1-ti) * ti) + (p6 * ti *ti);
	//printf("%f,%f\n", cti.x, cti.y);
	return distance_point(cti, p);
}

double distance_point_bezier3(point p , bezier3 b, double t){
	point cti;
	cti.x = (1-t)*(1-t)*(1-t)*b.c0.x + 3*(1-t)*(1-t)*t*b.c1.x + 3*(1-t)*t*t*b.c2.x + t*t*t*b.c3.x ;
	cti.y = (1-t)*(1-t)*(1-t)*b.c0.y + 3*(1-t)*(1-t)*t*b.c1.y + 3*(1-t)*t*t*b.c2.y + t*t*t*b.c3.y ;

	double d = 0;
	d = distance_point(cti, p);
	return d ;
}


















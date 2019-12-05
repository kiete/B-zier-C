#ifndef _CALCUL_H_
#define _CALCUL_H_

typedef struct point_t
{
	double x,y;
} point;


typedef struct vecteur_t
{
	double x,y;
} vecteur;

typedef struct bezier2_t
{
	point c0, c1, c2;
} bezier2;

typedef struct bezier3_t
{
	point c0, c1, c2, c3;
} bezier3;

bezier3 creer_bezier3();

bezier2 creer_bezier2();

point creer_point(double x, double y);

point add_point(point p1, point p2);

vecteur creer_vecteur_point(point p1, point p2);

vecteur creer_vecteur(double x, double y);

vecteur add_vecteur(vecteur v1, vecteur v2);

void aff_vect(vecteur v);

void aff_point(point p);

double distance_point(point p1, point p2);

double norme(vecteur v1);

vecteur multi_scalaire_vect(double a, vecteur v1);

point multi_scalaire_point(double a, point p1);

double produit_scalaire(vecteur v1, vecteur v2);

double distance_point_segment(point p, point a, point b);

double distance_point_bezier2(point p , bezier2 b, double ti);

double distance_point_bezier3(point p , bezier3 b, double ti);

#endif

#ifndef _CALCUL_CONTOUR_H_
#define _CALCUL_CONTOUR_H_

typedef enum orientation_t {N, S, O, E} orientation;

typedef struct robot_t {
	orientation o;
	double x,y;
	} robot;

tableau simplification(tableau contour , int j1 , int j2 ,double d);

int existe_premier_pixel(Image img);

point premier_pixel(Image img);

Pixel devant_gauche(Image img, robot r);

Pixel devant_droite(Image img, robot r);

void avancer(robot * r);

orientation tourner_droite( orientation o);

orientation tourner_droite( orientation o);

void nouvelle_orientation(robot * r, Image img);

tableau memoriser(tableau t, robot r);

tableau contour(Image img);

double fun_gamma (double i,double n);

double gama(double k, double n);

bezier2 approx_bezier2(tableau contour, int j1, int j2);

bezier3 approx_bezier3 (tableau T, int a, int b);

tableau_bezier3 simplification2(tableau contour, int j1, int j2, double d);

tableau_bezier3 simplification3(tableau contour, int j1, int j2, double d);

#endif

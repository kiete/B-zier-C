#ifndef _TABLEAU_H_
#define _TABLEAU_H_

typedef struct tableau_t {
	int t_max;
	int taille;
	point * tab;
	} tableau;

typedef struct tableau_contour_t {
	int t_max;
	int taille;
	tableau * tab;
	} tableau_contour;

typedef struct tableau_bezier3_t {
	int t_max;
	int taille;
	bezier3 * tab;
	} tableau_bezier3;


typedef struct tableau_contour_bezier3_t {
	int t_max;
	int taille;
	tableau_bezier3 * tab;
	} tableau_contour_bezier3;



tableau_contour_bezier3 ajout_point_contour_bezier3(tableau_contour_bezier3 t, tableau_bezier3 tabl);

tableau_contour_bezier3 nouveau_tab_contour_bezier3();

tableau_bezier3 ajout_point_bezier3(tableau_bezier3 t, bezier3 p);

bezier3 b2_vers_b3(bezier2 b2 );

tableau_bezier3 concatenation_bezier3(tableau_bezier3 b1, tableau_bezier3 b2);

tableau_bezier3 nouveau_tab_bezier3();

tableau_bezier3 ajout_point_bezier3(tableau_bezier3 t, bezier3 p);

tableau nouveau_tab();

tableau ajout_point(tableau t, point p);

tableau concatenation (tableau t1 , tableau t2);

tableau_bezier3 concatenation_bezier3(tableau_bezier3 b1, tableau_bezier3 b2);

void effacer(tableau t);

tableau_contour nouveau_tab_contour();

tableau_contour ajout_point_contour(tableau_contour t, tableau tabl);

#endif

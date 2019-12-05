#ifndef _MULTI_CONTOUR_H_
#define _MULTI_CONTOUR_H_

Image masque(Image I);
tableau contour_plus (Image img , Image mask);
tableau_contour multi_contour (Image img);
void enregistrer_contour (tableau_contour t , FILE * f);
void somme_contours (tableau_contour t);

#endif

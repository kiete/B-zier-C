#ifndef _TRACE_GRAPHIQUE_H_
#define _TRACE_GRAPHIQUE_H_

void trace_eps (FILE * sortie , char * entree , int mode );

void trace_eps_plus (FILE * sortie , char * entree , int mode );

void trace_simplifie (FILE * sortie , char * entree , double seuil );

void trace_bezier3 (FILE * sortie , char * entree , double seuil );

void trace_bezier2(FILE * sortie , char * entree , double seuil );

#endif

/****************************************************************************** 
  Impl�mentation du module image_pbm
******************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types_macros.h"
#include"image_pbm.h"

/* macro donnant l'indice d'un pixel de coordonn�es (_x,_y) de l'image _I */
#define INDICE_PIXEL(_I,_x,_y) ((_x)-1)+(_I).L*((_y)-1)

/* cr�ation d'une image PBM de dimensions L x H avec tous les pixels blancs */
Image creer_image(UINT L, UINT H)
{
	Image I;
	UINT i;
	
	I.L = L;
	I.H = H;
	
	/* alloctaion dynamique d'un tableau de L*H Pixel*/
	I.tab = (Pixel *)malloc(sizeof(Pixel)*L*H);
	
	/* test si le tableau a ete correctement alloue */
	if (I.tab == (Pixel *)0)
	{
		ERREUR_FATALE("Impossible de creer une image");
	}
	
	/* remplir le tableau avec des pixels blancs */
	for (i=0; i<L*H; i++)
		I.tab[i] = BLANC;
		
	return I;
}

/* suppression de l'image I = *p_I*/
void supprimer_image(Image *p_I)
{
	free(p_I->tab);
	p_I->L = 0;
	p_I->H = 0;
}

/* renvoie la valeur du pixel (x,y) de l'image I
   si (x,y) est hors de l'image la fonction renvoie BLANC */
Pixel get_pixel_image(Image I, int x, int y)
{
	if (x<1 || x>I.L || y<1 || y>I.H)
		return BLANC;
	return I.tab[INDICE_PIXEL(I,x,y)];
}

/* change la valeur du pixel (x,y) de l'image I avec la valeur v
   si (x,y) est hors de l'image la fonction ne fait rien */
void set_pixel_image(Image I, int x, int y, Pixel v)
{
	if (x<1 || x>I.L || y<1 || y>I.H)
		return;
	I.tab[INDICE_PIXEL(I,x,y)] = v;
}

/* lire l'image dans le fichier nomm� nom_f
   s'il y a une erreur dans le fichier le programme s'arrete en affichant
   un message */
Image lire_fichier_image(char *nom_f)
{
	FILE *f;
	UINT L,H;
	char *ligne;
	size_t n;
	ssize_t l_ligne;
	Image I;
	
	/* ouverture du fichier nom_f en lecture */
	f = fopen(nom_f, "r");
	if (f == (FILE *)NULL)
	{
		ERREUR_FATALE("lire_fichier_image : ouverture du fichier impossible\n");
	}
	
	/* lecture et test de la ligne 1 */
	ligne = (char *)NULL;
	n = 0;
	l_ligne = getline(&ligne, &n, f);
	/* la ligne est correcte si et ssi ligne = {'P','1',0} 
	  soit une chaine de 3 caracteres (le dernier est le caractere nul) */
	if (l_ligne != 3)
	{
		ERREUR_FATALE("lire_fichier_image : ligne 1 incorrecte\n");
	}
	if ((ligne[0] != 'P') || (ligne[1] != '1'))
	{
		ERREUR_FATALE("lire_fichier_image : ligne 1 incorrecte\n");
	}
	free(ligne);
	
	/* lecture et test de la ligne 2 */
	ligne = (char *)NULL;
	n = 0;
	l_ligne = getline(&ligne, &n, f);
	if (ligne[0] != '#'){
		ERREUR_FATALE("lire_fichier_image : ligne 2 incorrecte\n");
	}
	free(ligne);
	/* lecture des dimensions */

	ligne = (char *)NULL;
	n = 0;
	l_ligne = getline(&ligne, &n, f);
	int i = 0;
	while (ligne[i] == ' '){
		i = i+1;
	}
	L = 0;
	while ((ligne[i] <= '9')&&(ligne[i] >= '0')){
		L = L*10 + ligne[i] - 48;
		i = i+1;
	}
	
	while (ligne[i] == ' '){
		i = i+1;
	}
	H = 0;
	while ((ligne[i] <= '9')&&(ligne[i] >= '0')){
		H = H*10 + ligne[i] - 48;
		i = i+1;
	}
	free(ligne);

	/* cr�ation de l'image de dimensions L x H */
	
	I = creer_image(L, H);
	
	/* lecture des pixels du fichier 
	   seuls les caracteres '0' (BLANC) ou '1' (NOIR) 
	   doivent etre pris en compte */
	ligne = (char *)NULL;
	l_ligne = getline(&ligne, &n, f);
	i = 0;
	int l = 1;
	int h = 1;
	while (h <= H){
		while (l <= L){
			if (ligne[i] == '1'){
				set_pixel_image(I, l, h, NOIR);
				l++;
				i++;
			}else if (ligne[i] == '\n'){
				i = 0;
				free(ligne);
				ligne = (char *)NULL;
				l_ligne = getline(&ligne, &n, f);
			}else if (ligne[i] == '0'){
				l++;
				i++;
			}else {
				i++;
			}
		}
		l = 1;
		h++;		
	}		
	free(ligne);

	/* fermeture du fichier */
	fclose(f);
	
	return I;
}

/* �crire l'image I � l'�cran */
void ecrire_image(Image I)
{
	Pixel P;
	UINT x = 1;
	UINT y = 1;
	while (y <= I.H){
		while (x <= I.L){
			P = get_pixel_image(I, x, y);
			if (P == NOIR){
				printf("#");
			}else{
				printf("_");
			}
			x = x+1;
		}
		printf("\n");
		x = 1;
		y = y +1;
	} 
	printf("\n");
	
	
}

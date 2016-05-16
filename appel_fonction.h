//  Copyright (c) 2016 Armaury CAHUET, William ZERBATO. All rights reserved.
#include "matrice_type.h"

int Copie(char *source, char *dest);
void verification_fichier(FILE * fichier);
void affiche_info_bmp(Header_file file_info, Header_img img_info);

vc *creer_tableau_pixel_nb_1(vi largeur, vi hauteur);
vc **creer_tableau_pixel_nb_2(vi largeur, vi hauteur);
void modifier_couleur_nb_1(vc *tab, vi largeur, vi hauteur);
void modifier_couleur_nb_2(vc **tab, vi largeur, vi hauteur);

Pixel24 *creer_tableau_pixel_couleur_1(vi largeur, vi hauteur);
Pixel24 **creer_tableau_pixel_couleur_2(vi largeur, vi hauteur);
void modifier_couleur_reel_1(Pixel24 *tab,vi largeur,vi hauteur);
void modifier_couleur_reel_2(Pixel24 **tab, vi largeur, vi hauteur);




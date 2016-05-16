//  Copyright (c) 2016 Armaury CAHUET, William ZERBATO. All rights reserved.
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "appel_fonction.h"
#include <time.h>
#include <math.h>

int Copie(char *source, char *dest)
{
	FILE *s = fopen(source, "rb");
	FILE *d = fopen(dest, "wb");
	if (s)
	{
		while (feof(s) == 0)
			fputc(fgetc(s), d);
		fclose(s);
		fclose(d);
		return 0;
	}
	else return 1;
}

void verification_fichier(FILE * fichier)
{
	if (fichier == NULL)
		printf("YOU SHALL NOT PASS !!!\n");
	else
		printf("Fichier valide...\n");
}

void affiche_info_bmp(Header_file file_info, Header_img img_info)
{
	printf("\nType du Header: %c%c", file_info.type[0], file_info.type[1]);
	printf("\nTaille du fichier: %d", file_info.taille);
	printf("\nChamp reserve : %d", file_info.chp_reserve);
	printf("\nOffset : %d\n", file_info.offset);

	printf("Taille Entete Du Fichier=%d\n", sizeof(Header_file));
	printf("Largeur: %d\n", img_info.largeur);
	printf("Hauteur %d\n", img_info.hauteur);
	printf("plans %d\n", img_info.plans);
	printf("Bit par Pixel %d\n", img_info.bit_par_pixel);
	printf("compression %d\n", img_info.compression);
	printf("Bmptaille %d\n", img_info.bmptaille);
	printf("Hresolu %d\n", img_info.Hresolu);
	printf("Vresolu %d\n", img_info.Vresolu);
	printf("Nbre couleurs %d\n", img_info.nbcouleurs);
	printf("plans %d\n", img_info.nbcouleursimp);
}

Pixel24 *creer_tableau_pixel_couleur_1( vi largeur, vi hauteur)
{
			Pixel24 *tab = (Pixel24*)malloc( ((largeur*3)*hauteur) * sizeof(Pixel24) );
			return tab;
}
Pixel24 **creer_tableau_pixel_couleur_2(vi largeur, vi hauteur)
{
			vi i;
			Pixel24 **tab = (Pixel24**)malloc(sizeof(Pixel24 *)  *  hauteur);
			for (i = 0; i < hauteur; i++)
				tab[i] = (Pixel24*)malloc(sizeof(Pixel24) * largeur);

			return tab;
}

vc *creer_tableau_pixel_nb_1(vi largeur, vi hauteur)
{
		vc *tab = (vc *)malloc((largeur/8)*hauteur);
		return tab;
}

vc **creer_tableau_pixel_nb_2(vi largeur, vi hauteur)
{
		vi i;
		vc **tab = (vc **)malloc(sizeof(vc *) * hauteur);
		for ( i = 0; i < hauteur; i++)
			tab[i] = (vc*)malloc(sizeof(vc) * largeur / 8);
		return tab;
}

void modifier_couleur_nb_1(vc *tab, vi largeur, vi hauteur)
{
	vi i;
	vi k;
	for (i = 0; i < (largeur / 8);i++)
	{
		*(tab + i) = 0;
		*(tab - i + (hauteur*(largeur / 8))) = 0;
	}

	for (k = 0; k < (hauteur*(largeur / 8));k = k + largeur/8)
	{
		*(tab + k) = *(tab + k) & 0x7F;
		*(tab + k - 1 + (largeur/8)) = *(tab + k - 1 + (largeur/8)) & 0xFE;
	}
}

void modifier_couleur_nb_2(vc **tab, vi largeur, vi hauteur)
{
	vc *rang_tab_point = 0;
	vi i;
	vi j;
	vi k;
	rang_tab_point = *(tab + 0);
	for (i = 0; i < largeur / 8;i++)
	{
		*(rang_tab_point + i) = 0;
	}

	rang_tab_point = *(tab + (hauteur-1));
	for (j = 0;j < largeur / 8;j++)
	{
		*(rang_tab_point + j) = 0;
	}

	for (k = 0;k < hauteur; k++)
	{
		rang_tab_point = *(tab + k);
		*(rang_tab_point) = *(rang_tab_point)& 0x7F;
		*((rang_tab_point - 1 + largeur / 8)) = *((rang_tab_point - 1 + largeur / 8)) & 0xFE;
	}
}

void modifier_couleur_reel_1(Pixel24 *tab, vi largeur, vi hauteur)
{
	vi i;
	vi k;
	Pixel24 blanc, noir, bleu, vert, rouge;
	// Declaration des pixels
	{
		blanc.blue = 255;
		blanc.green = 255;
		blanc.red = 255;
		noir.blue = 0;
		noir.green = 0;
		noir.red = 0;
		bleu.blue = 255;
		bleu.green = 0;
		bleu.red = 0;
		vert.blue = 0;
		vert.green = 255;
		vert.red = 0;
		rouge.blue = 0;
		rouge.green = 0;
		rouge.red = 255;
	}

	for (i = 0; i < (largeur-1);i++) // Bordure supp et inf
	{
		*(tab + i) = vert;
		*(tab - i + (hauteur*largeur)-1) = vert;
		i++;
		*(tab + i) = bleu;
		*(tab - i + (hauteur*largeur)-1) = bleu;
		i++;
		*(tab + i) = rouge;
		*(tab - i + (hauteur*largeur)-1) = rouge;
		i++;
		*(tab + i) = noir;
		*(tab - i + (hauteur*largeur)-1) = noir;
	}

	for (k = 0; k < (hauteur)*(largeur) ;k = k + 4*largeur) // bordure cotés
	{
		vi l, m, n;
		*(tab + k) = vert;
		*(tab + k - 1 + largeur) = vert;

		l = k + largeur;
		*(tab + l) = bleu;
		*(tab + l - 1 + largeur) = bleu;

		m = l + largeur;
		*(tab + m) = rouge;
		*(tab + m - 1 + largeur) = rouge;

		n = m + largeur;
		*(tab + n) = noir;
		*(tab + n - 1 + largeur) = noir;
	}

	// Coin blanc en bas a gauche
	*tab = blanc;
	// Coin blanc en bas a droite
	*(tab + (largeur)-1) = blanc;
	// Coin blanc en haut gauche
	*(tab + (largeur)*(hauteur - 1)) = blanc;
	// Coin blanc en haut a droite
	*(tab + ((largeur)*hauteur) - 1) = blanc;

}

void modifier_couleur_reel_2(Pixel24 **tab, vi largeur, vi hauteur)
{
	vi i;
	vi k;
	vi s;
	Pixel24 *rang_tab_point = 0;
	Pixel24 blanc, noir, bleu, vert, rouge;
	// Declaration des pixels
	{
		blanc.blue = 255;
		blanc.green = 255;
		blanc.red = 255;
		noir.blue = 0;
		noir.green = 0;
		noir.red = 0;
		bleu.blue = 255;
		bleu.green = 0;
		bleu.red = 0;
		vert.blue = 0;
		vert.green = 255;
		vert.red = 0;
		rouge.blue = 0;
		rouge.green = 0;
		rouge.red = 255;
	}

		rang_tab_point = *(tab);
	for (i = 0; i < (largeur - 1);i++) // bordure inf
	{
		*(rang_tab_point + i) = vert;
		i++;

		*(rang_tab_point + i) = bleu;
		i++;

		*(rang_tab_point + i) = rouge;
		i++;

		*(rang_tab_point + i) = noir;
	}

	rang_tab_point = *(tab + hauteur - 1);
	for (k = 0; k < (largeur - 1);k++) // bordure supp
	{
		*(rang_tab_point + k) = vert;
		k++;

		*(rang_tab_point + k) = bleu;
		k++;

		*(rang_tab_point + k) = rouge;
		k++;

		*(rang_tab_point + k) = noir;
	}

	for (s = 0; s < hauteur;s++)
	{
		rang_tab_point = *(tab + s);
		*rang_tab_point = vert;
		*(rang_tab_point + largeur - 1) = vert;
		s++;

		rang_tab_point = *(tab + s);
		*rang_tab_point = bleu;
		*(rang_tab_point + largeur - 1) = bleu;
		s++;

		rang_tab_point = *(tab + s);
		*rang_tab_point = rouge;
		*(rang_tab_point + largeur - 1) = rouge;
		s++;

		rang_tab_point = *(tab + s);
		*rang_tab_point = noir;
		*(rang_tab_point + largeur - 1) = noir;
	}

	// Coin Blanc
	{
		rang_tab_point = *tab;
		// Coin blanc en bas a gauche
		*rang_tab_point = blanc;
		// Coin blanc en bas a droite
		*(rang_tab_point + (largeur)-1) = blanc;

		rang_tab_point = *(tab + hauteur - 1);
		// Coin blanc en haut gauche
		*(rang_tab_point) = blanc;
		// Coin blanc en haut a droite
		*(rang_tab_point + (largeur - 1)) = blanc;
	}
}

vecteurs * kPlacement(const int width, const int height, Pixel24 **tabColor, int nbrOfK, vecteurs *k)
{
    int i;
	//int nbPix = width*height;
	//int zoneK = 0;
    //vecteurs k[nbrOfK];
       k = (vecteurs *)malloc(nbrOfK*(sizeof(vecteurs*)));

		srand(time(NULL)); // initialisation de rand
        //zoneK = nbPix/nbrOfK;


		for (i = 0; i < nbrOfK; i++)
            {
                k[i].x = (int) rand()%width + 1;
                k[i].y = (int) rand()%height + 1;
                k[i].i = tabColor[k[i].x][k[i].y];
                cross(k[i].x,k[i].y, tabColor);
            }
    //printf("%d\n", k[1].x);

    return k;
}

int ** kArray(const int width, const int height, vecteurs *k, int nbrOfK, int **tabArray)
{
    int i, j, h, pos,calc,tempX,tempY;
    float temp = 10000,res;

    /*tabArray = (int **) malloc( height * (sizeof(int*)) );

    for (i = 0; i < height; ++i)
        {
        tabArray[i] = (int *)malloc(width*(sizeof(int)));
       // printf("%d\n", i);
printf("test\n");


        }*/
        	tabArray = ( int ** ) malloc( height * ( sizeof(int*) ));

	for (i = 0; i < height; ++i)
	{
		tabArray[i] = ( int * ) malloc( width * ( sizeof(int) ));
		//printf("test\n");
	}


//printf("%d\n", ((*k)+1)->x);
for (j = width-1; j >= 0; j--)
{

	for (h = height-1;h >= 0; h--)
	{
		for (i = 0; i< nbrOfK ; i++)
		{

			tempX = abs(k[i].x - j);

			tempY = abs(k[i].y - h);

			calc = (tempX^2) + (tempY^2);
			//printf("%d\n", calc);
			res = sqrt((float)calc);
             //printf("K %d : R1 = %d ; R2 = %d ; calc = %d ; Res = %2f\n", i, tempX, tempY, calc, res);

            if (res < temp)
			{
				temp = res;
					pos = i;

			}

        }
        tabArray[j][h] = pos;
        //printf("%d", tabArray[j][h]);
    }

	}
	for (j = width-1; j >= 0; j--)
    {

        for (h = height-1;h >= 0; h--)
        {
            printf("%d", tabArray[j][h]);
        }
    }

	return tabArray;
}
/*
vault moyk(int nbrOfK)
{
    vault moyArray [] = NULL;

    moyArray = (vault) malloc (nbrOfK * (sizeof(vault));

    return moyArray;
}
*/
void colorArray(const int width, const int height, vecteurs *k, int nbrOfK, int **tabArray, Pixel24 **tabColor)
{
    int j,h;
    for (j = width-1; j >= 0; j--)
    {

        for (h = height-1;h >= 0; h--)
        {
            tabColor[j][h] = k[tabArray[j][h]].i;
        }
    }

}

void cross(const int x, const int y, Pixel24 **tabColor)
{
    Pixel24 black;
    black.blue = 0;
    black.green = 0;
    black.red = 0;
    Pixel24 blanc;
    blanc.blue = 255;
    blanc.green = 255;
    blanc.red = 255;
    int i;// posx, posy;

    tabColor[x][y] = blanc;
    for(i=1; i < 3; i++)
    {
        //posx = x; posy = y;
        tabColor[x - i][y + i] = black;
        tabColor[x + i][y + i] = black;
        tabColor[x - i][y - i] = black;
        tabColor[x + i][y - i] = black;
    }

}

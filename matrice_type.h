//  Copyright (c) 2016 Armaury CAHUET, William ZERBATO. All rights reserved.
#ifndef MATRICE
#define MATRICE

typedef unsigned char vc;
typedef unsigned int vi;
typedef unsigned short int vsi;

struct matrice {
	vc nbr_ligne;
	vc nbr_colonne;
	vi size;
};

#pragma pack(1)
typedef struct
{
	vc type[2];
	vi taille;
	vi chp_reserve;
	vi offset;
} Header_file; // 14 octets le Header_file

typedef struct
{
	vi header_taille;
	vi largeur;
	vi hauteur;
	vsi plans;
	vsi bit_par_pixel;
	vi compression;
	vi bmptaille;
	vi Hresolu;
	vi Vresolu;
	vi nbcouleurs;
	vi nbcouleursimp;
	vc merdouille[100];
} Header_img; // 40 octets le Header_file

typedef struct
{
vc blue;
vc green;
vc red;
} Pixel24 ;


//OUR CODE

typedef struct
{
int x;
int y;
Pixel24 i;
} vecteurs;


vecteurs * kPlacement (const int width, const int height, Pixel24 **tabColor, int nbrOfK, vecteurs *k);
int ** kArray(const int width, const int height, vecteurs *k, int nbrOfK, int **tabArray);
void colorArray(const int width, const int height, vecteurs *k, int nbrOfK, int **tabArray, Pixel24 **tabColor);

typedef struct {
                    long x;
                    long y;
                    long i;} vault;

void cross(const int x, const int y, Pixel24 **tabColor);
#endif

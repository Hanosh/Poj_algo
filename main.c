//  Copyright (c) 2016 Armaury CAHUET, William ZERBATO. All rights reserved.
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "appel_fonction.h"

int main(int argc, char* argv[])
{
	if (argc != 3) // verification nombre d'arguments
	{
		printf("FORMAT INCORRECT : \n");
		printf("Format attendu: Executable  Dimension  image_source \n");
		printf("Executable = Project_lena_RGB\n");
		printf("Dimension = 1 ou 2\n");
		printf("image_source = lena_RGB.bmp ou lena_NB.bmp\n");
		system("pause");
	}
	else
	{
		if (strcmp(argv[1],"1") == 0 || strcmp(argv[1], "2") == 0) // verification dimensions
		{
			if (strcmp(argv[2], "lena_NB.bmp") == 0 || strcmp(argv[2], "lena_RGB.bmp") == 0) // verification fichier
			{
				FILE * original = NULL;
				vc car = 0;
				vi ligne = 0, colonne = 0;
				Pixel24 pixel, x;
				Header_file file_info;
				Header_img img_info;
				if (Copie(argv[2], "Nouveau.bmp")) return 0;  // on copie le fichier dans un 'nouveau' avec securité si le fichier n'existe pas ou n'est pas dans le dossier

				original = fopen("Nouveau.bmp", "rb+");
				verification_fichier(original);
				fread(&file_info, sizeof(Header_file), 1, original);
				fread(&img_info, sizeof(Header_img), 1, original);
				affiche_info_bmp(file_info, img_info);

				if (strcmp(argv[2], "lena_NB.bmp") == 0) // En noir et blanc
				{
					if (strcmp(argv[1], "1") == 0) // dimension 1
					{
						vi i;
						vc *tab = creer_tableau_pixel_nb_1(img_info.largeur, img_info.hauteur);
						fseek(original, file_info.offset, SEEK_SET);
						for (i = 0; i < (img_info.largeur / 8)* img_info.hauteur; i++ )
						{
							car = (vc)fgetc(original);
							*(tab + colonne) = car;
							colonne++;
						}

						modifier_couleur_nb_1(tab, img_info.largeur, img_info.hauteur);

						fseek(original, file_info.offset, SEEK_SET);
						for (i = 0; i < colonne;i++)
						{
							fputc((int)*(tab + i), original);
						}
						fclose(original);
					} // Dimension 1

					else // dimension 2
					{
						vi i;
						vc *rang_tab_point = NULL;
						vc **tab = creer_tableau_pixel_nb_2(img_info.largeur, img_info.hauteur);
						fseek(original, file_info.offset, SEEK_SET);

						for (ligne = 0; ligne < img_info.hauteur; ligne++)
						{
							rang_tab_point = *(tab + ligne);

							for (colonne = 0; colonne < img_info.largeur / 8; colonne++)
							{
								car = (vc)fgetc(original);
								*(rang_tab_point + colonne) = car;
							}
						}

						modifier_couleur_nb_2(tab, img_info.largeur, img_info.hauteur);

						fseek(original, file_info.offset, SEEK_SET);
						for(i = 0; i < ligne;i++)
						{
							vi k;
							rang_tab_point = *(tab + i);
							for (k = 0; k < colonne;k++)
							{
								fputc((int)*(rang_tab_point + k), original);
								printf("i %6d k %6d\r", i, k);
							}
						}
						fclose(original);
					} // Dimension 2

				}

				if (strcmp(argv[2], "lena_RGB.bmp") == 0) // En couleurs
				{

					if (strcmp(argv[1], "1") == 0) // Dimmension 1
					{
						vi i;
						Pixel24* tab = creer_tableau_pixel_couleur_1(img_info.largeur, img_info.hauteur);
						fseek(original, file_info.offset, SEEK_SET);
						for (i = 0; i < ((img_info.largeur))* img_info.hauteur; i++)
						{
							pixel.blue = (vc)fgetc(original);
							pixel.green = (vc)fgetc(original);
							pixel.red = (vc)fgetc(original);
							*(tab + colonne) = pixel;
							colonne++;
						}

						modifier_couleur_reel_1(tab, img_info.largeur, img_info.hauteur);

						fseek(original, file_info.offset, SEEK_SET);
						for (i = 0; i < colonne;i++)
						{
							x = *(tab + i);
							fputc((vc)x.blue, original);
							fputc((vc)x.green, original);
							fputc((vc)x.red, original);
						}
						fclose(original);
					} // Dimension 1

					else  // Dimension 2
					{
							vi i;
							int nbrOfK = 0;
							vecteurs *k;
							int **tabArray = NULL;
							Pixel24 *rang_tab_point = NULL;
 							Pixel24 **tab = creer_tableau_pixel_couleur_2(img_info.largeur, img_info.hauteur);
							fseek(original, file_info.offset, SEEK_SET);
							for (ligne = 0; ligne < img_info.hauteur; ligne++)
							{
								rang_tab_point = *(tab + ligne);
								for (colonne = 0; colonne < img_info.largeur;colonne++)
								{
									pixel.blue = (vc)fgetc(original);
									pixel.green = (vc)fgetc(original);
									pixel.red = (vc)fgetc(original);
									*(rang_tab_point + colonne) = pixel;
								}
							}
							/*    Pixel24 black;
                                black.blue = 0;
                                black.green = 0;
                                black.red = 0;
                                Pixel24 blanc;
                                blanc.blue = 255;
                                blanc.green = 255;
                                blanc.red = 255;

                            k[0].x = 100;
                            k[0].y = 100;
                            k[0].i = blanc;
                            k[1].x = 400;
                            k[1].y = 312;
                            k[1].i = black;*/
							while(nbrOfK < 1 || nbrOfK >= 17)
                            {
                                printf("nombre de K : \n");
                                scanf("%d", &nbrOfK);
                            }

                            k = kPlacement(img_info.largeur, img_info.hauteur, tab, nbrOfK, k);



                            printf("Placement des k = SUCCESS\n\n\tSi l'image ne s'affiche pas automatique, merci de le faire manuellement.");
                            printf("%d\n", k[1].x);
                            tabArray = kArray(img_info.largeur, img_info.hauteur, k, nbrOfK, tabArray);
                            colorArray(img_info.largeur, img_info.hauteur,  k, nbrOfK, tabArray, tab);
                            for (i = 0; i < nbrOfK; i++)
                            {
                                cross(k[i].x,k[i].y, tab);
                            }

							//modifier_couleur_reel_2(tab, img_info.largeur, img_info.hauteur);

							fseek(original, file_info.offset, SEEK_SET);
							for (i = 0; i < ligne;i++)
							{
								vi k;
								rang_tab_point = *(tab + i);
								for (k = 0; k < colonne;k++)
								{
									x = *(rang_tab_point + k);
									fputc((vc)x.blue, original);
									fputc((vc)x.green, original);
									fputc((vc)x.red, original);
								}
							}
							fclose(original);
					}
				}
				system("pause");
				system("mspaint.exe Nouveau.bmp");
			}
			else // Si fichier incorrect
			{
				printf("Le fichier image ne vaut pas lena_RGB.bmp ou lena_NB.bmp\n");
				system("pause");
			}

		}
		else // Si dimensioon incorrect
		{
			printf("La dimension ne vaut pas 1 ou 2\n");
			system("pause");
		}
	}
}

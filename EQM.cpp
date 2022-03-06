
#include <stdio.h>
#include "image_ppm.h"

/* 
  l’erreur quadratique moyenne(EQM):
  On compare chaque pixels de 2 images avec (x-y)²
*/

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgLue2[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageIn2.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgLue2);

   OCTET *ImgIn, *ImgIn2;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgIn2, OCTET, nTaille);
   lire_image_pgm(cNomImgLue2, ImgIn2, nH * nW);

    double som = 0;
    for (int i=0; i < nTaille; ++i){
        som += (ImgIn[i] - ImgIn2[i]) * (ImgIn[i] - ImgIn2[i]);
    }

    double res = som / nTaille;
    printf("difference = %f \n", res);   


   free(ImgIn); 
   free(ImgIn2);

   return 1;
}
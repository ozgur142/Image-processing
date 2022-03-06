
#include <stdio.h>
#include "image_ppm.h"

/*
  On modifie la composante(Y) avec une valeur (+/-)k
*/

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgOut[250];
  int k;
  int nH, nW, nTaille;
  
  if (argc != 4) 
     {
       printf("Usage: Y.pgm k(-128<k<+128) Ymodif.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   k = atoi(argv[2]);
   if (k > 128 || k < -128)
   {
     perror("k n'est pas dans les bonne bornes \n");
     exit(1);
   }
   sscanf (argv[3],"%s",cNomImgOut) ;

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);  


    for (int i = 0; i < nTaille; ++i){
        int y = ImgIn[i] + k;
        y = y > 255 ? 255 : y;
        y = y < 0 ? 0 : y;
        ImgOut[i] = y;
    }  

    ecrire_image_pgm(cNomImgOut, ImgOut,  nH, nW);

   free(ImgIn); 
   free(ImgOut);

   return 1;
}
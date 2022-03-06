
#include <stdio.h>
#include "image_ppm.h"

/*
   Avec l’image binaire et l’image dilatées on peut bien voir tous les contours
*/

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgLue2[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 4) 
     {
       printf("Usage: ImageIn.pgm dilatation.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgLue2) ;
   sscanf (argv[3],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgIn2, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nH = 256;
   nW = 256;
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   allocation_tableau(ImgIn2, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   lire_image_pgm(cNomImgLue2, ImgIn2, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
	

  for (int i=0; i < nH; i++){
    for (int j=0; j < nW; j++){
      int x = i*nW+j;
      if (ImgIn[x] == ImgIn2[x])
        ImgOut[x] = 255;
      else
        ImgOut[x] = 0;
    }
  }




   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut); free(ImgIn2);

   return 1;
}



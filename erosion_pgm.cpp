
#include <stdio.h>
#include "image_ppm.h"

/*
  Pour faire l’erosion on parcours tout l’image et on regarde ces 8 voisins puis s’il a un voisin blanc, on
  transforme ce pixel centrale en blanc sinon on laisse noir. Comme ca on enlève le bruit d’image et il
  devient plus facile à traiter.
*/

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
	

  for (int i=0; i < nH; i++){
    for (int j=0; j < nW; j++)
    {
      int pixelVal = 0;
      if (ImgIn[i*nW+j] == 0) //si le pixel est noir (sinon pas la peine)
      {
        for (int k = -1; k < 2; ++k){
          for (int t = -1; t < 2; ++t){
            int a = i+k;
            int b = j+t;
            int indice = a*nW+b;
            if (a < 0 || a >= nH || b < 0 || b >= nW || indice == i*nW+j)
              continue;
            else {
              if (ImgIn[indice] == 255)
                pixelVal = 255;
            }
          }
        }
      }
      else
        pixelVal = 255;
      ImgOut[i*nW+j] = pixelVal; 
    } 
  }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}



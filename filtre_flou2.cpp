
#include <stdio.h>
#include "image_ppm.h"

/*
  moyenne de ce pixel avec ses 8 voisins
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


// pour les bordures moyenneur
/*
  for(int i=0; i<nH; i++) {
    for(int j=0; j<nW; j++)
    {
      int x = 0;
      int quantite = 0;
      for(int k=-1; k<2; k++) {
        for(int t=-1; t<2; t++) 
        {
          if(i+k>=0 && i+k<nH && j+t>=0 && j+t<nW) {
            x += ImgIn[(i+k)*nW+j+t];
            quantite++;
          }
        }
      }
      ImgOut[i*nW+j] = (int)(x/quantite);
    }
  }
*/


 for (int i=0; i < nH; i++){
   for (int j=0; j < nW; j++)
     {
      if (i == 0 || j == 0 || i == nW-1 || i == nH-1)
        ImgOut[i*nW+j] = ImgIn[i*nW+j];
      else{
        int x = 0;
        for (int k = -1; k < 2; ++k){
          for (int t = -1; t < 2; ++t)
          {
            x += ImgIn[(i+k)*nW + j+t];
          }
        }
        ImgOut[i*nW+j] = x/9;
      }
    }
  }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}

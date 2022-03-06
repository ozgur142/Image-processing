
#include <stdio.h>
#include "image_ppm.h"

/*
  Pour supprimer des points parasites du fond de l’image binaire
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

   OCTET *ImgIn, *ImgOut, *ImgOut2;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nH = 256;
   nW = 256;
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);

   allocation_tableau(ImgOut2, OCTET, nTaille);


// Erosion puis dilatation pour remplier les trous


//Erosion
  for (int i=0; i < nH; i++){
    for (int j=0; j < nW; j++)
    {
      ImgOut[i*nW+j] = 0;
      for (int k = -1; k < 2; ++k)
      {
        for (int t = -1; t < 2; ++t)
        {
          int a = i+k;
          int b = j+t;
          int indice = a*nW+b;
          if (a < 0 || a >= nH || b < 0 || b >= nW)
            continue;
          else {
            if (ImgIn[indice] == 255){
              ImgOut[i*nW+j] = 255;
              break;
            }
            }
          }
        }
      }
       
  }


//Dilatation
  for (int i=0; i < nH; i++){
    for (int j=0; j < nW; j++)
    {
      ImgOut2[i*nW+j] = 255; // pour initialiser l'image output à blanc
      for (int k = -1; k < 2; ++k)
      {
        for (int t = -1; t < 2; ++t)
        {
          int a = i+k;
          int b = j+t;
          int indice = a*nW+b;
          if (a < 0 || a >= nH || b < 0 || b >= nW)
            continue;
          else {
            if (ImgOut[indice] == 0){
              ImgOut2[i*nW+j] = 0;
              break;
            }
            }
          }
        }
      }
  }




   ecrire_image_pgm(cNomImgEcrite, ImgOut2,  nH, nW);
   free(ImgIn); free(ImgOut); free(ImgOut2);

   return 1;
}



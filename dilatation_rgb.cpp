
#include <stdio.h>
#include "image_ppm.h"

/*
  Pour faire l’erosion on parcours tout l’image par les couche rouge, vert et blue et on regarde ces 8 voisins puis s’il a un voisin noir, on
  transforme ce pixel centrale en noir sinon on laisse blanc. Comme ça on enlève le bruit d’image et il
  devient plus facile à traiter.
*/

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut, *ImgInR, *ImgOutR, *ImgInG, *ImgOutG, *ImgInB, *ImgOutB;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   allocation_tableau(ImgInR, OCTET, nTaille);
   allocation_tableau(ImgInG, OCTET, nTaille);
   allocation_tableau(ImgInB, OCTET, nTaille);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOutR, OCTET, nTaille);
   allocation_tableau(ImgOutG, OCTET, nTaille);
   allocation_tableau(ImgOutB, OCTET, nTaille);
   allocation_tableau(ImgOut, OCTET, nTaille3);


   //SEPARATION DES COLEURS
   planR(ImgInR, ImgIn, nH * nW);
   planV(ImgInG, ImgIn, nH * nW);
   planB(ImgInB, ImgIn, nH * nW);


  for (int i=0; i < nH; i++){
    for (int j=0; j < nW; j++)
    {
      ImgOutR[i*nW+j] = 255; // pour initialiser l'image output à blanc
      ImgOutG[i*nW+j] = 255;
      ImgOutB[i*nW+j] = 255;
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
            if (ImgInR[indice] == 0) ImgOutR[i*nW+j] = 0;
            if (ImgInG[indice] == 0) ImgOutG[i*nW+j] = 0;
            if (ImgInB[indice] == 0) ImgOutB[i*nW+j] = 0;
          }
        }
      }
    }   
  }



  //reconstruction de rgb
  for (int i = 0; i < nTaille; ++i)
  {
    ImgOut[3*i] = ImgOutR[i];
    ImgOut[3*i+1] = ImgOutG[i];
    ImgOut[3*i+2] = ImgOutB[i];
  }

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);
   free(ImgOutR); free(ImgInR); 
   free(ImgInG); free(ImgOutG); 
   free(ImgInB); free(ImgOutB);

   return 1;
}



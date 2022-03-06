
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
       printf("Usage: ImageIn.ppm ImageOut.ppm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgInR, *ImgOutR, *ImgInG, *ImgOutG, *ImgInB, *ImgOutB, *ImgOutRGB;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   //nH = 256;
   //nW = 256;
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
   allocation_tableau(ImgOutRGB, OCTET, nTaille3);




   //SEPARATION DES COLEURS
   planR(ImgInR, ImgIn, nH * nW);
   planV(ImgInG, ImgIn, nH * nW);
   planB(ImgInB, ImgIn, nH * nW);


   //FLOUTAGE
   for (int i=0; i < nH; i++){
     for (int j=0; j < nW; j++)
       {
        if (i == 0 || j == 0 || i == nW-1 || i == nH-1){
          ImgOutR[i*nW+j] = ImgInR[i*nW+j];
          ImgOutG[i*nW+j] = ImgInG[i*nW+j];
          ImgOutB[i*nW+j] = ImgInB[i*nW+j];
        }

        else{
          int r = 0;
          int g = 0;
          int b = 0;
          for (int k = -1; k < 2; ++k)
          {
            for (int t = -1; t < 2; ++t)
            {
              r += ImgInR[(i+k)*nW + j+t];
              g += ImgInG[(i+k)*nW + j+t];
              b += ImgInB[(i+k)*nW + j+t];
            }
          }
          ImgOutR[i*nW+j] = r/9;
          ImgOutG[i*nW+j] = g/9;
          ImgOutB[i*nW+j] = b/9;
        }
      }
    }


    //reconstruction de rgb
    for (int i = 0; i < nTaille; ++i)
    {
      ImgOutRGB[3*i] = ImgOutR[i];
      ImgOutRGB[3*i+1] = ImgOutG[i];
      ImgOutRGB[3*i+2] = ImgOutB[i];
    }



   

   ecrire_image_ppm(cNomImgEcrite, ImgOutRGB,  nH, nW);
   free(ImgIn); free(ImgOutR);
   free(ImgInR); free(ImgInG); 
   free(ImgOutG); free(ImgInB); 
   free(ImgOutB); free(ImgOutRGB);




   return 1;
}


#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgLue2[250], cNomImgLue3[250], cNomImgOut[250];
  int nH, nW, nTaille;
  
  if (argc != 5) 
     {
       printf("Usage: ImageY.pgm ImageCr.pgm ImageCb.pgm ImageOut.ppm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgLue2) ;
   sscanf (argv[3],"%s",cNomImgLue3) ;
   sscanf (argv[4],"%s",cNomImgOut) ;

   OCTET *ImgOut, *ImgY, *ImgCb, *ImgCr;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

   int nTaille3 = nTaille * 3;

    allocation_tableau(ImgOut, OCTET, nTaille3);
   
   allocation_tableau(ImgY, OCTET, nTaille);
   allocation_tableau(ImgCb, OCTET, nTaille);
   allocation_tableau(ImgCr, OCTET, nTaille);

   lire_image_pgm(cNomImgLue, ImgY, nH * nW);
   lire_image_pgm(cNomImgLue2, ImgCb, nH * nW);
   lire_image_pgm(cNomImgLue3, ImgCr, nH * nW);





    // R = Y + 1.402*(Cr-128)
    // G = Y - 0.34414*(Cb-128) - 0.71414*(Cr-128)
    // B = Y + 1.772*(Cb-128) 
    for(int i = 0; i<nTaille; ++i){
       int R = ImgY[i] + 1.402*(ImgCr[i]-128); 
       if (R > 255)
         R = 255;
       if (R < 0)
         R = 0;
       int G = ImgY[i] - 0.34414*(ImgCb[i]-128) -  0.71414*(ImgCr[i]-128);
       if (G > 255)
         G = 255;
       if (G < 0)
         G = 0;
       int B = ImgY[i] + 1.772*(ImgCb[i]-128);
       if (B > 255)
         B = 255;
       if (B < 0)
         B = 0;
       ImgOut[3*i] = R;
       ImgOut[3*i+1] = G;
       ImgOut[3*i+2] = B;
   } 


   ecrire_image_ppm(cNomImgOut, ImgOut,  nH, nW);

   
   free(ImgOut); 
    free(ImgY);
    free(ImgCb); free(ImgCr);
    
   return 1;
}
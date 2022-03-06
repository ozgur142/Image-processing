
#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgInR, *ImgInG, *ImgInB, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   allocation_tableau(ImgInR, OCTET, nTaille);
   allocation_tableau(ImgInG, OCTET, nTaille);
   allocation_tableau(ImgInB, OCTET, nTaille);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);


   //SEPARATION DES COLEURS
   planR(ImgInR, ImgIn, nH * nW);
   planV(ImgInG, ImgIn, nH * nW);
   planB(ImgInB, ImgIn, nH * nW);


   //rgb to y =>  Y = 0.299*R + 0.587*G + 0.114*B 
  for(int i = 0; i<nTaille; ++i){
    int y= ImgInR[i]*0.299 + ImgInG[i]*0.587 + ImgInB[i]*0.114;
    ImgOut[i] = y;
  }



   

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); 
   free(ImgInR); free(ImgInG); 
    free(ImgInB); free(ImgOut);




   return 1;
}

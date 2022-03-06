
#include <stdio.h>
#include "image_ppm.h"

/*
  le programme décompose l'image rgb en 3 compasantes Y Cb Cr
*/

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgY[250], cNomImgCr[250], cNomImgCb[250];
  int nH, nW, nTaille;
  
  if (argc != 5) 
     {
       printf("Usage: ImageIn.ppm ImageOutY.pgm ImageOutCr.pgm ImageOutCb.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgY) ;
   sscanf (argv[3],"%s",cNomImgCr) ;
   sscanf (argv[4],"%s",cNomImgCb) ;

   OCTET *ImgIn, *ImgInR, *ImgInG, *ImgInB, *ImgY, *ImgCb, *ImgCr;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

   int nTaille3 = nTaille * 3;

    allocation_tableau(ImgIn, OCTET, nTaille3);
   allocation_tableau(ImgInR, OCTET, nTaille);
   allocation_tableau(ImgInG, OCTET, nTaille);
   allocation_tableau(ImgInB, OCTET, nTaille);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgY, OCTET, nTaille);
   allocation_tableau(ImgCb, OCTET, nTaille);
   allocation_tableau(ImgCr, OCTET, nTaille);

   //SEPARATION DES COLEURS
   planR(ImgInR, ImgIn, nH * nW);
   planV(ImgInG, ImgIn, nH * nW);
   planB(ImgInB, ImgIn, nH * nW);


    //rgb to y =>  Y = 0.299*R + 0.587*G + 0.114*B
    //             Cb = -0.168736*R - 0.331264*G + 0.5*B + 128
    //             Cr = 0.5*R - 0.418688*G - 0.081312*B + 128 
    for(int i = 0; i<nTaille; ++i){
       int y= ImgInR[i]*0.299 + ImgInG[i]*0.587 + ImgInB[i]*0.114;
       int Cb =  ImgInR[i]*-0.168736 - ImgInG[i]*0.331264 + ImgInB[i]*0.5 + 128;
       int Cr = ImgInR[i]*0.5 - ImgInG[i]*0.418688 - ImgInB[i]*0.081312 + 128;
       ImgY[i] = y;
       ImgCb[i] = Cb;
       ImgCr[i] = Cr;
   } 

   ecrire_image_pgm(cNomImgY, ImgY,  nH, nW);
   ecrire_image_pgm(cNomImgCr, ImgCb,  nH, nW);
   ecrire_image_pgm(cNomImgCb, ImgCr,  nH, nW);

   free(ImgIn); 
   free(ImgInR); free(ImgInG); 
    free(ImgInB); free(ImgY);
    free(ImgCb); free(ImgCr);

   return 1;
}
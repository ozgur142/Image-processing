
#include <stdio.h>
#include "image_ppm.h"

/*
  Première lecture de l’image de la norme des gradients : si norme du gradient <= SB alors 0, si
    norme du gradient >= SH alors 255.
  Deuxième lecture de l’image de la norme de gradients pré-seuillée avec SB et SH : si SB < norme
    du gradient < SH ET qu’au moins 1 de ses voisins = 255 alors 255 sinon 0.
*/

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, SB, SH;
  
  if (argc != 5) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm SH SB \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%d",&SH);
   sscanf (argv[4],"%d",&SB);

   OCTET *ImgIn, *ImgOut1, *ImgOut2;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut1, OCTET, nTaille);
   allocation_tableau(ImgOut2, OCTET, nTaille);
	


   //premier lecture
  for (int i=0; i < nH; i++){
    for (int j=0; j < nW; j++)
    {
      if ( ImgIn[i*nW+j] <= SB) 
        ImgOut1[i*nW+j]=0; 
      else if (ImgIn[i*nW+j] >= SH) 
        ImgOut1[i*nW+j]=255;
      else
        ImgOut1[i*nW+j] = ImgIn[i*nW+j];
    }
  }

  //deuxieme lecture
  for (int i=0; i < nH; i++){
    for (int j=0; j < nW; j++)
    {
      if (ImgOut1[i*nW+j] == 0 || ImgOut1[i*nW+j] == 255)
        ImgOut2[i*nW+j] = ImgOut1[i*nW+j];
      else{
        bool voisin = false;
        for (int k = -1; k < 2; ++k){
          for (int t = -1; t < 2; ++t){
            if (ImgOut2[(i+k)*nW + j+t] == 255)
              voisin = true;
          }
        }
        if (voisin)
          ImgOut2[i*nW+j] = 255;
        else
          ImgOut2[i*nW+j] = 0;
      }
    }
  }


   ecrire_image_pgm(cNomImgEcrite, ImgOut2,  nH, nW);
   free(ImgIn); free(ImgOut1);
   free(ImgOut2);

   return 1;
}

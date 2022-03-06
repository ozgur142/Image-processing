#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250];
  char histo3Out[250];
  int nH, nW, nTaille;
  int r[256];
  int g[256];
  int b[256];
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm histo3Out.dat \n"); 
       exit (1) ;
     }

  for (int i=0; i<256; ++i){
    r[i] = 0;
    g[i] = 0;
    b[i] = 0;
  }
     
   
   sscanf (argv[1],"%s",cNomImgLue);
   sscanf (argv[2],"%s",histo3Out);

   OCTET *ImgIn;

   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   
   for (int i=0; i < nTaille3; i+=3)
     {
       r[ImgIn[i]]++;
       g[ImgIn[i+1]]++;
       b[ImgIn[i+2]]++;
     }

    std::ofstream outfile(histo3Out);

    for (int i = 0; i < 256; i++)
        outfile<<i<<" "<<r[i]<<" "<<g[i]<<" "<<b[i]<<" "<<std::endl;

    free(ImgIn);

   return 1;
}
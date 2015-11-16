#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <string.h>



int main(){


  FILE* fichier1,*fichier2;
  int num,type,n_elements,i;
  double R[3],vec1[3],vec2[3],norm[3],surface;

  fichier2=fopen("3144210020_readed.pos","w");
  fichier1=fopen("3144210020_readed.dat","r");


  fprintf(fichier2,"View \"Field\" {\n");
  
  fscanf(fichier1,"%d\n",&n_elements);

  for(i=0 ; i<n_elements ; i++){
  fscanf(fichier1,"%d %d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",&num,&type,&R[0],&R[1],&R[2],&vec1[0],&vec1[1],&vec1[2],&vec2[0],&vec2[1],&vec2[2],&norm[0],&norm[1],&norm[2],&surface);

  fprintf(fichier2,"VP(%lf,%lf,%lf){%lf,%lf,%lf};\n",R[0],R[1],R[2],norm[0],norm[1],norm[2]);
  
  }
  fprintf(fichier2,"};");
  
  fclose(fichier1);
  fclose(fichier2);
  return 0;
  }

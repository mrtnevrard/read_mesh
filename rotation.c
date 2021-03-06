#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "header2.h"

int main()
{
  
  double R1[3][3],R2[3][3],R3[3][3],thetaz,thetay,thetax,*vec1,*vec2,*R,*norm,surface,*center;
  int n_elements,i,type_of,l;
  FILE* fichier1,*fichier2;
  float temps;
  clock_t t1, t2;
 
    t1 = clock();
 

  
 
  
  fichier1=fopen("meshing_readed.dat","r");
  fichier2=fopen("meshing_rotated.dat","w");
  
  
  
  fscanf(fichier1,"%d\n",&n_elements);
  fprintf(fichier2,"%d\n",n_elements);
  vec2 = (double*) calloc(3,sizeof(double));
  vec1 = (double*) calloc(3,sizeof(double));
  R = (double*) calloc(3,sizeof(double));
  norm = (double*) calloc(3,sizeof(double));
  center = (double*) calloc(3,sizeof(double));
  
  

  thetax=0.1;
  thetay=0.2;
  thetaz=0.1;
  
  R3[0][0]=cos(thetaz);
  R3[0][1]=-sin(thetaz);
  R3[0][2]=0.;
  R3[1][0]=sin(thetaz);
  R3[1][1]=cos(thetaz);
  R3[1][2]=0.;
  R3[2][0]=0.;
  R3[2][1]=0.;
  R3[2][2]=1.;
  
  R2[0][0]=cos(thetay);
  R2[0][1]=0.;
  R2[0][2]=-sin(thetay);
  R2[1][0]=0;
  R2[1][1]=1.;
  R2[1][2]=0.;
  R2[2][0]=sin(thetay);
  R2[2][1]=0.;
  R2[2][2]=cos(thetay);
  
  R1[0][0]=1;
  R1[0][1]=0;
  R1[0][2]=0.;
  R1[1][0]=0;
  R1[1][1]=cos(thetax);
  R1[1][2]=-sin(thetax);
  R1[2][0]=0.;
  R1[2][1]=sin(thetax);
  R1[2][2]=cos(thetax);
  
  for(i=0 ; i<n_elements ; i++){
    
    
    //  fscanf(fichier1,"%d %d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",&l,&type_of,&R[0],&R[1],&R[2],&vec1[0],&vec1[1],&vec1[2],&vec2[0],&vec2[1],&vec2[2],&norm[0],&norm[1],&norm[2],&surface,&center[0],&center[1],&center[2]);
    /*  
    R=prod(R1,prod(R2,prod(R3,R)));
    vec1=prod(R1,prod(R2,prod(R3,vec1)));
    vec2=prod(R1,prod(R2,prod(R3,vec2)));
    norm=prod(R1,prod(R2,prod(R3,norm)));
    center=prod(R1,prod(R2,prod(R3,center)));
    */
      fprintf(fichier2,"%d %d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",l,type_of,R[0],R[1],R[2],vec1[0],vec1[1],vec1[2],vec2[0],vec2[1],vec2[2],norm[0],norm[1],norm[2],surface,center[0],center[1],center[2]);




    
  }
  
 
  



  


 



  
 
  //  printf("vec2 = %lf %lf %lf \n error = %lf\n",vec2[0],vec2[1],vec2[2]);

  fclose(fichier1);
  fclose(fichier2);
     
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps (s)= %f\n", temps);
  return 0;
}
  


 

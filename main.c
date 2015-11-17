/************************************************************************************************

Main program : - read msh files and calculate position of vectors and normales
               - rotating objects


************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "header_main.h"
#include <sys/time.h>
int main(){
  
  float temps;
  clock_t t1, t2;
  FILE* folder1,*folder2;
  int n_elements,q;
  int* type_of;
  double** R;
  double** vec1;
  double** vec2;
  double** norm;
  double* surface;
  double** center;
  char ligne1[256];
  int i,n_nodes,nothing,n_elements1,**element,**element1,n_tag,*type_of1,j,k,a,type2,test_noeuds,test_elements1,test_elements2,l;
  double** node,**norm1,**vec11,**vec21,**R1,*surface1,**center1;
  double *phi_init,*theta_init;
  int c;
  int n_angles = 0;
  double* proba_angles,aleat,real_rand,real_rand_max;
 
  struct timeval start;

  gettimeofday(&start, NULL);
 
  
  t1 = clock();
  q=start.tv_usec;
  printf("%d\n",q);
 
  srand(q);
  test_noeuds=0;
  test_elements1=0;
  test_elements2=0;
  
  
  //-------------------ouverture du fichier .msh---------------------------------
  
  
  folder1=fopen("meshing.msh","r");
  
  
  //-------------------------lignes inintéressantes------------------------------
  
  for(i=1 ; i<7 ; i++){
    fscanf(folder1,"%s \n",ligne1);
  }
  


  
  
  //---------------------allocations du nombre de noeuds-----------------------
  fscanf(folder1,"%d \n",&n_nodes);
  node = (double**)calloc( n_nodes , sizeof(double*));
  
  
  for( i = 0 ; i < n_nodes ; i++ ){
    node[i] = (double*) calloc (3, sizeof(double));
  }
  
  for(i=0 ; i<n_nodes ; i++){
    
    fscanf(folder1,"%d %lf %lf %lf \n",&nothing,& node[i][0],&node[i][1],&node[i][2]);  
  }
  
  test_noeuds=nothing;
  if(test_noeuds!=n_nodes){
    
    printf("ERROR!!, the number of noeuds is not the same that annonced");
    exit(1);
    
  }
  
  
  //------------------éléments inintéressants---------------------------
  
  fscanf(folder1,"%s \n",ligne1);
  fscanf(folder1,"%s \n",ligne1);
  
  //-----------------nombre d'éléments----------------------------
  fscanf(folder1,"%d\n",&n_elements1);
  
  element1 = (int**)calloc( n_elements1 , sizeof(int*));
  type_of1 = (int*)calloc( n_elements1,sizeof(int));
  norm1 = (double**)calloc( n_elements1 , sizeof(double*));
  vec11 = (double**)calloc( n_elements1 , sizeof(double*));
  vec21 = (double**)calloc( n_elements1 , sizeof(double*));
  R1 = (double**)calloc( n_elements1 , sizeof(double*));
  surface1 = (double*)calloc( n_elements1,sizeof(double));
   center1 = (double**)calloc( n_elements1 , sizeof(double*));
  
  
  
  
  
  
  
  
  //------------------------------------------------------------------------------------------------
  //                                 Lecture des éléments
  //------------------------------------------------------------------------------------------------
  
  
  for( i = 0 ; i < n_elements1 ; i++ )
    {
      
      fscanf(folder1,"%d %d %d",&a,&type_of1[i],&n_tag);
      
      
      
      
      
      
      
      //--------------------------------------------------------------------------------------------
      //-------------------------------------------------------------------------------------------
      
      
      
      
      if(((type_of1[i]+1)<=4) && ((type_of1[i]+1)>=3)){
        test_elements1++;
	
	for ( j=0 ; j<n_tag ; j++ ){
	  fscanf(folder1,"%d ",&nothing);
	}
	
	
	element1[i] = (int*) calloc (type_of1[i]+1, sizeof(int));
	norm1[i] = (double*) calloc (3, sizeof(double));
	vec11[i] = (double*) calloc (3, sizeof(double));
	vec21[i] = (double*) calloc (3, sizeof(double));
	R1[i] = (double*) calloc (3, sizeof(double));
	center1[i] = (double*) calloc (3, sizeof(double));
	
	
	if(type_of1[i]==2){
	  fscanf(folder1,"%d %d %d \n",&element1[i][0],&element1[i][1],&element1[i][2]);
	  
	  
	}
	
	else{
	  fscanf(folder1,"%d %d %d %d\n",&element1[i][0],&element1[i][1],&element1[i][2],&element1[i][3]);
	}
	
	for(k=0;k<3;k++){
	  R1[i][k]=node[element1[i][0]-1][k];
	  vec11[i][k]=node[element1[i][1]-1][k]-R1[i][k];
	  vec21[i][k]=node[element1[i][2]-1][k]-R1[i][k];
	  center1[i][k]=R1[i][k]+vec11[i][k]/3.+vec21[i][k]/3.;
	  
	}
	
	norm1[i]=vecprod(vec11[i],vec21[i]);
	
	surface1[i]=sqrt(pow(norm1[i][0],2)+pow(norm1[i][1],2)+pow(norm1[i][2],2));
	if(surface1[i]!=0){
	  for(k=0 ; k<3 ; k++){
	    
	    
	    norm1[i][k]=norm1[i][k]/surface1[i];
	    
	    
	  }
	}
	if(type_of1[i]==2){
	  
	  surface1[i]=surface1[i]/2.;
	  
	}
	
	
	
	
	
	
	
        
	
	
	
      }
      
      
      
      
      
      
      
      //--------------------------------------------------------------------------------------------
      
      
      
      
      
      
      
      
      else{
	
	test_elements2++;
	
	for ( j=0 ; j<n_tag ; j++ ){
	  fscanf(folder1,"%d",&nothing);
	}
	
	
	if(type_of1[i]!=15){
	  type2=type_of1[i];
	}
	else{
	  type2=0;
	}
	element1[i] = (int*) calloc (type2+1, sizeof(int));
	
	
	
	
	for( j=0 ; j<=type2 ; j++ ){
	  
	  if(j!=type2){
	    fscanf(folder1,"%d",&nothing);
	  }
	  else{
	    fscanf(folder1,"%d\n",&nothing);
	  }	  
	}
	
      }
      // printf(" element %d: %lf %lf %lf\n",i,element[i]);
      
    }
  
  
  
  if(test_elements1!=n_elements1-test_elements2){
    
    printf("ERROR!, the number of physical surfaces is not the same that announced"); 
    exit(1);
  }
  
  n_elements=test_elements1;
  
  fclose(folder1);
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  l=0;
  
  
  element = (int**)calloc( n_elements , sizeof(int*));
  type_of = (int*)calloc( n_elements,sizeof(int));
  norm = (double**)calloc( n_elements , sizeof(double*));
  vec1 = (double**)calloc( n_elements , sizeof(double*));
  vec2 = (double**)calloc( n_elements , sizeof(double*));
  R = (double**)calloc( n_elements , sizeof(double*));
  surface = (double*)calloc( n_elements,sizeof(double));
  center = (double**)calloc(n_elements,sizeof(double*));
   
  
  
 
  
  
  
  for(i=0 ; i<n_elements1 ; i++){
    
    if(type_of1[i]==2 || type_of1[i]==3){
      
      
      type_of[l]=type_of1[i];
      surface[l]=surface1[i];
      
      element[l] = (int*) calloc (type_of[l]+1, sizeof(int));
      norm[l] = (double*) calloc (3, sizeof(double));
      vec1[l] = (double*) calloc (3, sizeof(double));
      vec2[l] = (double*) calloc (3, sizeof(double));
      R[l] = (double*) calloc (3, sizeof(double));
      center[l] = (double*) calloc(3, sizeof(double));
      
      
      
      
      for(k=0 ; k<type_of[l]+1 ; k++){
	
	
	element[l][k]=element1[i][k];
	
      }
      
      
      
      
      for(k=0 ; k<3 ; k++){
	
	
	norm[l][k]=norm1[i][k];
	vec1[l][k]=vec11[i][k];
	vec2[l][k]=vec21[i][k];
	R[l][k]=R1[i][k];
	center[l][k]=center1[i][k];
	
      }
      
     
      l++;
    }
    
    
    
  }
 
  

  
  
  
  fclose(folder1);





  /*

*******************    end of the reading of the folder.*************************************************

   */


  folder2= fopen("test_distrib.txt","r");

 
  


  while((c=fgetc(folder2)) != EOF)
    {
      if(c=='\n'){
	n_angles++;
	
      }
      
      
      
    }
  fclose(folder2);
  
  theta_init = (double*) calloc(n_angles,sizeof(double));
  phi_init = (double*) calloc(n_angles,sizeof(double));
  proba_angles = (double*) calloc(n_angles,sizeof(double));
  folder2 = fopen("test_distrib.txt","r");
  
  
  for ( i=0 ; i<n_angles ; i++){
    
    
    
    fscanf(folder2,"%d %lf %lf %lf\n",&nothing,&theta_init[i],&phi_init[i],&proba_angles[i]);
      
       
      
      }
  

  real_rand=rand();
  real_rand_max=RAND_MAX;
  
  aleat=real_rand/real_rand_max;

  printf("rand = %lf\n",aleat);

  for(i=0 ; i<10 ; i++)

    {


  real_rand=rand();
  real_rand_max=RAND_MAX;
  
  aleat=real_rand/(real_rand_max);

  printf("rand = %lf\n",aleat);
      

    }
  
  
  
  
  
  
  t2 = clock();
  
  
  temps=(t2-t1)/1000.;
  printf("time of run (s) : %f\n",temps);
  
  return 0;
}

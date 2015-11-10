#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include "header.h"

int main(){

  FILE* fichier1,*fichier2;
  char ligne1[256];
  int i,n_nodes,nothing,n_elements1,n_elements,**element,**element1,n_tag,*type_of1,*type_of,j,test1,k,a,type2,test_noeuds,test_elements1,test_elements2,l;
  double** node,**norm1,**norm,**vec11,**vec1,**vec21,**vec2,**R1,**R,*surface1,*surface;
  
  
  
  test1=0;
  test_noeuds=0;
  test_elements1=0;
  test_elements2=0;
  
  
  //-------------------ouverture du fichier .msh---------------------------------
  
  
  fichier1=fopen("3144210020.msh","r");
  fichier2=fopen("test_norm.dat","w");
  
  //-------------------------lignes inintéressantes------------------------------
  
  for(i=1 ; i<7 ; i++){
    fscanf(fichier1,"%s \n",ligne1);
  }
  
  
  
  //---------------------allocations du nombre de noeuds-----------------------
  fscanf(fichier1,"%d \n",&n_nodes);
  node = (double**)calloc( n_nodes , sizeof(double*));
  
  
  for( i = 0 ; i < n_nodes ; i++ ){
    node[i] = (double*) calloc (3, sizeof(double));
  }
  
  for(i=0 ; i<n_nodes ; i++){
   
    fscanf(fichier1,"%d %lf %lf %lf \n",&nothing,& node[i][0],&node[i][1],&node[i][2]);
 
  }
 
  test_noeuds=nothing;
    if(test_noeuds!=n_nodes){

      printf("ERROR!!, the number of noeuds is not the same that annonced");
       return 1;

    }
  
  
  //------------------éléments inintéressants---------------------------
  
  fscanf(fichier1,"%s \n",ligne1);
  fscanf(fichier1,"%s \n",ligne1);
  
  //-----------------nombre d'éléments----------------------------
  fscanf(fichier1,"%d\n",&n_elements1);
  
  element1 = (int**)calloc( n_elements1 , sizeof(int*));
  type_of1 = (int*)calloc( n_elements1,sizeof(int));
  norm1 = (double**)calloc( n_elements1 , sizeof(double*));
  vec11 = (double**)calloc( n_elements1 , sizeof(double*));
  vec21 = (double**)calloc( n_elements1 , sizeof(double*));
   R1 = (double**)calloc( n_elements1 , sizeof(double*));
  surface1 = (double*)calloc( n_elements1,sizeof(double));
  
  







  //------------------------------------------------------------------------------------------------
  //                                 Lecture des éléments
  //------------------------------------------------------------------------------------------------
  
  
  for( i = 0 ; i < n_elements1 ; i++ )
    {
      
      fscanf(fichier1,"%d %d %d",&a,&type_of1[i],&n_tag);
   






      //--------------------------------------------------------------------------------------------
      //-------------------------------------------------------------------------------------------



      
      if(((type_of1[i]+1)<=4) && ((type_of1[i]+1)>=3)){
        test_elements1++;
	
	for ( j=0 ; j<n_tag ; j++ ){
	  fscanf(fichier1,"%d ",&nothing);
	}


	element1[i] = (int*) calloc (type_of1[i]+1, sizeof(int));
	norm1[i] = (double*) calloc (3, sizeof(double));
	vec11[i] = (double*) calloc (3, sizeof(double));
	vec21[i] = (double*) calloc (3, sizeof(double));
	R1[i] = (double*) calloc (3, sizeof(double));
	


	  if(type_of1[i]==2){
	    fscanf(fichier1,"%d %d %d \n",&element1[i][0],&element1[i][1],&element1[i][2]);

	    
	  }
	  
	  else{
	    fscanf(fichier1,"%d %d %d %d\n",&element1[i][0],&element1[i][1],&element1[i][2],&element1[i][3]);
	  }
	    
	  for(k=0;k<3;k++){
	    R1[i][k]=node[element1[i][0]-1][k];
	    vec11[i][k]=node[element1[i][1]-1][k]-R1[i][k];
	    vec21[i][k]=node[element1[i][2]-1][k]-R1[i][k];
	   
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
	  fscanf(fichier1,"%d",&nothing);
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
	    fscanf(fichier1,"%d",&nothing);
	  }
	  else{
	    fscanf(fichier1,"%d\n",&nothing);
	  }	  
	}
	   	
      }
      // printf(" element %d: %lf %lf %lf\n",i,element[i]);
      
    }

  
  
  if(test_elements1!=n_elements1-test_elements2){
    
    printf("ERROR!, the number of physical surfaces is not the same that announced"); 
    return 1;
  }
  
  n_elements=test_elements1;
  
  fclose(fichier1);
  
  
  
  
  
  
  

  
  
  
  
  
  
  
  
  
  l=0;
  
  
  element = (int**)calloc( n_elements , sizeof(int*));
  type_of = (int*)calloc( n_elements,sizeof(int));
  norm = (double**)calloc( n_elements , sizeof(double*));
  vec1 = (double**)calloc( n_elements , sizeof(double*));
  vec2 = (double**)calloc( n_elements , sizeof(double*));
  R = (double**)calloc( n_elements , sizeof(double*));
  surface = (double*)calloc( n_elements,sizeof(double));
  
   
  
  
  fprintf(fichier2,"%d\n",n_elements);
  
  
  
  for(i=0 ; i<n_elements1 ; i++){
    
    if(type_of1[i]==2 || type_of1[i]==3){

     
      type_of[l]=type_of1[i];
      surface[l]=surface1[i];
 
      	element[l] = (int*) calloc (type_of[l]+1, sizeof(int));
	norm[l] = (double*) calloc (3, sizeof(double));
	vec1[l] = (double*) calloc (3, sizeof(double));
	vec2[l] = (double*) calloc (3, sizeof(double));
	R[l] = (double*) calloc (3, sizeof(double));
	
	

	
	
	for(k=0 ; k<type_of[l]+1 ; k++){
	  
	  
	  element[l][k]=element1[i][k];
	  
	}



	
	for(k=0 ; k<3 ; k++){
	  
	  
	  norm[l][k]=norm1[i][k];
	  vec1[l][k]=vec11[i][k];
	  vec2[l][k]=vec21[i][k];
	  R[l][k]=R1[i][k];
	  
	  
	}

	fprintf(fichier2,"%d %d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",l+1,type_of[l],R[l][0],R[l][1],R[l][2],vec1[l][0],vec1[l][1],vec1[l][2],vec2[l][0],vec2[l][1],vec2[l][2],norm[l][0],norm[l][1],norm[l][2],surface[l]);
      l++;
    }
    
    
    
  }
  
  
  free(element1);
  free(type_of1);
  free(norm1);
  free(vec11);
  free(vec21);
  free(R1);
  free(surface1);
  
  
  
  fclose(fichier2);
  
  return 0;
}

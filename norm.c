#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include "header_main.h"


double* vecprod(double vec1[3],double vec2[3]){
  
  double *prod;
   prod = (double*)calloc( 3,sizeof(double)); 
  if((vec1[0]-vec2[0])==0 && (vec1[1]-vec2[1])==0 && (vec2[2]-vec2[2])==0){

prod[0]=0;
  prod[1]=0;
  prod[2]=0;

  }
  else{
  
 
  prod[0]=vec1[1]*vec2[2]-vec1[2]*vec2[1];
  prod[1]=vec1[2]*vec2[0]-vec2[2]*vec1[0];
  prod[2]=vec1[0]*vec2[1]-vec2[0]*vec1[1];

  }
  
  return prod;
}

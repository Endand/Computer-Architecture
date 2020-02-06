#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
int row1, row2, col1, col2,i,j,k;

FILE* file;

if((file = fopen(argv[1],"r"))==NULL){
  printf("error");
  exit(0);
}
fscanf(file,"%d\t%d\n",&row1,&col1);

int** arr1=(int**)malloc(sizeof(int*)*row1);
for(k=0;k<row1;k++){
  arr1[k]=(int*) malloc(sizeof(int)*col1);
}

//printf("\nEnter elements of matrix 1:\n");
for(i=0; i<row1; i++){
  for(j=0; j<col1; j++)
  {
  arr1[i][j]=0;
  }
}
for(i=0; i<row1; i++){
  for(j=0; j<col1; j++)
  {
  fscanf(file,"%d\t",&arr1[i][j]);
  }
}


// Storing elements of second matrix.

fscanf(file,"%d\t%d\n",&row2,&col2);//read second dimensions



if(col1!=row2){ //check if it's possible
  printf("bad-matrices");
  for(k=0;k<row1;k++){//free arr1
    free(arr1[k]);
  }
  free(arr1);
fclose(file);
  return 0;
}


int** arr2=(int**)malloc(sizeof(int*)*row2);
for(k=0;k<row2;k++){
  arr2[k]=(int*) malloc(sizeof(int)*col2);
}

for(i=0; i<row2; i++){
  for(j=0; j<col2; j++)
  {
    arr2[i][j]=0;
  }
}
for(i=0; i<row2; i++){
  for(j=0; j<col2; j++)
  {
    fscanf(file,"%d",&arr2[i][j]);
  }
}

// Initializing all elements of result matrix to 0
//int result[row1][col2];
int** result=(int**)malloc(sizeof(int*)*row1);
for(k=0;k<row1;k++){
  result[k]=(int*) malloc(sizeof(int)*col2);
}

for(i=0; i<row1; i++){
  for(j=0; j<col2; j++)
  {
      result[i][j] = 0;

  }
}

//actual multiplication goes here

for(i=0;i<row1;i++){
  for(j=0;j<col2;j++){
    for(k=0;k<col1;k++){
      result[i][j]+=arr1[i][k]*arr2[k][j];
    }
  }
}

for(i=0; i<row1; i++){
  for(j=0; j<col2; j++)
  {
      printf("%d\t",result[i][j]);

  }
  printf("\n");
}





//freeEverything after

for(k=0;k<row1;k++){//free arr1
  free(arr1[k]);
}
free(arr1);

for(k=0;k<row2;k++){ //free arr2
  free(arr2[k]);
}
free(arr2);

for(k=0;k<row1;k++){ //free result
  free(result[k]);
}
free(result);





fclose(file);//end of program
return 0;
}

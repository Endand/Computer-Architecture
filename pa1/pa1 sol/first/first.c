#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
/*read in file*/
  FILE* file=fopen(argv[1],"r");
if(file==NULL){return 1;}
int size;
fscanf(file,"%d",&size);
if(size==0){return 1;}
int array[size];
int a;
for(a=0;a<size;a++){fscanf(file,"%d",&array[a]);}//make initial array

int i,j,temp;
for(i=1;i<size;i++){
  for (j = i-1; j>=0; j--) {

 if(abs(array[i]%2)==0 &&abs(array[j]%2)==1){ //if key is even and compare is odd, swap
      temp=array[i];
      array[i]=array[j];
      array[j]=temp;
	i--;
    }
    else if(abs(array[i]%2)==1 && abs(array[j]%2)==1){ //if key is odd and compare is odd, compare
      if(array[i]>array[j]){
	temp=array[i];
        array[i]=array[j];
        array[j]=temp;
	i--;
      }
	else continue;
    }
    else if(abs(array[i]%2)==0 && abs(array[j]%2)==0){ //if key is even and compare is even, compare
      if(array[i]<array[j]){
        temp=array[i];
        array[i]=array[j];
        array[j]=temp;
	i--;
      }
	else continue;
    }
    else if(abs(array[i]%2)==1 && abs(array[j]%2)==0){ //if key is odd and compare is even, stay
      continue;
    }
  }
}

for(a=0;a<size;a++){
printf("%d\t",array[a]);
}
fclose(file);
return 0;
}

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

int get(unsigned short x, int n){
x= ((1<<n)&x) >>n;
return x;
}

int main(int argc, char* argv[]){
//Read in the number and store it as an array
unsigned short num= (unsigned short)atoi(argv[1]);
if(!(num>=0&&num<=65535)){
  printf("error");
  exit(0);}

int i,comp1,comp2;
int isPal=1;
for(i=0;i<8;i++){
  comp1=get(num,i);
  comp2=get(num,16-i-1);
  // printf("comp1:%d, compt2:%d\n",comp1,comp2);
  if(comp1!=comp2){
    isPal=0;
    break;
  }
}
if(isPal==1){
  printf("Is-Palindrome\n");
}
else if(isPal==0){
  printf("Not-Palindrome\n");
}







return 0;
}

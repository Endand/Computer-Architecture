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
int size= (int) log2(num)+1;
int scount=0;
int pcount=0;
int n;
if(num==0){
  printf("Even-Parity\t");
  printf("%d\n",0);
  exit(0);
}
for(n=0;n<size;n++){
  if(get(num,n)==1){
    scount++;
    if(get(num,n+1)==1){
      scount++;
      pcount++;
      n++;
    }
  }
}


if(scount%2==0){
  printf("Even-Parity\t");
}
else if(scount%2==1){
  printf("Odd-Parity\t");
}
printf("%d\n",pcount);


return 0;
}

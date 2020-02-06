#include<stdlib.h>
#include<stdio.h>
#include<string.h>

unsigned short set(unsigned short x, int n, int v){
unsigned short find=1;
if(v==1){
x=(find<<n)|x;
}
if(v==0){
  x= x & ~(find<<n);
}
return x;
}

unsigned short comp(unsigned short x, int n){
  unsigned short find=1;
  x=(find<<n)^x;
  return x;
}

int get(unsigned short x, int n){
x= ((1<<n)&x) >>n;
return x;
}

int main(int argc, char* argv[]){
  FILE* file;
  if((file=fopen(argv[1],"r"))==NULL){
    printf("error");
    exit(0);
  }
  unsigned short num;
  fscanf(file,"%hu\n",&num);

  int first=0;
  int second=0;
  char cmd[5]="";
  int newnum=0;
  while(!feof(file)){
    fscanf(file,"%s\t%d\t%d\n",cmd,&first,&second);
    if(strcmp(cmd,"")==0){break;} //see if there is any commands
    //printf("cmd:%s\tfirst:%d\tsecond:%d\n",cmd,first,second); //test line
  if(strcmp(cmd,"set")==0){
  num=set(num,first,second);
  printf("%hu\n",num);

  }
  else if(strcmp(cmd,"comp")==0){

  num= comp(num,first);
  printf("%hu\n",num);
  }

  else if(strcmp(cmd,"get")==0){
  newnum= get(num,first);
printf("%d\n",newnum);
}
  }//while


fclose(file);
return 0;
} //main

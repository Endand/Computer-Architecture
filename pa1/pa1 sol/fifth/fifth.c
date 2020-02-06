#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
char* str;
int i;
for(i=1;i<argc;i++){
  str=argv[i];
  int size;
  size=strlen(str);
  int j;
  for(j=0;j<size;j++){
    if(str[j]=='a'||str[j]=='e'||str[j]=='i'||str[j]=='u'||str[j]=='o'||str[j]=='A'||str[j]=='E'||str[j]=='U'||str[j]=='I'||str[j]=='O'){
      printf("%c",str[j]);
    }
  }
}
return 0;
}

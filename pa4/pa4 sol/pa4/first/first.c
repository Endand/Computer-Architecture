#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

typedef struct node
{

    char name[20];
    int data;
    struct node *next;
}Node;

int search(char* id, char** arr, int size){
int i;
for(i=0;i<size;i++){
    if(strcmp(id,arr[i])==0){
      return i;
    }
  }
  return 0;
}
void initialize(FILE* file){ //get rid of first two lines
  char* dum=malloc(10*sizeof(char));
  int size,i;
  fscanf(file,"%s",dum);
  fscanf(file,"%d",&size);
  for(i=0;i<size;i++){
    fscanf(file,"%s",dum);
  }
  fscanf(file,"%s",dum);
  fscanf(file,"%d",&size);
  for(i=0;i<size;i++){
    fscanf(file,"%s",dum);
  }
  free(dum);
}

Node* insert(struct node* front, char* name, int data)
{

    struct node* nnode = (struct node*) malloc(sizeof(struct node));
    strcpy(nnode->name,name);
    nnode->data  = data;
    nnode->next = front;
    front = nnode;
    return front;
}
int searchMod(struct node* front, char* name, int newdata){
  Node* ptr=front;

  while(ptr!=NULL){
    if(strcmp(ptr->name,name)==0){
      ptr->data=newdata;
      return 1;
    }
    ptr=ptr->next;
  }
  return 0;
}

int searchdata(struct node* front, char* name){
  Node* ptr=front;
  while(ptr!=NULL){

    if(strcmp(ptr->name,name)==0){
      return ptr->data;
    }
    ptr=ptr->next;
  }
  return -2;
}

void freeLL(Node* front){
  Node* ptr;
  if(front==NULL){
    return;
  }
  while(front->next!=NULL){
    ptr=front;
    front=front->next;
    free(ptr);
  }

}

int main(int argc, char* argv[]){

  FILE* file=fopen(argv[1],"r");
  if(file==NULL){return 1;}

  //read in first line
  int insize;
  char* dummy=malloc(10*sizeof(char));
  fscanf(file,"%s",dummy);
  fscanf(file,"%d",&insize);
  int i,j;
  char** inarr =(char**)malloc(sizeof(char*)*insize);
  for(i=0;i<insize;i++){
    inarr[i]=(char*)malloc(sizeof(char)*200);
  }
  int* inval= (int*)malloc(sizeof(int)*insize);
  for(i=0;i<insize;i++){
    fscanf(file,"%s",inarr[i]);
    inval[i]=0;
  }

//create truth table
int powsize=1<<insize;
int** table= (int**)malloc(sizeof(int*)*(powsize));
for(i=0;i<powsize;i++){
table[i]= (int*)malloc(sizeof(int)*insize);
}
for(i=0;i<insize;i++){
int stride= 1<<(insize-i-1);
for(j=0; j<powsize;j++){
int quotient=j/stride;
  if(quotient%2==0){
    table[j][i]=0;
  }
  if(quotient%2!=0){
    table[j][i]=1;
  }
}//inner for loop
}//outer for loop

//print table
/*
for(i=0;i<powsize;i++){
for(j=0; j<insize;j++){
printf("%d\t",table[i][j]);
}//inner for loop
printf("\n");
}//outer for loop
*/

  //read in second line
  int outsize;
  fscanf(file,"%s",dummy);
  fscanf(file,"%d",&outsize);
  char** outarr =(char**)malloc(sizeof(char*)*outsize);
  for(i=0;i<outsize;i++){
    outarr[i]=(char*)malloc(sizeof(char)*200);
  }
  int* outval= (int*)malloc(sizeof(int)*outsize);
  for(i=0;i<outsize;i++){
    fscanf(file,"%s",outarr[i]);
    outval[i]=0;
  }

  char* op=malloc(4*sizeof(char));
  char* first=malloc(200*sizeof(char));
  char* second=malloc(200*sizeof(char));
  char* dest=malloc(200*sizeof(char));
  Node* front=(struct node*) malloc(sizeof(struct node));
  front->next=NULL;
  front->data=0;

  //initialize the INPUTVAR
  for(i=0;i<powsize;i++){ //repeat for every truth values

    for(j=0; j<insize;j++){ //update inval
      inval[j]=table[i][j];
    }

    //do the op

    int exists;
    int fval;
    int sval;
    int index;
    fscanf(file,"%s",op);
    while(!feof(file)){ //to go through every op

    if(strcmp("NOT",op)==0){
      fscanf(file,"%s",first);
      fscanf(file,"%s",dest);
      if(isupper(first[0])){
       index=search(first,inarr,insize);
      fval=inval[index];
      }
      if(islower(first[0])){
        fval=searchdata(front,first);
      }
      if(isupper(dest[0])){ //OUTVAR
      index=search(dest,outarr,outsize);
      outval[index]=!fval;
      }
      if(islower(dest[0])){ //temp
        exists= searchMod(front, dest, !fval);
        if(exists==0){front=insert(front, dest,!fval);
        }
      }
    }

    if(strcmp("AND",op)==0){
      fscanf(file,"%s",first);
      fscanf(file,"%s",second);
      fscanf(file,"%s",dest);
      if(isupper(first[0])){
      index=search(first,inarr,insize);
      fval=inval[index];
      //printf("fval:%d\t", fval);
      }
      if(isupper(second[0])){
      index=search(second,inarr,insize);
      sval=inval[index];
      //printf("sval:%d\t", sval);
      }
      if(islower(first[0])){
        fval=searchdata(front,first);
        }
      if(islower(second[0])){
        sval=searchdata(front,second);
      }
        if(isupper(dest[0])){ //OUTVAR
        index=search(dest,outarr,outsize);
        outval[index]=fval&&sval;
        }
        if(islower(dest[0])){ //temp
          exists= searchMod(front, dest, fval&&sval);
          if(exists==0){
            front=insert(front, dest,fval&&sval);
          }
        }
    }

    if(strcmp("OR",op)==0){
    fscanf(file,"%s",first);
    fscanf(file,"%s",second);
    fscanf(file,"%s",dest);
    if(isupper(first[0])){
    index=search(first,inarr,insize);
    fval=inval[index];
    }
    if(isupper(second[0])){
    index=search(second,inarr,insize);
    sval=inval[index];
    }
    if(islower(first[0])){
      fval=searchdata(front,first);
    }
    if(islower(second[0])){
      sval=searchdata(front,second);
    }
    if(isupper(dest[0])){ //OUTVAR
    index=search(dest,outarr,outsize);
    outval[index]=fval||sval;
    }
    if(islower(dest[0])){ //temp
      exists= searchMod(front, dest, fval||sval);
      if(exists==0){front=insert(front, dest,fval||sval);}
    }
    }

    if(strcmp("NAND",op)==0){
      fscanf(file,"%s",first);
      fscanf(file,"%s",second);
      fscanf(file,"%s",dest);
      if(isupper(first[0])){
      index=search(first,inarr,insize);
      fval=inval[index];
      }
      if(isupper(second[0])){
      index=search(second,inarr,insize);
      sval=inval[index];
      }
      if(islower(first[0])){
        fval=searchdata(front,first);
      }
      if(islower(second[0])){
        sval=searchdata(front,second);
      }
      if(isupper(dest[0])){ //OUTVAR
      index=search(dest,outarr,outsize);
      outval[index]=!(fval&&sval);
      }
      if(islower(dest[0])){ //temp
        exists= searchMod(front, dest, !(fval&&sval));
        if(exists==0){front=insert(front, dest,!(fval&&sval));}
      }
    }
    if(strcmp("NOR",op)==0){
      fscanf(file,"%s",first);
      fscanf(file,"%s",second);
      fscanf(file,"%s",dest);
      if(isupper(first[0])){
      index=search(first,inarr,insize);
      fval=inval[index];
      }
      if(isupper(second[0])){
      index=search(second,inarr,insize);
      sval=inval[index];
      }
      if(islower(first[0])){
        fval=searchdata(front,first);
      }
      if(islower(second[0])){
        sval=searchdata(front,second);
      }
      if(isupper(dest[0])){ //OUTVAR
      index=search(dest,outarr,outsize);
      outval[index]=!(fval||sval);
      }
      if(islower(dest[0])){ //temp
        exists= searchMod(front, dest, !(fval||sval));
        if(exists==0){front=insert(front, dest,!(fval||sval));}
      }
    }
    if(strcmp("XOR",op)==0){
    fscanf(file,"%s",first);
    fscanf(file,"%s",second);
    fscanf(file,"%s",dest);
    if(isupper(first[0])){
    index=search(first,inarr,insize);
    fval=inval[index];
    }
    if(isupper(second[0])){
    index=search(second,inarr,insize);
    sval=inval[index];
    }
    if(islower(first[0])){
      fval=searchdata(front,first);
    }
    if(islower(second[0])){
      sval=searchdata(front,second);
    }
    if(isupper(dest[0])){ //OUTVAR
    index=search(dest,outarr,outsize);
    outval[index]=fval^sval;
    }
    if(islower(dest[0])){ //temp
      exists= searchMod(front, dest, fval^sval);
      if(exists==0){front=insert(front, dest,fval^sval);}
    }
    }

      fscanf(file,"%s",op);
      if(feof(file)){break;}

    }//while
    int k;
    //print result
    for(k=0; k<insize;k++){
      printf("%d ", inval[k]);
    }
    for(k=0; k<outsize;k++){
      printf("%d ", outval[k]);
    }
    printf("\n");
    fclose(file);
    file=fopen(argv[1],"r");
    initialize(file);
  //  freeLL(front);
  } //for

  free(front);
  free(op);
  free(first);
  free(second);
  free(dest);


free(dummy);
for(i=0;i<outsize;i++){
free(outarr[i]);
}
free(outarr);
free(outval);

for(i=0;i<insize;i++){
free(inarr[i]);
}
free(inarr);
free(inval);

for(i=0;i<powsize;i++){
free(table[i]);
}
free(table);
fclose(file);

}//main

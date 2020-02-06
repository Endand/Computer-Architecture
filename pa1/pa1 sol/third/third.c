#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int val;
    struct node *next;
}Node;

void hprint(Node* hashtable[]){
  int i;
  for(i=0;i<10000;i++){
    Node* ptr =hashtable[i];
    while(ptr!=NULL){
      printf("%d\n", ptr->val);
      ptr=ptr->next;
    }
  }

}

Node* makeNode(int data){
  Node* newNode=NULL; //create a newNode to insert
  newNode =(struct node*)malloc(sizeof(struct node));
  newNode->val=data;
  newNode->next=NULL;
  return newNode;
}
int insert(Node* hashtable[], Node* node){

  int counter=0;
  int index=node->val%10000; //key function
  if(index<0){//if it's a negative number
    index=index+10000;
  }
  if(hashtable[index]==NULL){


    hashtable[index]=node;} //if index is empty then add the first node
  else{//if there is a collision;
    Node* ptr;
    int flag=0;
    ptr= hashtable[index];
    Node* prev=NULL;
    while(ptr!= NULL){

      if(ptr-> val!=node->val){
        prev=ptr;
        ptr=ptr->next;

      }
      else{
        flag=1;
        free(node);
        break;}

    }

  if(flag==0){prev->next=node;}

    counter++;
  }
  return counter;
}

int search(Node* hashtable[], int data){
Node* ptr;
int counter=0;
int index;
index=data%10000;
if(index<0){//if it's a negative number
  index=index+10000;
}
ptr=hashtable[index];
while(ptr!=NULL){
  if(ptr==NULL){return 0;}
  if(ptr->val==data){
    counter++;
    break;
  }
  else{ptr=ptr->next;}
}//while

return counter;
}


void freeHT(Node* indexptr){
Node* ptrptr;
while(indexptr!=NULL){
  ptrptr=indexptr;
  indexptr=indexptr->next;
  free(ptrptr);
}
}



Node* hashtable[10000]; //create hashtable

int main(int argc, char* argv[]){

    FILE* file;

    if((file = fopen(argv[1],"r"))==NULL){
      printf("error");
      exit(0);
    }


    int data;
    char c;
    int colcounter=0;
    int scounter=0;
    while(!feof(file)){
      fscanf(file,"%c\t%d\n",&c,&data);
      if(c=='i'){//insert
        Node* newNode=makeNode(data);// create a Node
        colcounter+=insert(hashtable,newNode);
      }
      if(c=='s'){//search

        scounter+=search(hashtable, data);
      }
    }
    printf("%d\n",colcounter);
    printf("%d",scounter);


  //free hashtable
  int index;
  Node* indexptr;
  for(index=0;index<10000;index++){
    indexptr=hashtable[index];
    freeHT(indexptr);
  }
//hprint(hashtable);
fclose(file);
return 0;
}//main

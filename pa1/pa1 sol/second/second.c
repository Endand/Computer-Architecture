#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int val;
    struct node *next;
}Node;

void printLL(Node* front){
  front=front->next;
  while(front!=NULL){
    printf("current val is: %d\n", front->val);
    front=front->next;
  }
}


void freeLL(Node* front){
  Node* ptr;
  if(front==NULL){
    free(front);
  }
  while(front!=NULL){
    ptr=front;
    front=front->next;
    free(ptr);
  }

}

int main(int argc, char* argv[]){

    FILE* file;

    if((file = fopen(argv[1],"r"))==NULL){
      printf("error");
      exit(0);
    }


    Node* front = NULL; //creat front node
    front = (Node*)malloc(sizeof(struct node));
    if (front == NULL) { //to test if malloc worked
        return 1;
    }
    front->val = -1;
    front->next = NULL;

    int data;
    char c;
    while(!feof(file)){
      fscanf(file,"%c\t%d\n",&c,&data);

      if(c=='i'){//insert
        Node* newNode=NULL; //create a newNode to insert
        newNode =malloc(sizeof( struct node));
        newNode->val=data;
        newNode->next=NULL;

        //add the newNode
        if(front->next==NULL){ //if it's the first Node
          front->next= newNode;
        }
        else{
          Node* prev;
          Node*ptr;
          prev=front;
          ptr=front->next;
          while(ptr!=NULL){
            if(ptr->val >= newNode->val){
              prev->next= newNode;
              newNode->next=ptr;
              break;
            }
            prev=ptr;
            ptr=ptr->next;
          }
          prev->next=newNode;
        }
      }


      if(c=='d'){//delete

        Node* prev;
        Node*ptr;

        prev=front;
        ptr=front->next;
        while(ptr!=NULL){
          if(ptr->val==data){
            prev->next= ptr->next;
            ptr->next=NULL;
            free(ptr);
            break;
          }
          prev=ptr;
          ptr=ptr->next;
        }
      }
    }//while

  //  printLL(front);
if(front->next==NULL){
  free(front);
  fclose(file);
  printf("%d",0);
  return 0;
}
  //get rid of dummy node
    Node* newfront;
    newfront=front->next;
    free(front);

    //count how many items are in the LL
    Node* current = newfront;

      int counter=0;
      while (current != NULL) {

          current = current->next;
          counter++;
      }

//print items in LL
      current=newfront;
      printf("%d\n",counter);
      if(counter==0){
        return 0;
      }

      int repeat;
      printf("%d\t",current->val);
      repeat= current->val;
      current = current->next;
    while (current != NULL) {
      if(repeat!=current->val){
        printf("%d\t",current->val);
      }
        repeat= current->val;
        current = current->next;
      }


      freeLL(newfront);
    //free(front);
fclose(file);
return 0;
}//main

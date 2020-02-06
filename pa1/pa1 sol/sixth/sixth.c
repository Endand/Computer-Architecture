#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int val;
    struct node *left;
    struct node* right;
}Node;

Node* makeNode(int data){
  Node* newNode=NULL; //create a newNode to insert
  newNode =(struct node*)malloc(sizeof(struct node));
  newNode->val=data;
  newNode->left=NULL;
  newNode->right=NULL;
  return newNode;
}

void traverse(Node* root){
  if(root!=NULL){
    traverse(root->left);
    printf("%d\t", root->val);
    traverse(root->right);
  }
}

void freeTree(Node* root){
  if(root==NULL){return;}
  freeTree(root->left);
  freeTree(root->right);
  free(root);
  return;
}

Node* insert(Node* root, Node* newNode){
  if(root==NULL){return newNode;}
  if(root->val>newNode->val){
    root->left= insert(root->left, newNode);
  }
  else if(root->val<newNode->val){
    root->right= insert(root->right, newNode);
  }
  else{//if duplicate
    free(newNode);
  }
  return root;
}

int main(int argc, char* argv[]){

    FILE* file;

    if((file = fopen(argv[1],"r"))==NULL){
      printf("error");
      exit(0);
    }

  else{
    int data;
    char c;
    Node* root=NULL;
    while(!feof(file)){
      fscanf(file,"%c\t%d\n",&c,&data);
      if(c=='i'){//insert
        Node* newNode= makeNode(data);
        root = insert(root,newNode);
      }

    }
    traverse(root);
    freeTree(root);
  }
  fclose(file);
    return 0;
  }//main

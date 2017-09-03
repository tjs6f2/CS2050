/*Thomas Schultz
 * CS2050 LAB7
 * TJS6F2
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct bt_ {
    int value;
    struct bt_ *right;
    struct bt_ *left;
}BST;

void printTree(BST *root);
void displayBST(BST *root,int depth);
void padding(char toPrint, int numTimes);
BST *insert(BST *root, int value);
int search(BST *root, int num);
BST *delete(BST *root, int value);
BST *findMin(BST *root);

int main(int argc, char *argv[]) {

    if(argc!=2) {//checks to make sure correct number of arguments in command line
        printf("Enter correct number of arguments\n");
        exit(0);
    }

    char *input=argv[1];
    FILE *fp=fopen(input,"r");

    if(fp==NULL) {
        printf("Unable to open file\n");
        exit(0);
    }

    BST *root=NULL;

    while(!feof(fp)) {//runs through file until it reaches end.
        int value;
        fscanf(fp,"%d",&value);//scans each #
        root=insert(root,value);//puts it in a tree
    }

    printTree(root);

    int num;

    printf("\nEnter a number to search for a tree: ");
    scanf("%d",&num);

    int results=search(root,num);

    if(results==0) {
        printf("\n%d not found\n",num);
    }
    else {
        printf("\n%d was found\n",num);
    }

    int num2;

    printf("\nEnter a number to remove from the tree: ");
    scanf("%d",&num2);

    root=delete(root,num2);

    printTree(root);

    fclose(fp);

    return 0;
}

void padding(char toPrint, int numTimes) {//function adds spacing 

    int i;

    for(i=0;i<numTimes;i++)
        printf("%c",toPrint);

}

void displayBST(BST *root,int depth) {//fucntion formats and prints binary tree

    if(root==NULL) {

        padding(' ',depth);
        printf("-\n");
        return;
    }

    displayBST(root->left,depth+4);
    padding(' ',depth);
    printf("%d\n",root->value);
    displayBST(root->right,depth+4);

}

void printTree(BST *root) {//fucntion call to print tree

    displayBST(root,0);

}

BST *insert(BST *root, int value) {//function adds numbers from file into a binary tree

    BST *temp=NULL;

    if(root==NULL) {//if tree is empty add a new node

        temp=(BST*)malloc(sizeof(BST));
        temp->value=value;
        temp->left=NULL;
        temp->right=NULL;

        return temp;
    }

    if(value<root->value)//if tree is filled start moving down the tree
        root->left=insert(root->left,value);
    else if(value>root->value) 
        root->right=insert(root->right,value);

    return root;
}

int search(BST *root,int num) {

    if(root==NULL) {
        return 0;
    }

    return 1;

}

BST *delete(BST *root, int value) {

    if(root==NULL) {//base case
        return NULL;
    }

    if(value < root->value) {//if value is smaller than root move to leftside of tree

        root->left=delete(root->left,value);
    }
    else if(value>root->value) {//greater than root
        root->right=delete(root->right,value);
    }
    else {//node with 0 or 1 child
        if(root->left==NULL && root->right == NULL) {
            free(root);
            root=NULL;
        }
        else if(root->left==NULL) {
            BST *temp=root;
            root=root->right;
            free(temp);
        }
        else if(root->right==NULL) {
            BST *temp=root;
            root=root->left;
            free(temp);
        }

        else {//node with 2 children.
            BST *temp=findMin(root->right);
            root->value=temp->value;
            root->right=delete(root->right,temp->value);
        }
    }
    return root;
}

BST *findMin(BST *root) {

    BST *current=root;

    while(current->left !=NULL) {//searches left tree for min
        current=current->left;
    }
    return current;
}


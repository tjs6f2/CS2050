/*Thomas Schultz
 * CS2050 LAB4
 * TJS6F2
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct node_{
    int data;
    struct node_ *next;
}node;

void print_list(node *list);
void free_list(node *list);
node *create_list(char *file);
node *insert_at_head(node *list, int data);

int main(int argc, char *argv[]) {

    if(argc!=2) {//error checks for input file 
        printf("Incorrect number of arguments\n");
        exit(0);
    }

    node *list=NULL;

    char *input=argv[1];

    list=create_list(input);//creates and stores list in variable

    print_list(list);//function call to print linked list

    free_list(list);//function call to free allocated memory

    return 0;
}

node* insert_at_head(node *list, int data) {

    node *newNode=(node*)malloc(sizeof(node));//allocated memory for newNode

    newNode->data=data;//sets the node to the data

    newNode->next=list;//assigns the "next" pointer of the current node to the head of the linked list

    list=newNode;//assigns newNode to list

    return list;//returns lists
}


node *create_list(char *file) {//creates a linked list from numbers in a file

    FILE *fp=fopen(file,"r");

    if(fp==NULL) {//if file is unable to open print error
        printf("\nError cannot open file\n");
        exit(0);
    }

    int data;
    node *list=NULL;

    while(!feof(fp)) {//starts reading data from file
        fscanf(fp,"%d", &data);
        list=insert_at_head(list,data);
    }

    fclose(fp);

    return list;
}

void print_list(node *list) {//function prints out linked list

    node *temp;

    temp=list;

    printf("\n");

    while(temp!=NULL) {//runs through list
        printf("%d->",temp->data);
        temp=temp->next;//moves to next node
    }
    printf("NULL\n");
    printf("\n");
}

void free_list(node *list) {//function frees all allocated memory to prevent memeory leaks

    node *head, *temp;

    head=list;
    temp=head;

    while(head!=NULL) {
        head=temp->next;

        free(temp);

        temp=head;
    }
}


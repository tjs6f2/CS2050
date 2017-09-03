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

    node *list;

    char *input=argv[1];

    list=create_list(input);

    print_list(list);

    free_list(list);

    return 0;
}

node *create_list(char *file) {

    int num;
    FILE *fp;

    node *head, *newNode, *temp;

    head=NULL;

    fp=fopen(file,"r");

    while(!feof(fp)) {
        fscanf(fp,"%d", &num);

        if(head==NULL) {

            head=(node*)malloc(sizeof(node));

            head->data=num;

            head->next=NULL;
        }
        else {

            newNode=(node*)malloc(sizeof(node));

            newNode->data=num;
            newNode->next=NULL;

            temp=head;

            while(temp->next!=NULL) {
                temp=temp->next;
            }
            temp->next=newNode;
        }
    }

    fclose(fp);

    return head;
}

void print_list(node *list) {

    node *temp;

    temp=list;

    printf("\n");

    while(temp!=NULL) {
        printf("%d->",temp->data);
        temp=temp->next;
    }
    printf("NULL\n");
    printf("\n");
}

void free_list(node *list) {

    node *head, *temp;

    head=list;
    temp=head;

    while(head!=NULL) {
        head=temp->next;

        free(temp);

        temp=head;
    }
}


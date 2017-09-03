/*Thomas Schultz
 * CS2050 HW2
 * TJS6F2
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_MODEL 25
#define MAX_LINE 50

typedef struct Car {

    char *model;
    char *color;
    int year;
    struct Car *next;
} car;

car *readFile(FILE *);
car *insertInSortedOrder(car *, char *, char *, int);
car *createCar(char *, char *, int);
char *verifyColor(FILE *, char *);
int updateCar(car *, char *, int);
car *removeCar(car *, char *);
void printCars(car *);
void freeMem(car *);

int main(int argc, char *argv[]) {

    if(argc!=3) {
        printf("Error wrong number of command line arguments");
    }

    char *input=argv[1];
    char *input2=argv[2];

    FILE *file=fopen(input,"r");
    FILE *file2=fopen(input2,"r");

    if(file==NULL || file2==NULL) {//error checks to see if files can be opened
        printf("Unable to open file\n");
        exit(0);
    }

    car *head=NULL;

    head=readFile(file);

    printCars(head);

    char model[MAX_MODEL],color[MAX_MODEL],select;
    int year;

    printf("What would you like to do? A) Add a car C) Change a car D) Delete a car Q) Quit ");
    scanf(" %c",&select);

    while(select!='Q') {//program loops until user exits program

        if(select=='A') {//selection lets you add a new car into inventory

            printf("\nEnter a model name to add: ");
            getchar();//takes in leftover new line character 
            scanf("%[^\t\n]s",model);//allows user to until mutlpile strings until new line 

            printf("Enter a model year: ");
            scanf("%d",&year);

            while(year>2017) {//checks to see if user entered valid year
                printf("\nInvalid year! The model hasn't been released yet!\n");
                printf("Enter a model year: ");
                scanf("%d",&year);
            }

            printf("Enter a color: ");
            getchar();
            scanf("%[^\t\n]s",color);

            head=insertInSortedOrder(head,model,color,year);

            printCars(head);
        }

        else if(select=='C') {//selection allows user to change a car in inventory

            printf("\nEnter a model name to change: ");
            getchar();
            scanf("%[^\t\n]s",model);

            while(updateCar(head,model,year)==-1) {//error checks to see if proper model name was entered
                printf("\nCar not found please try again\n");
                printf("Enter a model name to change: ");
                getchar();
                scanf("%[^\t\n]s",model);
            }

            printf("Enter the new model year: ");
            scanf("%d",&year);

            while(year>2017){//error checks to see if car is newer than 2017
                printf("Invalid year! The model hasn't been released yet!\n");
                printf("Enter the new model year: ");
                scanf("%d",&year);
            }

            updateCar(head,model,year);

            printCars(head);
        }

        else if(select=='D') {//selection deletes a car 
            printf("\nEnter a model name to delete: ");
            getchar();
            scanf("%[^\t\n]s",model);

            removeCar(head,model);

            printCars(head);
        }

        else if(select=='Q') {//selection frees up memory, closes file and exits program
            printf("Exiting program...\n");
            exit(0);
        }

        else {
            printf("\nWrong choice. Try again\n\n");
        }

        printf("What would you like to do? A) Add a car C) Change a car D) Delete a car Q) Quit ");
        scanf(" %c",&select);
    }

    freeMem(head);//frees all memory in linked list
    fclose(file);
    fclose(file2);

    return 0;
}

void printCars(car *head) {/*prints linked list*/

    car *p=head;

    printf("\nThe list of cars in inventory are:\n\n");

    while(p!=NULL) {//loop runs until reaches null printing linked list in proper format
        printf("%-5d %-20s %s\n", p->year, p->model,p->color);
        p=p->next;
    }
    printf("\n");
}

car* readFile(FILE *file){//function reads data from file and puts it in linked list

    char line[MAX_LINE],model[MAX_MODEL],color[MAX_MODEL],delimeter[2]="|";
    int year;
    char *token;
    car *head=NULL;

    while(fgets(line,MAX_LINE,file)!=NULL){//reads file until reaches the end of file

        token=strtok(line,delimeter);
        strcpy(model,token);//loads info into model

        token=strtok(NULL,delimeter);
        strcpy(color,token);//copies info into color 

        token=strtok(NULL,delimeter);
        year=atoi(token);//changes string to # and loads to year

        head=insertInSortedOrder(head,model,color,year);//adds to linked list
    }
    return head;
}

car *insertInSortedOrder(car *head, char *model, char *color, int year){/*turns info from file into a linked list*/

    car *newcar=createCar(model,color,year);
    car *temp,*p;

    if(head==NULL||strcmp(model,head->model)<0){
        newcar->next=head;
        head=newcar;

        return head;
    }

    p=head;

    while((p->next!=NULL)&&(strcmp(p->next->model,model)<0)){
        p=p->next;
    }

    temp=p->next;
    p->next=newcar;
    newcar->next=temp;

    return head;
}

car *createCar(char *model, char *color,int year){/*creates cars and memory for the linked list*/

    car *temp;

    temp=(car *)malloc(sizeof(car));

    temp->model=strdup(model);
    temp->color=strdup(color);
    temp->year=year;
    temp->next=NULL;

    return temp;
}

/*char *verifyColor(FILE *file2, char *color) {

  char line[MAX_LINE],colors[MAX_MODEL][MAX_MODEL];
  int i,j=0;

  while(fgets(line,MAX_LINE,file2)!=NULL) {
  if(line[strlen(line)-1]=='\n')
  line[strlen(line)-1]='\0';

  if(strcmp(line,color)==0)
  return color;
  strcpy(&colors[i],line);
  i++;
  }

  printf("\nInvalid color! Please pick from the following options:\n");

  for(j=0;j<i;j++) {
  printf("%s, ",colors);
  }
  return "WRONG";
  }*/

int updateCar(car *head, char *targetModel, int year) {/*finds car in linked list and changes its year*/

    car *p=head;

    while(p!=NULL) {//loops through linked list until model is found

        if(strcmp(p->model,targetModel)==0) {
            p->year=year;
            return 1;
        }

        p=p->next;
    }

    return -1;
}

car *removeCar(car *head, char *targetModel) {/*function deletes car from linked list and frees it's memory*/

    car *temp=head;
    car *temp2=head->next;

    if(strcmp(temp->model,targetModel)==0) {
        return head;
    }

    while(temp2!=NULL) {
        if(strcmp(temp2->model,targetModel)==0) {

            temp->next=temp2->next;
            free(temp2->model);//frees memory of deleted linked list
            free(temp2->color);
            free(temp2);

            return head;
        }

        temp=temp->next;
        temp2=temp2->next;
    }

    return head;
}

void freeMem(car *head) {/*Function frees all memory allocated to linked lists*/

    car *current=NULL;

    while((current=head)!=NULL) {//loops until linked list is cleared
        head=head->next;
        free(current->model);
        free(current->color);
        free(current);
    }
}


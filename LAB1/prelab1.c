/*Thomas Schultz
 * TJS6F2
 * CS2050 LAB1
 * 6/06/2017
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXNAME 10

int read_info(char *, int *,char**,float*);
void printArray(int *,char **, float *, int);

int main(int argc, char *argv[]) {

    if(argc!=2){//checking to see command line has 2 inputs
        printf("File name not provided\n");
        return 0;
    } 

    char *input=argv[1];

    int size=0;

    FILE *fptr=fopen(input,"r");
    if(fptr==NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    fscanf(fptr, "%d", &size);

    fclose(fptr);

    int *id=malloc(sizeof(int)*size);
    char **name=malloc(sizeof(char *)*size);
    int i;
    for(i=0;i<size;i++) {
        *(name+i)=malloc(sizeof(char)* MAXNAME);
    }
    float *gpa=malloc(sizeof(float)*size);

    int load=read_info(input,id,name,gpa);

    if(load==-1){//error checks file
        printf("Unable to open the file");
        return -1;
    }
    printArray(id,name,gpa,size);

    free(id);
    for(i=0;i<size;i++) {
        free(*(name+i));
    }
    free(name);
    free(gpa);

    return 0;
}

int read_info(char *file, int *id, char **name, float *gpa) {//finds # of values and loads numbers in pointers

    int x;
    int i;

    FILE *fptr=fopen(file, "r");

    if(fptr==NULL){
        return -1;
    }

    fscanf(fptr, "%d", &x);//loads first value of the file. #==5

    for(i=0; i<x; i++) {
        fscanf(fptr, "%s %d %f", *(name+i), (id+i), (gpa+i));
    }

    fclose(fptr);

    return x;
}

void printArray(int *id, char **name, float *gpa, int sum) {//prints numbers in array

    int i;

    printf("Name\t ID \tGPA\n");

    for(i=0;i<sum;i++) {
        printf("%s\t %d \t%.2f\n", *(name+i), *(id+i), *(gpa+i));
    }
}








/*Thomas Schultz
 * TJS6F2
 * CS2050 LAB2
 * 6/14/17
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Point{
    int x;
    int y;
} point;

//function prototypes used 
point *read_data(char *file,int size);
double distance(point *frist, point *second);
point *sort(point *array, int size);
void print_data(point *array, int size);

int main(int argc, char *argv[]) {

    if(argc!=3){
        printf("Enter correct number of arguments\n");
        exit(0);
    }

    char *input=argv[2];

    int size=atoi(argv[1]);

    point *ptr=read_data(input,size);

    if(ptr==NULL){//error checks to see if file can be opened
        printf("Unable to open file\n");
        exit(0);
    }

    ptr=sort(ptr,size);

    print_data(ptr,size);

    free(ptr);

    return 0;
}

point *read_data(char *file,int size) {/*function reads file and loads info into struct array*/

    FILE *fp=fopen(file, "r");//opens file
    if(fp==NULL) {
        return NULL;
    }

    int i;
    point *xy=malloc(sizeof(point)*size);//creates memory for structure 

    for(i=0;i<size;i++){//loads file into structure
        fscanf(fp, "%d %d", &(xy+i)->x, &(xy+i)->y);
    }

    fclose(fp);//closes file

    return xy;
}

double distance(point *first, point *second){/*takes two points and calculates distance between*/ 

    double dis;

    dis=sqrt(pow(second->x - first->x,2)+ pow(second->y-first->y,2));

    return dis;
}


point *sort(point *array, int size) {/*function sorts points based on origin of (0,0)*/
    int i, j, temp;
    point *origin=malloc(sizeof(point));
    origin->x=0;
    origin->y=0;

    for(i=0;i<size;i++){
        for(j=0;j<size-1;j++) {
            if(distance((array+j),origin)>distance((array+j+1),origin)){//calls distance function to compare distance between points 
                temp=(array+j)->x;//swamp occurs
                (array+j)->x=(array+j+1)->x;
                (array+j+1)->x=temp;

                temp=(array+j)->y;
                (array+j)->y=(array+j+1)->y;
                (array+j+1)->y=temp;
            }
        }
    }

    free(origin);

    return array;
}

void print_data(point *array, int size) {/*function that prints out data from structure*/

    int i;

    printf("Points sorted based on distance from the origin\n");

    for(i=0;i<size;i++){//prints out structure line by line
        printf("(%d, %d)\n", (array+i)->x, (array+i)->y);
    }
}

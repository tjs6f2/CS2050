/*Thomas Schultz
 * TJS6F2
 * CS2050 LAB2
 * 6/14/17
 */

#include <stdlib.h>
#include <stdio.h>

struct data{
    int x;
    int y;
};

struct data *read_data(int size);
void divide_numbers(struct data *array, int size);
struct data *sort(struct data *array, int size);
void print_data(struct data *array, int size);

int main(int argc, char *argv[]) {

    if(argc!=2){
        printf("Enter correct number of arguments\n");
        exit(0);
    }

    int size=atoi(argv[1]);

    struct data *ptr=read_data(size);

    divide_numbers(ptr,size);

    struct data *ptr2=sort(ptr,size);

    print_data(ptr2,size);

    return 0;
}

struct data *read_data(int size) {

    int i;
    struct data *xy=malloc(sizeof(struct data)*size);

    for(i=0;i<size;i++){
        printf("\nEnter a data set\n");
        scanf("%d %d", &xy[i].x, &xy[i].y);
    }

    return xy;
}

void divide_numbers(struct data *array, int size) {

    int i;

    printf("\nThe data sets divided\n");

    for(i=0;i<size;i++){
        printf("%d/%d=%f\n", array[i].x,array[i].y, (float)array[i].x/array[i].y);
    }
}

struct data *sort(struct data *array, int size) {
    int i, j;

    int min=-1;
    int minIndex=0;

    for(i=0;i<size;i++){
        min=array[i].x;
        minIndex=i;

        for(j=i+1;j<size;j++){
            if(min>array[j].x){
                min=array[j].x;
                minIndex=j;
            }
        }

        if(minIndex!=i){
            array[minIndex].x=array[i].x;
            array[i].x=min;
        }
    }

    return array;
}

void print_data(struct data *array, int size) {

    int i;

    printf("\nData sets sorted\n");

    for(i=0;i<size;i++){
        printf("%d %d\n", array[i].x, array[i].y);
    }
}

//Thomas Schultz
//

#include<stdio.h>

int factorial(int);
int costFunction(int);

int main(void) {

    int num;

    printf("Please enter a number: ");
    scanf("%d", &num);


    printf("\nThe factorial of %d is %d\n\n",num, factorial(num));

    int num2;

    printf("Please enter a number: ");
    scanf("%d", &num2);

    printf("\nThe total cost of %d is %d\n\n",num2,costFunction(num2));

    return 0;
}

int factorial(int num) {

    if(num==0) 
        return 1;
    else 
        return num*factorial(num-1);
}

int costFunction(int num) {
    if(num==0) {
        return 2;
    }
    else if(num==1) {
        return 5;
    }
    else {
        return(num*4+costFunction(num-1));
    }
}


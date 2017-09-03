/*Thomas Schultz
 * CS2050 LAB3
 * TJS6F2
 */

#include<stdio.h>
#include<stdlib.h>

void collatzDriver();
void collatz(int);
void hexConverterDriver();
int hexConverter(int);


int main(void) {

    collatzDriver();

    // hexConverterDriver();

    return 0;
}

void collatzDriver() {

    int num;

    while(num!=-1) {

        printf("\nEnter a positve number for the Collatz sequence or -1 to quit: ");
        scanf("%d", &num);

        while(num<=0 && num!=-1) {

            printf("\nInvalid input. Try again: ");
            scanf("%d", &num);
        }

        if(num!=-1) {
            printf("\n");
            collatz(num);
        }

        if(num==-1) {
            exit(0);
        }

    }
}

void collatz(int num) {

    printf("%d",num);

    if(num==1) {
        return;
    }
    else {
        printf("->");
        if(num%2==0) {
            collatz(num/2);
        }
        else {
            collatz(num*3+1);
        }
    }
}


/*int hexConverter(int num) {
  int digit=num%10;
  int newNum=num/10;
  static int power=-1;

  power++;

  if(newNum==0) {
  power=-1;

  }
  else {
  recursive function call
  }*/

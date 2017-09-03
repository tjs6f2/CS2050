/*Thomas Schultz
 * CS2050 LAB6
 * TJS6F2
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct Integer_
{
    int num;
    struct Integer_ *nextInt;
    struct Integer_ *prevInt;
}Integer;

Integer *allocateNode(int);
void addInt(Integer **, int);
void printNumbers(Integer *);
void freeNumbers(Integer *);
void deleteInt(Integer **);

int main(void)
{
    int choice;
    int num;
    Integer *top = NULL;

    do
    {
        printf("\nSelect an option\n1. add a number\n2. take a number off\n3. print numbers\n4. quit\nOption:\n> ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:{
                       printf("\nInsert your number : ");
                       scanf("%d", &num);
                       addInt(&top, num);
                   }
                   break;

            case 2:{
                       deleteInt(&top);
                   }
                   break;

            case 3: {
                        printNumbers(top);
                    }
                    break;

            case 4:
                    break;
            default: printf("\nInvalid option\n");

                     break;
        }
    }while(choice != 4);

    freeNumbers(top);

    return 0;
}

void deleteInt(Integer **top)
{
    if(*top == NULL)
        return;

    Integer *p = *top;
    *top = (*top)->nextInt, (*top)->prevInt = NULL;
    free(p), p = NULL;
}

void freeNumbers(Integer *top)
{
    Integer *temp;
    temp=top;

    while(top!=NULL) {
        temp=top->prevInt;
        free(top->nextInt);
        free(top->prevInt);
        free(top);
        top=temp;
    }
}

void printNumbers(Integer *top)
{
    printf("\n");
    Integer *p = top;

    while(p->nextInt != NULL)
        p = p->nextInt;

    while(p)
    {
        printf("%d", p->num);
        p = p->prevInt;

        if(p)
            printf("->");
    }
    printf("\n");
}

void addInt(Integer **top, int num)
{
    if(*top == NULL)
        *top = allocateNode(num);
    else
    {
        Integer *temp = allocateNode(num);
        temp->nextInt = *top;
        (*top)->prevInt = temp;
        *top = temp;
    }
}

Integer *allocateNode(int num)
{
    Integer *temp = NULL;
    temp = (Integer *)malloc(sizeof(Integer));

    if(temp == NULL)
    {
        printf("\nDynamic memory allocation failed\n");
        exit(-1);
    }

    temp->num = num, temp->nextInt = temp->prevInt = NULL;

    return temp;
}

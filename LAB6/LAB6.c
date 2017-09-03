/*Thomas Schultz
 * CS2050 LAB6
 * TJS6F2
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct word_
{
    char word[10];
    struct word_ *nextWord;
    struct word_ *prevWord;
}Word;

Word *addWord(Word *, Word *);
void printSentence(Word *);
void freeSentence(Word *);
Word *undoWord(Word **);

int main(void)
{
    int choice;
    Word *lastword = NULL;
    Word *undo=NULL;

    do {//program loops until user exits

        Word *new;
        printf("\n1. add word\n2. undo\n3. redo\n4. quit\nOption:\n> ");
        scanf("%d", &choice);

        if(choice==1) {//mallocate memory
            new=malloc(sizeof(Word));
        }

        switch(choice)
        {
            case 1:{//selection to add a word to the stack
                       printf("\nInsert your word: ");
                       scanf("%s", new->word);

                       lastword=addWord(lastword, new);
                       printf("\n");
                       printSentence(lastword);
                       printf("\n");
                   }
                   break;

            case 2:{//removes last word entered 
                       undo=undoWord(&lastword);
                       printf("\n");
                       printSentence(lastword);
                       printf("\n");
                   }
                   break;

            case 3: {//returns the last word removed by user
                        lastword=addWord(lastword,undo);
                        printf("\n");
                        printSentence(lastword);
                        printf("\n");
                    }
                    break;

            case 4: {//exits program
                        exit(0);
                    }
                    break;

            default: printf("\nInvalid option\n");

                     break;
        }
    }while(choice != 4);

    freeSentence(lastword);//frees memory in program

    return 0;
}

Word *undoWord(Word **lastWordPtr)//moves last word entered and stores it away until its called again
{
    Word *undone=*lastWordPtr;

    (*lastWordPtr) = (*lastWordPtr)->prevWord;
    (*lastWordPtr)->nextWord=NULL;
    undone->prevWord=NULL;
    undone->nextWord=NULL;

    return undone;
}

void freeSentence(Word *lastWord)//function frees all memory used in stack
{
    Word *prev;

    while(lastWord!=NULL) {
        prev=lastWord->prevWord;
        free(lastWord);
        lastWord=prev;
    }
}

void printSentence(Word *lastWord)//function prints sentence
{
    while(lastWord->prevWord!=NULL) {
        lastWord=lastWord->prevWord;
    }

    while(lastWord!=NULL) {
        printf("%s ",lastWord->word);

        lastWord=lastWord->nextWord;
    } 
}

Word *addWord(Word *lastWord, Word *nextWord)//adds a word to the stack
{
    if(lastWord==NULL) {
        nextWord->nextWord=NULL;
        nextWord->prevWord=NULL;
        return nextWord;
    }

    lastWord->nextWord=nextWord;
    nextWord->prevWord=lastWord;
    nextWord->nextWord=NULL;

    return nextWord;
}


/*Thomas Schultz
 * CS2050 HW1
 * TJS6F2
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME 30
#define MAX_LINE 100

int countLines(FILE *);
void allocate(int **, int **, char ***,char **,int);
void readLines(FILE *,int *, int *, char **,int);
void printPlayers(int *,int *, char **,int);
void sortPlayers(int *,int *,char **, int);
int findMVP(int *, int *,int);
int findPlayer(char **,char *, int);
void writeFile(FILE *, int *,int *, char **,int);
void freeMem(int *,int *,char **,char *, int);

int main(int argc, char *argv[]) {

    if(argc!=3){ 
        printf("Enter correct number of arguments\n");
        exit(0);
    }

    char *input=argv[1];
    char *output=argv[2];
    FILE *fp=fopen(input, "r");
    FILE *fp2=fopen(output, "w");

    if(fp==NULL || fp2==NULL) {
        printf("Cannot open file\n");
        exit(0);
    }

    int size=countLines(fp);

    int *goals=NULL;
    int *assists=NULL;
    char **names=NULL;
    char *find=NULL;

    allocate(&goals,&assists,&names,&find,size);//function call to allocate memory for pointes

    readLines(fp,goals,assists,names,size);//call to store data in pointer arrays

    printPlayers(goals,assists,names,size);//prints unsorted player list

    printf("\nSorted player list.\n");

    sortPlayers(goals,assists,names,size);//function call to use selection sort on data

    printPlayers(goals,assists,names,size);//call to print sorted player list by goal

    int mvp=findMVP(goals,assists,size);
    printf("\nMVP is %s with %d points\n",*(names+mvp), (*(goals+mvp)+*(assists+mvp)));

    printf("\nEnter a player to find: ");
    scanf("%s", find);
    int index=findPlayer(names,find,size);

    if(index==-1) 
        printf("\nError, player not found\n\n");
    else 
        printf("\n%s has %d goals and %d assists\n", *(names+index),*(goals+index),*(assists+index));


    writeFile(fp2,goals,assists,names,size);

    freeMem(goals,assists,names,find,size);

    fclose(fp);
    fclose(fp2);

    return 0;
}

int countLines(FILE *file) { /*Function reads # of lines in file and returns #*/

    int count=0;
    char ch=0;

    ch=getc(file);

    while(ch!=EOF) {//after reaching new line bump count until end of file 
        if(ch=='\n') {
            count++;
        }
        ch=getc(file);//goes to next line
    }
    rewind(file);
    return count; 
}

void allocate(int **goals, int **assists, char ***names, char **playerIndex, int size) {/*Function allocates space for goals, assists and names by the number of lines in the file*/

    int i;

    *goals=malloc(sizeof(int)*size);
    *assists=malloc(sizeof(int)*size);
    *names=malloc(sizeof(char *)*size);
    for(i=0;i<size;i++){
        *(*names+i)=malloc(sizeof(char)*MAX_NAME);
    }
    *playerIndex=malloc(sizeof(char)*MAX_NAME);
}

void readLines(FILE *ptr, int *goals, int *assists, char **names, int size) {/*fucntion uses fgets and strtok to read lines to file and load info into pointer arrays*/

    char *line=malloc(sizeof(char)*MAX_LINE);
    int i;
    char *token=NULL;

    for(i=0;i<size;i++) {
        if(fgets(line, MAX_LINE, ptr)!=NULL);{
            token=strtok(line," ");
            strcpy(*(names+i),token);
            token=strtok(NULL, " ");
            *(goals+i)=atoi(token);
            token=strtok(NULL, " ");
            *(assists+i)=atoi(token);
        }
    }
    free(line);
}

void printPlayers(int *goals, int *assists, char **names, int size) {/*Function prints off data stored in pointer arrays*/

    printf("\nName\t\t  Goals      Assists\n");
    int i;

    for(i=0;i<size;i++) {
        printf("%-18s %-10d %d\n",*(names+i),*(goals+i),*(assists+i));
    }
}

void sortPlayers(int *goals, int *assists, char **names, int size) {/*function uses selection sort to sort players by goals scored*/

    int index=0;
    int i,j,temp;
    char *tempName;

    for(i=0;i<size;i++) {
        index=i;
        for(j=i+1;j<size;j++) {
            if(*(goals+j)>*(goals+index)) 
                index=j;
        }
        if(index!=i) {
            //swapping occurs for each data set
            temp=*(goals+i);
            *(goals+i)=*(goals+index);
            *(goals+index)=temp;

            temp=*(assists+i);
            *(assists+i)=*(assists+index);
            *(assists+index)=temp;

            tempName=*(names+i);
            *(names+i)=*(names+index);
            *(names+index)=tempName;
        }
    }
}

int findMVP(int *goals, int *assists, int size) {/*Function finds index to player with most goals+assists.Runs for loop to determine index based on goals and assists*/

    int i;
    int mvp=0;
    int max=0;

    for(i=0;i<size;i++) {
        if(*(goals+i)+*(assists+i)>max) {
            max=*(goals+i)+*(assists+i);
            mvp=i;
        }
    }
    return mvp;
}

int findPlayer(char **names, char *index, int size) {/*function finds index of player name and returns it*/

    int i;
    for(i=0;i<size;i++) {
        if(strcmp(index,*(names+i))==0)//comapares to see if names are identical 
            return i;//returns index of players name
    }
    return -1;
}

void writeFile(FILE *ptr, int *goals, int *assists, char **names, int size) {/*function writes sorted data over to another file*/

    int i;

    for(i=0;i<size;i++) {
        fprintf(ptr,"%s %d %d\n",*(names+i), *(goals+i), *(assists+i));
    }
}

void freeMem(int *goals, int *assists, char **names,char *playerIndex, int size) {/*Frees memory from pointers declared in main*/

    free(goals);
    free(assists);
    int i;
    for(i=0;i<size;i++) {
        free(*(names+i));
    }
    free(names);
    free(playerIndex);
}




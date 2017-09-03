/*Thomas Schultz
 * CS2050 HW3
 * TJS6F2
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXCITYNAME 30
#define MAXLINELENGTH 50

typedef struct n_ 
{
    int zipCode;
    char *city;
    char state[3];
    struct n_ *left;
    struct n_ *right;
}Node;

Node *addNode(Node *root, Node *newNode) {//function connects nodes together to form tree

    if(newNode==NULL) {
        exit(1);
    }

    if(root==NULL) {//starts binary tree if there isn't one already
        return newNode;
    }
    else {

        if(newNode->zipCode > root->zipCode) {//sets right side of tree
            root->right = addNode(root->right,newNode);
        }

        if(newNode->zipCode < root->zipCode) {//sets left side of tree
            root->left = addNode(root->left,newNode);
        }
    }

    return root;
}

Node* importTree(char* filename) {

    Node* root = NULL;
    FILE *fPtr = fopen(filename, "r");

    if(!fPtr) {
        printf("Error opening file.\n");
        return NULL;
    }

    while(!feof(fPtr)) {

        Node* new = malloc(sizeof(Node));

        if(!new) {
            printf("Failed to allocate memory. Exiting program.\n\n");
            exit(1);
        }

        new->city = malloc(sizeof(char)*MAXCITYNAME);

        if(!(new->city)) {
            printf("Failed to allocate memory. Exiting program.\n\n");
            exit(1);
        }

        new->left = NULL;
        new->right = NULL;

        char* line = malloc(sizeof(char)*MAXLINELENGTH);

        if(!line) {
            printf("Failed to allocate memory. Exiting program.\n\n");
            exit(1);
        }

        if(fgets(line, MAXLINELENGTH, fPtr) == NULL) {

            if(!feof(fPtr)) {
                printf("File reading ended prematurely. Check for errors in the file.\n");
                exit(1);
            }

            free(new->city);
            free(line);
            free(new);
            fclose(fPtr);
            break;
        }

        char* tmp = strtok(line, ",");
        new->zipCode = atoi(tmp);
        tmp = strtok(NULL, ",");
        strcpy(new->city, tmp);
        new->city[strlen(tmp)+1] = '\0';
        tmp = strtok(NULL, ",");
        strcpy(new->state, tmp);
        new->state[2] = '\0';

        root = addNode(root, new);

        if(!root) {
            printf("Root of tree is NULL! Exiting program.\n\n");
            exit(1);
        }

        free(line);
    }

    return root;
}

int findStateCount(Node* root, char* state) {//function searches binary tree to see if state is found and then returns number of instances state shows up in tree

    if(root == NULL) {//cannot find state
        return 0;
    } 
    else {

        if(strcmp(root->state, state) == 0) {
            return 1 + findStateCount(root->left, state) + findStateCount(root->right, state);
        }
    }

    return findStateCount(root->left, state) + findStateCount(root->right, state);
}

Node* findZipCode(Node* root, int zipCode) {//function searches for zip and sees if theres a match

    if(root == NULL) {
        return NULL;
    } 
    else {
        if(root->zipCode == zipCode) {
            return root;
        }

        Node *find = NULL;

        find = findZipCode(root->left, zipCode);//searches left side of tree

        if(find!= NULL) {
            return find;
        }

        find = findZipCode(root->right, zipCode);//searches right side of tree

        if(find!= NULL) {
            return find;
        }
    }
    return NULL;
}

void freeTree(Node *root) {//function frees all memory used in program to prevent memory leaks

    if(root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root->city);
    free(root);
}

int main(int argc, char** argv) {

    if(argc != 2) {//sends error and exits program if file is not provided 
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    Node *root = NULL;
    Node *zipNode=NULL;

    root = importTree(argv[1]);

    if(root == NULL) {//error check to see if file can be opened
        printf("\nUnable to import tree from file");
        exit(1);
    }

    int num, zipCount,zipSearch = 0;
    char *stateSearch = malloc(sizeof(char)*3);

    while(num!=3) {//loop runs until user selects 3 to terminate program

        printf("\n1: Find number in a state\n2: Find a ZIP code\n3: Exit\n> ");
        scanf("%d", &num);

        switch(num) {

            case 1: {//selection tells how many zip codes are in a state

                        printf("\nEnter the state: ");
                        scanf("%s", stateSearch);

                        zipCount = findStateCount(root, stateSearch);

                        if(zipCount== 0) {

                            printf("\nNo results found for that state\n");

                        } 
                        else {

                            printf("\nThe state of %s has %d zip codes in the file.\n", stateSearch,zipCount);

                        }

                        break;
                    }

            case 2: {//selection finds city and state

                        printf("\nEnter the ZIP you want to find: ");
                        scanf("%d", &zipSearch);

                        zipNode = findZipCode(root, zipSearch);

                        if(zipNode == NULL) {//if zip code is not found
                            printf("\nNo results found for zip code %d\n", zipSearch);

                        } 
                        else {//if zip code is found
                            printf("\nResult found for zip code %d: ", zipSearch);
                            printf("\n\tCity: %s", zipNode->city);
                            printf("\n\tState: %s\n", zipNode->state);
                        }

                        break;
                    }

            case 3: {//selection terminates program

                        printf("\nProgram Terminated.\n");

                        freeTree(root);
                        free(stateSearch);
                        exit(0);

                        break;
                    }

            default: {

                         printf("\nError - not a valid option. Try again.\n");

                     }
        }
    }

    //frees memory used in program
    freeTree(root);
    free(stateSearch);

    return 0;
}


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {//change ; into a ,
    PaperBack,
    HardBack
} Type;

typedef struct book {
    char* name;
    char* author;
    int rating;
    Type type;
} Book;

typedef Book* Library;

Library loadLibrary(const char* filename, int* lenPtr);
void sortLibrary(Library library,  int length);
void printLibrary(Library library, int length);
void writeLibrary(Library library, int length, const char* filename);

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Incorrect Usage\n");
        printf("%s <input file> <output file>\n", argv[0]);
        return 0;
    }

    int length;
    Library library = loadLibrary(argv[1], &length);//added & to length

    sortLibrary(library, length);
    printLibrary(library, length);
    writeLibrary(library, length, argv[2]);//changed argv[0] to argv[2]

    int i;
    for (i = 0; i < length; i++){//curly braces around for loop
        free(library[i].name);
        free(library[i].author);//added ; 
    }

    free(library);

    return 0;
}

Library loadLibrary(const char* filename, int* lenPtr) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open file %s\n", filename);
        *lenPtr = 0;
        return NULL;
    }

    fscanf(fp, "%d", lenPtr);
    Library library = malloc(sizeof(Book) * (*lenPtr));//added *

    int i;
    for (i = 0; i < *lenPtr; i++) {
        library[i].name=malloc(sizeof(char));
        library[i].author=malloc(sizeof(char));
        fscanf(fp, "%s %s %d %u", library[i].name, library[i].author, &library[i].rating,&library[i].type);//added %u
    }

    return library;
    fclose(fp);
}

void sortLibrary(Library library,  int length) {
    int i;

    for (i = 1; i < length; i++) {
        int j = i;
        while (j > 0 && library[j].rating < library[j - 1].rating) {
            Book temp = library[j];
            library[j] = library[j - 1];
            library[j - 1] = temp;
        }
    }
}

void printLibrary(Library library, int length) {
    int i;
    for (i = 0; i < length; i++) {
        printf("%s %s %d", library[i].name, library[i].author, library[i].rating);
        if (library[i].type == PaperBack) {//added * & ==
            printf(" PaperBack\n");
        } else {
            printf(" HardBack\n");
        }
    }
}

void writeLibrary(Library library, int length, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        return ;
    }

    fprintf(fp, "%d\n", length);

    int i;
    for (i = 0; i < length; i++) {
        fprintf(fp, "%s %s %d", library[i].name, library[i].author, library[i].rating);

        if(library[i].type== PaperBack) {
            fprintf(fp," PaperBack\n");
        }
        else {
            fprintf(fp," HardBack\n");
        }
    }

    fclose(fp);
}


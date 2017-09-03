/*Thomas Schultz
 * CS2050 LAB8
 * TJS6F2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool isATime(char* word);
bool isADate(char* word);
bool isAPhoneNumber(char* word);

int main(int argc, char** argv) {

    if(argc != 2) {//checks to see correct number of arguments
        printf("Incorrect number of arguments\n");
        exit(-1);
    }

    char *input = argv[1];

    FILE* fp = fopen(input, "r");

    if(fp==NULL) {//ends program if file is unable to open
        printf("Could not open file\n");
        exit(-1);
    }

    char line[20];

    while(fgets(line,20,fp) != NULL) {//runs through program until reaches end of file

        bool check=false;

        check = isATime(line);

        if(check==true) {//prints time if valid
            printf("Time found: %s", line);
        }

        check = isADate(line);

        if(check==true) {//prints date if valid
            printf("Date found: %s", line);
        }

        check = isAPhoneNumber(line);

        if(check==true) {//prints phone number if valid 
            printf("Phone Number found: %s", line);
        }
    }

    fclose(fp);

    return 0;
}

bool isATime(char* word) {//function looks for valid times in the file. there are a set of critia for it to need to pass in order to be considered valid

    if(word == NULL) {
        return false;
    }

    char *delim = ":ap";

    char stringcopy[20];
    strcpy(stringcopy, word);//copies string so it doesn't get changed


    char* token = strtok(stringcopy, delim);//initializes variables
    int i = 0; 
    int d = 0;
    int a = 0;

    int count = 0;

    for(i = 0; word[i]; i++) {//checks for 1 colon
        count += (word[i] == ':');
    }

    if(count != 1) {//if it doesn't have 1 colon its not a valid time
        return false;
    }

    i = 0;

    if(strlen(word) < 6) {//cannot be more than 6 chars. 1 or 2 for hours. 1 for colon. 2 for minutes and 1 for pm/am
        return false;
    }

    while(token != NULL) {
        d = strlen(token);

        if(i == 0) {

            if(atoi(token) == 0) {
                return false;
            }

            if(d < 1 || d > 2) {//first token should be 1 or 2 digits
                return false; 
            }

            a = atoi(token);
            if(a < 1 || a > 12) {//checks to see if hours are between 1-12
                return false;
            }
        }

        if(i == 1) {//second token needs to be 2 digits
            if(strlen(token) != 2) {
                return false;
            }

            a = atoi(token);
            if(a < 1 || a > 59) {//checks to see if minutes are btween 1-59
                return false;
            }
        }

        if(i == 2) {//checks to see if it ends in am or pm
            if(*token != 'm') {
                return false;
            }

            if(strlen(token) != 2) {//checks for last char and null terminator at end
                return false;
            }
        }

        if(i >= 3) {
            return false;
        }

        token = strtok(NULL, delim);
        i++;
    }

    return true;
}	

bool isADate(char* word) {//function searches to find valid dates from data. Plz have mercy with this function.

    /*int day, month, year;
      int validDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 ,31};//amount of days in each month

      if (strlen(word) != 10)//must have 10 chars in it. month/day/year/null terminater 
      return false;

      if (word[1] != '/')//checks for / to divide month from day
      return false;

      if (word[4] != '/')// checks for / to divide day from year
      return false;

      word[2] = '\0';
      word[5] = '\0';

      month = atoi(word);
      day = atoi(&word[3]);
      year = atoi(&word[5]);

      if (isdigit(month)<1  ||  isdigit(month)>12)//if month isnt between 1-12 its not valid
      return false;

      if (isdigit(day)<0 || isdigit(day) > validDays[month-1]) {
      return false;
      }

      if (isdigit(year) <= 1900) {//only checking for dates after 1900
      return false;
      }

      return true;*/

    return false;

}

bool isAPhoneNumber(char* word) {//function looks through text file to find valid phone numbers

    //initialize variables 
    int num = 0;
    int hyphen = 0;
    int other = 0;
    char *ptr = word;

    if(atoi(ptr) == 0){ // Ensure the first value isn't 0
        return false;
    }

    while((*ptr) != '\0'){//run through each character until reach null terminater 
        if(isdigit(*ptr)){ //if its a num bump counter
            num++;
        }
        else if(*ptr == '-'){//if theres a dash bum counter
            hyphen++;
        }
        else if(*ptr != '\n' && *ptr != '\r'){
            other++;
        }
        ptr++;
    }

    if(num == 10 && hyphen == 2 && other == 0 && word[3] == '-' && word[7] == '-'){//if string meets all criteria then its a valid phone #
        return true;
    }
    else{
        return false;
    }
}

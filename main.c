/*
main.c
Assignment Project 2
Amos Munteanu
this file is the program that's being ran and hold's all the logic for when each function get's called and why it gets called
*/ 


#include <stdio.h>
#include "route-records.h"
#include <string.h>
#include <stdlib.h>


int main( int argc, char *argv[] )
{
    // declaring all the variables 
  char key1[MAX_KEY_LENGTH];
  char key2[MAX_KEY_LENGTH];
  char c;
  SearchType type;
  int length;
  char input;
  RouteRecord *record = NULL;
  FILE *fileIn = NULL;
   //looks for if the file exists and if not tells you it can't open
  fileIn = fopen("data.csv", "r");
  if(fileIn == NULL)
  {
    printf("ERROR: Could not open file");
    return -1;
  }
    record = createRecords(fileIn);
    length = fillRecords(record, fileIn); 
    fclose(fileIn);

    while(input != 53)
    {
    // let's you make a selection 
      printMenu();
      scanf("Enter Selection: %c", &input);
            while( (c =getchar())!='\n' && c !=EOF );


      if(input < 48 && input > 53) 
      {
        printf("Invalid choice.\n");
        printMenu();
        scanf(" %c", &input);
        while( (c =getchar())!='\n' && c !=EOF );
      }
    switch(input)
    {
        case 49:
        type = ROUTE;
        //searches by route
        printf("Enter route: ");
        fgets(key1, MAX_KEY_LENGTH, stdin);
        key1[strcspn(key1, "\n")] = 0;
        upperCaseCon(key1);
        while( (c =getchar())!='\n' && c !=EOF );
         
        printf("Enter destination: ");
        fgets(key2, MAX_KEY_LENGTH, stdin);
        key2[strcspn(key2, "\n")] = 0;
        upperCaseCon(key2);
        printf("\nSearching by route...\n");
        searchRecords(record, length, key1, key2, type);
        break;

        case 50:
        type = ORIGIN;
        //searchs by origin
        printf("Enter origin: ");
        fgets(key1, MAX_KEY_LENGTH, stdin);
        key1[strcspn(key1, "\n")] = 0;
        upperCaseCon(key1);
        printf("\nSearch by origin...\n");
        searchRecords(record, length, key1, key2, type);
        break;

        case 51:
        type = DESTINATION;
        //serches by desitnation 
        printf("Enter the destination: ");
        fgets(key1, MAX_KEY_LENGTH, stdin);
        key1[strcspn(key1, "\n")] = 0;
        upperCaseCon(key1);
        printf("\nSearch by destination...\n");
        searchRecords(record, length, key1, key2, type);
        break;

        case 52:
        type = AIRLINE;
        // searchs by airline
        printf("Enter airline: ");
        fgets(key1, MAX_KEY_LENGTH, stdin);
        key1[strcspn(key1, "\n")] = 0;
        upperCaseCon(key1);
        printf("\nSearch by airline...\n");
        searchRecords(record, length, key1, key2, type);
        break;
        
        case 53:

        free(record);
        printf("Good-bye!\n");
        break;
    }
    
    }
    return 0;
}

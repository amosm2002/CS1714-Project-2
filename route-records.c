/*
route-records.c
Assignment Project 2
Amos Munteanu
This file stores all of the function's and their logic to make main.c file work
*/ 


#include "route-records.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
Function: createRecords
This function grabs the record for the flight and stores it into an array
parameter1identifier: finds the length of the file
parameter2identifier: makes the passenger amount 0
parameter3dentifier: rewinds the file
Returns: the pointer to the array 
*/

RouteRecord* createRecords(FILE* fileIn)
{
  char buffer[200];
  int count = 0;
  RouteRecord *record = NULL; 
  fgets(buffer,100,fileIn);

  while(fgets(buffer, 100, fileIn) != NULL)
  {
    count = count + 1;
  }

  record = (RouteRecord*)malloc(count * sizeof(RouteRecord));

  for(int i = 0; i < 6; i++)
  {
    for(int j = 0; j < count; j++)
    {
      record[j].total[i] = 0; 
    }
  }

rewind(fileIn);
return record;
}


/*
Function: fillRecords
scans for the data in the file and fill's the array that was creatred with this data
parameter1identifier: scans for the different data
parameter2identifier: caclutes the months 
Returns: the number of RouteRecords used in the array
*/



int fillRecords( RouteRecord* r, FILE* fileIn )
{

  char usg_apt[4];
  char fg_apt[4];
  char carrier[4];
  int month;
  int curIndex = 0;
  int i = 1;
  int total;
  char buffer[100];
  char type[20];
  fgets(buffer, 100, fileIn);
  

  while(fgets(buffer, 100, fileIn) != NULL)
  {
    sscanf(buffer, "%d,%[^,],%[^,],%[^,],%[^,],%d", &month, usg_apt, 
    fg_apt, carrier, type, &total);
    
    if(strlen(carrier) < 3)
    {
       curIndex = findAirlineRoute(r, i, usg_apt, fg_apt, carrier, 0);
       
       if(curIndex == -1)
       {
         strcpy(r[i].origin, usg_apt);
         strcpy(r[i].destination, fg_apt);
         strcpy(r[i].airline, carrier);
         r[i].total[month - 1] = total;
       }
       
       else
       {
         r[curIndex].total[month - 1] = total;
       }
       i++;
    }
  }
  return i;
}

/*
Function: findAirlineRoute
this function finds a specifc record in the array
parameter1identifier: checks for the in the array
parameter2identifier: description of the second parameter
Returns: the index number for the array
*/

int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx)
{
  if(curIdx == length)
  {
    return -1;
  }
  if(strcmp(r[curIdx].origin, origin) == 0 && strcmp(r[curIdx].destination, destination) == 0 && 
    strcmp(r[curIdx].airline, airline) == 0)
  {
    return curIdx;
    
  }
  return findAirlineRoute(r,length, origin, destination, airline, curIdx + 1);
}


/*
Function: searchRecords
looks through the array created and prints out the results
parameter1identifier: searching the array for the data
parameter2identifier: cacluates the amount for each variable 
Returns: the total number of passangers and caluclates the avearage per month
*/



void searchRecords( RouteRecord* r, int length, const char* key1, const char* key2, SearchType st )
{
  int found = 0;
  int month[6] = {0,0,0,0,0,0};
  int totalTwo = 0;
  int count = 0;

 for(int i = 0; i < length; i++)
 {
    
    if(st == ORIGIN)
    {
      
      if(strcmp(r[i].origin, key1) == 0)
      {
        printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
        
        for(int j = 0; j < 6; j++)
        {
          month[j] += r[i].total[j];
          totalTwo += r[i].total[j];
        }

        found++;   
      }
    }
    else if(st == DESTINATION)
    {
      
      if(strcmp(r[i].destination, key1) == 0)
      {
        printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);

          for(int j = 0; j < 6; j++)
          {
            month[j] += r[i].total[j];
            totalTwo += r[i].total[j];
          }
        found++;
      }
    }
    else if(st == AIRLINE)
    {

      if(strcmp(r[i].airline, key1) == 0)
      {
        printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
          
          for(int j = 0; j < 6; j++)
          {
            month[j] += r[i].total[j];
            totalTwo += r[i].total[j];
          }
        found++;
      }
    }
    else
    {
      
      if(strcmp(r[i].origin, key1) == 0 && (strcmp(r[i].destination, key2) == 0))
      {
        printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
          
          for(int j = 0; j < 6; j++)
          {
            month[j] += r[i].total[j];
            totalTwo += r[i].total[j];
          }
        found++;
      }
    }
 } 

  printf("\n%d matches were found.\n\n", found);
  
  /*** Statistics ***/
  printf("Statistics\n");
  printf("Total Passengers: %d\n", totalTwo);
  
  for(int k = 0; k < 6; k++)
  {
    printf("Total Passengers in Month %d: %d\n",k + 1, month[k]);
  }
  printf("\n\nAverage Passengers per Month: %.lf\n", totalTwo / 6.0);
}


/*
Function: printMenu
prints the selection menu 
Returns: void
*/


void printMenu()
{
printf( "\n\n######### Airline Route Records Database MENU #########\n" );
printf( "1. Search by Route\n" );
printf( "2. Search by Origin Airport\n" );
printf( "3. Search by Destination Airport\n" );
printf( "4. Search by Airline\n" );
printf( "5. Quit\n" );
printf( "Enter your selection: " );
}

/*
Function: upperCaseCon
changes lowercase inputs to uppercase 
Returns: converts lowercase inputs to uppercase
*/

void upperCaseCon(char key[])
{
   for(int j = 0; j < strlen(key); j++)
   {
    key[j] = toupper(key[j]);
   }
} 




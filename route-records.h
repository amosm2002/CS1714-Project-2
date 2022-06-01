/*
route-records.h
Assignment Project 2
Amos Munteanu
This file stores the enum and function names
*/ 


#ifndef ROUTE_RECORDS_H
#define ROUTE_RECORDS_H
#include <stdio.h>
#define MAX_KEY_LENGTH 4  

typedef struct RouteRecord
{
  char origin[4];
  char destination[4];
  char airline[3];
  int total[6];
}RouteRecord;

typedef enum SearchType { ROUTE, ORIGIN, DESTINATION, AIRLINE } SearchType;

/*
Function: createRecords
This function grabs the record for the flight and stores it into an array
parameter1identifier: finds the length of the file
parameter2identifier: makes the passenger amount 0
parameter3dentifier: rewinds the file
Returns: the pointer to the array 
*/

RouteRecord* createRecords(FILE* fileIn);

/*
Function: fillRecords
scans for the data in the file and fill's the array that was creatred with this data
parameter1identifier: scans for the different data
parameter2identifier: caclutes the months 
Returns: the number of RouteRecords used in the array
*/

int fillRecords( RouteRecord* r, FILE* fileIn); 

/*
Function: findAirlineRoute
this function finds a specifc record in the array
parameter1identifier: checks for the in the array
parameter2identifier: description of the second parameter
Returns: the index number for the array
*/

int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx);

/*
Function: searchRecords
looks through the array created and prints out the results
parameter1identifier: searching the array for the data
parameter2identifier: cacluates the amount for each variable 
Returns: the total number of passangers and caluclates the avearage per month
*/

void searchRecords( RouteRecord* r, int length, const char* key1, const char* key2, SearchType st );

/*
Function: printMenu
prints the selection menu 
Returns: void
*/

void printMenu(); 

/*
Function: upperCaseCon
changes lowercase inputs to uppercase 
Returns: converts lowercase inputs to uppercase
*/

void upperCaseCon(char key[]);


#endif 
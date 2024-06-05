#ifndef ARRAY_UTILITIES_H
#define ARRAY_UTILITIES_H

// header files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "StandardConstants.h"

// constants made available to other files here
extern const int CELL_WIDTH;
extern const int MAX_ARRAY_SIDE;

extern const char THICK_DIVIDER_LINE;
extern const char THIN_DIVIDER_LINE;

// Data structures
typedef struct RangeTypeStruct
   {
    int lowVal;

    int highVal;
   } RangeType;

/*
Name: clearTwoDimArray
Process: returns allocated memory to the operating system
Function Input/Parameters: pointer to two dimensional array (int **),
                           number of columns(int)
Function Output/Parameters: none
Function Output/Returned: NULL
Device Input/---: none
Device Output/---: none
Dependencies: free (5 lines of code)
*/
int **clearTwoDimArray( int **array, int numRows )
{
    // initialize/define variables
    int index;

    for (index = 0; index < numRows; index++)
    {
        free(array[index]);
    }

    free(array);

    return NULL;
}
// NOTE: when I checked the notes for tuesdays class he put in numRows instead of numCols, but when the function parameters where originally given
// the code took in numCols, I decided to follow his given code from class on tuesday that takes in numRows.

/*
Name: copyArray
Process: copies values from one two dimensional array to another
Function Input/Parameters: pointer to source array (int **),
                           number of rows and columns (int)
Function Output/Parameters: pointer to destination array (int **)
Function Output/Returned: none
Device Input/---: none
Device Output/---: none
Dependencies: none (4 lines of code)
*/
void copyArray(int** destArray, int** srcArray, int numRows, int numCols)
{
    // initialize variables
    int rowIndex, colIndex;

    // loop through rows
    for (rowIndex = 0; rowIndex < numRows; rowIndex++)
    {
        // loop through columns
        for (colIndex = 0; colIndex < numCols; colIndex++)
        {
            // copy data
            destArray[rowIndex][colIndex] = srcArray[rowIndex][colIndex];
        }
    }

    // return
    return srcArray;
}
// question for this one, do i assume that the destArray already has space allocated into it or do I need to allocate space for it?

/*
Name: createTwoDimArray
Process: creates two dimensional array of integer values
         using given row and column limits,
         sets all elements to zero
Function Input/Parameters: number of rows and columns (int)
Function Output/Parameters: none
Function Output/Returned: pointer to two dimensional array (int **)
Device Input/---: none
Device Output/---: none
Dependencies: malloc, sizeof (C keyword) (6 lines of code)
*/
int** createTwoDimArray(int numRows, int numCols)
{
    // initialize variables
    int** twoDimPtr;
    int rowIndex, colIndex;

    // allocate space for the rows
    twoDimPtr = (int**)malloc(numRows * sizeof(int**));

    for (rowIndex = 0; rowIndex < numRows; rowIndex++)
    {
        // allocate space for each column
        twoDimPtr[rowIndex] = (int**)malloc(numCols * sizeof(int**));

        // loop across columns
        for (colIndex = 0; colIndex < numCols; colIndex++)
        {
            // set all elements to zero
            twoDimPtr[rowIndex][colIndex] = 0;
        }
    }

    // return
    return twoDimPtr;
}

/*
Name: displayArray
Process: displays two dimensional array of integer values greater than zero
         using given row and column limits,
         values are formatted and displayed in character cells,
         values below one are displayed as asterisks
Function Input/Parameters: pointer to two dimensional array (int **),
                           number of rows and columns (int),
                           subtitle to display (char *)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/---: none
Device Output/monitor: data displayed as specified
Dependencies: displayDividerLine, printf (14 lines of code)
*/
void displayArray(int** array, int numRows, int numCols, char* title)
{
    // initialize variables
    int rowIndex, colIndex, index;

    // display title
    while (title[index] != '\0')
    {
        printf("%c", title[index]);
        index++;
    }
    // move to new line
    printf("\n");

    // display top divider line
    displayDividerLine(numCols, THICK_DIVIDER_LINE);

    // loop through rows
    for (rowIndex = 0; rowIndex < numRows; rowIndex++)
    {
        // loop through columns
        for (colIndex = 0; colIndex < numCols; colIndex++)
        {
            // print pipe
            printf("%c", PIPE);

            // check if value is greater than 1
            if (array[rowIndex][colIndex] < 1)
            {
                // value less than 1 print 3 astericks
                printf("  *** ");
            }

            // otherwise print number with space at end
            printf("%5d ", array[rowIndex][colIndex);
        }

        // print end pipe and move to new line
        printf("%c", PIPE);
        printf("\n");

        // print divider line thin
        displayDividerLine(numCols, THIN_DIVIDER_LINE);

    }

    // display bottom divider line
    displayDividerLine(numCols, THICK_DIVIDER_LINE);
}
// the only thing here is I didn't know how to implement the cell width, I was unsure if I could replace something like %5d with %(CELL_WIDTH - 1)d

/*
Name: displayDividerLine
Process: displays horizontal divider line of correct width, 
         with vertical divider lines (PIPE) dividing the cells
         (of width CELL_WIDTH),
         and with given divider line thickness,
         top and bottom rows are thick dividers,
         internal rows are thin dividers
Function Input/Parameters: number of horizontal cells (int), 
                           thickness character (char)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/---: none
Device Output/monitor: divider line displayed as specified
Dependencies: printf, printChars (6 lines of code)
*/
void displayDividerLine(int horizNumCells, char thicknessChar)
{
    // initialize variables
    int index;

    // display the horizonal divider line
    for (index = 0; index < horizNumCells; index++)
    {
        // print a pipe
        printf("%c", PIPE);

        // print the thickness char
        printChars(CELL_WIDTH, thicknessChar);
    }

    // print last pipe
    printf("%c", PIPE);
    
    // move to new line
    printf("\n");
}
// the only thing here is that when working on this and displayArray I'm assuming the cell width doesn't include the pipes
// thus |------| is of cell width 6 not 8

/*
Name: getArraySide
Process: provides user data entry for one array side 
         to be used with a square two-dimensional array,
         value entered by user must be greater than two
         and less then the maximum parameter value;
         function repeats entry process until constraints are met
Function Input/Parameters: maximum side size allowed (int)
Function Output/Parameters: none
Function Output/Returned: user entered value (int)
Device Input/keyboard: data entered by user
Device Output/monitor: prompts provided
                prompt: "Enter array side (<min side size> - <max side size>): "
                error prompt: "Incorrect entry - <original prompt>"
                Text display lines may not be repeated in code
Dependencies: printf, scanf (11 lines of code)
*/
int getArraySide(int maxSideSize)
{
    // initialize variables
    int arraySide;

    // ask for array side
    printf("Enter array side (3 - %d): ", maxSideSize);
    scanf("%d", &arraySide);

    // print new line
    printf("\n");


    // check if arraySide is within bounds
    if (arraySide < 3 || arraySide > maxSideSize)
    {
        // not in bounds, say incorrect entry and reloop through
        printf("Incorrect entry - ");
        getArraySide(maxSideSize);
    }

    // correct entry found thus return it
    return arraySide;
}

/*
Name: getRandBetween
Process: generates random value between a given low and high value inclusive
Function Input/Parameters: low and high limits (int)
Function Output/Parameters: none
Function Output/Returned: value generated as specified
Device Input/---: none
Device Output/---: none
Dependencies: rand (2 lines of code)
*/
int getRandBetween(int lowLimit, int highLimit)
{
    // initialize variables
    int result;

    result = rand() % (highLimit - lowLimit + 1)) + lowLimit;

    return result;
}

/*
Name: getRangeToRemove
Process: prompts use for range to remove, between 1 as lowest
         to highest value within array for highest;
         lowest entry must be less than highest entry,
         repeats entry until input data is correct
Function Input/Parameters: given maximum side size (int),
                           number of rows and columns (int)
Function Output/Parameters: lowest and highest range values (RangeType *)
Function Output/Returned: none
Device Input/keyboard: data entered by user
Device Output/monitor: prompts provided
prompt: "Enter low limit (1 - <max array value >): "
        "Enter high limit (<low limit plus one> - <max array value>): "
        error prompt: "Incorrect entry - Retry:", 
        then repeat above entry statements
        Text display lines may not be repeated in code
Dependencies: printf, scanf (13 lines of code)
*/
void getRangeToRemove(RangeType* inputData, int numRows, int numCols)
{
    // initialize/declare variables
    int low, high;
    int max = numRows * numCols;
    int temp;

    printf("Range Removal Entry:");

    // ask for low limit above 1 below numRows * numCols
    // get lower value
    printf("    - Enter low limit (1 - %d): ", max);
    scanf("%d", &low);
    printf("\n");

    if (low > max)
    {
        printf("--- Incorrect - Retry:");
        printf("\n");
        // restart process call function again
        getRangeToRemove(inputData, numRows, numCols);
    }

    temp = low + 1;
    // get higher value
    printf("    - Enter high limit(%d - %d): ", temp, max);
    scanf("%d", &high);
    printf("\n");

    if (low > high || high > max)
    {
        printf("--- Incorrect - Retry:");
        printf("\n");
        // restart process call function again
        getRangeToRemove(inputData, numRows, numCols);
    }

    // passed all the previous tests now add to node
    inputData.lowVal = low;
    inputData.highVal = high;

}

/*
Name: isInArray
Process: searches two dimensional array, returns true if specified value
         is found in array, false otherwise;
         must return true as soon as it is found in the test
Function Input/Parameters: pointer to two dimensional array (int **),
                           number of rows and columns (int),
                           search value (int)
Function Output/Parameters: none
Function Output/Returned: Boolean result of test as specified
Device Input/---: none
Device Output/---: none
Dependencies: none (6 lines of code)
*/
bool isInArray(int** array, int numRows, int numCols, int searchVal)
{
    // initialize/define variables
    int rowIndex, colIndex;

    // loop through rows
    for (rowIndex = 0; rowIndex < numRows; rowIndex++)
    {
        // loop through columns
        for (colIndex = 0; colIndex < numCols; colIndex++)
        {
            if (array[rowIndex][colIndex] == searchVal)
            {
                // value found return true
                return true;
            }
        }
    }

    // end of loop value not found
    return false;
}

/*
Name: loadArrayWithValues
Process: given the number of rows and columns,
         loads two dimensional array with unique random values
         (no two values may be the same),
         values must start at one, and end at the maximum possible value
         for the array
Function Input/Parameters: pointer to two dimensional array (int **), 
                           number of rows and columns (int)
Function Output/Parameters: pointer to updated two dimensional array (int **)
Function Output/Returned: none
Device Input/---: none
Device Output/---: none
Dependencies: getRandBetween, isInArray (8 lines of code)
*/
void loadArrayWithValues(int** array, int numRows, int numCols)
{
    // initialize variables
    int max = numRows * numCols;
    int rowIndex;
    int colIndex = 0;
    int input;

    // loop across rows
    for (rowIndex = 0; rowIndex < numRows; rowIndex++)
    {
        // loop across columns
        while (colIndex < numCols)
        {
            // get a random number
            input = getRandBetween(1, max);

            // check if that number is already in array
            if (!isInArray(array, numRows, numCols, input))
            {
                // if not in array add to array
                array[rowIndex][colIndex] = input;

                // increment colIndex
                colIndex++;
            }
        }
    }

    return array;
}

/*
Name: printChars
Process: recursively prints a specified number of specified characters
Function Input/Parameters: number of characters (int),
                           character to display (char)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/---: none
Device Output/monitor: character(s) displayed as specified
Dependencies: printf, printChars (recursively) (3 lines of code)
*/
void printChars(int numChars, char outChar)
{
    if (numChars <= 0)
    {
        return NULL;
    }

    printf("%c", outChar);
    printChars(numChars - 1, outChar);
}

/*
Name: removeRange
Process: removes a range of values within a two dimensional array
Function Input/Parameters: pointer to two dimensional array (int **),
                           number of rows and columns (int),
                           range (low, high) limits (RangeType)
Function Output/Parameters: pointer to updated two dimensional array (int **)
Function Output/Returned: void
Device Input/---: none
Device Output/---: none
Dependencies: setElementToZero (3 lines of code)
*/
void removeRange(int** array, int numRows, int numCols, RangeType range)
{
    // initialize variables
    int index;

    for (index = range.lowVal; index <= range.highVal; index++)
    {
        setElementToZero(array, numRows, numCols, index);
    }
}

/*
Name: setElementToZero
Process: searches two dimensional array for value;
         if found, sets value to zero and returns true
         immediately upon making the assignment,
         otherwise returns false
Function Input/Parameters: pointer to two dimensional array (int **), 
                           number of rows and columns (int),
                           search value (int)
Function Output/Parameters: pointer to updated two dimensional array (int **)
Function Output/Returned: Boolean result of specified action
Device Input/---: none
Device Output/---: none
Dependencies: none (7 lines of code)
*/
bool setElementToZero(int** array, int numRows, int numCols, int searchValue)
{
    // initialize/define variables
    int rowIndex, colIndex;

    // loop through rows
    for (rowIndex = 0; rowIndex < numRows; rowIndex++)
    {
        // loop through columns
        for (colIndex = 0; colIndex < numCols; colIndex++)
        {
            if (array[rowIndex][colIndex] == searchVal)
            {
                // value found
                // set to zero
                array[rowIndex][colIndex] = 0;

                // return true
                return true;
            }
        }
    }

    // end of loop value not found
    return false;
}

#endif   // ARRAY_UTILITIES_H
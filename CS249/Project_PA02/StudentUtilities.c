#ifndef STUDENT_UTILITIES_H
#define STUDENT_UTILITIES_H

// header files
#include <stdio.h>
#include <string.h>
#include "File_Input_Utility.h"
#include "StandardConstants.h"

// data structure
typedef struct StudentDataStruct
   {
    char name[ STD_STR_LEN ];

    char gender;

    int studentId;

    double gpa;
   } StudentDataType;

// Prototypes

/*
Name: addElementWithData
Process: adds all individual data values to StudentDataType array 
         if capacity has not been exceeded,
         returns true upon success, false otherwise
Function input/parameters: data array (StudentDataType []), 
                           size and capacity (int),
                           student name (const char *),
                           student gender (char),
                           student ID (int),
                           student gpa (double)
Function output/parameters: updated data array (StudentDataType []),
                            updated size (int *)
Function output/returned: Boolean result of operation as specified
Device input/---: none
Device output/---: none
Dependencies: strcpy
*/
bool addElementWithData(StudentDataType array[], int* size, int capacity,
    const char* name, char gender, int studentId, double gpa)
{
    // initialize variables

    // check if at capacity
    if (*size < capacity)
    {
        // not at capacity yet thus add the data
        // add at array[size] because if size is zero it would add at the first position
        strcpy(array[*size].name, name);
        array[*size].gender = gender;
        array[*size].gpa = gpa;
        array[*size].studentId = studentId;

        // increment size pointer
        (*size)++;

        // return true
        return true;
    }

    // if here then size is at or greater than capacity
    // thus return false
    return false;
}

/*
Name: addElementFromElement
Process: adds data from element to StudentDataType array,
         uses supporting function 
Function input/parameters: data array (StudentDataType []), 
                           size and capacity (int),
                           source element (const StudentDataType)
Function output/parameters: updated data array (StudentDataType []),
                            updated size (int *)
Function output/returned: Boolean result of operation as specified
Device input/---: none
Device output/---: none
Dependencies: addElementWithData - function uses one code statement
*/
bool addElementFromElement(StudentDataType array[],
    int* size, int capacity, const StudentDataType student)
{
    // initialize variables

    // check if at capacity
    if (*size < capacity)
    {
        // size is not at capacity thus add data
        // call addElementWithData function
        addElementWithData(array[], *size, capacity, student.name, student.gender, student.studentId, student.gpa);

        // I'm going to return true here because although it returns true in the other one idk
        // if that will end this function as well
        return true;
    }
    
    // assume size is greater than or equal to capacity
    // thus return false
    return false;
}

/*
Name: copyArray
Process: copies elements from one array to another
Function input/parameters: source array (const StudentDataType []), size (int)
Function output/parameters: destination array (StudentDataType)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: deepCopy
*/
void copyArray(StudentDataType dest[], const StudentDataType src[], int size)
{
    // initialize variables
    int index;

    for (index = 0; index < size; index++)
    {
        deepCopy(&dest[index], src[index]);
    }
}

/*
Name: deepCopy
Process: copies all individual values from StudentDataType source
Function input/parameters: source element (const StudentDataType)
Function output/parameters: pointer to destination value (StudentDataType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: strcpy
*/
void deepCopy(StudentDataType* dest, const StudentDataType src)
{
    // initialize variables

    // copy over data
    strcpy(dest->name, src.name);
    dest->gender = src.gender;
    dest->gpa = src.gpa;
    dest->studentId = src.studentId;
}

/*
Name: displayData
Process: displays comma-delimited element data in array if array is not empty,
         otherwise displays "Data not found - Display aborted",
         allows for subtitle to be added to "Display Data - "
Function input/parameters: student data array (const StudentDataType []),
                           size (int), subtitle (const char *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: data displayed as specified
Dependencies: printf
*/
void displayData(const StudentDataType array[],
    int size, const char* subTitle)
{
    // initialize variables
    int index;

    // check that size isn't zero
    if (size <= 0)
    {
        printf("Data not found - Display aborted\n");

        // leave function
        return 0;
    }

    // otherwise start printing data
    printf("Display Data - %s\n", subTitle);
    for (index = 0; index < size; index++)
    {
        printf("[ %2d ]: %s, %c, %d, %f\n",
            index, array[index].name, array[index].gender,
            array[index].studentId, array[index].gpa);
    }

    // just to make sure the next thing printed is on a new line
    printf("\n")
}

/*
Name: findElement
Process: finds element value in array if it is there,
         saves data in parameter value and returns true,
         otherwise sets data in parameter to empty and returns false,
         must use name as the key
Function input/parameters: student data array (const StudentDataType []),
                           size (int), search value (const StudentDataType)
Function output/parameters: value if found, 
                            otherwise, value set to empty (StudentDataType *)
Function output/returned: Boolean result of operation
Device input/---: none
Device output/---: none
Dependencies: strcmp, deepCopy, setEmptyElementData
*/
bool findElement(StudentDataType* foundElement,
    const StudentDataType array[], int size, const StudentDataType searchValue)
{
    // initialize variables
    int index;

    // loop through array
    for (index = 0; index < size; index++)
    {
        // check if names are same
        if (strcmp(array[index].name, searchValue.name) == 0)
        {
            deepCopy(&foundElement, array[index]);

            return true;
        }
    }

    // not found set foundElement to empty
    setEmptyElementData(*foundElement);
    return false;
}

/*
Name: getFileName
Process: prompts user for file name, captures file name, 
         returns as parameter
Function input/parameters: none
Function output/parameters: captured file name (char *)
Function output/returned: none
Device input/keyboard: user data entry
Device output/monitor: user prompt as specified
Dependencies: printf, scanf
*/
void getFileName(char* fileName)
{
    // get file name
    printf("Enter file name: ");
    scanf("%s", filename);

    // goto new line
    printf("\n");
}

/*
Name: removeElement
Process: searches for element, if found, sets data into parameter value,
         shifts all remaining data down, and returns true,
         otherwise sets data in parameter to empty and returns false
Function input/parameters: student data array (StudentDataType []),
                           size (int), search value (const StudentDataType)
Function output/parameters: updated student data array (StudentDataType []),
                            value if found and removed, 
                            otherwise, value set to empty (StudentDataType *),
                            updated size (int *)
Function output/returned: Boolean result of operation as specified
Device input/---: none
Device output/---: none
Dependencies: strcmp, deepCopy, setEmptyElementData
*/
bool removeElement(StudentDataType* removedElement,
    StudentDataType array[], int* size, const StudentDataType searchVal)
{
    // initialize variables
    int index;

    // loop through to find value
    for (index = 0; index < *size; index++)
    {
        // check if value found, using name as key like in findElement
        if (strcmp(array[index].name = searchVal.name))
        {
            // value found thus remove it
            deepCopy(&removedElement, array[index]);

            // shift remaining data down
            for (index = 0; index < *size; index++)
            {
                array[index] = array[index + 1];
            }
            
            // set last value to empty
            setEmptyElementData(array[*size - 1]);

            // decrement size
            (*size)--;

            // return true
            return true;
        }
    }

    // value not found thus set removedElement to empty
    setEmptyElementData(*removedElement);
    return false;
}

/*
Name: runBubbleSort
Process: sorts data using bubble sort algorithm
Function input/parameters: student data array (StudentDataType []), size (int)
Function output/parameters: updated student data array (StudentDataType [])
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: strcmp, swapElements
*/
void runBubbleSort(StudentDataType array[], int size)
{
    // initialize vairbales
    int index = 0;
    bool swapped = true;

    // loop until there are no swaps in a runthrough
    while (swapped)
    {
        // set boolean to false
        swapped = false;

        // loop until next to last item
        while (index < size - 1)
        {
            // check if first greater than second (compare names)
            if (strcmp(array[index].name, array[index + 1].name < 0))
            {
                // swap them
                swapElements(array[], index, index + 1);

                // set swapped to true
                // this lets the function know there was a swap and it has to
                // do another run through
                swapped = true;
            }

            // increment index
            index++;
        }
        // end of loop, if there was a swap however the function will loop through again
    }
    // end of all swapping should be sorted
}

/*
Name: runInsertionSort
Process: sorts data using insertion sort algorithm
Function input/parameters: student data array (StudentDataType []), size (int)
Function output/parameters: updated student data array (StudentDataType [])
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: deepCopy, strcmp
*/
void runInsertionSort(StudentDataType array[], int size)
{
    // initialize variables
    int searchIndex, listIndex;
    StudentDataType temp;

    // loop across array starting at element 2
    while (listIndex < size)
    {
        // store data at listIndex into temp
        deepCopy(&temp, array[listIndex]);

        // start at index given by outer loop
        searchIndex = listIndex;

        // loop while not at bottom and while
        // test is less than item in slot below
        while (searchIndex > 0 &&
            strcmp(temp.name, array[searchIndex - 1].name))
        {
            // copy item below to the present
            deepCopy(&array[searchIndex], array[searchIndex - 1]);

            // decrement search index
            searchIndex--;
        }
        // end insertion loop

        // insert the character
        deepCopy(&array[searchIndex], temp);

        // increment list index
        listIndex++;
    }
    // end of list loop
    // list should be sorted
}

/*
Name: runSelectionSort
Process: sorts data using selection sort algorithm
Function input/parameters: student data array (StudentDataType []), size (int)
Function output/parameters: updated student data array (StudentDataType [])
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: strcmp, swapElements
*/
void runSelectionSort(StudentDataType array[], int size)
{
    // initialize variables
    int listIndex, lowIndex, curIndex;
    StudentDataType temp;

    // loop across array
    for (listIndex = 0; listIndex < size; listIndex++)
    {
        // set initial temp to first element to be searched
        lowIndex = listIndex;

        // loop across list from current to end
        for (curIndex = listIndex + 1;
            curIndex < size; curIndex++)
        {
            // check if current is less than temp
            if (strcmp(array[curIndex].name, arry[lowIndex].name) < 0)
            {
                // set temp to val at curIndex
                lowIndex = curIndex;
            }
        }
        // end search loop

        // swap item at present position
        // with the item at lowest index
        swapElements(array[], listIndex, lowIndex);
    }
    // end of looping
    // list should be sorted
}

/*
Name: setEmptyElementData
Process: sets student data type to empty or default values
Function input/parameters: none
Function output/parameters: student data value (StudentDataType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: none
*/
void setEmptyElementData(StudentDataType* element)
{
    // initialize variables

    // start setting things to empty
    // I know it says dependencies none but I wouldn't know how to do so
    // without the help of strcpy
    element->name[0] = "\0";
    element->gender = "\0";
    element->studentId = 0;
    element->gpa = 0.0;
}

/*
Name: showTitle
Process: displays program title with thick underline,
         "Data Management with N-Squared Sorting"
Function input/parameters: none
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: displays title as specified
Dependencies: printf
*/
void showTitle()
{
    // initialize variables
    int index;
    int length = 38;

    printf("Data Management with N-Squared Sorting\n");
    for (index = 0; index < length; index++)
    {
        printf("%c", '=')
    }
    printf('\n');
}

/*
Name: swapElements
Process: swaps elements within an array
Function input/parameters: left and right indices to be swapped
Function output/parameters: updated array with swapped values 
                           (StudentDataType [])
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: deepCopy
*/
void swapElements(StudentDataType array[], int leftIndex, int rightIndex)
{
    // initialize variables
    StudentDataType temp;
    deepCopy(&temp, array[leftIndex);
    deepCopy(&array[leftIndex], array[rightIndex]);
    deepCopy(&array[rightIndex], temp);
}

/*
Name: uploadStudentData
Process: uploads data from given file to student data array,
         returns number of items found;
         stops uploading process if array shows full
Function input/parameters: capacity (int) and file name (const char *)
Function output/parameters: updated array with uploaded values 
                           (StudentDataType [])
Function output/returned: number of items uploaded (int)
Device input/---: none
Device output/---: none
Dependencies: openInputFile, readStringToDelimiterFromFile,
              checkForEndOfInputFile, readIntegerFromFile, 
              readCharacterFromFile, readDoubleFromFile,
              addElementWithData, closeInputFile
*/
int uploadStudentData(StudentDataType studentDataArray[],
    int capacity, const char* fileName)
{
    char inputName[STD_STR_LEN];
    int inputStudentId, size = 0;
    char inputGender;
    double inputGpa;
    bool notFull = true;

    if (openInputFile(fileName))
    {
        // read prime
        readStringToDelimiterFromFile(SEMI_COLON, inputName);

        while (!checkForEndOfInputFile() && notFull)
        {
            inputStudentId = readIntegerFromFile();
            readCharacterFromFile();

            inputGender = readCharacterFromFile();
            readCharacterFromFile();

            inputGpa = readDoubleFromFile();

            notFull = addElementWithData(studentDataArray, &size, capacity,
                inputName, inputGender, inputStudentId, inputGpa);

            // read re-prime
            readStringToDelimiterFromFile(SEMI_COLON, inputName);
        }

        closeInputFile();
    }

    return size;
}

#endif   // STUDENT_UTILITIES_H
#ifndef STUDENT_UTILITIES_H
#define STUDENT_UTILITIES_H

// header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "File_Input_Utility.h"
#include "StandardConstants.h"

// data structures
typedef struct StudentDataStruct
{
    char name[STD_STR_LEN];

    char gender;

    int studentId;

    double gpa;
} StudentDataType;

typedef struct StudentArrayStruct
{
    StudentDataType* array;

    int size;

    int capacity;
} StudentArrayType;

// Prototypes

/*
Name: addElementWithData
Process: adds all individual data values to the StudentArrayType ADT,
         always checks for resize prior to adding the value
Function input/parameters: pointer to data array type (StudentArrayType *),
                           student name (const char *),
                           student gender (char),
                           student ID (int),
                           student gpa (double)
Function output/parameters: updated pointer to data array (StudentArrayType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: checkForResize, strcpy
*/
void addElementWithData(StudentArrayType* adtArray, const char* name,
    char gender, int studentId, double gpa)
{
    // initialize variables

    // check if array is full
    checkForResize(adtArray);

    // add data values to the array
    strcpy(adtArray->array[adtArray->size].name, name);
    adtArray->array[adtArray->size].gender = gender;
    adtArray->array[adtArray->size].studentId = studentId;
    adtArray->array[adtArray->size].gpa = gpa;

    // increment size
    adtArray->size++;
}

/*
Name: addElementFromElement
Process: adds data from element to the StudentArrayType ADT,
         uses supporting function
Function input/parameters: pointer to data array type (StudentArrayType *),
                           size and capacity (int),
                           source element (const StudentDataType)
Function output/parameters: pointer to updated array type (StudentArrayType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: addElementWithData - function uses one code statement
*/
void addElementFromElement(StudentArrayType* adtArray,
    const StudentDataType student)
{
    // initialize variables

    // call addElementWithData
    addElementWithData(adtArray, student.name, student.gender, 
        student.studentId, student.gpa);
}

/*
Name: checkForResize
Process: checks if array needs to be resized,
         resizes (increases capacity of) array to double capacity
Function input/parameters: pointer to student array ADT (StudentArrayType *)
Function output/parameters: updated pointer
                            to student array ADT (StudentArrayType *)
                            if resize has taken place,
                            otherwise ADT is unchanged
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: malloc, sizeof (C keyword), deepCopy, free
*/
void checkForResize(StudentArrayType* adtArray)
{
    // initialize variables
    StudentDataType* newArray;
    int newCapacity;
    int index;

    // check if size is equal to capacity
    if (adtArray->size >= adtArray->capacity)
    {
        // set newCapacity to 2* old
        newCapacity = adtArray->capacity * 2;

        // allocate space to new array
        newArray = (StudentArrayType*)malloc(newCapacity * sizeof(StudentArrayType));

        // loop through old array
        for (index = 0; index < adtArray->size; index++)
        {
            // copy each element
            newArray[index] = deepCopy(&adtArray->array[index]);
        }

        // free old array
        free(adtArray->array);
        
        // set ptr's array and capacity to newArray and newCapacity
        adtArray->capacity = newCapacity;
        adtArray->array = newArray;
    }
    // return ptr
    return adtArray;
}

/*
Name: clearStudentArrayType
Process: returns allocated memory for both StudentArrayType ADT
         and encapsulated StudentDataType back to operating system,
         returns NULL to calling function
Function input/parameters: pointer to student array ADT (StudentArrayType *)
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: free
*/
StudentArrayType* clearStudentArrayType(StudentArrayType* arrayPtr)
{
    // initialize variables

    // free the array
    free(arrayPtr->array);

    // free the ptr
    free(arrayPtr);

    // set ptr to null
    arrayPtr = NULL;

    // return ptr(null)
    return arrayPtr;
}

/*
Name: copyArrayType
Process: copies elements from one StudentArrayType ADT to another,
         resets array size as needed,
         also resets array capacity as needed if destination array type
         capacity is less than capacity of source StudentArrayType ADT
Function input/parameters: source array type(const StudentArrayType)
Function output/parameters: pointer to destination array type
                                                            (StudentArrayType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: checkForResize, deepCopy
*/
void copyArrayType(StudentArrayType* dest, const StudentArrayType src)
{
    // initialize variables
    int index;

    // set dest size to 0
    dest->size = 0;

    // loop through src array
    for (index = 0; index < src.size; index++)
    {
        // check for resize before adding data
        checkForResize(dest);

        // copy data
        deepCopy(&dest->array[index], src.array[index]);
        
        // increment size
        dest->size++;
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

    // start copying stuff over
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
Function input/parameters: student array type (const StudentArrayType),
                           subtitle (const char *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: data displayed as specified
Dependencies: printf
*/
void displayData(const StudentArrayType adtArray, const char* subTitle)
{
    // initialize variables
    int index;

    // check that size isn't zero
    if (adtArray.size <= 0)
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
            index, adtArray.array[index].name, adtArray.array[index].gender,
            adtArray.array[index].studentId, adtArray.array[index].gpa);
    }

    // just to make sure the next thing printed is on a new line
    printf("\n")
}

/*
Name: findElement
Process: finds element value in StudentArrayType ADT if it is there,
         saves data in parameter value and returns true,
         otherwise sets data in parameter to empty and returns false
Function input/parameters: student array type (const StudentArrayType),
                           search value (const StudentDataType)
Function output/parameters: value if found,
                            otherwise, value set to empty (StudentDataType *)
Function output/returned: Boolean result of operation
Device input/---: none
Device output/---: none
Dependencies: strcmp, deepCopy, setEmptyElementData
*/
bool findElement(StudentDataType* foundElement,
    const StudentArrayType adtArray, const StudentDataType searchValue)
{
    // initialize variables
    int index;

    // loop through array
    for (index = 0; index < adtArray.size; index++)
    {
        // check if value found
        if (strcmp(adtArray.array[index].name, searchValue.name) == 0)
        {
            // value found
            deepCopy(&foundElement, adtArray.array[index]);

            return true;
        }
    }

    // loop falls through value not found
    // set found to empty
    setEmptyElementData(foundElement);

    // return false
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
Name: initializeStudentArrayType
Process: dynamically creates StudentArrayType ADT instance
         along with dynamically allocating the array within it
Function input/parameters: given initial capacity (int)
Function output/parameters: none
Function output/returned: pointer to student type array (StudentArrayType *)
Device input/---: none
Device output/---: none
Dependencies: malloc, sizeof (C keyword)
*/
StudentArrayType* initializeStudentArrayType(int initialCapacity)
{
    // initialize function/variables
    StudentArrayType* temp;

    // create student array type instance
    temp = (StudentArrayType*)malloc(sizeof(StudentArrayType));

    // create array member of student array type
    temp->array = (StudentDataType*)malloc(initialCapacity * sizeof(StudentDataType);

    // set capacity
    temp->capacity = initialCapacity;

    // set size
    temp->size = 0;

    // return pointer
    return temp;
}

/*
Name: removeElement
Process: searches for element, if found, sets data into parameter value,
         shifts all remaining elements down, and returns true,
         otherwise sets data in parameter to empty and returns false
Function input/parameters: pointer to student array type (StudentArrayType *),
                           search value (const StudentDataType)
Function output/parameters: updated pointer to student array type
                            (StudentArrayType *),
                            value if found and removed,
                            otherwise, value set to empty (StudentDataType *)
Function output/returned: Boolean result of operation as specified
Device input/---: none
Device output/---: none
Dependencies: strcmp, deepCopy, setEmptyElementData
*/
bool removeElement(StudentDataType* removedElement,
    StudentArrayType* adtArray, const StudentDataType searchVal)
{
    // initialize variables
    int index;
    int wkgIndex;

    // loop across array
    for (index = 0; index < adtArray->size; index++)
    {
        // check for value found
        if (strcmp(adtArray->array[index].name, searchVal.name) == 0)
        {
            // value found
            // copy to removedElement
            deepCopy(&removedElement, adtArray->array[index]);

            // loop from index of found element till end
            for (wkgIndex = index; wkgIndex < adtArray->size; wkgIndex++)
            {
                // start shifting elements to the left
                deepCopy(&adtArray->array[wkgIndex], adtArray->array[wkgIndex + 1]);
            }
            // decrement size
            adtArray->size--;

            // return true
            return true;
        }
    }

    // assume val not found
    // set removedElement to empty
    setEmptyElementData(&removedElement);

    // return false
    return false;
}

/*
Name: runMerge
Process: merges StudentArrayType ADT subsets brought in between a low, middle,
         and high index segment of the StudentArrayType ADT,
         must dynamically create (and release) one internal array
         must use three array transfer loops
Function input/parameters: pointer to student array type (StudentArrayType *),
                           low index, middle index, high index (int)
Function output/parameters: pointer to updated student array type
                                                            (StudentArrayType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: malloc, sizeof (C keyword), deepCopy, free
*/
void runMerge(StudentArrayType* adtArray,
    int lowIndex, int middleIndex, int highIndex)
{
    // initialize variables
    int leftIndex, rightIndex, wkgIndex;

    // First, using the index parameters, find the capacity needed
    // for the local array and create the array
    // Only one array is created
    int lclArrCap = highIndex - lowIndex + 1;
    StudentArrayType* lclArr = (StudentArrayType* malloc(lclArrCap * sizeof(StudentArrayType));

    // Next, load the data from the source (parameter) array
    // (between the two indices, inclusive)
    // into the newly created local array
    for (wkgIndex = 0; wkgIndex < lclArrCap; wkgIndex++)
    {
        deepCopy(&lclArr->array[wkgIndex] = adtArray->array[lowIndex + wkgIndex]);
    }

    // Next, calculate the indices necessary to start and end
    // at the left side group and to start and end
    // at the right side group
    leftIndex = lowIndex;
    rightIndex = middleIndex + 1;
    wkgIndex = 0;

    // Loop until either the left or right side group is out of values
    // (first of three loops)
    while (leftIndex <= middleIndex && rightIndex <= highIndex)
    {
        // check if the first available value in the left group
        // is less than the first avaliable value in the right group
        if (strcmp(adtArray->array[leftIndex].name, 
            adtArray->array[rightIndex].name) < 0)
        {
            // assign the first available left value
            // to the source array's first available element
            deepCopy(&lclArr->array[wkgIndex], adtArray->array[leftIndex]);

            // increment the left group index
            leftIndex++;
        }

        // otherwise, assume the right group's first available value
        // is less
        else
        {
            // assign the first available right value
            // to the source array's first available element
            deepCopy(&lclArr->array[wkgIndex], adtArray->array[rightIndex]);

            // increment the right group index
            rightIndex++;
        }
        // increment the index for the source array
        wkgIndex++;
    }
    // end comparison loop

    // Loop until the left side group is out of values
    // (second of three loops)
    while (leftIndex <= middleIndex)
    {
        // assign the first available left value
        // to the source array's first available element
        deepCopy(&adtArray->array[leftIndex], lclArr->array[wkgIndex]);

        // increment the left group index
        leftIndex++;

        // increment the source array's index
        wkgIndex++;
    }
    // end left side clean out loop

    // Loop until the right side group is out of values
    // (third of three loops)
    while (rightIndex <= highIndex)
    {
        // assign the first right value to the source array's
        // first available element
        deepCopy(&adtArray->array[rightIndex], lclArr->array[wkgIndex]);

        // increment the right group index
        rightIndex++;

        // increment the source array's index
        wkgIndex++;
    }
    // end right side clean out loop

    free(lclArr);
}

/*
Name: runMergeSort
Process: sorts StudentArrayType ADT using merge sort algorithm,
         calls helper function with appropriate indices
Function input/parameters: pointer to student array type (StudentArrayType *)
Function output/parameters: pointer to updated student array type
                                                            (StudentArrayType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: runMergeSortHelper
*/
void runMergeSort(StudentArrayType* adtArray)
{
    // check ptr is not null
    if (adtArray == NULL)
    {
        return NULL;
    }

    // call runMergeSortHelper with 0 as low and size-1 as high
    runMergeSortHelper(adtArray->array, 0, adtArray->size - 1);
}

/*
Name: runMergeSortHelper
Process: recursively breaks given StudentArrayType ADT segments down
         to smaller segments between lowIndex and highIndex (inclusive),
         then sorts data using merge operation for segments created
Function input/parameters: pointer to student array type (StudentArrayType *),
                           low & high inclusive indices (int)
Function output/parameters: pointer to updated student array type
                                                            (StudentArrayType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: runMergeSortHelper (recursively), runMerge
*/
void runMergeSortHelper(StudentArrayType* adtArray,
    int lowIndex, int highIndex)
{
    // initialize varaibles
    int midIndex;

    // check that low is less than high
    if (lowIndex < highIndex)
    {
        midIndex = (lowIndex + highIndex) / 2;

        // recurse left
        runMergeSortHelper(adtArray, lowIndex, midIndex);

        // recurse right
        runMergeSortHelper(adtArray, midIndex + 1, highIndex);

        runMerge(adtArray, lowIndex, midIndex, highIndex);
    }
}

/*
Name: runPartition
Process: partitions StudentArrayType ADT
         must use the first value as the partition value;
         when this function is complete the partition value is
         in the correct location in the array;
         main loop must iterate from left to right
Function input/parameters: pointer to student array type (StudentArrayType *)
Function output/parameters: pointer to updated student array type
                                                            (StudentArrayType *)
Function output/returned: partition value index within array
Device input/---: none
Device output/---: none
Dependencies: strcmp, swapElements
*/
int runPartition(StudentArrayType* adtArray, int lowIndex, int highIndex)
{
    // Identify the partition value at the beginning
    // of the array segment (at lowIndex)
    char* pivotValue;
    strcpy(pivotValue, adtArray->array[lowIndex].name);
    StudentDataType* temp;

    // set the working index and the pivot index
    // to the low index parameter
    int pivotIndex = lowIndex;
    int wkgIndex = lowIndex;

    // Start a loop across the the array segment
    // from the low index to the high index, inclusive
    // This will use the working index
    while (wkgIndex <= highIndex)
    {
        // check if the value at the current working index
        // is less than the original pivot value
        if (strcmp(adtArray->array[wkgIndex].name, pivotValue) < 0)
        {
            // increment the pivot index
            pivotIndex++;

            // swap the value at the working index
            // with the value at the pivot index
            deepCopy(&temp, adtArray->array[pivotIndex]);
            deepCopy(&adtArray->array[pivotIndex], adtArray->array[wkgIndex]);
            deepCopy(&adtArray->array[wkgIndex], temp);
        }
    }
    // end working loop 

    // Swap the original pivot value (at the low index)
    // with the value at the current pivot index
    deepCopy(&temp, adtArray->array[pivotIndex]);
    deepCopy(&adtArray->array[pivotIndex], adtArray->array[lowIndex]);
    deepCopy(&adtArray->array[lowIndex], temp);

    // return the pivot index
    return pivotIndex;
}

/*
Name: runQuickSort
Process: sorts StudentArrayType ADT using quick sort algorithm,
         calls helper with appropriate indices to implement sort
Function input/parameters: pointer to student array type (StudentArrayType *)
Function output/parameters: pointer to updated student array type
                                                            (StudentArrayType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: runQuickSortHelper
*/
void runQuickSort(StudentArrayType* adtArray)
{
    runQuickSortHelper(adtArray, 0, adtArray->size - 1);
}

/*
Name: runQuickSortHelper
Process: helper function run with parameters that partition arrays
         on a given (first) element of an array segment,
         then recursively sort left and right sides of given partition value
Function input/parameters: pointer to student array type (StudentArrayType *)
         low & high inclusive indices (int)
Function output/parameters: pointer to updated student array type
                                                            (StudentArrayType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: runPartition, runQuickSortHelper (recursively)
*/
void runQuickSortHelper(StudentArrayType* adtArray,
    int lowIndex, int highIndex)
{
    // initialize variables
    int pivotIndex;

    // check if lowIndex less than highIndex
    if (lowIndex < highIndex)
    {
        pivotIndex = runPartition(adtArray, lowIndex, highIndex);
        runQuickSortHelper(adtArray, lowIndex, pivotIndex);
        runQuickSortHelper(adtArray, pivotIndex + 1, highIndex);
    }
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
    element->name[0] = "NULL_CHAR";
    element->gender = "x";
    element->studentId = 0;
    element->gpa = 0.0;
}

/*
Name: showTitle
Process: displays program title with thick underline,
         "Data Management with Log2N Sorting"
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

    printf("Data Management with Log2N Sorting\n");
    for (index = 0; index < length; index++)
    {
        printf("%c", '=')
    }
    printf('\n');
}

/*
Name: swapElements
Process: swaps elements within a StudentArrayType ADT array
Function input/parameters: left and right indices to be swapped
Function output/parameters: updated array with swapped values
                                                            (StudentArrayType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: deepCopy
*/
void swapElements(StudentArrayType* adtArray, int leftIndex, int rightIndex)
{
    // initialize variables
    StudentDataType temp;
    deepCopy(&temp, adtArray->array[leftIndex]);
    deepCopy(&adtArray->array[leftIndex], adtArray->array[rightIndex]);
    deepCopy(&adtArray->array[rightIndex], temp);
}

/*
Name: uploadStudentData
Process: uploads data from given file to StudentArrayType ADT,
         returns true if succesful upload, false otherwise
Function input/parameters: file name (const char *)
Function output/parameters: StudentArrayType ADT with uploaded values
                                                            (StudentArrayType *)
Function output/returned: Boolean result of operation as specified
Device input/---: none
Device output/---: none
Dependencies: openInputFile, readStringToDelimiterFromFile,
              checkForEndOfInputFile, readIntegerFromFile,
              readCharacterFromFile, readDoubleFromFile,
              addElementWithData, closeInputFile
*/
bool uploadStudentData(StudentArrayType* adtArray, const char* fileName)
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

        return true;
    }

    return false;
}

#endif   // STUDENT_UTILITIES_H
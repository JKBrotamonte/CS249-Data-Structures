#ifndef STUDENT_DATA_ENGINE_ARRAY_H
#define STUDENT_DATA_ENGINE_ARRAY_H

// header files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "StandardConstants.h"

// data structures
typedef struct StudentDataStruct
   {
    char name[ STD_STR_LEN ];

    char gender;

    int studentId;

    double gpa;
   } StudentDataType;

typedef struct StudentArrayStruct
   {
    StudentDataType *array;

    int size;

    int capacity;
   } StudentArrayType;

// file level constants
typedef enum { BEFORE_LOCATION, AT_LOCATION, AFTER_LOCATION } LocationCodeType;

// Prototypes

/*
Name: arrayIsEmpty
Process: returns true if list is empty, false otherwise
Function input/parameters: student array type (const StudentArrayType)
Function output/parameters: none
Function output/returned: Boolean result of test as specified
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool arrayIsEmpty(const StudentArrayType array)
{
    // initialize variables

    // check if ptr to array is null
    if (array.array != NULL)
    {
        // return false
        return false;
    }

    // return true
    return true;
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
Dependencies: malloc, sizeof (C keyword), deepCopyElement, free
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
            newArray[index] = deepCopyElement(&adtArray->array[index]);
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
Name: clearArray
Process: deallocates memory for both StudentArrayType ADT
         and encapsulated StudentDataType array,
         returns NULL to calling function
Function input/parameters: pointer to student array ADT (StudentArrayType *)
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: free
*/
StudentArrayType* clearArray(StudentArrayType* arrayPtr)
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
Name: copyArray
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
Dependencies: checkForResize, deepCopyElement
*/
void copyArray(StudentArrayType* dest, const StudentArrayType src)
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
        deepCopyElement(&dest->array[index], src.array[index]);

        // increment size
        dest->size++;
    }
}

/*
Name: deepCopyElement
Process: copies all member values from StudentDataType source
Function input/parameters: source element (const StudentDataType)
Function output/parameters: pointer to destination value (StudentDataType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: strcpy
*/
void deepCopyElement(StudentDataType* dest, const StudentDataType src)
{
    // initialize variables

    // start copying stuff over
    strcpy(dest->name, src.name);
    dest->gender = src.gender;
    dest->gpa = src.gpa;
    dest->studentId = src.studentId;
}

/*
Name: displayArrayData
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
void displayArrayData(const StudentArrayType adtArray, const char* subTitle)
{
    // initialize variables
    int index;

    // check that size isn't zero
    if (adtArray.size <= 0)
    {
        printf("Data not found - Display aborted\n");
    }

    else
    {
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
}

/*
Name: getElementAtLocation
Process: checks for index within bounds,
         acquires and returns the value as a parameter,
         and returns true,
         otherwise sets data in parameter to empty and returns false
Function input/parameters: student array type (const StudentArrayType),
                           list location (int)
Function output/parameters: value if found,
                            otherwise, value set to empty (StudentDataType *)
Function output/returned: Boolean result of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: deepCopyElement, setEmptyElementData
*/
bool getElementAtLocation(StudentDataType* returnVal,
    const StudentArrayType adtArray, int listLocation)
{
    // initialize variables
    
    // check if listLocation is within array
    if (listLocation <= adtArray.size)
    {
        // value found
        deepCopyElement(&returnVal, adtArray.array[listLocation]);
        
        // return value and true
        return true;
    }

    // loop falls through value not found
    // set found to empty
    setEmptyElementData(returnVal);

    // return false
    return false;
}

/*
Name: initializeArray
Process: dynamically creates StudentArrayType ADT instance
         along with dynamically allocating the array within it
Function input/parameters: given initial capacity (int)
Function output/parameters: none
Function output/returned: pointer to student array type ADT (StudentArrayType *)
Device input/---: none
Device output/---: none
Dependencies: malloc, sizeof (C keyword)
*/
StudentArrayType* initializeArray(int initialCapacity)
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
Name: insertArrayAdtDataAfterLocation
Process: verifies location within bounds,
         inserts individual data values to the StudentArrayType ADT
         after a specified zero-based location,
         always checks for resize prior to adding the value,
         moves all data up from insertion point, returns true
         if location not within bounds, returns false
Function input/parameters: data array type (StudentArrayType *),
                           student data (const StudentDataType),
                           list location (int)
Function output/parameters: pointer to updated data array (StudentArrayType *)
Function output/returned: success of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertArrayRawDataEngine (one line of code)
*/
bool insertArrayAdtDataAfterLocation(StudentArrayType* adtArray,
    const StudentDataType student, int listLocation)
{
    return insertArrayRawDataEngine(adtArray, student.name, student.gender, 
        student.studentId, student.gpa, listLocation, AFTER_LOCATION);
}

/*
Name: insertArrayAdtDataBeforeLocation
Process: verifies location within bounds,
         inserts source ADT to the StudentArrayType ADT
         prior to a specified zero-based location,
         always checks for resize prior to adding the value,
         moves all data up from insertion point, returns true
         if location not within bounds, returns false
Function input/parameters: data array type (StudentArrayType *),
                           student data (const StudentDataType),
                           list location (int)
Function output/parameters: pointer to updated data array (StudentArrayType *)
Function output/returned: success of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertArrayRawDataEngine (one line of code)
*/
bool insertArrayAdtDataBeforeLocation(StudentArrayType* adtArray,
    const StudentDataType student, int listLocation)
{
    return insertArrayRawDataEngine(adtArray, student.name, student.gender,
        student.studentId, student.gpa, listLocation, BEFORE_LOCATION);
}

/*
Name: insertArrayRawDataEngine
Process: verifies location within bounds,
         inserts individual data values to the StudentArrayType ADT
         switchably after, at, or before a specified zero-based location,
         always checks for resize prior to adding the data,
         for insertion before or after, moves all data up from insertion point,
         for insertion at, overwrites value at that location, returns true
         if location not within bounds, returns false,
         Note: Used as engine for other set and insert operations
Function input/parameters: data array type (StudentDataType *),
                           student name (const char *),
                           student gender (char),
                           student ID (int),
                           student gpa (double),
                           list location (int),
                           after/at/before selection (LocationCodeType)
Function output/parameters: pointer to updated data array (StudentArrayType *)
Function output/returned: success of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: checkForResize, deepCopyElement, strcpy
*/
bool insertArrayRawDataEngine(StudentArrayType* adtArray,
    const char* name, char gender, int studentId, double gpa,
    int listLocation, LocationCodeType locCode)
{
    // initialize variables
    int index;

    // check for resize 
    checkForResize(adtArray);

    // if( ( greater than or equal to zero AND less than size )
    //   OR ( check for location zero AND not at location ) )
    if ((listLocation >= 0 && listLocation < adtArray->size)
        || (listLocation == 0 && locCode != AT_LOCATION))
    {
        // check for after location AND check for size not equal to zero
        if (locCode == AFTER_LOCATION && adtArray->size != 0)
        {
            // increment listLoc
            listLocation++;
        }

        // check for not at location
        if (locCode != AT_LOCATION)
        {
            // loop from size down to location
            for (index = adtArray->size - 1; index >= listLocation; index--)
            {
                // assign value from one below to current
                deepCopyElement(&adtArray->array[index + 1], adtArray->array[index])
            }
            // end loop
        }

        // assign data
        strcpy(adtArray->array[listLocation].name, name);
        adtArray->array[listLocation].gender = gender;
        adtArray->array[listLocation].gpa = gpa;
        adtArray->array[listLocation].studentId = studentId;

        return true;
    }

    return false;
}

/*
Name: insertArrayRawDataAfterLocation
Process: verifies location within bounds,
         inserts individual data values to the StudentArrayType ADT
         after a specified zero-based location,
         always checks for resize prior to adding the value,
         moves all data up from insertion point, returns true
         if location not within bounds, returns false
Function input/parameters: data array type (StudentDataType *),
                           student name (const char *),
                           student gender (char),
                           student ID (int),
                           student gpa (double),
                           listLocation (int)
Function output/parameters: pointer to updated data array (StudentArrayType *)
Function output/returned: success of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertArrayRawDataEngine (one line of code)
*/
bool insertArrayRawDataAfterLocation(StudentArrayType* adtArray,
    const char* name, char gender, int studentId,
    double gpa, int listLocation)
{
    return insertArrayRawDataEngine(adtArray, name, gender,
        studentId, gpa, listLocation, AFTER_LOCATION);
}

/*
Name: insertArrayRawDataBeforeLocation
Process: verifies location within bounds,
         inserts individual data values to the StudentArrayType ADT
         prior to a specified zero-based location,
         always checks for resize prior to adding the value,
         moves all data up from insertion point, returns true
         if location not within bounds, returns false
Function input/parameters: data array type (StudentDataType *),
                           student name (const char *),
                           student gender (char),
                           student ID (int),
                           student gpa (double),
                           listLocation (int)
Function output/parameters: pointer to updated data array (StudentArrayType *)
Function output/returned: success of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertArrayRawDataEngine (one line of code)
*/
bool insertArrayRawDataBeforeLocation(StudentArrayType* adtArray, const char* name,
    char gender, int studentId, double gpa, int listLocation)
{
    return insertArrayRawDataEngine(adtArray, name, gender,
        studentId, gpa, listLocation, BEFORE_LOCATION);
}

/*
Name: removeArrayDataAtLocation
Process: checks for index in bounds,
         sets found data to returned variable,
         shifts all remaining elements down, and returns true,
         otherwise sets data in parameter to empty and returns false
Function input/parameters: pointer to student array type (StudentArrayType *),
                           search index (int)
Function output/parameters: updated pointer to student array type
                            (StudentArrayType *),
                            value if found and removed,
                            otherwise, value set to empty (StudentDataType *)
Function output/returned: Boolean result of operation as specified (bool)
Device input/---: none
Device output/---: none
Dependencies: deepCopyElement, setEmptyElementData
*/
bool removeArrayDataAtLocation(StudentDataType* removedElement,
    StudentArrayType* adtArray, int removeIndex)
{
    // initialize variables
    int index;

    // check for index in bounds
    if (removeIndex <= adtArray->size)
    {
        // value found
        // copy to removedElement
        deepCopyElement(&removedElement, adtArray->array[removeIndex]);
        // loop from index of found element till end
        for (index = removeIndex; index < adtArray->size; index++)
        {
            // start shifting elements to the left
            deepCopyElement(&adtArray->array[index], adtArray->array[index + 1]);
        }
        // decrement size
        adtArray->size--;

        // return true
        return true;
    }

    // assume val not found
    // set removedElement to empty
    setEmptyElementData(&removedElement);

    // return false
    return false;
}

/*
Name: setArrayAdtDataAtLocation
Process: verifies location within bounds,
         overwrites Adt data in the StudentArrayType ADT
         at a specified zero-based location,
         always checks for resize prior to adding the value, returns true
         if location not within bounds, returns false
Function input/parameters: data array type (StudentArrayType *),
                           student data (const StudentDataType),
                           list location (int)
Function output/parameters: pointer to updated data array (StudentArrayType *)
Function output/returned: success of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertArrayRawDataEngine (one line of code)
*/
bool setArrayAdtDataAtLocation(StudentArrayType* adtArray,
    const StudentDataType student, int listLocation)
{
    return insertArrayRawDataEngine(adtArray, student.name, student.gender,
        student.studentId, student.gpa, listLocation, AT_LOCATION);
}

/*
Name: setArrayRawDataAtLocation
Process: verifies location within bounds,
         overwrites individual data values to the StudentArrayType ADT
         at a specified zero-based location,
         always checks for resize prior to adding the value, returns true
         if location not within bounds, returns false
Function input/parameters: data array type (StudentDataType *),
                           student name (const char *),
                           student gender (char),
                           student ID (int),
                           student gpa (double),
                           listLocation (int)
Function output/parameters: pointer to updated data array (StudentArrayType *)
Function output/returned: success of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertArrayRawDataEngine (one line of code)
*/
bool setArrayRawDataAtLocation( StudentArrayType *adtArray, const char *name,
                     char gender, int studentId, double gpa, int listLocation )
{
    return insertArrayRawDataEngine(adtArray, name, gender,
        studentId, gpa, listLocation, AFTER_LOCATION);

/*
Name: setEmptyElementData
Process: sets student data type members to empty or default values
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


#endif   // STUDENT_DATA_ENGINE_ARRAY_H
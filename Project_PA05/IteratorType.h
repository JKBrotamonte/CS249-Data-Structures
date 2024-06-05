#ifndef ITERATOR_TYPE_H
#define ITERATOR_TYPE_H

// header files
#include "ADT_StudentDataEngine_Array.h"

// Data structure(s)
typedef struct IteratorStruct
   {
    StudentArrayType *array;

    int currentIndex;
   } IteratorType;

// Prototypes

/*
Name: appendAdtDataAtEnd
Process: adds ADT data to end location of iterator
         and returns true if successful, otherwise returns false,
         no change to currentIndex
Function input/parameters: pointer to iterator (IteratorType *),
                           value to be added (const StudentDataType)
Function output/parameters: pointer to updated iterator (IteratorType *)
Function output/returned: Boolean result of the operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertArrayAdtDataAfterLocation
*/
bool appendAdtDataAtEnd(IteratorType* iterator,
    const StudentDataType student)
{
    // initialize variables

    // add student data to end of array
    return insertArrayAdtDataAfterLocation(iterator->array, student, iterator->array.size - 1);
}

/*
Name: appendRawDataAtEnd
Process: adds individual member data of ADT to end of iterator
         and returns true if successful, otherwise returns false,
         no change to current index
Function input/parameters: pointer to iterator (IteratorType *),
                           student name (const char *),
                           student gender (char),
                           student ID (int),
                           student gpa (double)
Function output/parameters: pointer to updated iterator (IteratorType *)
Function output/returned: Boolean result of the operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertArrayRawDataAfterLocation
*/
bool appendRawDataAtEnd(IteratorType* iterator, const char* name,
    char gender, int studentId, double gpa)
{
    return insertArrayRawDataAfterLocation(iterator->array, name, gender, studentId, gpa, iterator->array.size);
}

/*
Name: clearIterator
Process: deallocates memory for IteratorType,
         and for StudentArrayType within
Function input/parameters: pointer to iterator (IteratorType *)
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: free, clearArray
*/
IteratorType* clearIterator(IteratorType* iterator)
{
    clearArray(iterator->array);

    free(iterator);

    return iterator;
}

/*
Name: displayIterator
Process: displays iterator in order with current item in brackets,
         if list is empty, displays "Iterator Empty - No Data Displayed"
Function input/parameters: iterator (const Iterator)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: displayed as specified
Dependencies: iteratorIsEmpty, getElementAtLocation, printf
*/
void displayIterator(const IteratorType iterator)
{
    // initialize variables
    int index;
    StudentDataType* printVal;

    // check if list is empty
    if (iteratorIsEmpty(iterator))
    {
        printf("Iterator Empty - No Data Displayed\n");
    }

    else
    {
        // otherwise start printing data
        // loop through array
        for (index = 0; index < iterator.array.size; index++)
        {
            // get element at location
            getElementAtLocation(printVal, iterator.array, index);

            // check if index is currentIndex
            if (index == iterator.currentIndex)
            {
                // print with brackets surrounding name
                printf("[%s]; ", printVal.name);
            }

            else 
            {
                // otherwise just print name with no brackets
                printf("%s; ", printVal.name);
            }
        }

        // just to make sure the next thing printed is on a new line
        printf("\n");
    }
}

/*
Name: getAtCurrent
Process: if available, access data at current index and returns true,
         otherwise, returns false
Function input/parameters: iterator (const Iterator)
Function output/parameters: returned student data (StudentDataType *)
Function output/returned: Boolean result of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: getElementAtLocation
*/
bool getAtCurrent(StudentDataType* returnVal, const IteratorType iterator)
{
    // check if current index is within array size
    if (iterator.currentIndex >= 0 && iterator.currentIndex < iterator.array.size)
    {
        // get that element
        getElementAtLocation(returnVal, iterator.array, iterator.currentIndex);
    }
}

/*
Name: hasNext
Process: if it is possible for the current index to move forward in the array,
         and the array is not empty, returns true, otherwise returns false
Function input/parameters: iterator (const Iterator)
Function output/parameters: none
Function output/returned: Boolean result of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: iteratorIsEmpty
*/
bool hasNext(const IteratorType iterator)
{
    // check if array is empty or current is at end
    if (iterator.array == NULL || iterator->currentIndex >= iterator.array.size - 1)
    {
        return false;
    }

    return true;
}

/*
Name: hasPrev
Process: if it is possible for the current index to move backward in the array,
         and the array is not empty, returns true, otherwise returns false
Function input/parameters: iterator (const Iterator)
Function output/parameters: none
Function output/returned: Boolean result of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: iteratorIsEmpty
*/
bool hasPrev(const IteratorType iterator)
{
    // check if array is empty
    if (iterator.array == NULL)
    {
        return false;
    }

    // check if current is at beginning of array
    if (iterator.currentIndex == 0)
    {
        return false;
    }

    // checks fall through return true
    return true;
}

/*
Name: initializeIterator
Process: initializes iterator data as needed
         and initializes Student Data Engine
Function input/parameters: initial capacity (int)
Function output/parameters: none
Function output/returned: pointer to initialized iterator ADT (IteratorType *)
Device input/---: none
Device output/---: none
Dependencies: malloc, initializeArray
*/
IteratorType *initializeIterator( int initialCapacity )
{

    // create an IteratorType
    IteratorType* it = malloc stuff

        // initialize the array engine
        it->array = initializeArray(initialCapacity);

    // initialize the current index
    it->currentIndex = 0;

    return it;
}

/*
Name: insertAdtDataAtBeginning
Process: inserts ADT data at beginning location of iterator
         and returns true if successful, otherwise returns false,
         no change to current index
Function input/parameters: pointer to iterator (IteratorType *),
                           value to added (const StudentDataType)
Function output/parameters: pointer to updated iterator (IteratorType *)
Function output/returned: Boolean result of the operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertArrayAdtDataBeforeLocation
*/
bool insertAdtDataAtBeginning(IteratorType* iterator,
    const StudentDataType student)
{
    return insertArrayAdtDataBeforeLocation(iterator->array, student, 0);
}

/*
Name: insertAdtDataAtCurrent
Process: adds ADT data to current index location of iterator
         and returns true if successful, otherwise returns false,
         no change to current index
Function input/parameters: pointer to iterator (IteratorType *),
                           value to added (const StudentDataType)
Function output/parameters: pointer to updated iterator (IteratorType *)
Function output/returned: Boolean result of the operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertArrayDataAdtBeforeLocation
*/
bool insertAdtDataAtCurrent(IteratorType* iterator,
    const StudentDataType student)
{
    return insertArrayAdtDataBeforeLocation(iterator->array, student, iterator->currentIndex);
}

/*
Name: insertRawDataAtBeginning
Process: inserts individual member data of ADT to beginning location of iterator
         and returns true if successful, otherwise returns false,
         no change to current index
Function input/parameters: pointer to iterator (IteratorType *),
                           student name (const char *),
                           student gender (char),
                           student ID (int),
                           student gpa (double)
Function output/parameters: pointer to updated iterator (IteratorType *)
Function output/returned: Boolean result of the operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertArrayRawDataBeforeLocation
*/
bool insertRawDataAtBeginning(IteratorType* iterator, const char* name,
    char gender, int studentId, double gpa)
{
    return insertArrayRawDataBeforeLocation(iterator->array, name, gender, studentId, gpa, 0);
}

/*
Name: insertRawDataAtCurrent
Process: inserts individual member data of ADT at current location of iterator
         and returns true if successful, otherwise returns false,
         no change to current index
Function input/parameters: pointer to iterator (IteratorType *),
                           student name (const char *),
                           student gender (char),
                           student ID (int),
                           student gpa (double)
Function output/parameters: pointer to updated iterator (IteratorType *)
Function output/returned: Boolean result of the operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertArrayRawDataBeforeLocation
*/
bool insertRawDataAtCurrent(IteratorType* iterator, const char* name,
    char gender, int studentId, double gpa)
{
    return insertArrayRawDataBeforeLocation(iterator->array, name, 
        gender, studentId, gpa, iterator->currentIndex);
}

/*
Name: iteratorIsEmpty
Process: returns true if iterator is empty, false otherwise
Function input/parameters: iterator (const IteratorType)
Function output/parameters: none
Function output/returned: Boolean result of specified test (bool)
Device input/---: none
Device output/---: none
Dependencies: arrayIsEmpty
*/
bool iteratorIsEmpty(const IteratorType iterator)
{
    if (arrayIsEmpty(iterator.array))
    {
        return true;
    }

    return false;
}

/*
Name: moveNext
Process: if it is possible to move forward in the array,
         increments the current index and returns true,
         otherwise returns false
Function input/parameters: iterator (IteratorType *)
Function output/parameters: none
Function output/returned: Boolean result of the operation (bool)
Device input/---: none
Device output/---: none
Dependencies: hasNext
*/
bool moveNext(IteratorType* iterator)
{
    if (hasNext(iterator))
    {
        // increment currentIndex
        iterator->currentIndex++;

        return true;
    }

    return false;
}

/*
Name: movePrev
Process: if it is possible to move backward in the array,
         decrements the current index and returns true,
         otherwise returns false
Function input/parameters: iterator (IteratorType *)
Function output/parameters: none
Function output/returned: Boolean result of the operation (bool)
Device input/---: none
Device output/---: none
Dependencies: hasPrev
*/
bool movePrev(IteratorType* iterator)
{
    if (hasPrev(iterator))
    {
        // decrement currentIndex
        iterator->currentIndex--;

        return true;
    }

    return false;
}

/*
Name: removeAdtDataFromCurrent
Process: if data is available, it is removed from the current index location
         and the function returns true, otherwise it returns false,
         no change to current index unless last item removed
Function input/parameters: pointer to iterator (IteratorType *)
Function output/parameters: value to be returned (StudentDataType *),
                            pointer to updated iterator (IteratorType *)
Function output/returned: Boolean result of the operation (bool)
Device input/---: none
Device output/---: none
Dependencies: removeArrayDataAtLocation, hasNext
*/
bool removeAdtDataFromCurrent(StudentDataType* returnVal,
    IteratorType* iterator)
{
    // check if current hasNext
    if (hasNext(iterator))
    {
        removeArrayDataAtLocation(returnVal, iterator->array, iterator->currentIndex);
    }

    // else
    else
    {
        removeArrayDataAtLocation(returnVal, iterator->array, iterator->currentIndex);

        // decrement currentIndex
        iterator->currentIndex--;
    }

    
}

/*
Name: setCurrentAtBeginning
Process: if array is not empty, sets current to first location
         and returns true if successful, otherwise returns false
Function input/parameters: pointer to iterator (IteratorType *)
Function output/parameters: pointer to updated iterator (IteratorType *)
Function output/returned: Boolean result of the operation (bool)
Device input/---: none
Device output/---: none
Dependencies: iteratorIsEmpty
*/
bool setCurrentAtBeginning(IteratorType* iterator)
{
    if (iteratorIsEmpty(iterator))
    {
        return false;
    }

    // set current to beginning
    iterator->currentIndex = 0;

    return true;
}

/*
Name: setCurrentAtEnd
Process: if array is not empty, sets current to last location
         and returns true if successful, otherwise returns false
Function input/parameters: pointer to iterator (IteratorType *)
Function output/parameters: pointer to updated iterator (IteratorType *)
Function output/returned: Boolean result of the operation (bool)
Device input/---: none
Device output/---: none
Dependencies: iteratorIsEmpty
*/
bool setCurrentAtEnd(IteratorType* iterator)
{
    // check if empty
    if (iteratorIsEmpty(iterator))
    {
        return false;
    }

    // set currentIndex to end
    iterator->currentIndex = iterator->array.size;
}


#endif   // ITERATOR_TYPE_H
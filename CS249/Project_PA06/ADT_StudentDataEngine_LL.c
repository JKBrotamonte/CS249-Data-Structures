#ifndef STUDENT_DATA_ENGINE_ARRAY_H
#define STUDENT_DATA_ENGINE_ARRAY_H

// header files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "StandardConstants.h"

// data structures
typedef struct StudentDataLLStruct
   {
    char name[ STD_STR_LEN ];

    char gender;

    int studentId;

    double gpa;

    struct StudentDataLLStruct *nextPtr;
   } StudentNodeType;

typedef struct StudentLinkedListStruct
   {
    StudentNodeType *headPtr;

   } StudentLinkedListType;

// file level constants
typedef enum { BEFORE_LOCATION, AT_LOCATION, AFTER_LOCATION } LocationCodeType;

// Prototypes

/*
Name: clearLinkedList
Process: iteratively deallocates memory for StudentNodeType linked list,
         then deallocates memory for StudentLinkedListType structure
         returns NULL to calling function
Function input/parameters: pointer to student linked list
                                                       (StudentLinkedListType *)
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: free
*/
StudentLinkedListType* clearLinkedList(StudentLinkedListType* linkedList)
{
    // initialize variables
    StudentNodeType* wkgPtr = linkedList->headPtr;
    StudentNodeType* temp;

    while (current != NULL)
    {
        temp = wkgPtr;
        wkgPtr = wkgPtr->nextPtr;
        free(temp);
    }
    free(linkedList);
    return NULL;
}

/*
Name: copyLinkedList
Process: copies nodes from one linked list ADT to another
Function input/parameters: source linked list (StudentLinkedListType *)
Function output/parameters: none
Function output/returned: pointer to destination linked list type
                                                       (StudentLinkedListType *)
Device input/---: none
Device output/---: none
Dependencies: createLLNodeWithNode (suggested 10 lines)
*/
StudentLinkedListType* copyLinkedList(StudentLinkedListType* linkedList)
{
    // initialize variables
    StudentLinkedListType* destList;
    StudentNodeType* origWkgPtr = linkedList->headPtr->nextPtr;
    StudentNodeType* cpyWkgPtr;
    StudentNodeType* newNode;
    
    // check orig head ptr null
    if (linkedList->headPtr != NULL)
    {

        destList->headPtr = NULL;

        // copy first item
        newNode = createLLNodeWithNode(&linkedList->nextPtr);
        newNode->nextPtr = NULL;

        destList->headPtr = newNode;

        cpyWkgPtr = destList->headPtr;

        // copy nodes from src list to dest list
        while (origWkgPtr != NULL)
        {
            newNode = createLLNodeWithNode(&origWkgPtr);
            newNode->nextPtr = NULL;

            cpyWkgPtr->nextPtr = newNode;

            origWkgPtr = origWkgPtr->nextPtr;
            cpyWkgPtr = cpyWkgPtr->nextPtr;
        }

        // should be done copying
        return destList;
    }

    // if here then original linked list's head ptr was null thus set dest list head ptr to null and return
    destList->headPtr = NULL;
    return destList;
}

/*
Name: createLLNodeWithData
Process: creates linked list node, assigns data to it,
         sets next pointer to NULL, returns pointer to the new node
Function input/parameters: student name (const char *),
                           student gender (char),
                           student ID (int),
                           student gpa (double)
Function output/parameters: none
Function output/returned: pointer to newly created node (StudentNodeType *)
Device input/---: none
Device output/---: none
Dependencies: malloc, strcpy
*/
StudentNodeType* createLLNodeWithData(const char* name,
    char gender, int studentId, double gpa)
{
    // initialize variables
    StudentNodeType* newNode;

    // allocate memory for node
    newNode = (StudentNodeType*)malloc(sizeof(StudentNodeType));

    // assign data to new node
    strcpy(newNode->name, name);
    newNode->gender = gender;
    newNode->studentId = studentId;
    newNode->gpa = gpa;

    // set next ptr to null
    newNode->nextPtr = NULL;

    // return ptr to new node
    return newNode;
}

/*
Name: CreateLLNodeWithNode
Process: creates linked list node, assigns node data to it,
         sets next pointer to NULL, returns pointer to the new node
Function input/parameters: linked list node (StudentNodeType *)
Function output/parameters: none
Function output/returned: pointer to newly created node (StudentNodeType *)
Device input/---: none
Device output/---: none
Dependencies: createLLNodeWithData (one line of code)
*/
StudentNodeType* createLLNodeWithNode(StudentNodeType* srcPtr)
[
    return createLLNodeWithData(srcPtr->name, srcPtr->gender, 
    srcPtr->studentId, srcPtr->gpa);
]

/*
Name: deepCopyNode
Process: copies all member values from StudentNodeType source,
         does not assign next pointer
Function input/parameters: source node (const StudentNodeType)
Function output/parameters: pointer to destination value (StudentNodeType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: strcpy
*/
void deepCopyNode(StudentNodeType* dest, const StudentNodeType src)
{
    // copy data
    strcpy(dest->name, src->name);
    dest->gender = src->gender;
    dest->studentId = src->studentId;
    dest->gpa = src->gpa;
}

/*
Name: displayLLData
Process: displays comma-delimited element data in linked list
         if it is not empty,
         otherwise displays "Data not found - Display aborted",
         allows for subtitle to be added to "Display Data - "
Function input/parameters: student linked list head pointer
                                                  (const StudentLinkedListType),
                           subtitle (const char *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: data displayed as specified
Dependencies: printf
*/
void displayLLData(const StudentLinkedListType linkedList,
    const char* subTitle)
{
    // initialize variables
    int index;
    StudentNodeType* wkgPtr = linkedList->headPtr;

    // check that list isn't empty
    if (linkedList->headPtr == NULL)
    {
        printf("Data not found - Display aborted\n");
    }

    else
    {
        // otherwise start printing data
        printf("Display Data - %s\n", subTitle);
        while (wkgPtr != NULL)
        {
            printf("[ %2d ]: %s, %c, %d, %f\n",
                index, wkgPtr->name, wkgPtr->gender,
                wkgPtr->studentId, wkgPtr->gpa);

            // increment wkgPtr
            wkgPtr = wkgPtr->nextPtr;
        }

        // just to make sure the next thing printed is on a new line
        printf("\n")
    }
}

/*
Name: getLLSize
Process: finds the size (number of items) of the linked list, returns
Function input/parameters: linked list (const StudentLinkedListType)
Function output/parameters: none
Function output/returned: number of nodes (int)
Device input/---: none
Device output/---: none
Dependencies: none
*/
int getLLSize(const StudentLinkedListType linkedList)
{
    int size = 0;
    StudentNodeType wkgPtr = linkedList->headPtr;

    while (wkgPtr != NULL)
    {
        size++;
        wkgPtr = wkgPtr->nextPtr;
    }

    return size;
}

/*
Name: getNodeAtLocation
Process: checks for index in bounds,
         sets found data to returned variable, returns true,
         otherwise if not in bounds, sets data to empty/default values,
         returns false
Function input/parameters: pointer to linked list (StudentLinkedListType *),
                           pseudo list location to access (int)
Function output/parameters: accessed item,
                            or empty node if not found (StudentNodeType *)
Function output/returned: Boolean result of successful removal (bool)
Device input/---: none
Device output/---: none
Dependencies: deepCopyNode, setEmptyNodeData
*/
bool getNodeAtLocation(StudentNodeType* accessedElement,
    const StudentLinkedListType linkedList, int accessedIndex)
{
    // initialize variables
    StudentNodeType* wkgPtr = linkedList->headPtr;
    int index = 0;

    // loop till wkgPtr points to element we want or till end of list
    while (index < accessedIndex && wkgPtr->nextPtr != NULL)
    {
        wkgPtr = wkgPtr->nextPtr;
        index++;
    }

    // check that wkg ptr is at desired location
    if (index == accessedIndex)
    {
        // copy node data to accessedElement
        deepCopyNode(&accessedElement, wkgPtr);
        return true;
    }

    // otherwise not found set accessed element to empty and return false
    setEmptyNodeData(&accessedElement);
    free(accessedElement);
    return false;

}

/*
Name: initializeLinkedList
Process: initializes linked list type, sets head pointer member to NULL
Function input/parameters: none
Function output/parameters: none
Function output/returned: linked list (StudentLinkedListType *)
Device input/---: none
Device output/---: none
Dependencies: malloc
*/
StudentLinkedListType* initializeLinkedList()
{
    StudentLinkedListType* newList = (StudentLinkedListType*)malloc(sizeof(StudentLinkedListType));
    newList->headPtr = NULL;

    return newList;
}

/*
Name: insertLLAdtDataAfterLocation
Process: verifies location within bounds,
         inserts given node into the linked list
         AFTER a specified zero-based location, returns true
         if location not within bounds, returns false
Function input/parameters: pointer to linked list (StudentLinkedListType *),
                           student ADT (const StudentNodeType),
                           pseudo list location (int)
Function output/parameters: updated pointer to linked list
                                                       (StudentLinkedListType *)
Function output/returned: success of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertLLRawDataEngine - one line of code
*/
bool insertLLAdtDataAfterLocation(StudentLinkedListType* linkedList,
    const StudentNodeType student, int listLocation)
{
    return insertLLRawDataEngine(&linkedList, student.name, student.gender,
        student.studentId, student.gpa, listLocation, AFTER_LOCATION);
}

/*
Name: insertLLAdtDataBeforeLocation
Process: verifies location within bounds,
         inserts given node into the linked list
         PRIOR TO a specified zero-based location, returns true,
         if location not within bounds, returns false
Function input/parameters: pointer to linked list (StudentLinkedListType *),
                           student ADT (const StudentNodeType),
                           pseudo list location (int)
Function output/parameters: updated pointer to linked list
                                                      (StudentLinkedListType *),
                           pseudo list location (int)
Function output/returned: success of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertLLRawDataEngine (one line of code)
*/
bool insertLLAdtDataBeforeLocation(StudentLinkedListType* linkedList,
    const StudentNodeType student, int listLocation)
{
    return insertLLRawDataEngine(&linkedList, student.name, student.gender, 
        student.studentId, student.gpa, listLocation, BEFORE_LOCATION);
}

/*
Name: insertLLRawDataEngine
Process: verifies location within bounds,
         inserts individual data values to the StudentLinkedListType ADT
         switchably before, at, or after, returns true
         if location not within bounds, returns false
         for insertion at, overwrites value at that location, returns true
         if location not within bounds, returns false,
         Note: Used as engine for other set and insert operations
Function input/parameters: pointer to linked list (StudentLinkedListType *),
                           student name (const char *),
                           student gender (char),
                           student ID (int),
                           student gpa (double),
                           pseudo list location (int),
                           location code (LocationCodeType)
Function output/parameters: updated pointer to linked list
                                                       (StudentLinkedListType *)
Function output/returned: success of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: createLLNodeWithData, strcpy
*/
bool insertLLRawDataEngine(StudentLinkedListType* linkedList,
    const char* name, char gender, int studentId,
    double gpa, int listLocation, LocationCodeType locCode)
{
    // initialize variables
    int size = getLLSize(linkedList);
    StudentNodeType* newNode;
    StudentNodeType* wkgPtr;
    StudentNodeType* prevPtr;
    int index;

    // check if in bounds
    if (location < 0 || location > size)
    {
        return false;
    }

    // put data in newNode
    newNode = createLLNodeWithData(name, gender, studentId, gpa);

    // insert node at specified location
    if (location == 0 || (location == 1 && locCode == BEFORE_LOCATION))
    {
        newNode->nextPtr = linkedList->headPtr;
        linkedList->headPtr = newNode;
    }

    else
    {
        wkgPtr = linkedList->headPtr;
        index = 1;

        // here we loop to find the node of the location index which is set to wkgPtr
        while (index < location && wkgPtr->nextPtr != NULL)
        {
            wkgPtr = wkgPtr->nextPtr;
            index++;
        }

        if (index == location)
        {
            if (locCode == BEFORE_LOCATION)
            {
                newNode->nextPtr = wkgPtr;

                if (index == 1)
                {
                    linkedList->headPtr = newNode;
                }

                else
                {
                    prevPtr = linkedList->headPtr;
                    while (prevPtr->nextPtr != wkgPtr)
                    {
                        prev = prev->nextPtr;
                    }
                    prev->nextPtr = newNode;
                }
            }
            else if (locCode == AT_lOCATION)
            {
                strcpy(wkgPtr->name, name);
                wkgPtr->gender = gender;
                wkgPtr->studentId = studentId;
                wkgPtr->gpa = gpa;
            }
            else If(locCode = AFTER_LOCATION)
            {
                newNode->nextPtr = wkgPtr->nextPtr;
                wkgPtr->nextPtr = newNode;
            }
        }
        else 
        {
            free(newNode);
            return false;
        }
    }

    return true;
}

/*
Name: insertLLRawDataAfterLocation
Process: verifies location within bounds,
         inserts individual data values to the StudentLinkedListType ADT
         AFTER a specified zero-based pseudo location, returns true
         if location not within bounds, returns false
Function input/parameters: pointer to linked list (StudentLinkedListType *),
                           student name (const char *),
                           student gender (char),
                           student ID (int),
                           student gpa (double),
                           pseudo list location (int)
Function output/parameters: updated pointer to linked list
                                                       (StudentLinkedListType *)
Function output/returned: success of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertLLRawDataEngine (one line of code)
*/
bool insertLLRawDataAfterLocation(StudentLinkedListType* linkedList,
    const char* name, char gender, int studentId,
    double gpa, int listLocation)
{
    return insertLLRawDataEngine(&linkedList, name, gender,
        studentId, gpa, listLocation, AFTER_LOCATION);
}

/*
Name: insertLLRawDataBeforeLocation
Process: verifies location within bounds,
         inserts individual data values to the StudentLinkedListType ADT
         PRIOR TO a specified zero-based pseudo location, returns true
         if location not within bounds, returns false
Function input/parameters: pointer to linked list (StudentLinkedListType *)
                           student name (const char *),
                           student gender (char),
                           student ID (int),
                           student gpa (double),
                           pseudo list location (int)
Function output/parameters: updated pointer to linked list
                                                       (StudentLinkedListType *)
Function output/returned: success of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertLLRawDataEngine (one line of code)
*/
bool insertLLRawDataBeforeLocation(StudentLinkedListType* linkedList,
    const char* name, char gender, int studentId,
    double gpa, int listLocation)
{
    return insertLLRawDataEngine(&linkedList, name, gender,
        studentId, gpa, listLocation, BEFORE_LOCATION);
}

/*
Name: linkedListIsEmpty
Process: returns true if list is empty, false otherwise
Function input/parameters: linked list (const StudentLinkedListType)
Function output/parameters: none
Function output/returned: Boolean result of test as specified (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool linkedListIsEmpty(const StudentLinkedListType linkedList)
{
    if (linkedList->headPtr == NULL)
    {
        return true;
    }

    return false;
}

/*
Name: removeLLDataAtLocation
Process: checks for index in bounds,
         sets found data to returned variable,
         removes data from linked list, returns true,
         otherwise if not in bounds, sets data to empty/default values,
         returns false
Function input/parameters: pointer to linked list (StudentLinkedListType *),
                           pseudo list location to remove (int)
Function output/parameters: updated pointer to linked list
                                                      (StudentLinkedListType *),
                            removed item, or empty node if not found
                                                          (StudentNodeType *),
Function output/returned: Boolean result of successful removal (bool)
Device input/---: none
Device output/---: none
Dependencies: deepCopyNode, free, setEmptyNodeData
*/
bool removeLLDataAtLocation(StudentNodeType* removedElement,
    StudentLinkedListType* linkedList, int removeIndex)
{
    // initialize variables
    StudentNodeType* wkgPtr = linkedList->headPtr;
    StudentNodeType* temp;
    int size = getLLSize(linkedList);
    int index = 0;

    while (index < removeIndex && wkgPtr->nextPtr != NULL)
    {
        wkgPtr = wkgPtr->nextPtr;
        index++;
    }

    if (index = removeIndex)
    {
        // set copy wkgPtr into removed element
        deepCopyNode(&removedElement, wkgPtr);

        // remove the element and move other elements down
        while (wkgPtr->nextPtr != NULL)
        {
            temp->nextPtr = wkgPtr->nextPtr->nextPtr;
            temp = wkgPtr->nextPtr;
            wkgPtr = temp;
            wkgPtr->nextPtr = temp->nextPtr;
            wkgPtr = wkgPtr->nextPtr;
        }

        return true;
    }

    else
    {
        // not found
        setEmptyNodeData(&removedElement);
        free(removedElement);
        return false;
    }
}

/*
Name: setEmptyNodeData
Process: sets student data type members to empty or default values,
         sets next pointer to NULL
Function input/parameters: student data value (StudentNodeType *)
Function output/parameters: updated student data value (StudentNodeType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: none
*/
void setEmptyNodeData(StudentNodeType* element)
{
    element->name[0] = "NULL_CHAR";
    element->gender = "x";
    element->studentId = 0;
    element->gpa = 0.0;
}

/*
Name: setLLAdtDataAtLocation
Process: verifies location within bounds,
         overwrites node data at specified node, returns true
         if location not within bounds, returns false
Function input/parameters: pointer to linked list (StudentLinkedListType *),
                           student ADT (const StudentNodeType),
                           pseudo list location (int)
Function output/parameters: updated pointer to linked list
                                                       (StudentLinkedListType *)
Function output/returned: success of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertLLRawDataEngine (one line of code)
*/
bool setLLAdtDataAtLocation(StudentLinkedListType* linkedList,
    const StudentNodeType student, int listLocation)
{
    return insertLLRawDataEngine(&linkedList, student.name, student.gender,
        student.studentId, student.gpa, listLocation, AT_LOCATION);
}

/*
Name: setLLRawDataAtLocation
Process: verifies location within bounds,
         overwrites individual data at specified node, returns true
         if location not within bounds, returns false
Function input/parameters: pointer to linked list (StudentLinkedListType *),
                           student ADT (const StudentNodeType),
                           pseudo list location (int)
Function output/parameters: updated pointer to linked list
                                                       (StudentLinkedListType *)
Function output/returned: success of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertLLRawDataEngine (one line of code)
*/

bool setLLRawDataAtLocation(StudentLinkedListType* linkedList,
    const char* name, char gender, int studentId,
    double gpa, int listLocation)
{
    return insertLLRawDataEngine(&linkedList, name, gender,
        studentId, gpa, listLocation, AT_LOCATION);
}

#endif   // STUDENT_DATA_ENGINE_ARRAY_H
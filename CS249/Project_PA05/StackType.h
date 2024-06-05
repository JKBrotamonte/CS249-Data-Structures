#ifndef STACK_TYPE_H
#define STACK_TYPE_H

// header file(s)
#include "ADT_StudentDataEngine_Array.h"

// data structure(s) - type declaration
typedef StudentArrayType StackType;

// prototypes

/*
Name: clearStack
Process: deallocates memory for StackType(aka ArrayType)
Function input/parameters: pointer to stack ADT (StackType *)
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: clearArray
*/
StackType* clearStack(StackType* stack)
{
    stack = clearArray(stack);

    return stack;
}

/*
Name: initializeStack
Process: initializes stack data for StackType(aka ArrayType)
Function input/parameters: initial capacity (int)
Function output/parameters: none
Function output/returned: pointer to stack (StackType *)
Device input/---: none
Device output/---: none
Dependencies: initializeArray
*/
StackType* initializeStack(int initialCapacity)
{
    stack = initializeArray(initialCapacity);

    return stack;
}

/*
Name: peekAdtData
Process: returns value as ADT from top of stack, does not pop from stack
Function input/parameters: pointer to stack (StackType *)
Function output/parameters: returned value (StudentDataType *)
Function output/returned: Boolean result of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: getElementAtLocation
*/
bool peekAdtData(StudentDataType* returnVal, StackType* stack)
{
    return getElementAtLocation(&returnVal, stack->array, stack->size - 1);
}

/*
Name: popAdtData
Process: returns value as ADT from top of stack, pops from stack
Function input/parameters: pointer to stack (StackType *)
Function output/parameters: returned value (StudentDataType *),
                            updated pointer to stack (StackType *)
Function output/returned: Boolean result of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: removeArrayDataAtLocation
*/
bool popAdtData(StudentDataType* returnVal, StackType* stack)
{
    // pop from top of stack or end of list
    return removeArrayDataAtLocation(returnVal, stack->array, stack->size - 1);
}

/*
Name: pushAdtData
Process: pushes ADT value onto stack
Function input/parameters: pointer to stack (StackType *),
                           student data (const StudentDataType)
Function output/parameters: updated pointer to stack (StackType *)
Function output/returned: Boolean result of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: pushRawData
*/
bool pushAdtData(StackType* stack, const StudentDataType student)
{
    return pushRawData(stack, student.name, student.gender, student.studentId, student.gpa);
}

/*
Name: pushRawData
Process: pushes individual data values onto stack
Function input/parameters: pointer to stack (StackType *),
                           student name (const char *),
                           student gender (char),
                           student ID (int),
                           student gpa (double),
Function output/parameters: pointer to updated stack (StackType *)
Function output/returned: Boolean result of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertRawDataAfterLocation, stackIsEmpty
*/
bool pushRawData(StackType* stack, const char* name, char gender,
    int studentId, double gpa)
{
    // check if stack is empty
    if (stackIsEmpty(stack))
    {
        return false;
    }

    // push data at top of stack end of list
    return insertArrayRawDataAfterLocation(stack->array, name, gender, studentId, gpa, stack->size - 1);
}

/*
Name: stackIsEmpty
Process: returns true if stack is empty, false otherwise
Function input/parameters: stack (const StackType)
Function output/parameters: none
Device input/---: none
Function output/returned: Boolean result of test (bool)
Device output/---: none
Dependencies: arrayIsEmpty
*/
bool stackIsEmpty(const StackType stack)
{
    return arrayIsEmpty(stack->array);
}


#endif   // STACK_TYPE_H
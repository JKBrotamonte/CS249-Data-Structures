#ifndef HEAP_UTILITY_H
#define HEAP_UTILITY_H

// header files
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "File_Input_Utility.h"
#include "StandardConstants.h"

// data types

typedef struct ContractorStruct
   {
    int licenseNum;
    char businessName[ STD_STR_LEN ];
    char classCode[ MIN_STR_LEN ];
    char classDetail[ STD_STR_LEN ];
    char city[ MIN_STR_LEN ];
    int priority;
   } ContractorType;

typedef struct HeapStruct
   {
    ContractorType *array;

    int size;
   } HeapType;

typedef enum { GET_PRIORITY, 
               INITIALIZE_PRIORITY_ENGINE, CLEAR_PRIORITY_ENGINE } PriorityCode;

// prototypes
// global variables
int MIN_HEAP_CAPACITY = 100;
int* generatedPriorities = NULL;
int numGeneratedPriorities = 0;

/*
Name: accessPriority
Process: generates unique value between 1 and 100 (MIN_HEAP_CAPACITY),
         generated value is not repeated during one program run
         Priority Codes:
         INITIALIZE_PRIORITY_ENGINE - sets up priority generating system
         GET_PRIORITY - generates a unique value between 1 and 100 
                                                             (MIN_HEAP_CAPACITY)
         CLEAR_PRIORITY_ENGINE - deallocates dynamic memory created
         for the function operation
Function input/parameters: control codes as specified (PriorityCode)
Function output/parameters: none
Function output/returned: value as specified (int)
Device input/---: none
Device output/---: none
Dependencies: rand, malloc w/sizeof, isInArray, free
*/
int accessPriority(PriorityCode code)
{
    // initalize variables
    int priority;

    if (code == INITIALIZE_PRIORITY_ENGINE)
    {
        // allocate memory for the array of generated priorities
        generatedPriorities = malloc(MIN_HEAP_CAPACITY * sizeof(int));

        // initialize array with 0's
                // initialize the array with zeros
        for (int i = 0; i < MIN_HEAP_CAPACITY; i++)
        {
            generatedPriorities[i] = 0;
        }

        // reset number of generated priorities
        numGeneratedPriorities = 0;
    }

    else if (code == GET_PRIORITY)
    {
        // get random priority val
        priority = rand() % MIN_HEAP_CAPACITY + 1;

        // check if the priority has already been generated
        while (isInArray(generatedPriorities, priority, numGeneratedPriorities)) 
        {
            priority = rand() % MIN_HEAP_CAPACITY + 1;
        }

        // add the priority to the array of generated priorities
        generatedPriorities[numGeneratedPriorities++] = priority;

        return priority;
    }

    else if (code == CLEAR_PRIORITY_ENGINE)
    {
        // deallocate memory for the array of generated priorities
        free(generatedPriorities);

        // reset the global variables for the priority generating system
        generatedPriorities = NULL;
        numGeneratedPriorities = 0;
    }

    return 0;
}

/*
Name: addRawDataToHeap
Process: adds data to end of heap, uses bubbleUp to resettle heap,
         allows for display of addition operations,
         returns true if successful and not past limit MIN_HEAP_CAPACITY),
         false otherwise
Function input/parameters: pointer to heap (HeapType *), 
                           contractor license (int),
                           contractor business name, class code (const char *),
                           contractor class detail, city (const char *),
                           priority (int), display flag (bool)
Function output/parameters: pointer to updated heap (HeapType *)
Function output/returned: value as specified (bool)
Device input/---: none
Device output/---: none
Dependencies: setContractorRawData, bubbleUp
*/
bool addRawDataToHeap(HeapType* heap,
    int ctrctrLicense,
    const char* ctrctrBizName,
    const char* ctrctrClassCode,
    const char* ctrctrClassDetail,
    const char* ctrctrCity,
    int priority, bool displayFlag)
{
    // initialize variables
    ContractorType newContractor;

    // check if heap is full
    if (heap->size < MIN_HEAP_CAPACITY)
    {
        // heap not full thus continue
        // check displayflag
        if (displayFlag)
        {
            printf("%d) License Number: %d, Business Name: %s, Class Code: %s, Class Detail: %s, City: %s, Priority: %d\n"
                , heap->size, ctrctrLicense, ctrctrBizName, ctrctrClassCode, ctrctrClassDetail, ctrctrCity, priority);
        }

        // add data to struct
        setContractorRawData(&newContractor, ctrctrLicense, ctrctrBizName, 
            ctrctrClassCode, ctrctrClassDetail, ctrctrCity, priority);
        // add contractor struct to heap
        heap->array[heap->size] = newContractor;

        // bubble up
        bubbleUp(heap, heap->size, displayFlag);

        heap->size++;
        return true;
    }
    // if here assume heap full
    return false;
}

/*
Name: bubbleUp
Process: recursively implements heap bubble up operation of min heap,
         with optional display of operations,
         necessary swaps use only two lines of code, 
         no interim/temporary value used
Function input/parameters: pointer to heap (HeapType *), current index (int),
                           display flag (bool)
Function output/parameters: pointer to updated heap (HeapType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: setContractorStructData, printf, bubbleUp (recursively)
*/
void bubbleUp(HeapType* heap, int currentIndex, bool displayFlag)
{
    // initialize variables
    int parentIndex;
    ContractorType temp;

    // base case
    if (currentIndex == 0) 
    {
        return;
    }

    // calculate parent index
    parentIndex = (currentIndex - 1) / 2;

    // if current priority less than parents priority swap
    if (heap->array[currentIndex].priority < heap->array[parentIndex].priority)
    {
        setContractorStructData(&temp, heap->array[currentIndex]);
        setContractorStructData(&heap->array[currentIndex], heap->array[parentIndex]);
        setContractorStructData(&heap->array[parentIndex], temp);

        // check for display flag
        if (displayFlag)
        {
            // display the swap operation with contractor names and priorities
            printf("- Bubble up swap:\n");
            printf("  - moving up child: %s (%d)\n", heap->array[currentIndex].businessName, heap->array[currentIndex].priority);
            printf("  - moving down parent: %s (%d)\n", heap->array[parentIndex].businessName, heap->array[parentIndex].priority);
        }

        // recursivly perform bubble up on parent
        bubbleUp(heap, parentIndex, displayFlag);
    }
}

/*
Name: clearHeap
Process: deallocates dynamic data used for heap contents
Function input/parameters: pointer to heap (HeapType *)
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: free
*/
HeapType* clearHeap(HeapType* heap)
{
    free(heap->array);

    heap->size = 0;

    return heap;
}

/*
Name: getDataFromFile
Process: uploads data from file with unknown number of data sets,
         has internal Boolean for upload verification,
         returns true if data found and uploaded, false otherwise,
         priority is acquired and applied to each data item as it is input
Function input/parameters: file name (const char *), display flag (bool)
Function output/parameters: pointer to heap (HeapType *)
Function output/returned: result of file operation (bool)
Device input/hard drive: data from HD
Device output/monitor: if internal Boolean set, displays uploaded values
Dependencies: openInputFile, readStringToDelimiterFromFile, 
              readStringToLineEndFromFile, checkForEndOfInputFile, 
              readIntegerFromFile, readCharacterFromFile, 
              accessPriority, addRawDataToHeap, printf, closeInputFile
*/
bool getDataFromFile(HeapType* heap, const char* fileName, bool displayFlag)
{

}

/*
Name: heapIsEmpty
Process: returns true if heap is empty, false othwerwise
Function input/parameters: heap (const HeapType)
Function output/parameters: none
Function output/returned: result as specified (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool heapIsEmpty(const HeapType heap)
{
    return(heap.size == 0);
}

/*
Name: initializeHeap
Process: allocates memory for heap, and for heap contents
Function input/parameters: none
Function output/parameters: none
Function output/returned: pointer to updated heap (HeapType *)
Device input/---: none
Device output/---: none
Dependencies: malloc w/sizeof
*/
HeapType* initializeHeap()
{
    // allocate mem for heap struct
    HeapType* heap = (HeapType*)malloc(sizeof(HeapType));

    // allocate mem for heap array
    heap->array = (ContractorType*)malloc(sizeof(ContractorType));

    // initialize heap size to 0
    heap->size = 0;

    // return
    return heap;
}

/*
Name: isInArray
Process: utility function that reports if a specified value 
         has been found in a given array
Function input/parameters: pointer to integer array (int *), value (int),
                           size of array (int)
Function output/parameters: none
Function output/returned: result as specified (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool isInArray(int* array, int value, int arraySize)
{
    // initialize variables
    int index;

    // loop through array

    for (index = 0; index < arraySize; index++)
    {
        // check for value at index
        if (array[index] == value)
        {
            // value found return true
            return true;
        }
    }

    // value not found return false
    return false;
}

/*
Name: removeFromHeap
Process: removes value from min heap, resets top of heap,
         then resettles heap,
         allows optional display of operations
Function input/parameters: pointer to heap (HeapType *), display flag (bool)
Function output/parameters: pointer to returned value (Contractor *),
                            pointer to updated heap (HeapType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: setContractorStructData, printf, trickleDown
*/
void removeFromHeap(ContractorType* returned,
    HeapType* heap, bool displayFlag)
{
    // initialize variables

    // save top of heap
    *returned = heap->array[0];

    // set top of heap to last element
    setContractorStructData(&heap->array[0], heap->array[heap->size - 1]);

    // decrease size of heap
    heap->size--;

    // check display flag
    if (displayFlag)
    {
        printf("Removing business: %s", returned->businessName);
    }

    // trickle down the new top of heap to its correct pos
    trickleDown(heap, 0, displayFlag);
}

/*
Name: setContractorRawData
Process: copies data from raw data to destination pointer
Function input/parameters: license number (int), 
                           business name & class code (const char *),
                           class detail & city (const char *),
                           priority (int)
Function output/parameters: destination pointer (ContractorType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: strcpy
*/
void setContractorRawData(ContractorType* destPtr,
    int ctrctrLicense,
    const char* ctrctrBizName,
    const char* ctrctrClassCode,
    const char* ctrctrClassDetail,
    const char* ctrctrCity,
    int priority)
{
    // copy values to dest pointer
    destPtr->licenseNum = ctrctrLicense;
    strcpy(destPtr->businessName, ctrctrBizName);
    strcpy(destPtr->classCode, ctrctrClassCode);
    strcpy(destPtr->classDetail, ctrctrClassDetail);
    strcpy(destPtr->city, ctrctrCity);
    destPtr->priority = priority;
}
/*
Name: setContractorStructData
Process: copies data from source node to destination pointer
Function input/parameters: node to be copied (const ContractorType)
Function output/parameters: destination pointer (ContractorType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: setContractorRawData
*/
void setContractorStructData(ContractorType* destPtr,
    const ContractorType source)
{
    setContractorRawData(destPtr, source.licenseNum, source.businessName, 
        source.classCode, source.classDetail, source.city, source.priority);
}

/*
Name: trickleDown
Process: recursively implements heap trickle down operation in min heap
         with optional display of operations,
         necessary swaps use only two lines of code, 
         no interim/temporary value used
Function input/parameters: pointer to heap (HeapType *), current index (int),
                           display flag (bool)
Function output/parameters: pointer to updated heap (HeapType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: setContractorStructData, printf, trickleDown (recursively)
Author Note: used four "if" and/or "else if" statements, 
             used five inequality tests,
             not including display flag tests,
             this is not required but it should be considered
*/
void trickleDown(HeapType* heap, int currentIndex, bool displayFlag)
{
    // initialize variables
    int leftChild = 2 * currentIndex + 1;
    int rightChild = 2 * currentIndex + 2;
    int smallestChild = currentIndex;
    char* side;
    ContractorType temp;

    // find smallest child
    if (leftChild < heap->size &&
        heap->array[leftChild].priority < heap->array[smallestChild].priority)
    {
        smallestChild = leftChild;
        side = "left";
    }

    if (rightChild < heap->size &&
        heap->array[rightChild].priority < heap->array[smallestChild].priority)
    {
        smallestChild = rightChild;
        side = "right";
    }

    // if smallest child is not the current then swap and trickledown
    if (smallestChild != currentIndex)
    {
        // swap nodes
        setContractorStructData(&temp, heap->array[currentIndex]);
        setContractorStructData(&heap->array[currentIndex], heap->array[smallestChild]);
        setContractorStructData(&heap->array[smallestChild], temp);

        // check displayFlag
        if (displayFlag)
        {
            // display operations
            printf("- Trickle down swap:\n");
            printf("  - moving down parent: %s (%d)\n", heap->array[currentIndex].businessName, 
                heap->array[currentIndex].priority);
            printf("  - moving up %s child: %s (%d)\n", side, heap->array[smallestChild].businessName, 
                heap->array[smallestChild].priority);
        }
        
        // trickle down recursively with smallest child
        trickleDown(heap, smallestChild, displayFlag);
    }
}

#endif  // HEAP_UTILITY_H

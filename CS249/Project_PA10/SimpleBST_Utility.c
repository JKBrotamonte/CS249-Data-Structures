#ifndef BST_UTILITY_H
#define BST_UTILITY_H

// header files
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "StandardConstants.h"
#include "File_Input_Utility.h"

// external constants


// data types

typedef struct CityDataStruct
{
    char name[MIN_STR_LEN];
    int population;

    struct CityDataStruct* leftChildPtr;
    struct CityDataStruct* rightChildPtr;
} CityDataType;

// prototypes

/*
Name: clearTree
Process: recursively deallocates tree nodes using a post order traversal
Function input/parameters: working pointer for recursion (StudentDataType *)
Function output/parameters: none
Function output/returned: empty tree (NULL)
Device input/file: none
Device output/monitor: none
Dependencies: free, clearTree (recursively)
*/
CityDataType* clearTree(CityDataType* wkgPtr)
{
    if (wkgPtr != NULL)
    {
        clearTree(wkgPtr->leftChildPtr);
        clearTree(wkgPtr->rightChildPtr);
        free(wkgPtr);
        wkgPtr = NULL;
    }
    return wkgPtr;
}

/*
Name: compareStrings
Process: compares two strings as follows:
         - if left string is greater than the right string,
         returns value greater than zero
         - if left string is less than the right string,
         returns value less than zero
         - if strings are equal but one is longer, longer one is greater
         - otherwise, returns zero
Function input/parameters: two strings to be compared (const char *)
Function output/parameters: none
Function output/returned: result as specified above (int)
Device input/file: none
Device output/monitor: none
Dependencies: strlen
*/
int compareStrings(const char* leftStr, const char* rightStr)
{
    int result = strcmp(leftStr, rightStr);
    int leftLen = strlen(leftStr);
    int rightLen = strlen(rightStr);

    if (result == 0) // strings are equal
    {
        if (leftLen > rightLen)
        {
            result = 1; // left string is longer, so it is greater
        }
        else if (leftLen < rightLen)
        {
            result = -1; // right string is longer, so it is greater
        }
    }

    return result;
}

/*
Name: copyTree
Process: recursively duplicates the provided tree
         using a pre order traversal strategy
Function input/parameters: working pointer for recursion (CityDataType *)
Function output/parameters: none
Function output/returned: pointer to duplicate tree (CityDataType *)
Device input/---: none
Device output/---: none
Dependencies: initializeCityNodeFromNode, copyTree (recursively)
*/
CityDataType* copyTree(CityDataType* wkgPtr)
{
    if (wkgPtr == NULL)
    {
        return NULL;
    }

    CityDataType* newNode = initializeCityNodeFromNode(*wkgPtr);
    newNode->leftChildPtr = copyTree(wkgPtr->leftChildPtr);
    newNode->rightChildPtr = copyTree(wkgPtr->rightChildPtr);

    return newNode;
}

/*
Name: countTreeNodes
Process: finds the number of nodes in a given BST
Function input/parameters: working pointer for recursion (CityDataType *)
Function output/parameters: none
Function output/returned: number of nodes found (int)
Device input/---: none
Device output/---: none
Dependencies: countTreeNodeHelper
*/
int countTreeNodes(CityDataType* rootPtr)
{
    int counter = 0;
    countTreeNodeHelper(rootPtr, &counter);
    return counter;
}

/*
Name: countTreeNodeHelper
Process: recursively finds the number of nodes in a given BST
Function input/parameters: working pointer for recursion (CityDataType *)
Function output/parameters: pointer to number of nodes (int *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: countTreeNodeHelper (recursively)
*/
void countTreeNodeHelper(CityDataType* cdtPtr, int* counter)
{
    // initialize variables


    if (cdtPtr != NULL)
    {
        countTreeNodeHelper(cdtPtr->leftChildPtr, counter); // recursively count nodes in the left subtree
        countTreeNodeHelper(cdtPtr->rightChildPtr, counter); // recursively count nodes in the right subtree
        (*counter)++; // increment the counter to count the current node
    }
}

/*
Name: displayData
Process: displays data sorted by city name
Function input/parameters: root pointer (CityDataType *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: displayInOrder
*/
void displayData(CityDataType* rootPtr)
{
    // initialize variables
    int count = 0;

    if (rootPtr == NULL) 
    {
        printf("The tree is empty.\n");
        return;
    }

    displayInOrder(rootPtr, &count);
}

/*
Name: displayInOrder
Process: recursively displays tree with numbered values
         using in order traversal,
         dynamically creates and frees string for display
Function input/parameters: working pointer for recursion (CityDataType *),
                           pointer to count (int *)
Function output/parameters: none
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: cityDataToString, malloc, sizeof, printf, free,
              displayInOrder (recursively)
*/
void displayInOrder(CityDataType* cdtPtr, int* count)
{
    // initialize variables
    char* str;

    if (cdtPtr != NULL)
    {
        displayInOrder(cdtPtr->leftChildPtr, count);

        str = (char*)malloc(sizeof(char) * MAX_STR_LEN);
        cityDataToString(str, *cdtPtr);

        (*count)++;
        printf("%d) %s\n", *count, str);

        free(str);
        str = NULL;

        displayInOrder(cdtPtr->rightChildPtr, count);
    }
}

/*
Name: findMax
Process: finds the maximum of two integer values
Function input/parameters: two integer values (int)
Function output/parameters: none
Function output/returned: larger of the two numbers (int)
Device input/---: none
Device output/---: none
Dependencies: none
*/
int findMax(int oneVal, int otherVal)
{
    if (oneVal >= otherVal)
    {
        return oneVal;
    }
    else
    {
        return otherVal;
    }
}

/*
Name: findOptimalTreeHeight
Process: finds the optimal height of a given BST
Function input/parameters: pointer to root (CityDataType *)
Function output/parameters: none
Function output/returned: optimal tree height (int)
Device input/---: none
Device output/---: none
Dependencies: countTreeNodes
*/
int findOptimalTreeHeight(CityDataType* cdtPtr)
{
    int numNodes = 0;

    // count the number of nodes in the tree
    countTreeNodeHelper(cdtPtr, &numNodes);

    int height = 0;
    int nodesAtHeight = 1;

    while (numNodes > nodesAtHeight)
    {
        // calculate the number of nodes at the next height
        nodesAtHeight = nodesAtHeight * 2 + 1;

        // increment the height
        height++;
    }

    // return the optimal height
    return height;
}

/*
Name: findActualTreeHeight
Process: recursively finds the actual height of a given BST
Function input/parameters: pointer to root (CityDataType *)
Function output/parameters: none
Function output/returned: actual tree height (int)
Device input/---: none
Device output/---: none
Dependencies: findActualTreeHeight (recursively), findMax
*/
int findActualTreeHeight(CityDataType* cdtPtr)
{
    // initialize variables
    // find height of left subtree
    int leftHeight = findActualTreeHeight(cdtPtr->leftChildPtr);

    // find height of right subtree
    int rightHeight = findActualTreeHeight(cdtPtr->rightChildPtr);

    // base case: empty tree has height -1
    if (cdtPtr == NULL)
    {
        return -1;
    }

    // actual height is max height of subtrees + 1 for root node
    return findMax(leftHeight, rightHeight) + 1;
}

/*
Name: getBstDataFromFile
Process: uploads data from file with unknown number of data sets,
         allows for Boolean flag to show upload
Function input/parameters: file name (char *), verbose flag (bool)
Function output/parameters: none
Function output/returned: pointer to newly created BST
Device input/file: data from HD
Device output/monitor: none
Dependencies: openInputFile, readStringToLineEndFromFile, initializeBST
              checkForEndOfInputFile, readIntegerFromFile,
              readCharacterFromFile, readStringToDelimiterFromFile,
              readStringToLineEndFromFile,  initializeCityNodeFromData,
              insert, printf, closeInputFile
*/
CityDataType* getBstDataFromFile(const char* fileName, bool verbose);

/*
Name: initializeBST
Process: sets BST root pointer to NULL, root pointer is returned by address
Function input/parameters: address of working pointer (CityDataType **)
Function output/parameters: address of updated working pointer
                            (CityDataType **)
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
void initializeBST(CityDataType** bstPtr)
{
    // set the root pointer to NULL
    *bstPtr = NULL;
}

/*
Name: initializeCityNodeFromData
Process: captures data from individual data items,
         dynamically creates new node,
         copies data, and returns pointer to new node
Function input/parameters: data to be copied (char *, int, double)
Function output/parameters: none
Function output/returned: pointer to new node as specified (CityDataType *)
Device input/file: none
Device output/monitor: none
Dependencies: malloc, sizeof, strcpy
*/
CityDataType* initializeCityNodeFromData(const char* name, int population)
{
    // initialize variables
    CityDataType* newCity;

    // allocate memory for new node
    newCity = (CityDataType*)malloc(sizeof(CityDataType));

    // copy stuff
    strcpy(newCity->name, name);
    newCity->population = population;

    // set ptrs to null
    newCity->leftChildPtr = NULL;
    newCity->rightChildPtr = NULL;

    // return pointer to new node
    return newCity;
}

/*
Name: initializeCityNodeFromNode
Process: captures data from source node pointer, dynamically creates new node,
         copies data, and returns pointer to new node
Function input/parameters: node to be copied (CityDataType)
Function output/parameters: none
Function output/returned: pointer to new node as specified (CityDataType *)
Device input/file: none
Device output/monitor: none
Dependencies: initializeCityNodeFromData
*/
CityDataType* initializeCityNodeFromNode(const CityDataType source)
{
    return initializeCityNodeFromData(source->name, source->population);
}

/*
Name: insert
Process: recursively searches for available location in BST,
         creates new node and returns it to the calling function,
         if node is already in tree, data is overwritten
Function input/parameters: working pointer for recursion (CityDataType *),
                           node to be inserted (const CityDataType)
Function output/parameters: none
Function output/returned: pointer to new node and subtrees
                          as specified (CityDataType *)
Device input/file: none
Device output/monitor: none
Dependencies: compareStrings, setCityNodeData, initializeCityNodeFromNode,
              insert (recursively)
*/
CityDataType* insert(CityDataType* wkgPtr, const CityDataType inData)
{
    // If tree is empty, create a new node and return it
    if (wkgPtr == NULL) 
    {
        wkgPtr = initializeCityNodeFromNode(inData);
        return wkgPtr;
    }

    // Compare node data to insertion data
    int cmp = compareStrings(inData.name, wkgPtr->name);

    // If insertion data is less than current node data, go left
    if (cmp < 0) 
    {
        wkgPtr->leftChildPtr = insert(wkgPtr->leftChildPtr, inData);
    }
    // If insertion data is greater than current node data, go right
    else if (cmp > 0) 
    {
        wkgPtr->rightChildPtr = insert(wkgPtr->rightChildPtr, inData);
    }
    // If insertion data matches current node data, update the node
    else 
    {
        setCityNodeData(wkgPtr, inData);
    }

    // Return pointer to current node
    return wkgPtr;
}

/*
Name: isEmpty
Process: tests root node for NULL, returns result
Function input/parameters: pointer to root node (CityDataType *)
Function output/parameters: none
Function output/returned: result of test as specified (bool)
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
bool isEmpty(CityDataType* sdtPtr)
{
    // returns the result of if(sdtPtr == NULL)
    return sdtPtr == NULL;
}

/*
Name: removeFromMax
Process: recursively searches for max node,
         when found, node is unlinked from tree and returned
Function input/parameters: pointer to parent and child nodes (CityDataType *)
Function output/parameters: none
Function output/returned: pointer to removed node (CityDataType *)
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
CityDataType* removeFromMax(CityDataType* parentPtr,
    CityDataType* childPtr)
{
    if (childPtr->rightChildPtr != NULL)
    {
        return removeFromMax(childPtr, childPtr->rightChildPtr);
    }
    parentPtr->rightChildPtr = childPtr->leftChildPtr;
    return childPtr;
}

/*
Name: removeItem
Process: searches for item, if found, creates new node from search pointer,
         then removes item from tree using helper function,
         otherwise returns NULL
Function input/parameters: address of pointer to root node (CityDataType *),
                           node to be removed with at least city name key
Function output/parameters: address of updated root node pointer
                            (CityDataType **)
Function output/returned: pointer to dynamically created duplicate
                          of removed item (CityDataType *)
Device input/file: none
Device output/monitor: none
Dependencies: search, initializeCityNodeFromNode, removeItemHelper
*/
CityDataType* removeItem(CityDataType** rootPtr, const char* cityName)
{
    CityDataType* nodeToRemove = search(*rootPtr, cityName);

    if (nodeToRemove == NULL) 
    {
        return NULL;
    }

    CityDataType* removedNode = initializeCityNodeFromNode(*nodeToRemove);
    *rootPtr = removeItemHelper(*rootPtr, cityName);

    return removedNode;
}

/*
Name: removeItemHelper
Process: recursively searches for item, removes node,
         returns dynamic memory of removed node to OS,
         returns updated link to parent (at each recursive level),
         only one return at end of function
Function input/parameters: pointer to working node (CityDataType *),
                           node to be removed with at least city name key
                           (const CityDataType)
Function output/parameters: none
Function output/returned: link to recursive parent
Device input/file: none
Device output/monitor: none
Dependencies: compareStrings, setCityNodeData, removeFromMax, free,
              removeItemHelper (recursively)
*/
CityDataType* removeItemHelper(CityDataType* wkgPtr, const char* cityName)
{
    if (wkgPtr == NULL) 
    {
        return wkgPtr;
    }

    int cmpResult = compareStrings(cityName, wkgPtr->name);

    if (cmpResult < 0) 
    {
        wkgPtr->leftChildPtr = removeItemHelper(wkgPtr->leftChildPtr, cityName);
    }
    else if (cmpResult > 0) 
    {
        wkgPtr->rightChildPtr = removeItemHelper(wkgPtr->rightChildPtr, cityName);
    }
    else 
    {
        if (wkgPtr->leftChildPtr == NULL) 
        {
            CityDataType* temp = wkgPtr->rightChildPtr;
            free(wkgPtr);
            return temp;
        }
        else if (wkgPtr->rightChildPtr == NULL) 
        {
            CityDataType* temp = wkgPtr->leftChildPtr;
            free(wkgPtr);
            return temp;
        }

        CityDataType* temp = removeFromMax(wkgPtr, wkgPtr->leftChildPtr);
        setCityNodeData(wkgPtr, *temp);
        wkgPtr->leftChildPtr = removeItemHelper(wkgPtr->leftChildPtr, temp->name);
        free(temp);
    }

    return wkgPtr;
}

/*
Name: search
Process: recursively searches for item, if found, returns pointer to node,
         otherwise, returns NULL
Function input/parameters: pointer to working node (CityDataType *),
                           node to be found with city name key
                           (const char *)
Function output/parameters: none
Function output/returned: link to found node, or NULL, as specified
Device input/file: none
Device output/monitor: none
Dependencies: compareStrings, search (recursively)
*/
CityDataType* search(CityDataType* wkgPtr, const char* cityName)
{
    // initalize variables
    int cmp = compareStrings(cityName, wkgPtr->name);

    if (cmp == 0) 
    {
        // item found
        return wkgPtr;
    }

    if (cmp < 0) 
    {
        // search in the left subtree
        return search(wkgPtr->leftChildPtr, cityName);
    }

    if (cmp > 0)
    {
        // search in the right subtree
        return search(wkgPtr->rightChildPtr, cityName);
    }
}

/*
Name: setCityNodeData
Process: copies data from source node to destination pointer
Function input/parameters: node to be copied (CityDataType)
Function output/parameters: destination pointer (CityDataType *)
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: strcpy
*/
void setCityNodeData(CityDataType* destPtr, const CityDataType source)
{
    strcpy(destPtr->name, source.name);
    destPtr->population = source.population;
}

/*
Name: cityDataToString
Process: sets data from node to formatted string
Function input/parameters: node with data to be set (CityDataType)
Function output/parameters: string array with result (char [])
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: sprintf
*/
void cityDataToString(char str[], CityDataType cityData)
{
    sprintf(str, "City name: %s, Population: %d", cityData.name, cityData.population);
}

#endif   // BST_UTILITY_H

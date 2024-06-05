#ifndef TWO_THREE_UTILITY_H
#define TWO_THREE_UTILITY_H

// header file
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "StandardConstants.h"

// local constants
typedef enum { LEFT_CHILD_SELECT = 101, 
                        CENTER_CHILD_SELECT, RIGHT_CHILD_SELECT } SelectionCode;
typedef enum { ZERO_DATA_ITEMS, ONE_DATA_ITEM, 
                               TWO_DATA_ITEMS, THREE_DATA_ITEMS } ItemCountCode;

// data structures
typedef struct ContractorStruct
   {
    int licenseNum;
    char businessName[ STD_STR_LEN ];
    char classCode[ MIN_STR_LEN ];
    char classDetail[ STD_STR_LEN ];
    char city[ MIN_STR_LEN ];
   } ContractorType;

typedef struct TwoThreeStruct
   {
    ContractorType *leftData, *centerData, *rightData;

    int numItems;

    struct TwoThreeStruct *leftChildPtr, *ctrChildPtr, *rightChildPtr;
    struct TwoThreeStruct *auxLeftPtr, *auxRightPtr;
    struct TwoThreeStruct *parentPtr;
    
   } TwoThreeNode;

// prototypes

/*
Name: addAndOrganizeData
Process: adds item to a previously established node, 
         in the appropriate location,
         returns pointer to the node
Function input/parameters: working pointer (TwoThreeNode *),
                           new contracter data (ContractorType *)
Function output/parameters: none
Function output/returned: pointer to updated two or three node (TwoThreeNode *)
Device input/---: none
Device output/---: none
Dependencies: strcpy (as needed), createContractorDataFromAdt,
              compareStrings
*/
TwoThreeNode* addAndOrganizeData(TwoThreeNode* wkgPtr,
    ContractorType* newData)
{
    // initialize variables
    int comp1;
    int comp2;
    ContractorType* temp;

    // if node has no data
    if (wkgPtr->numItems == ZERO_DATA_ITEMS)
    {
        // add data to left
        wkgPtr->leftData = createContractorDataFromAdt(newData);
        wkgPtr->numItems = ONE_DATA_ITEM;
    }

    // if node has one item
    else if (wkgPtr->numItems == ONE_DATA_ITEM)
    {
        // compare the strings
        comp1 = compareStrings(newData->businessName, wkgPtr->leftData->businessName);

        // check if new data less than the one data item
        if (comp1 < 0)
        {
            // less than so add data to left
            wkgPtr->centerData = createContractorDataFromAdt(wkgPtr->leftData);
            wkgPtr->leftData = createContractorDataFromAdt(newData);
        }

        // otherwise assume new data greater than
        else
        {
            wkgPtr->centerData = createContractorDataFromAdt(newData);
        }

        wkgPtr->numItems = TWO_DATA_ITEMS;
    }

    // assume node has two data items
    else
    {
        // get comparison values
        comp1 = compareStrings(newData->businessName, wkgPtr->leftData->businessName);
        comp2 = compareStrings(newData->businessName, wkgPtr->centerData->businessName);

        // check less than both
        if (comp1 < 0)
        {
            temp = createContractorDataFromAdt(wkgPtr->leftData);
            wkgPtr->leftData = createContractorDataFromAdt(newData);
            wkgPtr->rightData = createContractorDataFromAdt(wkgPtr->centerData);
            wkgPtr->centerData = createContractorDataFromAdt(temp);
        }

        // check if greater than left data but less than center data
        else if (comp2 < 0)
        {
            wkgPtr->rightData = createContractorDataFromAdt(wkgPtr->centerData);
            wkgPtr->centerData = createContractorDataFromAdt(newData);
        }

        // other wise assume new data greater than both
        else
        {
            wkgPtr->rightData = createContractorDataFromAdt(newData);
        }

        wkgPtr->numItems = THREE_DATA_ITEMS;
    }

    return wkgPtr;
}

/*
Name: addItemWithAdtData
Process: adds item to tree given contractor Adt data
Function input/parameters: address of root pointer (TwoThreeNode **),
                           new contracter data (ContractorType *)
Function output/parameters: none
Function output/returned: pointer to root node
Device input/---: none
Device output/---: none
Dependencies: addItemWithAdtDataHelper
*/
TwoThreeNode* addItemWithAdtData(TwoThreeNode* rootPtr,
    ContractorType* newData)
{
    TwoThreeNode* wkgPtr = rootPtr;

    addItemWithAdtDataHelper(&rootPtr, wkgPtr, newData);

    return rootPtr;
}

/*
Name: addItemWithAdtDataHelper
Process: helper function adds item to tree given contractor Adt data
Function input/parameters: address of root pointer (TwoThreeNode **),
                           working pointer (TwoThreeNode *),
                           new contracter data (ContractorType *)
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: strcpy (as needed), createContractorDataFromAdt,
              compareStrings, addItemWithAdtDataHelper,
              addAndOrganizeData, resolveThreeFourNode
*/
void addItemWithAdtDataHelper(TwoThreeNode** rootPtr,
    TwoThreeNode* wkgPtr,
    ContractorType* newData)
{
    // initialize variables
    int cmp = compareStrings(newData->lastName, wkgPtr->data->lastName);
    ContractorType* newContractorData;

    // If newData is less than the current recurse left
    if (cmp < 0)
    {
        addItemWithAdtDataHelper(rootPtr, wkgPtr->leftChild, newData);
    }
    // If newData is greater than the current recurse right
    else if (cmp > 0)
    {
        addItemWithAdtDataHelper(rootPtr, wkgPtr->rightChild, newData);
    }
    // If newData is equal to the current node data, add new data
    else
    {
        newContractorData = createContractorDataFromAdt(newData);
        addAndOrganizeData(wkgPtr, newContractorData);

        // Resolve any 3/4 nodes starting from the current node
        resolveThreeFourNode(rootPtr, wkgPtr);
    }
}

/*
Name: addItemWithRawData
Process: adds node with all Contractor data
Function input/parameters: pointer to root node (TwoThreeNode *),
                           license number (int), business name (const char *),
                           class code, class detail, city (const char *)
Function output/parameters: none
Function output/returned: pointer to root node
Device input/---: none
Device output/---: none
Dependencies: createContractorDataWithData, addItemWithAdtDataHelper, free
*/
TwoThreeNode* addItemWithRawData(TwoThreeNode* rootPtr,
    int licNum,
    const char* bizName, const char* clsCode,
    const char* clsDetail, const char* city)
{
    ContractorType* newData = createContractorDataWithData(licNum,
        bizName, clsCode, clsDetail, city);
    TwoThreeNode* wkgPtr = rootPtr;

    addItemWithAdtDataHelper(&rootPtr, wkgPtr, newData);

    free(newData);

    return rootPtr;
}

/*
Name: clearTwoThreeNode
Process: deallocates memory for one individual node
         returns NULL,
         does not handle children of node
Function input/parameters: pointer to node (TwoThreeNode *)
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: free
*/
TwoThreeNode* clearTwoThreeNode(TwoThreeNode* wkgPtr)
{
    if (wkgPtr != NULL)
    {
        free(wkgPtr);
    }

    return NULL;
}

/*
Name: clearTwoThreeTree
Process: deallocates memory for all tree nodes individually, 
         returns NULL
Function input/parameters: pointer to tree (TwoThreeNode *)
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: clearTwoThreeNode, clearTwoThreeTree (recursively)
*/
TwoThreeNode* clearTwoThreeTree(TwoThreeNode* wkgPtr)
{
    if (wkgPtr != NULL)
    {
        // recurse left
        wkgPtr->leftChildPtr = clearTwoThreeTree(wkgPtr->leftChildPtr);

        // recurse center
        wkgPtr->ctrChildPtr = clearTwoThreeTree(wkgPtr->ctrChildPtr);

        // recurse right
        wkgPtr->rightChildPtr = clearTwoThreeTree(wkgPtr->rightChildPtr);

        // clear current
        wkgPtr = clearTwoThreeNode(wkgPtr);
    }

    return NULL;
}

/*
Name: compareStrings
Process: test for alphabetical difference between two strings,
         returns less than zero if left string 
         is alphabetically less than right string,
         returns equal to zero if left string 
         is alphabetically equal to right string,
         returns greater than zero if left string 
         is alphabetically greater than right string,
         tests all characters as lower case,
         if two strings are alphabetically equal,
         longer string is greater unless they are equal length
Function input/parameters: left and right strings (const char *)
Function output/parameters: none
Function output/returned: result as specified (int)
Device input/---: none
Device output/---: none
Dependencies: toLowerCase, strlen
*/
int compareStrings(const char* leftString, const char* rightString)
{
    int diff, index = 0;

    while (leftString[index] != NULL_CHAR
        && rightString[index] != NULL_CHAR)
    {
        diff = toLowerCase(leftString[index])
            - toLowerCase(rightString[index]);

        if (diff != 0)
        {
            return diff;
        }

        index++;
    }

    return strlen(leftString) - strlen(rightString);
}

/*
Name: copyTwoThreeTree
Process: creates duplicate copy of given two three tree
Function input/parameters: pointer to two three tree (TwoThreeNode *)
Function output/parameters: none
Function output/returned: pointer to new copy of two three tree (TwoThreeNode *)
Device input/---: none
Device output/---: none
Dependencies: createEmptyTwoThreeNode, createContractorDataFromAdt,
              copyTwoThreeTree (recursively)
*/
TwoThreeNode* copyTwoThreeTree(TwoThreeNode* wkgPtr)
{
    // initliaze variables
    TwoThreeNode* cpyPtr = createEmptyTwoThreeNode();

    // check if wkgptr is null
    if (wkgPtr == NULL)
    {
        return NULL;
    }

    // start copying data from wkg to cpy
    if (wkgPtr->leftData != NULL)
    {
        cpyPtr->leftData = createContractorDataFromAdt(wkgPtr->leftData);
    }

    if (wkgPtr->centerData != NULL)
    {
        cpyPtr->centerData = createContractorDataFromAdt(wkgPtr->centerData);
    }

    if (wkgPtr->rightData != NULL)
    {
        cpyPtr->rightData = createContractorDataFromAdt(wkgPtr->rightData);
    }

    cpyPtr->numItems = wkgPtr->numItems;

    // recusivly copy children
    cpyPtr->leftChildPtr = copyTwoThreeTree(wkgPtr->leftChildPtr);
    cpyPtr->ctrChildPtr = copyTwoThreeTree(wkgPtr->ctrChildPtr);
    cpyPtr->rightChildPtr = copyTwoThreeTree(wkgPtr->rightChildPtr);

    return cpyPtr;
}

/*
Name: createContractorDataWithData
Process: creates contractor data node from given contractor data items
Function input/parameters: license number (int), business name (const char *),
                           class code, class detail, and city (const char *)
Function output/parameters: none
Function output/returned: pointer to new contractor data (ContractorType *)
Device input/---: none
Device output/---: none
Dependencies: malloc/sizeof, strcpy
*/
ContractorType* createContractorDataWithData(int licNum, const char* bizName,
    const char* clsCode, const char* clsDetail, const char* city)
{
    ContractorType* newPtr
        = (ContractorType*)malloc(sizeof(ContractorType));

    newPtr->licenseNum = licNum;

    strcpy(newPtr->businessName, bizName);
    strcpy(newPtr->classCode, clsCode);
    strcpy(newPtr->classDetail, clsDetail);
    strcpy(newPtr->city, city);

    return newPtr;
}

/*
Name: createContractorDataFromAdt
Process: creates contractor data node from given contractor Adt
Function input/parameters: source Adt pointer (const ContractorType *)
Function output/parameters: none
Function output/returned: pointer to new contractor data (ContractorType *)
Device input/---: none
Device output/---: none
Dependencies: createContractorDataWithData
*/
ContractorType* createContractorDataFromAdt(const ContractorType* sourcePtr)
{
    return createContractorDataWithData(sourcePtr->licenseNum,
        sourcePtr->businessName, sourcePtr->classCode,
        sourcePtr->classDetail, sourcePtr->city);
}

/*
Name: createEmptyTwoThreeNode
Process: allocates data for two three node, sets all data to zero or NULL
         as appropriate, returns pointer to node
Function input/parameters: none
Function output/parameters: none
Function output/returned: pointer to created node (TwoThreeNode *)
Device input/---: none
Device output/---: none
Dependencies: malloc/sizeof
*/
TwoThreeNode* createEmptyTwoThreeNode()
{
    TwoThreeNode* newPtr = (TwoThreeNode*)malloc(sizeof(TwoThreeNode));

    newPtr->numItems = ZERO_DATA_ITEMS;

    newPtr->leftData = NULL;
    newPtr->centerData = NULL;
    newPtr->rightData = NULL;

    newPtr->leftChildPtr = NULL;
    newPtr->auxLeftPtr = NULL;
    newPtr->ctrChildPtr = NULL;
    newPtr->auxRightPtr = NULL;
    newPtr->rightChildPtr = NULL;

    newPtr->parentPtr = NULL;

    return newPtr;
}

/*
Name: createNewChild
Process: creates new child selectably from left or right side of three four node,
         sets all links for the new node, returns pointer to node
Function input/parameters: working and parent pointers (TwoThreeNode *),
                           code to indicate left or right child (SelectionCode)
Function output/parameters: none
Function output/returned: pointer to newly created child
Device input/---: none
Device output/---: none
Dependencies: createContractorDataFromAdt, createEmptyTwoThreeNode
*/
TwoThreeNode* createNewChild(TwoThreeNode* wkgPtr,
    TwoThreeNode* parPtr, SelectionCode childCode)
{
    TwoThreeNode* newPtr = createEmptyTwoThreeNode();

    if (childCode == LEFT_CHILD_SELECT)
    {
        newPtr->centerData = createContractorDataFromAdt(wkgPtr->leftData);
        newPtr->leftChildPtr = wkgPtr->leftChildPtr;
        newPtr->rightChildPtr = wkgPtr->auxLeftPtr;

        if (newPtr->leftChildPtr != NULL)
        {
            newPtr->leftChildPtr->parentPtr = newPtr;
            newPtr->rightChildPtr->parentPtr = newPtr;
        }
    }

    else  // assume right child select
    {
        newPtr->centerData = createContractorDataFromAdt(wkgPtr->rightData);
        newPtr->leftChildPtr = wkgPtr->auxRightPtr;
        newPtr->rightChildPtr = wkgPtr->rightChildPtr;

        if (newPtr->rightChildPtr != NULL)
        {
            newPtr->leftChildPtr->parentPtr = newPtr;
            newPtr->rightChildPtr->parentPtr = newPtr;
        }
    }

    newPtr->parentPtr = parPtr;

    newPtr->numItems = ONE_DATA_ITEM;

    return newPtr;
}

/*
Name: displayDataInOrder
Process: user function to call for in order display,
         uses divider bars above and below display with title on top bar,
         calls helper, must display "Data Not Found - Display Aborted"
         if tree is empty
Function input/parameters: working pointer (TwoThreeNode *),
                           Boolean flag to indicate position and level display
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: displayDataInOrderHelper, printf
*/
void displayDataInOrder(TwoThreeNode* wkgPtr, bool showLocation)
{
    int levelCount = 0;

    printf("\n========== Two Three Tree Display ==========\n");

    if (wkgPtr != NULL)
    {
        displayDataInOrderHelper(wkgPtr, levelCount, showLocation);

        printf("\n============================================\n");
    }

    else
    {
        printf("\nData Not Found - Display Aborted\n");
    }
}

/*
Name: displayDataInOrderHelper
Process: helper function implements in order data display of two three tree,
         if Boolean flag is set, also shows position in node
         and level in tree,
         no display (printf) may be repeated for a given position
         (i.e., one printf for 'C', one printf for 'L', one printf for 'R')
Function input/parameters: working pointer (TwoThreeNode *), level count (int),
                           Boolean flag for level/position (bool)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: printf, displayDataInOrderHelper (recursively)
*/
void displayDataInOrderHelper(TwoThreeNode* wkgPtr,
    int levelCount, bool showLocation)
{
    // initialize variables

    if (wkgPtr != NULL)
    {
        // recurse left
        displayDataInOrderHelper(wkgPtr->leftChildPtr, levelCount + 1, showLocation);

        // display data
        // display left
        if (wkgPtr->leftData != NULL)
        {
            printf("%d %s\n", wkgPtr->leftData->licenseNum, wkgPtr->leftData->businessName);

            if (showLocation)
            {
                printf("L%d\n", levelCount);
            }
        }

        // display center
        if (wkgPtr->centerData != NULL) {
            printf("%d %s\n", wkgPtr->centerData->licenseNum, wkgPtr->centerData->businessName);

            if (showLocation) {
                printf("C%d\n", levelCount);
            }
        }

        // display right
        if (wkgPtr->rightData != NULL) {
            printf("%d %s\n", wkgPtr->rightData->licenseNum, wkgPtr->rightData->businessName);

            if (showLocation) {
                printf("R%d\n", levelCount);
            }
        }

        // recurse center
        displayDataInOrderHelper(wkgPtr->ctrChildPtr, levelCount + 1, showLocation);

        // recurse right
        displayDataInOrderHelper(wkgPtr->rightChildPtr, levelCount + 1, showLocation);
    }
}

/*
Name: initializeTwoThreeTree
Process: returns NULL to initialize tree pointer
Function input/parameters: none
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: none
*/
TwoThreeNode* initializeTwoThreeTree()
{
    return NULL;
}

/*
Name: resolveThreeFourNode
Process: is passed the most recent node added,
         checks for 3/4 node, if so, breaks it up into separate left and right
         children and passes the center value to the node above,
         when complete, recurses to the parent node to resolve that as needed
Function input/parameters: address of root pointer (TwoThreeNode **),
                           pointer to working pointer (TwoThreeNode *)
Function output/parameters: root pointer address, in case root pointer
                            is updated (TwoThreeNode **)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: createEmptyTwoThreeNode, createContractorDataFromAdt,
              createNewChild, resolveThreeFourNode (recursively)
*/
void resolveThreeFourNode(TwoThreeNode** rootPtr, TwoThreeNode* wkgPtr)
{
    // initialize variables
    TwoThreeNode* leftChild;
    TwoThreeNode* rightChild;
    TwoThreeNode* newRoot = createEmptyTwoThreeNode();
    TwoThreeNode* parent;
    TwoThreeNode* newChild;

    // check that num items is equal to 4
    if (wkgPtr->numItems != ZERO_DATA_ITEMS && wkgPtr->numItems != ONE_DATA_ITEM
        && wkgPtr->numItems != TWO_DATA_ITEMS && wkgPtr->numItems != THREE_DATA_ITEMS)
    {
        // create the child nodes
        leftChild = createNewChild(wkgPtr, wkgPtr->parentPtr, LEFT_CHILD_SELECT);
        rightChild = createNewChild(wkgPtr, wkgPtr->parentPtr, RIGHT_CHILD_SELECT);

        // assign left and right child nodes to new nodes
        leftChild->leftChildPtr = wkgPtr->leftChildPtr;
        leftChild->rightChildPtr = wkgPtr->auxLeftPtr;
        rightChild->leftChildPtr = wkgPtr->auxRightPtr;
        rightChild->rightChildPtr = wkgPtr->rightChildPtr;

        // assign parent node to new nodes
        if (wkgPtr->leftChildPtr != NULL)
        {
            wkgPtr->leftChildPtr->parentPtr = leftChild;
            wkgPtr->auxLeftPtr->parentPtr = leftChild;
        }
        if (wkgPtr->auxRightPtr != NULL)
        {
            wkgPtr->auxRightPtr->parentPtr = rightChild;
            wkgPtr->rightChildPtr->parentPtr = rightChild;
        }

        // assign values to parent node 
        if (wkgPtr == *rootPtr)
        {
            TwoThreeNode* newRoot = createEmptyTwoThreeNode();
            newRoot->centerData = createContractorDataFromAdt(wkgPtr->centerData);
            newRoot->leftChildPtr = leftChild;
            newRoot->rightChildPtr = rightChild;
            leftChild->parentPtr = newRoot;
            rightChild->parentPtr = newRoot;
            *rootPtr = newRoot;
        }

        else
        {
            parent = wkgPtr->parentPtr;
            newChild = createNewChild(wkgPtr, parent, NO_SELECT);

            if (parent->leftChildPtr == wkgPtr)
            {
                parent->leftChildPtr = newChild;
            }

            else if (parent->auxLeftPtr == wkgPtr)
            {
                parent->auxLeftPtr = newChild;
            }

            else if (parent->auxRightPtr == wkgPtr)
            {
                parent->auxRightPtr = newChild;
            }

            else
            {
                parent->rightChildPtr = newChild;
            }

            newChild->leftChildPtr = leftChild;
            newChild->rightChildPtr = rightChild;
            leftChild->parentPtr = newChild;
            rightChild->parentPtr = newChild;

            resolveThreeFourNode(rootPtr, parent);
        }
    }
}

/*
Name: toLowerCase
Process: tests for upper case character, if so, converts to lower case,
         otherwise, takes no action
Function input/parameters: test character (char)
Function output/parameters: none
Function output/returned: updated character as specified
Device input/---: none
Device output/---: none
Dependencies: none
*/
char toLowerCase(char testChar)
{
    if (testChar >= 'A' && testChar <= 'Z')
    {
        return testChar - 'A' + 'a';
    }

    return testChar;
}

#endif  // TWO_THREE_UTILITY_H
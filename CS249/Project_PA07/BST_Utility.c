#ifndef BST_UTILITY_H
#define BST_UTILITY_H

// header files
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "File_Input_Utility.h"
#include "StandardConstants.h"

// external constants


// data types

typedef struct ContractorStruct
   {
    int licenseNum;
    char businessName[ STD_STR_LEN ];
    char classCode[ MIN_STR_LEN ];
    char classDetail[ STD_STR_LEN ];
    char city[ MIN_STR_LEN ];

    struct ContractorStruct *leftChildPtr;
    struct ContractorStruct *rightChildPtr;
   } ContractorType;

// prototypes

/*
Name: clearTree
Process: recursively deallocates tree data, uses post order traversal algorithm
Function input/parameters: working pointer for recursion (ContractorType *)
Function output/parameters: none
Function output/returned: empty tree (NULL)
Device input/---: none
Device output/---: none
Dependencies: free, clearTree (recursively)
*/
ContractorType* clearTree(ContractorType* wkgPtr)
{
    if (wkgPtr != NULL)
    {
        // recurse left
        clearTree(wkgPtr->leftChildPtr);

        // recurse right
        clearTree(wkgPtr->rightChildPtr);

        // free ptr
        free(wkgPtr);
    }

    return wkgPtr;
}

/*
Name: compareStringSegments
Process: compares two string segments as follows:
         - compares the string segments up to the length of the test segment
         - if test segment segment is alphabetically greater 
                                      than the equal sized right string segment, 
         returns value greater than zero
         - if test segment segment is alphabetically less 
                                                  than the right string segment, 
         returns value less than zero
         - if string segments are equal returns zero
Function input/parameters: two strings to be compared (const char *)
Function output/parameters: none
Function output/returned: result as specified above (int)
Device input/---: none
Device output/---: none
Dependencies: strlen
*/
int compareStringSegments(const char* testSegment, const char* otherStr)
{
    // initialize variables
    int index;
    int testLen = strLen(testSegment);
    int otherLen = strLen(otherStr);

    // loop until end of both strings and while both have the same characters at the index
    while (index < testLen && index < otherLen
        && testSegment[index] == otherStr[index])
    {
        index++;
        // basically find the index at which the strings start to differ
    }

    // if char at index for both strings are equal then strings are equal
    if (testSegment[index] == otherStr[index])
    {
        return 0;
    }

    // otherwise check that test is greater than other
    if (testSegment[index] > otherStr[index])
    {
        return 1;
    }

    // otherwise assume test is less than other
    else
    {
        return -1;
    }
}

/*
Name: contractorDataToString
Process: sets data from node to formatted string
Function input/parameters: node with data to be set (ContractorType)
Function output/parameters: string array with result (char [])
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: sprintf
*/
void contractorDataToString(char destStr[], ContractorType contractorData)
{
    sprintf(destStr, "%d,%s,%s,%s,%s", 
        contractorData.licenseNum, contractorData.businessName, 
        contractorData.classCode, contractorData.classDetail, contractorData.city);
}

/*
Name: copyTree
Process: recursively duplicates the provided tree
         using a pre order traversal strategy
Function input/parameters: working pointer for recursion (ContractorType *)
Function output/parameters: none
Function output/returned: pointer to duplicate tree (ContractorType *)
Device input/---: none
Device output/---: none
Dependencies: initializeContractorNodeFromNode, copyTree (recursively)
*/
ContractorType* copyTree(ContractorType* wkgPtr)
{
    // initialize variables
    ContractorType* newNode;

    // check if wkgptr is null
    if (wkgPtr == NULL)
    {
        return NULL;
    }

    // otherwise start copying
    newNode = initializeContractorNodeFromNode(*wkgPtr);
    
    // recurse left
    newNode->leftChildPtr = copyTree(wkgPtr->leftChildPtr);

    // recurse right
    newNode->rightChildPtr = copyTree(wkgPtr->rightChildPtr);
}

/*
Name: displayInOrder
Process: recursively displays tree using in order traversal
Function input/parameters: working pointer for recursion (ContractorType *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: displayed as specified
Dependencies: contractorDataToString, printf, displayInOrder (recursively)
*/
void displayInOrder(ContractorType* ctrctrPtr)
{
    // initialize variables
    char displayStr[HUGE_STR_LEN];

    // check ptr is not null
    if (ctrctrPtr != NULL)
    {
        // recurse left
        displayInOrder(ctrctrPtr->leftChildPtr);

        // display string
        contractorDataToString(displayStr, *ctrctrPtr);
        printf("%s\n", displayStr);

        // recurse right
        displayInOrder(ctrctrPtr->rightChildPtr);
    }
}

/*
Name: displayPostOrder
Process: recursively displays tree using post order traversal,
         dynamically creates and frees string for display
Function input/parameters: working pointer for recursion (ContractorType *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: displayed as specified
Dependencies: contractorDataToString, printf, displayPostOrder (recursively)
*/
void displayPostOrder(ContractorType* ctrctrPtr)
{
    // initialize variables
    char displayStr[HUGE_STR_LEN];

    // check ptr is not null
    if (ctrctrPtr != NULL)
    {
        // recurse left
        displayInOrder(ctrctrPtr->leftChildPtr);

        // recurse right
        displayInOrder(ctrctrPtr->rightChildPtr);

        // display string
        contractorDataToString(displayStr, *ctrctrPtr);
        printf("%s\n", displayStr);
    }
}

/*
Name: displayPreOrder
Process: recursively displays tree using pre order traversal,
         dynamically creates and frees string for display
Function input/parameters: working pointer for recursion (ContractorType *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: displayed as specified
Dependencies: contractorDataToString, printf, displayPreOrder (recursively)
*/
void displayPreOrder(ContractorType* ctrctrPtr)
{
    // initialize variables
    char displayStr[HUGE_STR_LEN];

    // check ptr is not null
    if (ctrctrPtr != NULL)
    {
        // display string
        contractorDataToString(displayStr, *ctrctrPtr);
        printf("%s\n", displayStr);

        // recurse left
        displayInOrder(ctrctrPtr->leftChildPtr);

        // recurse right
        displayInOrder(ctrctrPtr->rightChildPtr);
    }
}

/*
Name: displaySelectionInOrder
Process: recursively displays selected items in tree using in order traversal,
         items are specified by starting segment of business name string,         
         dynamically creates and frees string for display
Function input/parameters: working pointer for recursion (ContractorType *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: displayed as specified
Dependencies: compareStringSegments, contractorDataToString, printf,
              displaySelectionInOrder (recursively)
*/
void displaySelectionInOrder(ContractorType* ctrctrPtr, char* nameSegment)
{
    char str[HUGE_STR_LEN];

    // check ptr not null
    if (ctrctrPtr != NULL)
    {
        // recurse left
        displaySelectionInOrder(ctrctrPtr->leftChildPtr, nameSegment);

        // check for string equal to nameSegment
        if (compareStringSegments(nameSegment, ctrctrPtr->businessName) == 0)
        {
            // print out
            contractorDataToString(str, *ctrctrPtr);
            printf("%s\n", str);
        }

        // recurse right
        displaySelectionInOrder(ctrctrPtr->rightChildPtr, nameSegment);
    }
}

/*
Name: getDataFromFile
Process: uploads data from file with unknown number of data sets,
         has internal Boolean to test for data input success
Function input/parameters: file name (const char *)
Function output/parameters: none
Function output/returned: pointer to BST holding data (ContractorType *)
Device input/---: data from HD
Device output/monitor: if internal Boolean set, displays uploaded values
Dependencies: openInputFile, readStringToDelimiterFromFile, 
              checkForEndOfInputFile, readIntegerFromFile, 
              readCharacterFromFile, insertRawData, printf, closeInputFile
*/
ContractorType* getDataFromFile(const char* fileName)
{
    ContractorType* root = NULL;
    bool success = false;
    int licenseNum;
    char businessName[STD_STR_LEN];
    char classCode[MIN_STR_LEN];
    char classDetail[STD_STR_LEN];
    char city[MIN_STR_LEN];

    if (openInputFile(fileName))
    {
        // read prime
        readStringToDelimiterFromFile(SEMI_COLON, businessName);
        readStringToDelimiterFromFile(SEMI_COLON, classCode);
        readStringToDelimiterFromFile(SEMI_COLON, classDetail);
        readStringToDelimiterFromFile(SEMI_COLON, city);

        while (!checkForEndOfInputFile() && notFull)
        {
            licenseNum = readIntegerFromFile();
            readCharacterFromFile();

            success = insertRawData(root, licenseNum, businessName,
                classCode, classDetail, city);

            // read re-prime
            readStringToDelimiterFromFile(SEMI_COLON, businessName);
            readStringToDelimiterFromFile(SEMI_COLON, classCode);
            readStringToDelimiterFromFile(SEMI_COLON, classDetail);
            readStringToDelimiterFromFile(SEMI_COLON, city);
        }

        closeInputFile();
    }

    return root;
}

/*
Name: initializeBST
Process: sets BST root pointer to NULL, root pointer is returned by address
Function input/parameters: address of working pointer (ContractorType **)
Function output/parameters: address of updated working pointer 
                            (ContractorType **)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: none
*/
void initializeBST(ContractorType** bstPtr)
{
    *bstPtr = NULL;
}

/*
Name: initializeContractorNodeFromData
Process: captures data from individual data items, 
         dynamically creates new node,
         copies data, and returns pointer to new node         
Function input/parameters: data to be copied (char *, int, double)
Function output/parameters: none
Function output/returned: pointer to new node as specified (ContractorType *)
Device input/---: none
Device output/---: none
Dependencies: malloc, strcpy, keyword sizeof
*/
ContractorType* initializeContractorNodeFromData(int ctrctrLicense,
    const char* ctrctrBizName, const char* ctrctrClassCode,
    const char* ctrctrClassDetail, const char* ctrctrCity)
{
    // initialize variables
    ContractorType* newContract;

    // allocate memory to new node
    newContract = malloc(sizeof(ContractorType));

    // copy data into new node
    newContract->licenseNum = ctrctrLicense;
    strcpy(newContract->businessName, ctrctrBizName);
    strcpy(newContract->classCode, ctrctrClassCode);
    strcpy(newContract->classDetail, ctrctrClassDetail);
    strcpy(newContract->city, ctrctrCity);

    // set left and right child pointers to null
    newContract->leftChildPtr = NULL;
    newContract->rightChildPtr = NULL;

    // return ptr
    return newcontract;
}

/*
Name: initializeContractorNodeFromNode
Process: captures data from source node pointer, dynamically creates new node,
         copies data, and returns pointer to new node         
Function input/parameters: node to be copied (ContractorType)
Function output/parameters: none
Function output/returned: pointer to new node as specified (ContractorType *)
Device input/---: none
Device output/---: none
Dependencies: initializeContractorNodeFromData
*/
ContractorType* initializeContractorNodeFromNode(const ContractorType source)
{   
    return initializeContractorNodeFromData(source.licenseNum, source.businessName, 
        source.classCode, source.classDetail, source.city);
}

/*
Name: insertNodeData
Process: recursively searches for available node in BST by name,
         creates new node and returns it to the calling function,
         if node is already in tree, data is overwritten,
         uses "look up" strategy
Function input/parameters: working pointer for recursion (ContractorType *),
                           license number (int), 
                           business name & class code (const char *),
                           class detail & city (const char *)
Function output/parameters: none
Function output/returned: pointer to new node as specified (ContractorType *)
Device input/---: none
Device output/---: none
Dependencies: insertRawData
*/
ContractorType* insertNodeData(ContractorType* wkgPtr,
    const ContractorType ctrctrNode)
{
    return insertRawData(wkgPtr, ctrctrNode.licenseNum, ctrctrNode.businessName,
        ctrctrNode.classCode, ctrctrNode.classDetail, ctrctrNode.city);
}

/*
Name: insertRawData
Process: recursively searches for available node in BST by name,
         creates new node and returns it to the calling function,
         if node is already in tree, data is overwritten,
         uses "look up" strategy
Function input/parameters: working pointer for recursion (ContractorType *),
                           license number (int), 
                           business name & class code (const char *),
                           class detail & city (const char *)
Function output/parameters: none
Function output/returned: pointer to new node as specified (ContractorType *)
Device input/---: none
Device output/---: none
Dependencies: compareStringSegments, setContractorRawData, 
              initializeContractorNodeFromData, insertRawData (recursively)
*/
ContractorType* insertRawData(ContractorType* wkgPtr,
    int ctrctrLicense,
    const char* ctrctrBizName,
    const char* ctrctrClassCode,
    const char* ctrctrClassDetail,
    const char* ctrctrCity)
{
    // initialize variables
    int compare;

    // check ptr is null
    if (wkgPtr == NULL)
    {
        // create new node and set root to it
        wkgPtr = initializeContractorNodeFromData(ctrctrLicense, ctrctrBizName, ctrctrClassCode,
            ctrctrClassDetail, ctrctrCity);

        return wkgPtr;
    }

    // get comparison value
    compare = compareStringSegments(ctrctrBizName, wkgPtr->businessName);

    // check if biz names are same
    if (compare == 0)
    {
        // overwrite data
        setContractorRawData(wkgPtr, ctrctrLicense, ctrctrBizName, ctrctrClassCode,
            ctrctrClassDetail, ctrctrCity);

        return wkgPtr;
    }

    // check if new node name is less than current
    else if (compare < 0)
    {
        // recurse left
        wkgPtr->leftChildPtr = insertRawData(wkgPtr->leftChildPtr, ctrctrLicense, ctrctrBizName,
            ctrctrClassCode, ctrctrClassDetail, ctrctrCity);
    }

    // otherwise assume new node name is greater than current
    else
    {
        // recurse right
        wkgPtr->rightChildPtr = insertRawData(wkgPtr->rightChildPtr, ctrctrLicense, ctrctrBizName,
            ctrctrClassCode, ctrctrClassDetail, ctrctrCity);
    }

    return wkgPtr;
}

/*
Name: isEmpty
Process: tests root node for NULL, returns result
Function input/parameters: pointer to root node (ContractorType *)
Function output/parameters: none
Function output/returned: result of test as specified (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool isEmpty(ContractorType* ctrctrPtr)
{
    if (ctrctrPtr == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
Name: removeFromMax
Process: recursively searches for max node,
         when found, node is unlinked from tree,
         and returned
Function input/parameters: pointer to parent and child nodes (ContractorType *)
Function output/parameters: none
Function output/returned: pointer to removed node (ContractorType *)
Device input/---: none
Device output/---: none
Dependencies: removeFromMax (recursively)
*/
ContractorType* removeFromMax(ContractorType* parentPtr,
    ContractorType* childPtr)
{
    // initialize variables

    if (childPtr->rightChildPtr == NULL)
    {
        if (parentPtr == childPtr)
        {
            return childPtr->leftChildPtr;
        }

        else
        {
            parentPtr->rightChildPtr = childPtr->leftChildPtr;
            return childPtr;
        }
    }

    return removeFromMax(childPtr, childPtr->rightChildPtr);
}

/*
Name: removeItem
Process: searches for item, if found, creates new node from search pointer,
         then removes item from tree using helper function,
         otherwise returns NULL
Function input/parameters: pointer to root node (ContractorType *),
                           name segment to be removed (const char *) 
Function output/parameters: pointer to removed data (ContractorType *)
Function output/returned: root/link to recursive pointer (ContractorType *)
Device input/---: none
Device output/---: none
Dependencies: search, setContractorNodeData, removeItemHelper
*/
ContractorType* removeItem(ContractorType* resultPtr, ContractorType* rootPtr,
    const char* toRemove)
{
    // initialize variables
    ContractorType* removeNode = search(rootPtr, toRemove);

    // check that node exists
    if (removeNode != NULL)
    {
        rootPtr = removeItemHelper(rootPtr, toRemove);
        setContractorNodeData(resultPtr, removeNode);
        return resultPtr;
    }

    return NULL;
}

/*
Name: removeItemHelper
Process: recursively searches for item, removes node,
         returns dynamic memory of removed node to OS,
         returns updated link to parent (at each recursive level),
         only one return at end of function
Function input/parameters: pointer to working node (ContractorType *),
                           name segment to be removed (const char *) 
Function output/parameters: none
Function output/returned: root/link to recursive parent
Device input/---: none
Device output/---: none
Dependencies: setContractorNodeData, free, removeItemHelper (recursively),
               compareStringSegments, removeFromMax
*/
ContractorType* removeItemHelper(ContractorType* wkgPtr,
    const char* toRemove)
{
    // initialize variables
    int compare;
    ContractorType* temp;

    // check if wkgptr is null
    if (wkgPtr == NULL)
    {
        return wkgPtr;
    }

    // get comparison value
    compare = compareStringSegments(toRemove, wkgPtr->businessName);

    // check that compare is less than 0
    if (compare < 0)
    {
        // recurse left
        wkgPtr->left = removeItemHelper(wkgPtr->left, toRemove);
        return wkgPtr;
    }

    // check that compare is greater than 0
    else if (compare > 0)
    {
        // recurse right
        wkgPtr->right = removeItemHelper(wkgPtr->right, toRemove);
        return wkgPtr;
    }

    // otherwise assume item found and remove it
    else
    {
        // check if wkgPtrs left and right childs are null
        if (wkgPtr->leftChildPtr == NULL && wkgPtr->rightChildPtr == NULL)
        {
            free(wkgPtr);
            return wkgPtr;
        }

        // otherwise assume at least one child is not null
        // check if left child is null
        else if (wkgPtr->leftChildPtr == NULL)
        {
            temp = wkgPtr->rightChildPtr;
            setContractorNodeData(wkgPtr, *temp);
            wkgPtr->rightChildPtr = removeItemHelper(wkgPtr->rightChildPtr, temp->businessName);
            return wkgPtr;
        }

        // check if right child is null
        else if (wkgPtr->rightChildPtr == NULL)
        {
            temp = wkgPtr->left;
            setContractorNodeData(wkgPtr, *temp);
            wkgPtr->left = removeItemHelper(wkgPtr->left, temp->businessName);
            return wkgPtr;
        }

        // if here assume both children arn't null
        else
        {
            temp = removeFromMax(wkgPtr, wkgPtr->left);
            setContractorNodeData(wkgPtr, *temp);
            wkgPtr->left = removeItemHelper(wkgPtr->left, temp->businessName);
            return wkgPtr;
        }
    }
}

/*
Name: search
Process: recursively searches for item, if found, returns pointer to node,
         otherwise, returns NULL
Function input/parameters: pointer to working node (ContractorType *),
                           name segment to be removed (const char *)
Function output/parameters: none
Function output/returned: pointer to found node, or NULL, as specified
Device input/---: none
Device output/---: none
Dependencies: compareStringSegments, search (recursively)
*/
ContractorType* search(ContractorType* wkgPtr, const char* toFind)
{
    // initialize variables
    int compare;

    // check if wkgptr is null
    if (wkgPtr == NULL)
    {
        return wkgPtr;
    }

    //  get compare val
    compare = compareStringSegments(toFind, wkgPtr->businessName);

    // check for compare = 0
    if (compare = 0)
    {
        // found thus return
        return wkgPtr;
    }

    else if (compare < 0)
    {
        // recurse left
        return search(wkgPtr->leftChildPtr, toFind);
    }

    // otherwise recurse right
    else
    {
        return search(wkgPtr->rightChildPtr, toFind);
    }
}

/*
Name: setContractorRawData
Process: copies data from raw data to destination pointer,
         does not copy or set node child pointers
Function input/parameters: license number (int), 
                           business name & class code (const char *),
                           class detail & city (const char *)
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
    const char* ctrctrCity)
{
    destPtr->ctrctrLicense = ctrctrLicense;
    strcpy(destPtr->ctrctrBizName, ctrctrBizName);
    strcpy(destPtr->ctrctrClassCode, ctrctrClassCode);
    strcpy(destPtr->ctrctrClassDetail, ctrctrClassDetail);
    strcpy(destPtr->ctrctrCity, ctrctrCity);
}

/*
Name: setContractorNodeData
Process: copies data from source node to destination pointer,
         does not copy or set node child pointers
Function input/parameters: node to be copied (ContractorType)
Function output/parameters: destination pointer (ContractorType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: setContractorRawData
*/
void setContractorNodeData(ContractorType* destPtr,
    const ContractorType source)
{
    setContractorRawData(destPtr, source.licenseNum, source.businessName,
        source.classCode, source.classDetail, source.city);
}

#endif   // BST_UTILITY_H

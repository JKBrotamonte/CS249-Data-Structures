// Exam function list
// - You must be able to develop any of the following functions
//   as either pseudo code or C program code
// - You must also be able to recognize and apply Big O complexity
// - In some cases, you may be provided code and you will
//   be required to explain what action the code executes and/or 
//   what the code produces with a given set of input data
// - You must also be prepared to explain or implement a graph
//   traversal, either with BFS or DFS

Project 6
=========
StudentLinkedListType * clearLinkedList(StudentLinkedListType * linkedList)
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
// 3/3

StudentLinkedListType* copyLinkedList(StudentLinkedListType* linkedList)
{
    StudentNodeType* wkgSrcPtr, * wkgDestPtr;
    StudentLinkedListType* destList
        = (StudentLinkedListType*)malloc(sizeof(StudentLinkedListType));

    destList->headPtr = NULL;

    if (linkedList->headPtr != NULL)
    {
        wkgSrcPtr = linkedList->headPtr->nextPtr;

        destList->headPtr = createLLNodeWithNode(linkedList->headPtr);

        wkgDestPtr = destList->headPtr;

        while (wkgSrcPtr != NULL)
        {
            wkgDestPtr->nextPtr = createLLNodeWithNode(wkgSrcPtr);

            wkgDestPtr = wkgDestPtr->nextPtr;

            wkgSrcPtr = wkgSrcPtr->nextPtr;
        }
    }

    return destList;
}
// given by teach

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
// 3/3

StudentNodeType* createLLNodeWithNode(StudentNodeType* srcPtr)
{
    return createLLNodeWithData(srcPtr->name, srcPtr->gender,
    srcPtr->studentId, srcPtr->gpa);
}
// 3/3

void deepCopyNode(StudentNodeType* dest, const StudentNodeType src)
{
    // copy data
    strcpy(dest->name, src->name);
    dest->gender = src->gender;
    dest->studentId = src->studentId;
    dest->gpa = src->gpa;
}
// 3/3

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
// 3/3

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
// 3/3

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
    return false;
}
// 3/3

StudentLinkedListType* initializeLinkedList()
{
    StudentLinkedListType* newList = (StudentLinkedListType*)malloc(sizeof(StudentLinkedListType));
    newList->headPtr = NULL;

    return newList;
}
// 3/3

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
            return false;
        }
    }

    return true;
}
// got 2/3
// they said no need to free here and code is a bit redundant

bool linkedListIsEmpty(const StudentLinkedListType linkedList)
{
    if (linkedList->headPtr == NULL)
    {
        return true;
    }

    return false;
}
// 3/3

bool removeLLDataAtLocation(StudentNodeType *removedElement, StudentLinkedListType *linkedList, int removeIndex)
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
            // use deep copy to move shit
            deepCopyNode(&temp->nextPtr, wkgPtr->nextPtr->nextPtr)
            deepCopyNode(temp, wkgPtr->nextPtr)
            deepCopyNode(wkgPtr, temp)
            deepCopyNode(wkgPtr->nextPtr, temp->nextPtr)
            deepCopyNode(wkgPtr, wkgPtr->nextPtr)
        }
        free(temp);

        return true;
    }

    else
    {
        // not found
        setEmptyNodeData(&removedElement);
        return false;
    }
}
// got 1/3
// they said should use deep copy to move data up
// and doesn't need to use free removedElement unless element is found
// i think fixed

void setEmptyNodeData(StudentNodeType* element)
{
    element->name[0] = "NULL_CHAR";
    element->gender = "x";
    element->studentId = 0;
    element->gpa = 0.0;
}
// 3/3

bool setLLAdtDataAtLocation(StudentLinkedListType* linkedList,
    const StudentNodeType student, int listLocation)
{
    return insertLLRawDataEngine(&linkedList, student.name, student.gender,
        student.studentId, student.gpa, listLocation, AT_LOCATION);
}
// 3/3

bool setLLRawDataAtLocation(StudentLinkedListType* linkedList,
    const char* name, char gender, int studentId,
    double gpa, int listLocation)
{
    return insertLLRawDataEngine(&linkedList, name, gender,
        studentId, gpa, listLocation, AT_LOCATION);
}
// 3/3

Project 7
=========

ContractorType * clearTree(ContractorType* wkgPtr)
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
// 3/3

int compareStringSegments(const char* testSegment, const char* otherStr)
{
    int diff, index = 0;
    int testSegStrLen = strlen(testSegment);

    while (index < testSegStrLen)
    {
        diff = testSegment[index] - otherStr[index];

        if (diff != 0)
        {
            return diff;
        }

        index++;
    }

    return 0;
}
// from teach

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

    return newNode;
}
// 2/3 should return at end
// fixed?

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
// 3/3

void displayPostOrder(ContractorType* ctrctrPtr)
{
    // initialize variables
    char displayStr[HUGE_STR_LEN];

    // check ptr is not null
    if (ctrctrPtr != NULL)
    {
        // recurse left
        displayPostOrder(ctrctrPtr->leftChildPtr);

        // recurse right
        displayPostOrder(ctrctrPtr->rightChildPtr);

        // display string
        contractorDataToString(displayStr, *ctrctrPtr);
        printf("%s\n", displayStr);
    }
}
// 2/3 should use function displayPostOrder not displayInOrder
// fixed

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
        displayPreOrder(ctrctrPtr->leftChildPtr);

        // recurse right
        displayPreOrder(ctrctrPtr->rightChildPtr);
    }
}
// 2/3 should use displayPreOrder not displayInOrder function
// fixed

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
// 3/3

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
// 1/3
// should initialize root
// should handle header case

ContractorType* initializeContractorNodeFromData(int ctrctrLicense,
    const char* ctrctrBizName, const char* ctrctrClassCode,
    const char* ctrctrClassDetail, const char* ctrctrCity)
{
    // initialize variables
    ContractorType* newContract;

    // allocate memory to new node
    newContract = (ContractorType*)malloc(sizeof(ContractorType));

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
// 2/3 malloc incorrect
// fixed

ContractorType* insertNodeData(ContractorType* wkgPtr,
    const ContractorType ctrctrNode)
{
    return insertRawData(wkgPtr, ctrctrNode.licenseNum, ctrctrNode.businessName,
        ctrctrNode.classCode, ctrctrNode.classDetail, ctrctrNode.city);
}
// 3/3

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
// 3/3

bool isEmpty(ContractorType* ctrctrPtr)
{
    return(ctrctrPtr == NULL);
}
// 1/3 needs to be one line of code
// fixed

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
// 0/3
// should return child ptr if null
// should set parent rightChild to child leftChild if null
// second if/else unnecessary
somePtr* removeFromMax(somePtr* parPtr, somePtr* childPtr)
{
    if (childPtr->rightChildPtr != NULL)
    {
        return removeFromMax(childPtr, childPtr->rightChildPtr);
    }
    parPtr->rightChildPtr = childPtr->leftChildPtr;
    return childPtr;
}
return the current pointer
// from teach
// just use this

ContractorType* removeItem(ContractorType* resultPtr, ContractorType* rootPtr,
    const char* toRemove)
{
    // initialize variables
    ContractorType* removeNode = search(rootPtr, toRemove);

    // check that node exists
    if (removeNode != NULL)
    {
        setContractorNodeData(resultPtr, removeNode);
        rootPtr = removeItemHelper(rootPtr, toRemove);
        return resultPtr;
    }

    return NULL;
}
// 2/3 should setContractorNodeData before calling helper
// fixed i think


ContractorType *removeItemHelper( ContractorType *wkgPtr, const char *toRemove ) - as pseudocode
ContractorType * removeItemHelper(ContractorType * wkgPtr, const char* toRemove)
{
    // get an integer from the comparison
    compareResult = compareStringSegment(toRemove, wkgPtr->businessName);

    // check for comparison < 0 - check for less than current

        // recurse to the left, assign result to left child pointer

    // otherwise, check for comparison > 0 - check for greater than current

        // recurse to the right, assign result to right child pointer

    // value found

    // otherwise, check for removed node, no left child

        // set the working pointer to the right child

    // otherwise, check for remove node, no right child

        // set the working pointer to the left child

    // node has two children

    // otherwise, check for left child has no right child

        // set the data from the left child into the current wkg node
    setContractorNodeData(wkgPtr, *wkgPtr->leftChildPtr);

    // set the left child of the wkg pointer to a temp pointer
    tempPtr = wkgPtr->leftChildPtr;

    // link the current (wkg) node's left child ptr to the temp pointer's left child ptr
    wkgPtr->leftChildPtr = tempPtr->leftChildPtr;

    // free the temp pointer
    free(tempPtr);

    // otherwise

        // set temp pointer to removeFromMax

        // set the current/wkg node to the data from the temp pointer

        // free the temp pointer

    // return wkg pointer
}
// psuedo code from teach
// in the thing he said remember the psuedo code so will be focusing on that
ContractorType * removeItemHelper(ContractorType * wkgPtr,
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
// 0/3 cannot return something that's been freed
// should call free in every case that items found
// no need to call removeItemHelper when items been found
// in the case of 2 children should check need for balance
// wont even bother with this

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
// 3/3 but last else unnecessary, makes it so returns are only inside ifs
// not changing it cause still 3/3 and don't wanna fuck that shi up


Project 8
=========

TwoThreeNode * addAndOrganizeData(TwoThreeNode* wkgPtr,
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
// 0/3
// need a business name string to compare with
// temp is used in all the if statements

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
// 0/3
// check if the wrkPtr is NULL first
// check for a one data node then check for a two data node
void addItemWithAdtDataHelper(TwoThreeNode** rootPtrAddress,
    TwoThreeNode* wkgPtr,
    ContractorType* newData
)
{
    // initialize function/variables
    TwoThreeNode* newNode;
    char bizName[STD_STR_LEN];
    strcpy(bizName, wkgPtr->businessName);
    // check for empty tree
    if (wkgPtr == NULL)
    {
        // create an empty node
        newNode = createEmptyTwoThreeNode();

        // set number of items to 1
        newNode->numItems = ONE_DATA_ITEM;
        // set center data to create data function, with data
        newNode = createContractorDataFromAdt(newData); // check for
        dereference
            // assign node to root pointer
            * rootPtrAddress = newNode;
    }
    // otherwise, check for one node, not leaf
    else if (wkgPtr->numItems == ONE_ITEM && wkgPtr->leftChild != NULL)
    {
        // check for new data less than the node's center data
        if (compareStrings(newData->businessName, wkgPtr->centerData -
        > businessName) < 0)
        {
            // recurse to the left
            addItemWithAdtDataHelper(rootPtrAddress, wkgPtr->leftChildPtr,
                newData);
        }
        // otherwise
        else
        {
            // recurse to the right
            addItemWithAdtDataHelper(rootPtrAddress, wkgPtr->rightChildPtr,
                newData);
        }
    }
    // otherwise, check for two node, not leaf
    else if (wkgPtr->numItems == TWO_DATA_ITEMS && wkgPtr->rightChild != NULL
        )
    {
        // check for new data less than the node's left data
        if (compareStrings(newData->businessName, wkgPtr->leftData -
        > businessName) < 0)
        {
            // recurse left
            addItemWithAdtDataHelper(rootPtrAddress, wkgPtr->leftChildPtr,
                newData);
        }
        // otherwise, check for new data greater than the node's right data
        else if (compareStrings(newData->businessName, wkgPtr->rightData -
        > businessName) > 0)
        {
            // recurse right
            addItemWithAdtDataHelper(rootPtrAddress, wkgPtr->rightChildPtr,
                newData);
        }
        // otherwise, assume center link
        else
        {
            // recurse center
            addItemWithAdtDataHelper(rootPtrAddress, wkgPtr->centerChildPtr,
                newData);
        }
    }
    // otherwise, assume found node - handle getting into node
    else
    {
        // call addAndOrganizeData with current pointer
        wkgPtr = addAndOrganizeData(wkgPtr, newData);

        // call resolveThreeFourNode with current pointer
        resolveThreeFourNode(rootPtr, wkgPtr);
    }
}
// code from teach
// just use this

void addItemWithAdtDataHelper(TwoThreeNode** rootPtrAddress,
    TwoThreeNode* wkgPtr,
    ContractorType* newData)
{
    // initialize function/variables
    
    // check for empty tree
    
        // create an empty node
        
        // set number of items to 1
        (*rootPtr)->nu
        // set center data to create data function, with data
        
        // assign node to root pointer
        * rootPtrAddress = newNode;
    
    // otherwise, check for one node, not leaf
    if (wkgPtr->numItems == ONE_ITEM && wkgPtr->leftChild != NULL)
        // check for new data less than the node's center data
        
            // recurse to the left
        
        // otherwise
        
            // recurse to the right
        
        // otherwise, check for two node, not leaf
        
            // check for new data less than the node's left data
        
                // recurse left
        
            // otherwise, check for new data greater than the node's right data
        
                // recurse right
        
            // otherwise
        
                // recurse center
        
        // otherwise, assume found node - handle getting into node
        
            // call addAndOrganizeData with current pointer
        
            // call resolveThreeFourNode with current pointer
}
// given psuedo code

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
// 3/3

TwoThreeNode* clearTwoThreeNode(TwoThreeNode* wkgPtr)
{
    if (wkgPtr != NULL)
    {
        free(wkgPtr);
    }

    return NULL;
}
// must check if the child pointers are null and free them aswl
TwoThreeNode* clearTwoThreeNode(TwoThreeNode* wkgPtr)
{
    if (wkgPtr->leftData != NULL)
    {
        free(wkgPtr->leftData);
    }
    if (wkgPtr->centerData != NULL)
    {
        free(wkgPtr->centerData);
    }
    if (wkgPtr->rightData != NULL)
    {
        free(wkgPtr->rightData);
    }
    free(wkgPtr);
}
// from teach
// just use this

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

        return wkgPtr;
    }

    return NULL;
}
// return wkg ptr in the if statement
// fixed

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
// 3/3 change the other one to be like this one aswl

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
// 0/3
// leftChildPtr not leftData
// check for one data item and two data item
TwoThreeNode* copyTwoThreeTree(TwoThreeNode* wkgPtr)
{
    // initialize function/variables
    TwoThreeNode* newNode = NULL;
    // check for current pointer not NULL
    if (wkgPtr != NULL)
    {
        // create a new node
        newNode = createEmptyTwoThreeNode();

        // assign recursion to left link of current to new node's left link
        newNode->leftChildPtr = copyTwoThreeTree(wkgPtr->leftChildPtr);
        // check for left child not NULL
        if (newNode->leftChildPtr != NULL)
        {
            // set the left child's parent back to new node
            newNode->leftChildPtr->parentPtr = newNode;
        }
        // check for current node is a one node
        if (wkgPtr->numItems == ONE_DATA_ITEM)
        {
            // set the new node to a one node
            newNode->numItems = ONE_DATA_ITEM;
            // create new data, assign from center node to new node center
            node
                newNode->centerData = createContractorDataFromAdt(wkgPtr -
> centerData);
        }
        // otherwise, assume current node is a two node
        else
        {
            // set the new node to a two node
            newNode->numItems = TWO_DATA_ITEM;
            // create new data, assign from left node to new node left node
            newNode->leftData = createContractorDataFromAdt(wkgPtr->leftData
            );
            // assign recursion to center link of current to new node's
            center link
                newNode->centerChildPtr = copyTwoThreeTree(wkgPtr -
> centerChildPtr);
            // check for child not NULL
            if (newNode->centerChildPtr != NULL)
            {
                // set the child's parent back to the new node
                newNode->centerChildPtr->parent = newNode;
            }
            // create new data, assign from right node to new node right node
            newNode->rightData = createContractorDataFromAdt(wkgPtr -
> rightData);
        }
        // assign recursion to right child
        newNode->rightChildPtr = copyTwoThreeTree(wkgPtr->rightChildPtr);
        // check for right child not NULL
        if (newNode->rightChildPtr != NULL)
        {
            // set the right child's parent back to new node
            newNode->rightChildPtr->parentPtr = newNode;
        }
    }
    // end of check for not NULL
    // return new node
    return newNode;
}
// code from teach
// just use this


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
// 3/3

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
// 3/3

TwoThreeNode *createNewChild( TwoThreeNode *wkgPtr, 
                                TwoThreeNode *parPtr, SelectionCode childCode )  - as pseudocode



TwoThreeNode * createNewChild(TwoThreeNode * wkgPtr,
        TwoThreeNode * parPtr, SelectionCode childCode)
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
// 3/3 just turn this into psuedo code

TwoThreeNode* createNewChild(TwoThreeNode* wkgPtr,
    TwoThreeNode* parPtr, SelectionCode childCode)
{
    // initialize function/variables
    
    // check for left childCode
    
        // create a new node
    
        // set to one node
    
        // set new node center to the wkg left data
    
        // set new node left link to wkg left link
    
        // set new node right link to wkg aux left link

        // check for new node left link not NULL
    
            // set left link's parent's link to new node
    
            // set right link's parent's link to new node
    
    // otherwise
    
        // create a new node
    
        // set to one node
    
        // set new node center to the wkg right data
    
        // set new node left link to wkg aux right link
    
        // set new node right link to wkg right link

        // check for new node right link not NULL
    
            // set left link's parent's link to new node
    
            // set right link's parent's link to new node
    
    // set number to one
    
    // set new node's parent pointer to (parameter) parent pointer
    
    // return pointer to new node
    
    return NULL; // temporary stub return
}
// given psuedo code

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
// 1/3
// if statements should check for one data and two data items

TwoThreeNode* initializeTwoThreeTree()
{
    return NULL;
}
// 3/3

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
// 0/3
// check for num items equal to 3
// in the if check for one and two data items
void resolveThreeFourNode(TwoThreeNode** rootPtr, TwoThreeNode* wkgPtr)
{
    // create a parent pointer

    // check for three node

        // check for node at root

            // create a new node, with new left/right children

            // set center data of wkg node to center data of new node

            // set node num items to ONE_DATA_ITEM

            // set the root pointer to this new node

            // set the new node's left child to a new child (taken care of)

            // set the new node's right child to a new child (...)

        // check for parent is one node

            // check for wkg node is left of parent

                // shift parent's center data to the right

                // set the parent's left data to wkg node center data

                // set the parent's center data to NULL

                // set the parent's left child to a new child (LEFT)

                // set the parent's center child to a new child (RIGHT)

                // set this to a two node

            // check for wkg node is right of parent

                // shift parent's center data to the left

                // set the parent's right data to wkg node center data

                // set the parent's center data to NULL

                // set the parent's center child to a new child (LEFT)

                // set the parent's right child to a new child (RIGHT)

                // set this to a two node

        // check for parent is two node

            // check for wkg node is left of parent

                // set to three node

                // set the parent's center data (ptr) to parent's left data

                // set left data to wkg ptr's center data

                // set the aux right node pter to center node ptr

                // set the center node ptr to NULL

                // set the left child ptr to a new child (LEFT)

                // set the aux left child ptr to a new child (RIGHT)

            // check for wgk node is center under parent

            // check for wkg node is right of parent

        // end of check for two node parent

        // free wkg pointer

        // recurse with the parent pointe

    // end of check for three node

}
// psuedo code from teach

char toLowerCase(char testChar)
{
    if (testChar >= 'A' && testChar <= 'Z')
    {
        return testChar - 'A' + 'a';
    }

    return testChar;
}
// 3/3


Project 9
=========

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
// 0/__
// lost points not really sure tf happened here
int accessPriority(PriorityCode code)
{
    // declaring variables
    static int* array = NULL, int size = 0;
    int testValue = NON_VALID_PRIORITY;
    // check for INITIALIZE
    // create an array of integers
    // check for GET
    // on: isInArray
    // assign the value to the array
    // update the size
    // check for CLEAR
    // clear the array
    // return the testValue
}
if (verbose)
{
    printf("%3dC", levelNum);
}
printf("the data for that node");
// from teach but incomplete i think

bool addRawDataToHeap(HeapType* heap,
    int ctrctrLicense,
    const char* ctrctrBizName,
    const char* ctrctrClassCode,
    const char* ctrctrClassDetail,
    const char* ctrctrCity,
    int priority, bool displayFlag)
{
    // initialize variables

    // check if heap is full
    if (heap->size < MIN_HEAP_CAPACITY)
    {
        // heap not full thus continue

        // include display flag thing here but idk how
        if (displayFlag == true)
        {
            // do something
        }

        // add data to struct
        newContractor = setContractorRawData(heap->array[size], ctrctrLicense, ctrctrBizName,
            ctrctrClassCode, ctrctrClassDetail, ctrctrCity, priority);
        // add contractor struct to heap
        heap->array[heap->size] = newContractor;

        heap->size += 1;

        // bubble up
        bubbleUp(heap, heap->size - 1, displayFlag);
        return true;
    }
    // if here assume heap full
    return false;
}
// all declared variables are uneccessary
// should not be printing here
// does not increment heap size before calling bubbleup
// seccond parameter of bubbleup should use heap->size - 1
// fixed i think

void bubbleUp(HeapType* heap, int currentIndex, bool displayFlag)
{
    // initialize variables
    int parentIndex;
    ContractorType temp;

    // base case
    if (currentIndex <= 0)
    {
        return 0;
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
// 2/5
// only two assignment statements for swap
// says gur but idk which one
// should check if currentIndex>0 before performing operations
// should call setcontractor outside of priority checks


HeapType* clearHeap(HeapType* heap)
{
    free(heap->array);

    free(heap);

    return heap;
}
// should not set size=0
// missing free for heap
// fixed

bool getDataFromFile( HeapType *heap, const char *fileName, bool displayFlag )
// don't have

bool heapIsEmpty(const HeapType heap)
{
    return(heap.size == 0);
}
// 5/5

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
// 2/5
// should check that heap size > 0 before performing operations
// incorrectly sets returned value
// should decrement size before calling setcontractor
void removeFromHeap(ContractorType* returned,
    HeapType* heap, bool displayFlag)
{
    if (heap->size > 0)
    {
        // remove item at index zero
        // assign it to where it needs to be
        returned = heap->array[0];

        heap->size -= 1;

        // set top of heap to last element
        setContractorStructData(&heap->array[0], heap->array[heap->size - 1]);

        // check display flag
        if (displayFlag)
        {
            printf("Removing business: %s", returned->businessName);
        }

        // trickle down the new top of heap to its correct pos
        trickleDown(heap, 0, displayFlag);
    }
}
// this is probably better
// not sure about the returned value tho


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
// 5/5

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
// 0/5
// only two assignment statements for swap
// gur tf
// incorrect algorithm
void trickleDown(HeapType* heap, int currentIndex, bool displayFlag)
{
    // initialize function/variables
    // create children indices
    int rightChildIndex = currentIndex * 2 + 2;
    int leftChildIndex = currentIndex * 2 + 1;
    // create parent data
    ContractorType parentData, transitionData;
    // set a transition index to the parent index
    int transitionIndex = currentIndex;
    // set parent Data
    setContractorStructData(&parentData, heap->array[currentIndex]);
    // check if left child index less than array size
    // AND if left child priority is less than the parent priority
    if (leftChildIndex < heap->size
        && heap->array[leftChildIndex].priority
        < heap->array[currentIndex].priority)
    {
        // set a transition child data to the left child data
        setContractorStructData(&transitionData, heap->array[leftChildIndex]);
        // set a transition index to the left child index
        transitionIndex = leftChildIndex;
    }
    // check if right child index less than array size
    // AND if right child priority is less then the parent's priority
    // AND if right child's priority is less than the left child's priority
    if (rightChildIndex < heap->size
        && heap->array[rightChildIndex].priority < heap->array[currentIndex].
        priority
        && heap->array[rightChildIndex].priority < heap->array[leftChildIndex
        ].priority)
    {
        // set a transition child data to the right child data
        setContractorStructData(&transitionData, heap->array[rightChildIndex]);
        // set a transition index to the right child index
        transitionIndex = rightChildIndex;
    }
    // check for transition index not equal to parent index
    if (transitionIndex != currentIndex)
    {
        // set the array at the parent index to the child data
        setContractorStructData(&heap->array[currentIndex], transitionData);
        // set the array at the child index to the parent data
        setContractorStructData(&heap->array[transitionIndex], parentData);
        // recurse on the transition index
        trickleDown(heap, transitionIndex);
    }
}
// from teach


Project 10
==========

---BST Component
void countTreeNodeHelper(CityDataType * cdtPtr, int* counter)
{
    // initialize variables


    if (cdtPtr != NULL)
    {
        countTreeNodeHelper(cdtPtr->leftChildPtr, counter); // recursively count nodes in the left subtree
        (*counter) += 1; // increment the counter to count the current node
        countTreeNodeHelper(cdtPtr->rightChildPtr, counter); // recursively count nodes in the right subtree
        (*counter) += 1;
    }
}
// 1/3
// Should be *counter = *counter + 1; Just doing ++ only increments the pointer position.
// should increment count before calling count on right child

int findOptimalTreeHeight(CityDataType *cdtPtr)
{
    // initialize function/variables
       // initialize/set division counter to zero
    int divCtr = 0;
    // get the number of items in the tree
    int numItems = countTreeNodes(cdtPtr);


    // loop while the remaining value is greater than zero
    while (numItems > 1)
    {
        // divide the remaining value by 2 and reset
        numItems = numItems / 2;

        // increment division counter
        divCtr = divCtr + 1;
    }

    return divCtr;
}
// given by teach

int findActualTreeHeight(CityDataType* cdtPtr)
{
    int leftHt, rightHt;

    if (cdtPtr != NULL)
    {
        leftHt = findActualTreeHeight(cdtPtr->leftChildPtr);
        rightHt = findActualTreeHeight(cdtPtr->rightChildPtr);

        return findMax(leftHt, rightHt) + 1;
    }

    return -1;
}
// given by teach

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
// another option cause 3/3

---Hash Table Component
void addHashItem(HashTableType * hashData, char* cityName, int cityPop)
{
    // initialize function/variables
    int hashIndex;
    CityDataType* city;

    // get the hash index
    hashIndex = generateHashIndex(*hashData, cityName);

    // set the data into a node
    city = initializeCityNodeFromData(cityName, cityPop);

    // assign the data to element with the BST
    hashData->table[hashIndex]
        = insert(hashData->table[hashIndex], *city);

    // deallocate the node
    free(city);
}
// given by teach

HashTableType* clearHashTable(HashTableType* hashData)
{
    // initialize variables
    int index;

    // Loop through each slot in the table
    for (index = 0; index < hashData->capacity; index++)
    {
        // Get the head node of the linked list at this slot
        CityDataType* head = hashData->table[index];

        // Loop through the linked list and free each node
        while (head != NULL)
        {
            CityDataType* temp = head;
            head = head->next;
            free(temp);
        }

        // Set the slot to NULL to indicate an empty list
        hashData->table[index] = NULL;
    }

    // Free the table itself
    free(hashData->table);

    // Set the capacity to 0 to indicate an empty hash table
    hashData->capacity = 0;
}
// 0/3
// gur twice and incorrect algorithm



HashTableType* copyHashTable(HashTableType* source)
{
    // Create a new hash table with the same capacity as the source table
    HashTableType* newTable = initializeHashTable(source->capacity);
    int index;

    // Copy the data from the source table into the new table
    for (index = 0; index < source->capacity; index++)
    {
        CityDataType* sourceTree = source->table[index];
        CityDataType* newTree = NULL;

        if (sourceTree != NULL)
        {
            newTree = copyTree(sourceTree);
        }

        newTable->table[index] = newTree;
    }

    return newTable;
}
// 0/3
// gur twice
// incorrect algorithm


double findMean(int* array, int size)
{
    int index;

    int sum = 0;

    for (index = 0; index < size; index++)
    {
        sum += array[index];
    }

    return (double)sum / size;
}
// 3/3
// gur 3 times
// unnecessary check for size == 0

int findMedian(int* array, int size)
{
    int listIndex, searchIndex, minIndex, temp;

    for (listIndex = 0; listIndex < size - 1; listIndex++)
    {
        minIndex = listIndex;

        for (searchIndex = listIndex + 1;
            searchIndex < size; searchIndex++)
        {
            if (array[searchIndex] < array[minIndex])
            {
                minIndex = searchIndex;
            }
        }
        temp = array[listIndex];
        array[listIndex] = array[minIndex];
        array[minIndex] = temp;
    }

    return array[size / 2];
}
// given by teach

int generateHashIndex(const HashTableType hashData, const char* cityName)
{
    int strLen = strlen(cityName);
    int strIndex = 0, loopIndex = 0, sum = 0;


    while (loopIndex < strLen || loopIndex < MINIMUM_HASH_CHARACTERS)
    {
        sum = sum + (int)(cityName[strIndex]);

        loopIndex = loopIndex + 1;

        strIndex = (strIndex + 1) % strLen;
    }

    return sum % hashData.capacity;
}
// given by teach

HashTableType *getHashDataFromFile( const char *fileName, 
                                                   int capacity, bool verbose )
// yeah fuck no

HashTableType* initializeHashTable(int capacity)
{
    // initialize variables
    int index;
    int wkgIndex;

    HashTableType* hashData = malloc(sizeof(HashTableType));
    if (hashData == NULL)
    {
        return NULL;
    }
    hashData->capacity = capacity;

    hashData->table = malloc(capacity * sizeof(CityDataType*));
    if (hashData->table == NULL)
    {
        free(hashData);
        return NULL;
    }

    // Initialize each element of the hash table with an empty BST
    for (int index = 0; index < capacity; index++)
    {
        hashData->table[index] = initializeBST();
        if (hashData->table[index] == NULL)
        {
            for (int wkgIndex = 0; wkgIndex < index; wkgIndex++)
            {
                clearTree(hashData->table[wkgIndex]);
            }
            free(hashData->table);
            free(hashData);
            return NULL;
        }
    }

    return hashData;
}
// 0/3
// gur
// incorrect algorithm
HashTableType* initializeHashTable(int capacity)
{
    HashTableType* hashPtr;
    int index = 0;

    // allocate mem for table
    hashPtr = (HashTableType*)malloc(sizeof(HashTableType));
    hashTable->capacity = capacity;

    // allocate memory for array of nodes
    hashPtr->array = (somethingtype*)malloc(sizeof(somethingtype * capacity));
    for (index = 0; index < capacity; index++)
    {
        hashPtr->array[index] = NULL;
    }

    return hashPtr;
}
// better i think

CityDataType* removeHashItem(HashTableType* hashData, const char* cityName)
{
    // Find the hashed index for the given city name
    int index = generateHashIndex(*hashData, cityName);

    // If the table is empty at the calculated index, return NULL
    if (hashData->table[index] == NULL)
    {
        return NULL;
    }

    // Otherwise, remove the city node from the binary search tree at that index
    CityDataType* removedNode = removeItem(&(hashData->table[index]), cityName);

    // Return the removed node
    return removedNode;
}
// 3/3
// unecessary null return

CityDataType* searchHashTable(const HashTableType hashData,
    const char* cityName)
{
    // Get the hash index for the given city name
    int hashIndex = generateHashIndex(hashData, cityName);

    // Search for the city name in the BST at the hash index
    CityDataType* cityNode = search(hashData.table[hashIndex], cityName);

    // Return the pointer to the node if it was found
    return cityNode;

}
// 3/3

void showHashTableStatus(const HashTableType hashData)
{
    printf("Hash Table Status:\n\n");

    // Get counts and calculate statistics
    int* counts = (int*)malloc(sizeof(int) * hashData.capacity);
    int totalNodes = 0;
    int maxNodes = 0;
    int minNodes = INT_MAX;
    for (int i = 0; i < hashData.capacity; i++)
    {
        int count = countTreeNodes(*(hashData.table + i));
        *(counts + i) = count;
        totalNodes += count;
        if (count > maxNodes)
        {
            maxNodes = count;
        }
        if (count < minNodes)
        {
            minNodes = count;
        }
    }
    double meanNodes = findMean(counts, hashData.capacity);
    int medianNodes = findMedian(counts, hashData.capacity);

    // Display counts and statistics
    printf("BST Items : ");
    for (int i = 0; i < hashData.capacity; i++)
    {
        printf("%3d ", *(counts + i));
    }
    printf("\n");

    printf("           ");
    for (int i = 0; i < hashData.capacity; i++)
    {
        printf("--- ");
    }
    printf("\n");

    printf("Hash Index: ");
    for (int i = 0; i < hashData.capacity; i++)
    {
        printf("%3d ", i);
    }
    printf("\n\n");

    printf("Max nodes in one element    : %4d\n", maxNodes);
    printf("Min num nodes in one element: %4d\n", minNodes);
    printf("Range (min to max)          : %4d\n", maxNodes - minNodes);
    printf("Mean num nodes              : %6.2f\n", meanNodes);
    printf("Median node num             : %4d\n", medianNodes);
    printf("Total nodes processed       : %4d\n", totalNodes);
    printf("=========================================================================================\n");

    // Free memory allocated for counts
    free(counts);
}
// 0/3
// gur twice
// incorrect algorithm

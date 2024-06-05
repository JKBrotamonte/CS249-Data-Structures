// Exam function list
// - You must be able to develop any of the following functions
//   as either pseudo code or C program code
// - You must also be able to analyze a given set of code
//   for Big O complexity
// - In some cases, you may be provided code and you will
//   be required to explain what action the code executes and/or 
//   what the code produces with a given set of input data

// PA01 ---------------------------------------------------------------------------
int **clearTwoDimArray( int **array, int numRows )
  {
      // initialize/define variables
      int index;

      for (index = 0; index < numRows; index++)
      {
          free(array[index]);
      }

      free(array);

      return NULL;
  }


void copyArray( int **destArray, int **srcArray, int numRows, int numCols )
{
    // initialize variables
    int rowIndex, colIndex;

    // loop through rows
    for (rowIndex = 0; rowIndex < numRows; rowIndex++)
    {
        // loop through columns
        for (colIndex = 0; colIndex < numCols; colIndex++)
        {
            // copy data
            destArray[rowIndex][colIndex] = srcArray[rowIndex][colIndex];
        }
    }

    // return
    return srcArray;
}

int **createTwoDimArray( int numRows, int numCols )
{
    // initialize variables
    int** twoDimPtr;
    int rowIndex, colIndex;

    // allocate space for the rows
    twoDimPtr = (int**)malloc(numRows * sizeof(int**));

    for (rowIndex = 0; rowIndex < numRows; rowIndex++)
    {
        // allocate space for each column
        twoDimPtr[rowIndex] = (int**)malloc(numCols * sizeof(int**));

        // loop across columns
        for (colIndex = 0; colIndex < numCols; colIndex++)
        {
            // set all elements to zero
            twoDimPtr[rowIndex][colIndex] = 0;
        }
    }

    // return
    return twoDimPtr;
}

void displayArray(int** array, int numRows, int numCols, char* title)
{

}

// for this one my grader said "only one line of text for each displayed statement so delete some of the printf("\n")
int getArraySide( int maxSideSize )
{
    // initialize variables
    int arraySide;

    // ask for array side
    printf("Enter array side (3 - %d): ", maxSideSize);
    scanf("%d", &arraySide);

    printf("\n");

    // check if arraySide is within bounds
    if (arraySide < 3 || arraySide > maxSideSize)
    {
        // not in bounds, say incorrect entry and reloop through
        printf("Incorrect entry - ");
        getArraySide(maxSideSize);
    }

    // correct entry found thus return it
    return arraySide;
}

int getRandBetween(int lowLimit, int highLimit)
{
    // initialize variables
    int result;

    result = rand() % (highLimit - lowLimit + 1)) + lowLimit;

    return result;
}

// redo only got 1/5 from grader
// they said "{only one line of text for each displayed statement}
// text line for error message used twice
// data structure should be accessed with arrows not dots
// when done recursively, the header will print multiple times
// incorrect error checks
void getRangeToRemove( RangeType *inputData, int numRows, int numCols )
{
    // create a max variable from the rows & cols
    // set initialized Boolean here

    // print the header

    // start loop

        // prompt for the low limit, one to max provided

        // check for correct low limit

            // prompt for the high limit, include one above low up to max provided

            // capture input

        // test all three conditions, assign the results to the Boolean
        // - low val < high val
        // - low val >= 1
        // - high val <= maximum value

        // check the Boolean
    if (!successfulInput)

        // print "Incorrect entry - Retry: "

 // end loop - using a Boolean variable
        while (!successfulInput);
}

// they commented "returns result immediately upon finding value" but got 5/5
bool isInArray( int **array, int numRows, int numCols, int searchVal )
{
    // initialize/define variables
    int rowIndex, colIndex;

    // loop through rows
    for (rowIndex = 0; rowIndex < numRows; rowIndex++)
    {
        // loop through columns
        for (colIndex = 0; colIndex < numCols; colIndex++)
        {
            if (array[rowIndex][colIndex] == searchVal)
            {
                // value found return true
                return true;
            }
        }
    }

    // end of loop value not found
    return false;
}

// lost a point because i return on a void function
void loadArrayWithValues( int **array, int numRows, int numCols )
{
    // initialize variables
    int max = numRows * numCols;
    int rowIndex;
    int colIndex = 0;
    int input;

    // loop across rows
    for (rowIndex = 0; rowIndex < numRows; rowIndex++)
    {
        // loop across columns
        while (colIndex < numCols)
        {
            // get a random number
            input = getRandBetween(1, max);

            // check if that number is already in array
            if (!isInArray(array, numRows, numCols, input))
            {
                // if not in array add to array
                array[rowIndex][colIndex] = input;

                // increment colIndex
                colIndex++;
            }
        }
    }
}

void printChars( int numChars, char outChar )
{
    if (numChars > 0)
    {
        printChars(numChars - 1, outChar);
    }

    printf("%c", outChar);
}

void removeRange( int **array, int numRows, int numCols, RangeType range )
{
    // initialize variables
    int index;

    for (index = range.lowVal; index <= range.highVal; index++)
    {
        setElementToZero(array, numRows, numCols, index);
    }
}

// grader commented returns result immediately upon finding value but still 5/5
bool setElementToZero( int **array, int numRows, int numCols, int searchValue )
{
    // initialize/define variables
    int rowIndex, colIndex;

    // loop through rows
    for (rowIndex = 0; rowIndex < numRows; rowIndex++)
    {
        // loop through columns
        for (colIndex = 0; colIndex < numCols; colIndex++)
        {
            if (array[rowIndex][colIndex] == searchVal)
            {
                // value found
                // set to zero
                array[rowIndex][colIndex] = 0;

                // return true
                return true;
            }
        }
    }

    // end of loop value not found
    return false;
}

// PA02 ---------------------------------------------------------------------------
bool addElementWithData(StudentDataType array[], int* size, int capacity,
    const char* name, char gender, int studentId, double gpa)
{
    // initialize variables

    // check if at capacity
    if (*size < capacity)
    {
        // not at capacity yet thus add the data
        // add at array[size] because if size is zero it would add at the first position
        strcpy(array[*size].name, name);
        array[*size].gender = gender;
        array[*size].gpa = gpa;
        array[*size].studentId = studentId;

        // increment size pointer
        (*size)++;

        // return true
        return true;
    }

    // if here then size is at or greater than capacity
    // thus return false
    return false;
}

// old code was wrong I believe this is right
bool addElementFromElement(StudentDataType array[],
    int* size, int capacity, const StudentDataType student)
{
    return addElementWithData(array[], *size, capacity, student.name, student.gender, student.studentId, student.gpa);
}

void copyArray( StudentDataType dest[], const StudentDataType src[], int size )
{
    // initialize variables
    int index;

    for (index = 0; index < size; index++)
    {
        deepCopy(&dest[index], src[index]);
    }
}

void deepCopy( StudentDataType *dest, const StudentDataType src )
{
    // initialize variables

    // copy over data
    strcpy(dest->name, src.name);
    dest->gender = src.gender;
    dest->gpa = src.gpa;
    dest->studentId = src.studentId;
}

// lost a point for the return in a void function
void displayData(const StudentDataType array[],
    int size, const char* subTitle)
{
    // initialize variables
    int index;

    // check that size isn't zero
    if (size <= 0)
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
            index, array[index].name, array[index].gender,
            array[index].studentId, array[index].gpa);
    }

    // just to make sure the next thing printed is on a new line
    printf("\n")
}

// lost a point because foundElement is a pointer but is treated as a variable
bool findElement(StudentDataType* foundElement,
    const StudentDataType array[], int size, const StudentDataType searchValue)
{
    // initialize variables
    int index;

    // loop through array
    for (index = 0; index < size; index++)
    {
        // check if names are same
        if (strcmp(array[index].name, searchValue.name) == 0)
        {
            deepCopy(*foundElement, array[index]);

            return true;
        }
    }

    // not found set foundElement to empty
    setEmptyElementData(*foundElement);
    return false;
}

// lost a point becasue 'n' in filename must be capitalized
// fixed
void getFileName( char *fileName )
{
// get file name
printf("Enter file name: ");
scanf("%s", &fileName);

// goto new line
printf("\n");
}

// lost 2 points because
// variable assignment within strcmp parameter list
// removed element is a pointer but treated as a variable
// no need to set last element to empty
// better to use a while loop and exit when found
bool removeElement(StudentDataType* removedElement,
    StudentDataType array[], int* size, const StudentDataType searchVal)
{
    // initialize variables
    int index;

    // loop through to find value
    for (index = 0; index < *size; index++)
    {
        // check if value found, using name as key like in findElement
        if (strcmp(array[index].name = searchVal.name))
        {
            // value found thus remove it
            deepCopy(&removedElement, array[index]);

            // shift remaining data down
            for (index = 0; index < *size; index++)
            {
                array[index] = array[index + 1];
            }

            // set last value to empty
            setEmptyElementData(array[*size - 1]);

            // decrement size
            (*size)--;

            // return true
            return true;
        }
    }

    // value not found thus set removedElement to empty
    setEmptyElementData(*removedElement);
    return false;
}

// lost a point because strcmp check is reversed
void runBubbleSort(StudentDataType array[], int size)
{
    // initialize vairbales
    int index;
    bool swapped = true;

    // loop until there are no swaps in a runthrough
    while (swapped)
    {
        // set boolean to false
        swapped = false;
        index = 0;

        // loop until next to last item
        while (index < size - 1)
        {
            // check if first greater than second (compare names)
            if (strcmp(array[index].name, array[index + 1].name > 0))
            {
                // swap them
                swapElements(array[], index, index + 1);

                // set swapped to true
                // this lets the function know there was a swap and it has to
                // do another run through
                swapped = true;
            }

            // increment index
            index++;
        }
        // end of loop, if there was a swap however the function will loop through again
    }
    // end of all swapping should be sorted
}
// another way of doing runBubbleSort
void runBubbleSort(StudentDataType array[], int size)
{
    int listIndex, bubbleIndex;

    // can be up to size or size - 1
    // loop across the list/array
    for (listIndex = 0; listIndex < size - 1; listIndex++)
    {
        // must stop at size - 1
        for (bubbleIndex = 0; bubbleIndex < size - 1; bubbleIndex++)
        {
            // check if name at bubbleIndex is bigger than name at bubbleIndex + 1
            if (strcmp(array[bubbleIndex].name, array[bubbleIndex + 1].name) > 0)
            {
                swapElements(array[], bubbleIndex, bubbleIndex + 1);
            }
        }
    }
}

// lost a point because result of strcmp is not checked
// and better to use a for loop when only looking for size
void runInsertionSort( StudentDataType array[], int size )
{
    // initialize variables
    int searchIndex, listIndex;
    StudentDataType temp;

    // loop across array
    for (listIndex = 0; listIndex < size; listIndex++)
    {
        // store data at listIndex into temp
        deepCopy(&temp, array[listIndex]);

        // start at index given by outer loop
        searchIndex = listIndex;

        // loop while not at bottom and while
        // test is less than item in slot below
        while (searchIndex > 0 &&
            strcmp(temp.name, array[searchIndex - 1].name) < 0)
        {
            // copy item below to the present
            deepCopy(&array[searchIndex], array[searchIndex - 1]);

            // decrement search index
            searchIndex--;
        }
        // end insertion loop

        // insert the character
        deepCopy(&array[searchIndex], temp);

        // increment list index
        listIndex++;
    }
    // end of list loop
    // list should be sorted
}

// 4/4 but said temp is unused
void runSelectionSort( StudentDataType array[], int size )
{
    // initialize variables
    int listIndex, lowIndex, curIndex;

    // loop across array
    for (listIndex = 0; listIndex < size; listIndex++)
    {
        // set initial temp to first element to be searched
        lowIndex = listIndex;

        // loop across list from current to end
        for (curIndex = listIndex + 1;
            curIndex < size; curIndex++)
        {
            // check if current is less than temp
            if (strcmp(array[curIndex].name, arry[lowIndex].name) < 0)
            {
                // set temp to val at curIndex
                lowIndex = curIndex;
            }
        }
        // end search loop

        // swap item at present position
        // with the item at lowest index
        swapElements(array[], listIndex, lowIndex);
    }
    // end of looping
    // list should be sorted
}

// said gender should be set to 'x'
// fixed
void setEmptyElementData( StudentDataType *element )
{
    // initialize variables

    // start setting things to empty
    // I know it says dependencies none but I wouldn't know how to do so
    // without the help of strcpy
    element->name[0] = "\0";
    element->gender = "x";
    element->studentId = 0;
    element->gpa = 0.0;
}

void swapElements( StudentDataType array[], int leftIndex, int rightIndex )
{
    // initialize variables
    StudentDataType temp;
    deepCopy(&temp, array[leftIndex);
    deepCopy(&array[leftIndex], array[rightIndex]);
    deepCopy(&array[rightIndex], temp);
}

int uploadStudentData(StudentDataType studentDataArray[],
    int capacity, const char* fileName)
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
    }

    return size;
}

// PA03 ---------------------------------------------------------------------------

// 3/3 but said must use resize before adding
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

void addElementFromElement(StudentArrayType* adtArray,
    const StudentDataType student)
{
    // initialize variables

    // call addElementWithData
    addElementWithData(adtArray, student.name, student.gender,
        student.studentId, student.gpa);
}

void checkForResize( StudentArrayType *adtArray )
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

void copyArrayType( StudentArrayType *dest, const StudentArrayType src )
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

StudentArrayType *initializeStudentArrayType( int initialCapacity )
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

bool removeElement( StudentDataType *removedElement, 
                   StudentArrayType *adtArray, const StudentDataType searchVal )
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

void runMerge( StudentArrayType *adtArray, 
                                  int lowIndex, int middleIndex, int highIndex )
{
    // initialize variables
    int leftIndex, rightIndex, wkgIndex;

    // First, using the index parameters, find the capacity needed
    // for the local array and create the array
    // Only one array is created
    int lclArrCap = highIndex - lowIndex + 1;
    StudentArrayType* lclArr = (StudentArrayType *) malloc(lclArrCap * sizeof(StudentArrayType));

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

    // append lcl to other
    for (wkgIndex = 0; wkgIndex < lclArrCap; wkgIndex++)
    {
        deepCopy(&adtArray->array[lowIndex + wkgIndex], lclArr->array[wkgIndex]);
    }

    free(lclArr);
}
// another way to do runMerge
void runMerge(StudentArrayType* adtArray,
    int lowIndex, int middleIndex, int highIndex)
{
    // initialize a lot of variables
       // wkgLow, lowMax, wkgHi, hiMax, wkgDest, txfrIndex;
    int wkgLow, lowMax, wkgHi, hiMax, wkgDest;
    // capacity, assign that to high - low + 1
    int tempArrayCap = highIndex - lowIndex + 1;
    // create the array here, assign to pointer/array name
    StudentDataType* tempArray
        = (StudentDataType*)malloc(tempArrayCap * sizeof(StudentDataType));

    // loop across the temp array
    for (txfrIndex = 0; txfrIndex < tempArrayCap; txfrIndex++)
    {
        // move parameter array elements into temp array
        deepCopy(&tempArray[txfrIndex],
            adtArray->array[lowIndex + txfrIndex]);
    }
    // end loop

    // set necessary indices
    wkgLow = 0;
    lowMax = middleIndex - lowIndex;
    wkgHi = wkgMax + 1;
    hiMax = tempArrayCapacity - 1;
    wkgDest = lowIndex;

    // start with comparison loop
    // - loop up to shortest of the two array parts
    // - wkgLow is <= lowMax and wkgHi <= hiMax
    while (wkgLow <= lowMax && wkgHi <= hiMax)
    {
        // check for value at the wkgLow is less than the value at wkgHi
        if (strcmp(tempArray[wkgLow].name, tempArray[wkgHi].name) < 0)
        {
            // assign value at the wkgLow to value at wkgDest
            deepCopy(&adtArray[wkgDest], tempArray[wkgLow]);

            // increment wkgLow
            wkgLow++;
        }
        // otherwise, assume value at wkgHi is less
        else
        {
            // assign value at wkgHi to value at wkgDest
            deepCopy(&adtArray[wkgDest], tempArray[wkgHi]);

            // increment wkgHi
            wkgHi++;
        }

        // increment the wkgDest
        wkgDest++;
    }
    // end comparison loop

    // clean up loop - left side of temp array
    // wkgLow is <= lowMax
    while (wkgLow <= lowMax)
    {
        // assign value at wkgLow to value at wkgDest
        deepCopy(&adtArray[wkgDest], tempArray[wkgLow]);

        // increment both indices
        wkgLow++; wkgDest++;
    }
    // end of left clean up loop

    // clean up loop - right side of temp array
    // wkgHi is <= highMax
    while (wkgHi <= highMax)
    {
        // assign value at wkgHi to value at wkgDest
        deepCopy(&adtArray[wkgDest], tempArray[wkgHi]);

        // increment both indices
        wkgHi++; wkgDest++;
    }
    // end of left clean up loop

    // free the temporary array
    free(tempArray);
}

// lost a point for returning in null function
void runMergeSort( StudentArrayType *adtArray )
{
    // check ptr is not null
    if (adtArray != NULL)
    {
        // call runMergeSortHelper with 0 as low and size-1 as high
        runMergeSortHelper(adtArray->array, 0, adtArray->size - 1);
    }
}

void runMergeSortHelper( StudentArrayType *adtArray, 
                                                   int lowIndex, int highIndex )
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

// lost a point for not using swapElements
int runPartition( StudentArrayType *adtArray, int lowIndex, int highIndex )
{
    // Identify the partition value at the beginning
    // of the array segment (at lowIndex)
    char* pivotValue;
    strcpy(pivotValue, adtArray->array[lowIndex].name);

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
            swapElements(adtArray->array, pivotIndex, wkgIndex);
        }
    }
    // end working loop 

    // Swap the original pivot value (at the low index)
    // with the value at the current pivot index
    swapElements(adtArray->array, lowIndex, pivotIndex);

    // return the pivot index
    return pivotIndex;
}
// another way of doing runPartition
int runPartition(StudentArrayType* adtArray, int lowIndex, int highIndex)
{
    // initializing variables
       // set the pivot index to the low index

    // loop across the list, starting at pivot index + 1, up to and including high index

        // check if the current(loop index) value is less than (or equal to) the value at low index

            // increment the pivot index

            // swap between the pivot index and the current index

    // end loop

    // swap between the found pivot index and the low index

    // return pivot index
    return 0;  // temp
}
// even better way
int runPartition(StudentArrayType* adtArray, int lowIndex, int highIndex)
{
    // initializing variables
    // set the pivot index to the low index
    int pivotIndex = lowIndex;
    int index;
    
    // loop across the list, starting at pivot index + 1, up to and including high index
    for (index = pitvotIndex + 1; index <= highIndex; index++)
    {
        // check if the current(loop index) value is less than (or equal to) the value at low index
        if (strcmp(adtArray->array[index].name,
            adtArray->array[lowIndex].name) <= 0)
        {
            // increment the pivot index
            pivotIndex++;

            // swap between the pivot index and the current index
            swapElements(adtArray, index, pivotIndex);
        }
    }

    // swap between the found pivot index and the low index
    swapElements(adtArray, lowIndex, pivotIndex);

    return pivotIndex;
}

void runQuickSort(StudentArrayType* adtArray)
{
    runQuickSortHelper(adtArray, 0, adtArray->size - 1);
}

// lost points because first runQuickSortHelper should have pivotIndex - 1
// should be fixed
void runQuickSortHelper( StudentArrayType *adtArray, 
                                                   int lowIndex, int highIndex )
{
    // initialize variables
    int pivotIndex;

    // check if lowIndex less than highIndex
    if (lowIndex < highIndex)
    {
        pivotIndex = runPartition(adtArray, lowIndex, highIndex);
        runQuickSortHelper(adtArray, lowIndex, pivotIndex - 1);
        runQuickSortHelper(adtArray, pivotIndex + 1, highIndex);
    }
}

// lost a point because gender should be 'x' and name should be NULL_CHAR
// fixed
void setEmptyElementData( StudentDataType *element )
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

void swapElements( StudentArrayType *adtArray, int leftIndex, int rightIndex )
{
    // initialize variables
    StudentDataType temp;
    deepCopy(&temp, adtArray->array[leftIndex]);
    deepCopy(&adtArray->array[leftIndex], adtArray->array[rightIndex]);
    deepCopy(&adtArray->array[rightIndex], temp);
}

bool uploadStudentData( StudentArrayType *adtArray, const char *fileName )
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

// PA04 ---------------------------------------------------------------------------
CellNodeType** clearSudokuArray(CellNodeType** arrayPtr)
{
    int rowIndex;

    for (rowIndex = 0; rowIndex < GRID_SIDE; rowIndex++)
    {
        free(arrayPtr[rowIndex]);
    }

    free(arrayPtr);

    return NULL;
}

CellNodeType **createSudokuArray()
{
    CellNodeType** arrayPtr;
    int rowIndex, colIndex;

    arrayPtr = (CellNodeType**)malloc(GRID_SIDE * sizeof(CellNodeType*));

    for (rowIndex = 0; rowIndex < GRID_SIDE; rowIndex++)
    {
        arrayPtr[rowIndex]
            = (CellNodeType*)malloc(GRID_SIDE * sizeof(CellNodeType));

        for (colIndex = 0; colIndex < GRID_SIDE; colIndex++)
        {
            arrayPtr[rowIndex][colIndex].fixedCell = false;
            arrayPtr[rowIndex][colIndex].value = 0;
        }
    }

    return arrayPtr;
}

bool createSudokuGameHelper(CellNodeType** gameArray,
        int rowPos, int colPos, bool showGrid)
{
    // Initialize variables
    int num;

    // if successfully filled the last cell return true
    if (rowPos == GRID_SIDE && colPos == GRID_SIDE)
    {
        return true;
    }

    // check if reached end of current row
    if (colPos == GRID_SIDE)
    {
        // move to next row
        colPos = 0;
        row++;
    }

    // check if current cell is a fixed cell
    if (gameArray[rowPos][colPos].fixedCell)
    {
        // move on to next cell
        return createSudokuGameHelper(gameArray, rowPos, colPos + 1, showGrid);
    }

    // try each value from 1 to 9 to put into cell
    for (num = 1; num <= GRID_SIDE; num++)
    {
        // check for any conflicts with current number
        if (!hasConflict(gameArray, rowPos, colPos, num))
        {
            // no colnflict thus set current cell val to current number
            gameArray[rowPos][colPos].value = num;

            // display trying num at cordinates
            printf("\nTrying: %d at (%d, %d)\n", num, rowPos, colPos);
            // display grid if showGrid == TRUE
            displayGrid(gameArray, showGrid);

            // recurse to try the next cell
            if (createSudokuGameHelper(gameArray, rowPos, colPos + 1 , showGrid))
            {
                // succesfully added a value to cell
                return true;
            }

            // if next cell can't be filled backtrack
            // set current to 0
            gameArray[rowPos][colPos].value = 0;

            // display backtracking at cordinates
            printf("\nBacktracking at (%d, $d)\n", rowPos, colPos);
            // display grid if showGrid is true
            displayGrid(gameArray, showGrid);
        }
    }

    // if here then have tried all numbers unsuccessfully
    return false;
}
// another way to do createSudokuGameHelper
bool createSudokuGameHelper(CellNodeType** gameArray,
    int rowPos, int colPos, bool showGrid)
{
    // initialize variables

    // check for off end of array - horizontal

        // increment the row

        // reset the column to zero

    // check for off end of array - vertical

        // return success/true

    // check for this being a fixed cell

        // call the recursion for the next column, and return it

    // loop from low val (1) to high val (9)

        // check for NO conflict

            // set the value in the element

            // call recursion for the next column, check for true

                // return success/true

            // unset the value, set to zero

    // end loop across numbers

    // return failure/false
    return false;  // temporary stub return
}

bool hasConflict( CellNodeType **gameArray, 
                                   int rowLocIndex, int colLocIndex, int value )
{
    return isInRow(gameArray, rowLocIndex, value)
        || isInCol(gameArray, colLocIndex, value)
        || isInSubGrid(gameArray, rowLocIndex, colLocIndex, value);
}

bool isInCol( CellNodeType **gameArray, int colIndex, int value )
{
    int rowIndex;

    for (rowIndex = 0; rowIndex < GRID_SIDE; rowIndex++)
    {
        if (gameArray[rowIndex][colIndex].value == value)
        {
            return true;
        }
    }

    return false;
}

bool isInRow( CellNodeType **gameArray, int rowIndex, int value )
{
    int colIndex;

    for (colIndex = 0; colIndex < GRID_SIDE; colIndex++)
    {
        if (gameArray[rowIndex][colIndex].value == value)
        {
            return true;
        }
    }

    return false;
}

bool isInSubGrid( CellNodeType **gameArray, 
                                   int rowLocIndex, int colLocIndex, int value )
{
    int rowStart = rowLocIndex - rowLocIndex % SUB_GRID_SIDE;
    int colStart = colLocIndex - colLocIndex % SUB_GRID_SIDE;
    int rowIndex, colIndex;

    for (rowIndex = rowStart;
        rowIndex < rowStart + SUB_GRID_SIDE; rowIndex++)
    {
        for (colIndex = colStart;
            colIndex < colStart + SUB_GRID_SIDE; colIndex++)
        {
            if (gameArray[rowIndex][colIndex].value == value)
            {
                return true;
            }
        }
    }

    return false;
}

// PA05 ---------------------------------------------------------------------------
StudentArrayType *clearArray( StudentArrayType *arrayPtr )
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

void copyArray( StudentArrayType *dest, const StudentArrayType src )
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

StudentArrayType *initializeArray( int initialCapacity )
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

bool insertArrayRawDataEngine( StudentArrayType *adtArray,
          const char *name, char gender, int studentId, double gpa,
                                    int listLocation, LocationCodeType locCode )
{
    // initialize variables

    // check for resize 

    // if( ( greater than or equal to zero AND less than size )
    //   OR ( check for location zero AND not at location ) )

        // check for after location AND check for size not equal to zero

            // increment listLoc


        // check for not at location

            // loop from size down to location

                // assign value from one below to current

            // end loop

        // assign data

    return false;  // temporary stub return
}
// or 
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
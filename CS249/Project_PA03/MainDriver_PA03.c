// header file
#include "ADT_StudentUtilities.h"

// local constants for program
const int INITIAL_CAPACITY = 30;

int main()
{
    // initialize function/program

       // initialize variables
    int searchIndex;
    char fileName[STD_STR_LEN];
    StudentArrayType* originalArray;
    StudentArrayType* originalWithRemoved;
    StudentArrayType* mergeSortArray;
    StudentArrayType* quickSortArray;
    StudentDataType tempElement;

    // show title
       // function: showTitle
    showTitle();

    // initialize array types
    originalArray = initializeStudentArrayType(INITIAL_CAPACITY);
    originalWithRemoved = initializeStudentArrayType(INITIAL_CAPACITY);
    mergeSortArray = initializeStudentArrayType(INITIAL_CAPACITY);
    quickSortArray = initializeStudentArrayType(INITIAL_CAPACITY);


    // get input

       // get file name
          // function: getFileName
    getFileName(fileName);

    // upload student data, test for success
       // function: uploadStudentData
    if (uploadStudentData(originalArray, fileName))
    {
        // process data

           // display original list

           // find element
        searchIndex = 35;
        findElement(&tempElement, *originalArray,
            originalArray->array[searchIndex]);
        printf("\nElement found: %s, %c, %d, %7.5f\n",
            tempElement.name,
            tempElement.gender,
            tempElement.studentId,
            tempElement.gpa);

        // remove element
        searchIndex = 20;
        copyArrayType(originalWithRemoved, *originalArray);
        removeElement(&tempElement, originalWithRemoved,
            originalArray->array[searchIndex]);

        printf("\nElement removed: %s, %c, %d, %7.5f\n",
            tempElement.name,
            tempElement.gender,
            tempElement.studentId,
            tempElement.gpa);


        // merge sort
           // function: copyArray, runMergeSort
        copyArrayType(mergeSortArray, *originalArray);
        runMergeSort(mergeSortArray);

        // quick sort
           // function: copyArray, runQuickSort
        copyArrayType(quickSortArray, *originalArray);
        runQuickSort(quickSortArray);

        // display results

           // display original list
              // function: displayData
        displayData(*originalArray, "Original Array");

        // display original list with removed item
           // function: displayData
        displayData(*originalWithRemoved, "Array with one item removed");

        // display merge sorted data
           // function: displayData
        displayData(*mergeSortArray, "Merge Sort Result");

        // display quick sorted data
           // function: displayData
        displayData(*quickSortArray, "Quick Sort Result");
    }

    else
    {
        printf("\nFailed to upload data - Program aborted\n");
    }

    // end program

       // deallocate array types
    originalArray = clearStudentArrayType(originalArray);
    originalWithRemoved = clearStudentArrayType(originalWithRemoved);
    mergeSortArray = clearStudentArrayType(mergeSortArray);
    quickSortArray = clearStudentArrayType(quickSortArray);

    // report end program
       // function: printf
    printf("\nProgram End\n");

    // return program success
    return 0;
}


#ifndef QUEUE_TYPE_H
#define QUEUE_TYPE_H

// header file(s)
#include "ADT_StudentDataEngine_Array.h"

// local constant(s)

// data structure(s)
typedef StudentArrayType QueueType;

// prototypes

/*
Name: clearQueue
Process: deallocates memory for QueueType and ArrayType
Function input/parameters: pointer to queue ADT (QueueType *)
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: clearArray
*/
QueueType* clearQueue(QueueType* queue)
{
    queue = clearArray(queue);

    return queue;
}

/*
Name: initializeQueue
Process: initializes Student Data Engine
Function input/parameters: initial capacity (int)
Function output/parameters: none
Function output/returned: pointer to initialized queue ADT (QueueType *)
Device input/---: none
Device output/---: none
Dependencies: initializeArray
*/
QueueType* initializeQueue(int initialCapacity)
{
    queue = initializeArray(initialCapacity);

    return queue;
}

/*
Name: dequeueAdtData
Process: returns data from front of queue
Function input/parameters: pointer to queue (QueueType *)
Function output/parameters: returned value if available,
                            or empty value otherwise,
                            pointer to updated queue ADT (QueueType *)
Function output/returned: Boolean result of specified operation (bool)
Device input/---: none
Device output/---: none
Dependencies: removeArrayDataAtLocation
*/
bool dequeueAdtData(StudentDataType* returnedValue, QueueType* queue)
{
    // dequeue from front of queue or beginning of list
    return removeArrayDataAtLocation(returnedValue, 0);
}

/*
Name: enqueueAdtData
Process: adds data as ADT to end of queue
Function input/parameters: pointer to queue (QueueType *),
                           data to be enqueued (const StudentDataType)
Function output/parameters: pointer to updated queue ADT (QueueType *)
Function output/returned: Boolean result of specified operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertArrayAdtDataBeforeLocation
*/
bool enqueueAdtData(QueueType* queue, const StudentDataType newData)
{
    // enqueue from end of queue or end of list
    return insertArrayAdtDataBeforeLocation(queue->array, newData, queue->size - 1);
}

/*
Name: enqueueRawData
Process: adds data as individual values to end of queue, updates rear index
Function input/parameters: pointer to queue (QueueType *),
                           data to be enqueued (const StudentDataType)
                           student name (const char *),
                           student gender (char),
                           student ID (int),
                           student gpa (double),
Function output/parameters: pointer to updated queue ADT (QueueType *)
Function output/returned: Boolean result of specified operation (bool)
Device input/---: none
Device output/---: none
Dependencies: insertArrayRawDataBeforeLocation
*/
bool enqueueRawData(QueueType* queue, const char* name, char gender,
    int studentId, double gpa)
{
    // enqueue from end of queue or end of list
    return insertArrayAdtDataBeforeLocation(queue->array, name, gender, studentId, gpa, queue->size - 1);
}

/*
Name: peekQueue
Process: returns data from front of queue without dequeueing it
Function input/parameters: pointer to queue (QueueType *)
Function output/parameters: returned value if available,
                            or empty value otherwise
Function output/returned: Boolean result of specified operation (bool)
Device input/---: none
Device output/---: none
Dependencies: getElementAtLocation
*/
bool peekQueue(StudentDataType* returnVal, const QueueType queue)
{
    return getElementAtLocation(returnVal, queue.array, 0);
}

/*
Name: queueIsEmpty
Process: returns true if queue array is empty, false otherwise
Function input/parameters: queue (const QueueType)
Function output/parameters: none
Function output/returned: Boolean result of specified operation (bool)
Device input/---: none
Device output/---: none
Dependencies: arrayIsEmpty
*/
bool queueIsEmpty(const QueueType queue)
{
    return arrayIsEmpty(queue.array);
}


#endif   // QUEUE_TYPE_H
#ifndef HASH_UTILITY_H
#define HASH_UTILITY_H

// header files
#include "SimpleBST_Utility.h"
#include <string.h>

// Data Types
typedef struct HashTableStruct
{
    CityDataType** table;

    int capacity;
} HashTableType;

// prototypes

/*
Name: addHashItem
Process: adds new item to hash table
Function input/parameters: pointer to hash table (HashTableType *),
                           city name (const char *), city population (int)
Function output/parameters: updated pointer to hash table (HashTableType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: generateHashIndex, initializeCityNodeFromData, insert
*/
void addHashItem(HashTableType* hashData, char* cityName, int cityPop)
{
    // Generate hash index for city name
    int hashIndex = generateHashIndex(*hashData, cityName);

    // Search for the city in the table
    CityDataType* cityNode = search((*hashData).table[hashIndex], cityName);

    if (cityNode != NULL) 
    {
        // City already exists in the table, update its population
        setCityNodeData(cityNode, cityName, cityPop);
    }
    else 
    {
        // City does not exist in the table, create a new node and insert it
        CityDataType* newCityNode = initializeCityNodeFromData(cityName, cityPop);
        (*hashData).table[hashIndex] = insert((*hashData).table[hashIndex], *newCityNode);
    }
}

/*
Name: clearHashTable
Process: clears contents of hash table, and then hash table itself
Function input/parameters: pointer to hash table (HashTableType *)
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: clearTree, free
*/
HashTableType* clearHashTable(HashTableType* hashData)
{
    // Loop through each slot in the table
    for (int i = 0; i < hashData->capacity; i++)
    {
        // Get the head node of the linked list at this slot
        CityDataType* head = hashData->table[i];

        // Loop through the linked list and free each node
        while (head != NULL)
        {
            CityDataType* temp = head;
            head = head->next;
            free(temp);
        }

        // Set the slot to NULL to indicate an empty list
        hashData->table[i] = NULL;
    }

    // Free the table itself
    free(hashData->table);

    // Set the capacity to 0 to indicate an empty hash table
    hashData->capacity = 0;
}

/*
Name: copyHashTable
Process: creates new hash table and makes duplicate
Function input/parameters: pointer to source hash table (HashTableType *)
Function output/parameters: none
Function output/returned: pointer to new hash table (HashTableType *)
Device input/---: none
Device output/---: none
Dependencies: initializeHashTable, copyTree
*/
HashTableType* copyHashTable(HashTableType* source)
{
    // Create a new hash table with the same capacity as the source table
    HashTableType* newTable = initializeHashTable(source->capacity);

    // Copy the data from the source table into the new table
    for (int i = 0; i < source->capacity; i++) 
    {
        CityDataType* sourceTree = source->table[i];
        CityDataType* newTree = NULL;

        if (sourceTree != NULL) 
        {
            newTree = copyTree(sourceTree);
        }

        newTable->table[i] = newTree;
    }

    return newTable;
}

/*
Name: findMean
Process: finds the mean of a set of integers
Function input/parameters: integer array (int *), size (int)
Function output/parameters: none
Function output/returned: mean of values (double)
Device input/---: none
Device output/---: none
Dependencies: none
*/
double findMean(int* array, int size)
{
    if (size == 0) 
    {
        // Handle the case where the array is empty
        return 0.0;
    }

    int sum = 0;
    for (int i = 0; i < size; i++) 
    {
        sum += array[i];
    }

    return (double)sum / size;
}

/*
Name: findMedian
Process: finds the median of a set of integers,
         assumes all input arrays will have an odd number of values
Function input/parameters: integer array (int *), size (int)
Function output/parameters: none
Function output/returned: median of values (int)
Device input/---: none
Device output/---: none
Dependencies: none
*/
int findMedian(int* array, int size)
{
    int middleIndex = size / 2;
    int median = array[middleIndex];
    return median;
}

/*
Name: generateHashIndex
Process: finds hashed index for given data item,
         sums integer values of city name characters,
         if city name length is less than MINIMUM_HASH_CHARACTERS,
         repeats going over the city letters as needed to meet this minimum
Function input/parameters: hash table (const HashTableType),
                           city name (const char *)
Function output/parameters: none
Function output/returned: generated hash index (int)
Device input/---: none
Device output/---: none
Dependencies: strlen
*/
int generateHashIndex(const HashTableType hashData, const char* cityName)
{
    int index = 0;
    int nameLength = strlen(cityName);

    if (nameLength < MINIMUM_HASH_CHARACTERS)
    {
        char tempCityName[MINIMUM_HASH_CHARACTERS];
        int i = 0;
        while (i < MINIMUM_HASH_CHARACTERS)
        {
            tempCityName[i] = cityName[i % nameLength];
            i++;
        }
        cityName = tempCityName;
        nameLength = MINIMUM_HASH_CHARACTERS;
    }

    for (int i = 0; i < nameLength; i++)
    {
        index += (int)cityName[i];
    }

    index %= hashData.capacity;

    return index;
}

/*
Name: getHashDataFromFile
Process: uploads data from city file with unknown number of data sets,
         provides Boolean parameter to display data input success
Function input/parameters: file name (char *), capacity (int),
                           verbose flag (bool)
Function output/parameters: none
Function output/returned: pointer to newly created hash table
                            (HashTableType *)
Device input/file: data from HD
Device output/---: none
Dependencies: openInputFile, initializeHashTable, readStringToDelimiterFromFile,
              readStringToLineEndFromFile, checkForEndOfInputFile,
              readCharacterFromFile, readIntegerFromFile,
              addHashItem, printf, closeInputFile
*/
HashTableType* getHashDataFromFile(const char* fileName,
    int capacity, bool verbose);

/*
Name: initializeHashTable
Process: dynamically creates new hash table with internal components
Function input/parameters: capacity (int)
Function output/parameters: none
Function output/returned: pointer to newly created hash table
                            (HashTableType *)
Device input/file: data from HD
Device output/---: none
Dependencies: malloc w/sizeof, initializeBST
*/
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

/*
Name: removeHashItem
Process: acquires hashed item, returns
Function input/parameters: pointer to hash table (HashTableType *),
                           city name (const char *)
Function output/parameters: none
Function output/returned: pointer to removed item (CityDataType *), or NULL
Device input/---: none
Device output/---: none
Dependencies: generateHashIndex, removeItem
*/
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

/*
Name: searchHashTable
Process: searches for value in table, returns pointer if found
Function input/parameters: hash table (const HashTableType),
                           city name (const char *)
Function output/parameters: none
Function output/returned: pointer to found item (CityDataType *), or NULL
Device input/---: none
Device output/---: none
Dependencies: generateHashIndex, search
*/
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

/*
Name: showHashTableStatus
Process: displays item counts from each BST element in the hash table,
         displays highest and lowest number of items in an element,
         displays range between highest and lowest,
         displays the mean and median,
         and displays the total number of nodes found,
         all in a formatted structure
Function input/parameters: hashTable (const HashTableType)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: hash data status displayed as specified
Dependencies: malloc w/sizeof, countTreeNodes, printf,
              findMean, findMedian, free
*/
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

#endif  //  HASH_UTILITY_H
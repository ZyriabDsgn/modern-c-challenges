// This is the solution I found, I'm not really satisfied with the `mergeArrays`
// function. I wish I found a more elegant solution, not needing 3 variables for
// the indexes... I decided to make all functions pure as I like it that way but
// I guess modifing the passed arguments would have been a nice solution to ease
// manual memory management
// I decided to go with `int` because I did not have the book at hand when I
// started and forgot it talked about using `double` or strings ¯\_(ツ)_/¯

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LENGTH 10

// Basic utility function for debugging purposes
void printArray(const int array[static 1], const size_t size, const char* msg) {
    for (size_t i = 0; i < size; i++) {
        printf("%s[%zu]: %d\n ", msg, i, array[i]);
    }
}

// Simple test function
bool isArraySorted(const int array[static 1], const size_t size) {
    // Finishing before the last element prevents undefined behavior
    // We can start at 0 because size_t is unsigned and thus cannot be negative
    for (size_t i = 0; i < size - 1; i++) {
        if (array[i - 1] > array[i] || array[i + 1] < array[i]) {
            return false;
        }
    }

    return true;
}

// Returns both arrays as one merged array
int* mergeArrays(const int a[static 1], const int b[static 1],
                 const size_t aSize, const size_t bSize) {
    size_t bufferSize = aSize + bSize;
    int* buffer = malloc(bufferSize * sizeof(int));

    // Each array has its own index variable
    // If one index is above its array size and the other is not, we can just
    // append the remaining values to the buffer
    // Otherwise, we check both arrays against each other,
    // relative to the next non-merged elements' index
    for (size_t i = 0, k = 0, j = 0; i < bufferSize; i++) {
        if ((j >= bSize && k < aSize) || (k < aSize && a[k] <= b[j])) {
            buffer[i] = a[k];
            k++;
        } else if ((k >= aSize && j < bSize) || (j < bSize && a[k] > b[j])) {
            buffer[i] = b[j];
            j++;
        }
    }

    return buffer;
}

int* mergeSort(int array[static 1], const size_t arraySize) {
    if (arraySize == 1) {
        return array;
    }

    // If the given array size is odd,
    // we will add the remaining element to the second one
    // e.g.: [1,2,3,4,5] -> [1,2] [3,4,5]
    bool isArraySizeOdd = arraySize % 2 == 1;
    size_t firstArraySize = arraySize / 2;
    size_t secondArraySize = firstArraySize + (isArraySizeOdd ? 1 : 0);

    int* firstArray = malloc(firstArraySize * sizeof(int));
    int* secondArray = malloc(secondArraySize * sizeof(int));

    // Copies the first half of the array
    memcpy(firstArray, array, firstArraySize * sizeof(int));
    // Copies the second half of the array
    memcpy(secondArray, array + firstArraySize, secondArraySize * sizeof(int));

    // The recursive calls to mergeSort will divide the given array until it is
    // made of one element, after that it will loop back to the mergeArrays
    // function that will actually sort each elements
    int* finalResult = mergeArrays(mergeSort(firstArray, firstArraySize),
                                   mergeSort(secondArray, secondArraySize),
                                   firstArraySize, secondArraySize);

    free(firstArray);
    free(secondArray);

    return finalResult;
}

int main(void) {
    int arr[ARRAY_LENGTH] = {5, 1, 6, 13, 742, 2, 6, 7, 1, 3};

    int* sorted = mergeSort(arr, ARRAY_LENGTH);

    // printArray(arr, 10, "before sorting");
    // puts("-----------------------");
    // printArray(sorted, length, "after sorting");

    printf("Is original sorted?: %d\n", isArraySorted(arr, ARRAY_LENGTH));
    printf("Is final sorted?: %d\n", isArraySorted(sorted, ARRAY_LENGTH));

    free(sorted);

    return EXIT_SUCCESS;
}

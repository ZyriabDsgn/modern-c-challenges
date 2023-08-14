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
void printArray(int const array[static 1], size_t const size,
                char const msg[static 1]) {
    for (size_t i = 0; i < size; i++) {
        printf("%s[%zu]: %d\n ", msg, i, array[i]);
    }
}

// Simple test function
bool isArraySorted(int const array[static 1], size_t const size) {
    // Finishing before the last element prevents undefined behavior
    for (size_t i = 1; i < size - 1; i++) {
        if (array[i - 1] > array[i] || array[i + 1] < array[i]) {
            return false;
        }
    }

    return true;
}

// Returns both arrays as one merged (and sorted) array
int* mergeArrays(int const a[static 1], int const b[static 1],
                 size_t const aSize, size_t const bSize) {
    size_t const bufferSize = aSize + bSize;
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

int* mergeSort(int const array[static 1], size_t const arraySize) {
    if (arraySize == 1) {
        return (int*)array;
    }

    // If the given array size is odd,
    // we will add the remaining element to the second one
    // e.g.: [1,2,3,4,5] -> [1,2] [3,4,5]
    bool const isArraySizeOdd = arraySize % 2 == 1;
    size_t const firstArrayHalf = arraySize / 2;
    size_t const secondArrayHalf = firstArrayHalf + (isArraySizeOdd ? 1 : 0);

    // The recursive calls to mergeSort will divide the given array until it is
    // made of one element, after that it will loop back to the mergeArrays
    // function that will actually sort each elements
    // passing the full `array` with `firstArrayHalf` will just process the
    // first half of `array` `array + firstArrayHalf` is basic pointer
    // arithmetics that skip the first half of `array`
    int* const finalResult =
        mergeArrays(mergeSort(array, firstArrayHalf),
                    mergeSort(array + firstArrayHalf, secondArrayHalf),
                    firstArrayHalf, secondArrayHalf);

    return finalResult;
}

int main(void) {
    int const arr[ARRAY_LENGTH] = {5, 1, -6, 13, 742, 2, 6, 7, 1, 3};

    int* sorted = mergeSort(arr, ARRAY_LENGTH);

    // printArray(arr, ARRAY_LENGTH, "before sorting");
    // puts("-----------------------");
    // printArray(sorted, ARRAY_LENGTH, "after sorting");

    printf("Is original sorted?: %d\n", isArraySorted(arr, ARRAY_LENGTH));
    printf("Is final sorted?: %d\n", isArraySorted(sorted, ARRAY_LENGTH));

    free(sorted);

    return EXIT_SUCCESS;
}

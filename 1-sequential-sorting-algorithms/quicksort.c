// This is my solution to the quicksort challenge
// There's many possible implementations and I'm not sure that this is the best
// I guess the challenge is more about playing around with the language
// rather than finding the cleanest/best way to write the algorithm.
// In order to change a bit, compared to mergesort, I decided to go take
// imperative approach and modify the passed array directly Also it's 100% stack
// memory so that's a nice change :)
// I had a function that would take the median element of 3 in the array (start,
// middle, end) but it was creating segfaults for some reason and I did not
// wanted to spend more time on this challenge as I am eager to continue the
// book :D Last element as pivot is good enough for the exercise, I guess ;)

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LENGTH 10

// Basic utility function for debugging purposes
void printArray(double const array[static 1], size_t const arraySize,
                char const msg[static 1]) {
    for (size_t i = 0; i < arraySize; i++) {
        printf("%s[%zu]: %g\n ", msg, i, array[i]);
    }
}

// Simple test function
bool isArraySorted(double const array[static 1], size_t const arraySize) {
    if (arraySize <= 1) {
        return true;
    }
    // Finishing before the last element prevents undefined behavior
    for (size_t i = 1; i < arraySize - 1; i++) {
        if (array[i - 1] > array[i] || array[i + 1] < array[i]) {
            return false;
        }
    }

    return true;
}

// Imperatively swaps two elements in the given array
void swapArrayElements(double array[static 2], size_t const firstIndex,
                       size_t const secondIndex) {
    double buffer = array[firstIndex];
    array[firstIndex] = array[secondIndex];
    array[secondIndex] = buffer;
}

// Iterates over the elements of `array`, from `first` to `last`
void z_qsort(double array[static 1], size_t const first, size_t const last) {
    if (first >= last) {
        return;
    }

    size_t left = first;
    size_t right = last;
    size_t const pivotIndex = last;

    // Divide & conquer
    // We create "virtual" partitions by increasing/decreasing 2 indices
    // `left` = elements smaller than the pivot
    // `right` = elements greater than the pivot
    // we stop stop when the element is greater/smaller than the pivot
    // we then swap the two pointed elements
    while (left < right) {
        // Will stop incrementing if the element is greater than the pivot
        // or if `left` is greater or equal to `last`
        while (left < last && array[left] <= array[pivotIndex]) {
            left++;
        }

        // At this point, `left` points to the the first element found
        // that is greater than the pivot

        // Will stop incrementing if the element is greater than the pivot
        while (array[right] > array[pivotIndex]) {
            right--;
        }

        // At this point, `right` points to the first element found
        // that is smaller or equal to the pivot

        // We swap these two so that they are on the right side of the pivot
        swapArrayElements(array, left, right);
    }

    // We swap the pivot with the latest element greater than the pivot
    // That means that now, the pivot is between the two elements
    // that are at the right place in their "partitioned arrays"
    // e.g.: if we had [5, 6, 80, 99, 1, <10>]
    // the array is now: [5, 6, 1, <10>, 99, 80]
    swapArrayElements(array, pivotIndex, right);

    // We sort the "partitioned array" left of the pivot
    z_qsort(array, first, right == 0 ? right : right - 1);

    // We sort the "partitioned array" right of the pivot
    z_qsort(array, right + 1, last);
}

int main(void) {
    double arr[ARRAY_LENGTH] = {4.0,   6.0,  10.5, 1.1,   0.0,
                                845.0, 13.0, 10.0, -14.0, 160.0};

    z_qsort(arr, 0, ARRAY_LENGTH - 1);

    printArray(arr, ARRAY_LENGTH, "Sorted");

    printf("Is sorted?: %d\n", isArraySorted(arr, ARRAY_LENGTH));

    return EXIT_SUCCESS;
}

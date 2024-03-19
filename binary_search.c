#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform binary search on an array
long binarySearch(long arr[], long size, long target) {
    long left = 0;
    long right = size - 1;

    while (left <= right) {
        long mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid; // Element found, return the index
        }
        else if (arr[mid] < target) {
            left = mid + 1; // Target is in the right half
        }
        else {
            right = mid - 1; // Target is in the left half
        }
    }

    return -1; // Element not found
}

int main() {
    // Dynamic Array
    long dynamicArrSize = 1000000;
    long* dynamicArr = (long*)malloc(dynamicArrSize * sizeof(long));

    // fill array with numbers
    for (long i = 0; i < dynamicArrSize; i++) {
        dynamicArr[i] = i;
    }
    // finding a number using binary search
    long target = 999999; // Choosing a target within the range of the array
    long result;

    result = binarySearch(dynamicArr, dynamicArrSize, target);
    if (result != -1) {
        printf("Dynamic Array: Element found at index %ld\n", result);
    }
    else {
        printf("Dynamic Array: Element not found\n");
    }
    
    free(dynamicArr); // Freeing dynamically allocated memory
    
    return 0;
}


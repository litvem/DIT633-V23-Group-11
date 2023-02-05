#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

#define MAX 3 // Max size of the array

int main() {
    srand(time(0));

    int* array = malloc(MAX * sizeof(int));

    for (int i = 0; i < MAX; i++) {
        array[i] = rand() % 99;
    }

    printf("\nThe value of the address of the array (pointer) is: %p\n", array);
    
    //Both options work:
    //printf("First integer in the array is (array[0]): %d\n", array[0]); 
    printf("First integer in the array is (array[0]): %d\n", *array);
    
    //Both options work:
    //printf("The last integer in the array is: %d\n", array[MAX -1]);
    printf("The last integer in the array is: %d\n", *(array + (MAX -1)));
    
    //Both options work:
    //printf("The size of an integer (number of bytes) is: %u \n", sizeof(*array)); // value of the first integer
    printf("The size of an integer (number of bytes) is: %lu \n", sizeof(int));

    printf("The size of the whole array in bytes is : %lu \n\n", MAX * sizeof(int));


    // print all values
    for (int i = 0; i < MAX; i++) {
        printf(" array[%d] = %1d\n", i, *(array + i)); // *(array + i) same as: array[i]
    }

    // print all values
    printf("\n-----------------\n");
    for (int i = 0; i < MAX; i++) {
        printf(" array[%d] = %2d  * 2 = %3d\n", i, *(array + i), *(array + i) * 2); // *(array + i) * 2  same as: array[i] * 2
    }

    // Free the array
    free(array);

    return 0;
}
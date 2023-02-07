// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 3
// Exercise 5
// Submission code: VF078-vF

/*------------------------------------------------------------------------------------------
Exercise 5: The program creates an array of integers and fills it with MAX number of random
  integers from 1 to 99.
  The program prints followings:

  The value of the address of the array (pointer) is:  xxxxxxxxxx 
  First integer in the array is (array[0]):  xxxxxxxxxx 
  The last integer in the array is:  xxxxxxxxxx 
  The size of an integer (number of bytes) is: xxxxxxxxx 
  The size of the whole array in bytes is: xxxxxxxxx 

  Next the program print out each integer value (using a pointer), then prints value multiplied 
  by 2.
-------------------------------------------------------------------------------------------*/

// Include section
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

// Define section
#define MAX 5                                       // Max size of the array

// Main function
int main() 
{
    // Give a random function a new seed
    srand(time(0));

    // Create a pointer to the first element of the array and 
    // dynamically allocate memory for the array. 
    int* array = malloc(MAX * sizeof(int));

    // Iterate over all element of the array of size MAX
    for (int i = 0; i < MAX; i++) 
    {
        // Randomly generate array element
        *(array + i) = rand() % 99;
    }

    // Print the address of the first element of the array in memory
    printf("\nThe value of the address of the array (pointer) is: %p\n", array);
    
    // Print first element in the array
    printf("First integer in the array is (array[0]): %d\n", *array);
    
    // Print last element in the array 
    printf("The last integer in the array is: %d\n", *(array + (MAX - 1)));
    
    // Print size of element in the array, in this case since array points to an integer
    // it provides the size of an integer.
    printf("The size of an integer (number of bytes) is: %u \n", sizeof(*array));
    
    // Print size of the whole array
    printf("The size of the whole array in bytes is : %lu \n\n", MAX * sizeof(int));

    // Iterate over all element of the array of size MAX
    for (int i = 0; i < MAX; i++) 
    {
        // Print array element value
        printf(" array[%d] = %1d\n", i, *(array + i));
    }

    printf("\n-----------------\n");

    // Iterate over all element of the array of size MAX
    for (int i = 0; i < MAX; i++) 
    {
        // Print array element value multiplied by two
        printf(" array[%d] = %2d  * 2 = %3d\n", i, *(array + i), *(array + i) * 2); // *(array + i) * 2  same as: array[i] * 2
    }

    // Free memory allocated to the array
    free(array);

    // End of the program
    return 0;
}
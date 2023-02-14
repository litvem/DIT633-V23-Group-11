// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 4
// Exercise 4
// Submission code: xxxxx

/*------------------------------------------------------------------------------------------
    Exercise 4: The program uses a declared unsorted test array and searches for a 
    specified number. The unsorted array is printed and if the value is found it 
    return the index of the first position of the specified number but in the case
    that the number is not found -1 is returned. Then the program uses bubble sort 
    to sort the test array in memory and prints the new sorted array. 
-------------------------------------------------------------------------------------------*/

// Include section
#include <stdlib.h>
#include <stdio.h>

// Define section
#define  searchNr 23                                    // Number to search for

// Function declarations
int search_number(int number, int tab[], int size);     // Function to search for a number in the array
void bubbleSort(int size, int tab[]);                   // Function that implements bubble sort
void swap(int* a, int* b);                              // Function that swap two values in memory
void printArray(int size, int tab[]);                   // Function that prints the values of the array

// Main function
int main()
{
    // Test array for the program
    int test[] = {1, 2, 34, 5, 67, 3, 23, 12, 13, 10};
    // Store size of the array
    int size = sizeof(test) / sizeof(test[0]);
    // Display the alue to search for
    printf("---------------\n Searching for:%d \n", searchNr, size);
    printf("---------------\n Unsorted array: ");
    // Display the unsorted array
    printArray(size, test);
    // Store the result of the search_number function
    int index = search_number(searchNr,test,size);
    
    printf("\n---------------\n Result:");
    // Case if index is bigger or equals to 0
    if(index >= 0)
    {
        // Display the index
        printf(" found at index %d\n", index); 
    }
    // Case if index is -1, i.e., the number was not found
    else
    {
        // Notify user about error
        printf(" %d. Number not found. \n", index);
    }

    // Call the function to sort the array in memory
    bubbleSort(size, test);
    // Display sorted array
    printf("---------------\n Sorted array: ");
    printArray(size, test);
    
    // End of the program
    return 0; 
}

// Definition of function that determine if the number is in the array
int search_number(int number, int tab[], int size)
{
    // Iterate over elements in array to find the given number
    for(int i = 0; i < size - 1 ; i++)
    {         
        // Case if given number is found
        if(number == tab[i])
        {   // Return value of its index
            return i;                        
        }
    }
    // Return -1 if the number was not found
    return - 1;
}

// Definition of function for bubble sort
void bubbleSort(int size, int tab[])
{
    // Iterate elements in array where the last i elements are in the right place
    for(int i = 0; i < size - 1; i++)
    {           
        // Iterate elements in array and putting the highest value at the last position
        for(int j = 0; j < size - i - 1; j++)
        {      
            // Case if current element is bigger than the next element
            if(*(tab + j) > *(tab + j + 1))
            {
                // Note: same as tab[j] > tab[j + 1]

                // Call helper finction to swap elements
                swap((tab + j), (tab + j + 1));
            // Note: same as &[tabj], &tab[j+1]
            }
        }
    }
}

// Definition of function that swaps the value of two pointer in memory
void swap(int *a, int *b)
{
    // Create temporary variable to store the value in pointer a
    int temp = *a;
    // Store value in pointer b in pointer a
    *a = *b;
    // Store value of temporary variable in pointer b
    *b = temp;          
}

// Definition of function that prints the values of the array
void printArray(int size, int tab[])
{
    // Iterate over elements in array
    for(int i = 0; i < size; i++)
    {   
        // Display array index and its value
        printf("  %d ", tab[i]);        
    }
}


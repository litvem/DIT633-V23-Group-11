// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 4
// Exercise 4
// Submission code: xxxxx

/*------------------------------------------------------------------------------------------
    Exercise 4: The program uses a declared unsorted test array and searches for a 
    specified number.The unsorted array is printed and if the value is found it 
    return the index of the first position of the specified number but in the case
    that the number is not found -1 is returned. Then the program uses bubble sort 
    to sort the test array in memory and prints the new sorted array. 
-------------------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>

#define  searchNr 23 // number to search for

// Function declaration
int search_number(int number, int tab[], int size);     // Function to search for a number in the array
void bubbleSort(int size, int tab[]);                   // Function that implements bubble sort
void swap(int* a, int* b);                              // Function that swap two values in memory
void printArray(int size, int tab[]);                   // Function that prints the values of the array

int main(){

    int test[] = {1,2,34,5,67,3,23,12,13,10};   // The test array for the program
    int size = sizeof(test)/sizeof(test[0]);    // Storing the size of the array

    printf("---------------\n Searching for:%d \n", searchNr, size);  // Printing the value to search for
    printf("---------------\n Unsorted array: ");
    printArray(size, test);                             // Print the unsorted array

    int index = search_number(searchNr,test,size);            // Storing the result of the search_number function
    
    printf("\n---------------\n Result:");
    
    if(index >= 0){                                     // If index is bigger or equal to 0
        printf(" found at index %d\n", index); 
    }else{
        printf(" %d .Number not found. \n",index);      // If index is -1, the number was not found
    }

    bubbleSort(size, test);     // Using bubble sort to sort the array in memory
    printf("---------------\n Sorted array: ");
    printArray(size, test);     // Using printArray to print the sorted array 

    return 0; // End of the program
}

// Function that determinates if a number is in the array
int search_number(int number, int tab[], int size){

    for(int i = 0; i < size -1 ; i ++){         // Looping thourgh the array to find the given number
        
        if(number == tab[i]){                       // If the given number is found
            return i;                           // return the value of the index                            
        }
    }
    return -1; // If the value is not found returning -1
}

void bubbleSort(int size, int tab[]){
    for(int i = 0; i < size -1; i++){           // Looping through the array where the last i elements are in the right place
        for(int j= 0; j < size-i-1; j++){       // Looping through the array an putting the highest value at the last position
            if(*(tab + j)> *(tab + j + 1)){     // If the current value is bigger than the next value
            // Note: same as tab[j] > tab[j +1]
                swap((tab + j),(tab + j + 1));  // Calling the swap function and providing the
            //Note: same as &[tabj], &tab[j+1]
            }
        }
    }
}
// Function that swaps the value of two pointer in memory
void swap(int* a, int* b){
    int temp = *a;      // Create a temporary int to store the value in pointer a
    *a = *b;            // Store the value in pointer b in pointer a
    *b = temp;          // Store the value in the temporary in b.
}

// Function that prints the values of the array
void printArray(int size, int tab[]){
    for(int i = 0; i < size; i++){      // Looping through the array
        printf("  %d ", tab[i]);        // Print the array index and it value
    }
}


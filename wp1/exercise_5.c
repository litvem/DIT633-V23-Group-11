// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 1
// Exercise 5
// Submission code: XXXX

/*------------------------------------------------------------------------------------------
Exercise 5: 
 The program generates a histogram for the frequency of different numbers in an array
 with randomize values. The size of the array is set to MAX (set to 100) and can contain 
 values between 0 and MAXNUMBER (set to 20).

 Example:
    Given an array table[] = {1,2,12,5,1,0,0,5,9,12,0,2,3,0} the program will print out:

    0   xxxx
    1   xx
    2   xx
    3   x
    5   xx
    9   x
    12  xx
-------------------------------------------------------------------------------------------*/

//Include section
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

//Define section
#define MAX 100        // Defines the maximum number of the values in the table
#define MAXNUMBER 20   // Defines the maximum value of random numbers


// ---------------------------------- Function declarations ---------------------------------

/* This function generates a set of random numbers
and fills the table *tab with these numbers */
void create_random(int* tab);

/* This function takes the *tab of random numbers
and creates a table with the frequency counts for these numbers */
void count_frequency(int* tab, int* freq);

/* This function takes the frequency count table
and draws a histogram of the values in that frequency table */
void draw_histogram(int* freq);

// ------------------------------------ Function definitions --------------------------------
void create_random(int *tab) {
    // Declare variable for random number
    int randomNr;

    // Initialize random number generator with start point 0.
    srand(time(0));
    
    // Inserts random numbers in the table with size MAX and prints the table.
    printf("Table[] = { ");
    // Iterate over all number up until MAXNUMBER
    for (int i = 0; i < MAX; ++i) {
        randomNr = rand() % MAXNUMBER;   // Create a random number between 0 and MAXNUMBER
        tab[i] = randomNr;               // Insert the generated number into the table
        printf(" %d ", randomNr);        // Print the table of random numbers
    }
    printf("}\n");
}

void count_frequency(int *tab, int *freq) {
    // Declare and initialize variable for counting numbers frequency
    int counter = 0;

    // i equals to a possible value in the table (i.e., a number between 0 and 20 if MAXNUMBER set to 20)
    for (int i = 0; i < MAXNUMBER; ++i) {

        // Loop iterates through the whole table
        for (int j = 0; j < MAX; ++j) {
            if (i == tab[j]) {   // If a possible value (i) is found in the table
                ++counter;   // The counter increases with one
            }
        }
        // The numbers of duplicate values is stored in the freq array
        freq[i] = counter;

        // If the number does not exist in the table the value 0 is stored
        counter = 0; // Resets the counter for each iteration
    }
}

// To verify that 100 numbers are counted, uncomment lines 90 and 91
void draw_histogram(int *freq) {
    // int counter = 0;
    // int total = 0;
    printf("\nHISTOGRAM FOR THE TABLE ABOVE: \n");

    // Iterate though all possible values in the array
    for (int i = 0; i < MAXNUMBER; ++i) {

        // The histogram only prints values that are not zero, e.g., bigger than zero
        if (freq[i] != 0) {
            printf("%d ", i);
            // Print number of 'x' depending on frequency for each number
            for (int j = 0; j < freq[i]; ++j) {
                printf("x");
            }
        }
        printf("\n");
    }
}
// ---------------------------------------------------------------------------------------------

// Main program section
int main(void) {

    //Variables declaration
    int table[MAX];
    int frequency[MAXNUMBER];

    // Call functions to perform required operations
    create_random(table);                     // Generate random numbers and put them in a table
    count_frequency(table, frequency);   // Create a table with frequencies of numbers in the given table
    draw_histogram(frequency);                // Draw histogram based of frequency table

    return 0;
}
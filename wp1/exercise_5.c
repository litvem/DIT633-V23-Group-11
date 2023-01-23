// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 1
// Exercise 5
// Submission code: XXXX

/*------------------------------------------------------------------------------------------
Exercise 5: 
 The program generates a histogram for a the frequenxy of different number in an array 
 with randomize values. The size of the array is set to MAX (set to 100) and can contain 
 values between 0 and MAXNUMBERS (set to 20).

 Example:
    Given an array table[]={1,2,12,5,1,0,0,5,9,12,0,2,3,0} the program will printout:

    0   xxxx
    1   xx
    2   xx
    3   x
    5   xx
    9   x
    12  xx
-------------------------------------------------------------------------------------------*/

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

#define MAX 100 // Defines the maximum number of the values in the table 
#define MAXNUMBER 20 // Defines the maximum value of random numbers 


// ------ Function declarations   ----------  

// This function generates a set of random numbers 
// and fills the table *tab with these numbers 
void create_random(int* tab);

// This function takes the *tab of random numbers 
// and creates a table with the frequency counts for these numbers 
void count_frequency(int* tab, int* freq);

// This function takes the frequency count table 
// and draws a histogram of the values in that frequency table 
void draw_histogram(int* freq);

// ------ Function definitions   ---------- 

void create_random(int *tab) {
    
    int randomNr; 
    srand(time(0)); // initilize random number generator with start point 0. 
    
    // Inserts random numbers in the table with size MAX and prints the table.
    
    printf("Table[] = { ");
    for (int i = 0; i < MAX;i++) {
        randomNr = rand() % MAXNUMBER; // creates a random number between 0 and MAXNUMBER
        tab[i] = randomNr; // inserts the generated number into the table
        printf(" %d ", randomNr);
    }
    printf("}\n");
}

void count_frequency(int *tab, int *freq) {
    int counter = 0;

    for (int i = 0; i < MAXNUMBER; i++) {
        // i equals a possible value in the table, i.e. a nr between 0 and 20 iff MAXNUMBER set to 20
        
        for (int j = 0; j < MAX; j++) {// iterates though the whole table
            if (i == tab[j]) {// if a possible value (i) is found in the table
                counter++; // the counter increases with one
            }
        }
        freq[i] = counter; // the numbers of duplicate values is stored in the freq array. 
        // if the number does not exist in the table the value 0 is stored. 
        counter = 0; // resets the counter for each iteration
    }
}

// to verify that 100 numbers are counted, uncomment the code below
void draw_histogram(int *freq) {
    //int counter = 0;
    //int total = 0;
    printf("\nHISTOGRAM FOR THE TABLE ABOVE: \n");
    for (int i = 0; i < MAXNUMBER; i++) { // we iterate though all possible values in the array 
        if (freq[i] != 0) { // the histogram only prints values that are not zero . i.e bigger than zero
            printf("%d ", i);
            for (int j = 0; j < freq[i]; j++) {
                printf("x");
                //counter++;
            }
        }
        printf("\n");

      //  printf(" (%d)\n",counter);
      // total += counter;
      // counter = 0;
    }
   // printf(" total(%d)\n", total);

}

// ------ Main   -------------------------- 

// The main entry point for the program 
//  
// If you choose to go for the optional part 
// Please modify it accordingly 
int main(void) {

    int table[MAX], n;
    int frequency[MAXNUMBER];

    create_random(table);
    count_frequency(table, frequency);
    draw_histogram(frequency);

    return 0;
}
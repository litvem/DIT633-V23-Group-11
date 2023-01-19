// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 0
// Exercises 1-3
// Submission code: NA-2317

/*-----------------------------------------------------------------------------------------
Exercises demonstrate how the program reacts depending on the number of arguments provided.
------------------------------------------------------------------------------------------*/

//Include section
#include <stdio.h>
#include <string.h>

// Main functions in the progress, program arguments supported
int main (int argc, char* argv[]) {

    // Based on the amount of arguments provided, prints different messages
    if(argc != 2) {
        printf("\nError: -h.\n");   // Prints message if no arguments or more than 1 argument have been provided
    } else if(strcmp(argv[1], "-h") == 0) { // Compares the argument provided with '-h'
        printf("\nOnly one argument can be provided and it cannot be -h.\n"); // Prints message if provided argument equals to '-h'
    } else {
        printf("\nHello World! I'm %s!\n", argv[1]);   // Prints message if exactly 1 argument provided (incl. provided argument)
    }
    return 0;
}

// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 1
// Exercise 1
// Submission code: XXXX

/*------------------------------------------------------------------------------------------
Exercise 1: Program ask the user to enter the number. If provided number is within interval
 from 1 to 5, program prints sentence accordingly.
 Program continues to ask for a number if the number in the interval between 1 and 5.
 If number is not in the interval 1 to 5, program exits.
-------------------------------------------------------------------------------------------*/

// Include section
#include <stdio.h>

// Main program section
int main (int argc, char* argv[]) {

    // Variable declaration
    int number = 0;

    /* Program will ask for and take the user input at least once.
      If the input is in the interval from 1 to 5, it will continue executing.
      If the input is outside mentioned interval, program will notify the user and exit.*/
    do {

        // Prompt to enter number
        printf("\nEnter number: ");

        // Read number from the console
        scanf("%d", &number);

        // Print different sentences depending on the received input for numbers in interval 1 to 5
        switch(number) {
            case 1:   // Print message to the user if number 1 was entered
            printf("May the Force be with you.");
            break;
            case 2:   // Print message to the user if number 2 was entered
            printf("I'll be back.");
            break;
            case 3:   // Print message to the user if number 3 was entered
            printf("Houston, we have a problem.");
            break;
            case 4:   // Print message to the user if number 4 was entered
            printf("Magic Mirror on the wall, who is the fairest one of all?");
            break;
            case 5:   // Print message to the user if number 1 was entered
            printf("Toto, I've a feeling we're not in Kansas anymore.");
            break;
            default:   // Print message to the user before exiting the program
            printf("Entered number is out of range.");
            break;
        }
        //Loop condition for the interval from 1 to 5
    } while(number >= 1 && number <= 5);

    return 0;
}
// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 2
// Exercise 4 part 2
// Submission code: XXXX

/*-----------------------------------------------------------------------------------------------------------------
Exercise 4 part 2: The program takes one argument (hexadecimal number) and prints out bit positions for the engine,
 gear, key, break1 and break2.
 The arguments correspond to the decoded byte (output of file code.c).
 The program prints error message if it finds anything wrong (e.g., too many or too few arguments were provided,
 faulty input values). The program unpacks the bytes and prints it out according to the below specification:

 Name           Value
 -----------------------
 engine_on
 gear_pos
 key_pos
 brake1
 brake2
-----------------------------------------------------------------------------------------------------------------*/

// Include section
#include <stdio.h>
#include <stdlib.h>

// Function declarations
int check_input(int input);
void print_decoded(unsigned char byte);

// Main function
int main(int argc , char** argv ){ 
    // Case if number of provided argument equals to 2
    if(argc == 2) {
        // Assign values of arguments to two integers accordingly to the ASCII table
        int first4bits = argv[1][0]; // if it is a number the char value is returned
        int last4bits = argv[1][1];

        // Check of argument values using check_input() function
        first4bits = check_input(first4bits);
        last4bits = check_input(last4bits);

        // Notify user about incorrect argument values
        if(last4bits > 13 || first4bits > 12) {
            printf("Invalid input. The maximum hexadecimal value is CB.");
            // Terminate program and exit with 1
            exit(1);
        }

        unsigned char byte;                 // Declare variable to store value of byte
        byte = last4bits;                   // Assign value of last4bits to variable byte
        byte = byte | (first4bits << 4);    // Shift value of first4bits to the left by 4 and combine it with value of byte

        // Call function print_decoded() to print value of byte
        print_decoded(byte);
    } // Notify user if provided argument has incorrect format
    else {
        printf("Argument input is incorrect. Provide only one argument.");
    }
}

// Definition of function to check the format of the input
int check_input(int input) {
    // Case if input value is greater than or equal to 48 and less than or equal to 57
    if(input >= 48 && input <= 57) { // check if the value is the char value for a number
        // Reduce value of input by 48
        return input -= 48;
    } // Case if input value is greater than or equal to 65 and less than 71
    else if(input >= 65 && input < 71) { // case when the input is a capital letter
        // Reduce value of input by 55
        return input -= 55;
    } // Case if input value is greater than or equal to 97 and less than 103
    else if(input >= 97 && input < 103) { // case when the input is a lower case letter
        // Reduce value of input by 87
        return input -= 87;
    } // Notify user if provided hexadecimal number was incorrect
    else {
        printf("Invalid hexadecimal number.\n");
        exit(1);
    }
}

// Definition of function to print decoded number according to format in specifications
void print_decoded(unsigned char byte){
    // Variable declarations
    int engine;
    int gear;
    int key;
    int brake1;
    int brake2;

    // Get value of engine using bit shifting
    engine = byte >> 7;
    // removing the engine value (1 bit) by bit shifting 1 step to the left
    byte = byte << 1;

    // Get value of gear using bit shifting
    gear = byte >> 5;
    // removing the gear value (3 bits) from the byte by bit shifting 3 step to the left
    byte = byte << 3;

    // Get value of key using bit shifting
    key = byte >> 6;
    // removing the key values ( 2 bits) by bit shifting 2 steps to the left
    byte = byte << 2;

    // Get value of brake1 using bit shifting
    brake1 = byte >> 7;
    // removing the brake1 value (1 bit) by bit shifting 1 step to the left
    byte = byte << 1;

    // Get value of brake2 using bit shifting
    brake2 = byte >> 7;

    // Print numbers according to given format
    printf(" Name            Value  \n");
    printf("------------------------ \n");
    printf(" engine_on         %d\n", engine);
    printf(" gear_pos          %d\n", gear);
    printf(" key_pos           %d\n", key);
    printf(" brake1            %d\n", brake1);
    printf(" brake2            %d\n", brake2);
}



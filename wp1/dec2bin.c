// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 1
// Exercise 4 part 1
// Submission code: XXXX

/*------------------------------------------------------------------------------------------
References:
 - Code inspired by CodeVault: https://www.youtube.com/watch?v=Kj3iboADvUc&t=460s
-------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------
Exercise 4:
 The program accepts any number between 0 and tha maximum value of type long, then converts
 inputted decimal number to a binary format.
 Program execution includes following cases:
 - checks if the string of arguments contains the correct digits,
 - is able to provide help if the user provides parameter '-h',
 - outputs an error message if the conversion was not successful, and
 - returns 2 if the conversion is unsuccessful.

 Decimal number for conversion to binary format should be provided as program argument in
 command line.
-------------------------------------------------------------------------------------------*/

// Include section
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Define section
#define oneByteMAX 255
#define twoBytesMAX 65535
#define threeBytesMAX 16777215
#define bitsInByte 8

/* Function to convert decimal number to binary format
! Note: This approach doesn't use extra memory */
int convert2Binary(int num) {
    // Variable declaration
    char byte;                     // Variable to store value of byte
    int byteSize = sizeof(char);   // sizeof byteSize = 1 byte

    // Print message if given number equals to 0 and exits with code 2
    if (num == 0) { 
        printf("00000000");
        return 0;
    }

    // Case if the number is bigger than three bytes threshold
    if (num > threeBytesMAX) {
        byteSize *= 4;
    } // Case if number is between two and three bytes threshold
    else if (num <= threeBytesMAX && num > twoBytesMAX) {
        byteSize *= 3;
    } // Case if number is between one and two bytes threshold
    else if (num <= twoBytesMAX && num > oneByteMAX) {
        byteSize *= 2;
    }

    // Reverse iteration to get the right order
    for (int i = byteSize - 1; i >= 0; i--) {
        /* A byte is usually stored as a char.
            We want to convert num to pointer.
            Therefore, the address of num (&num) is converted to a pointer '(char *) &num'.
            Since the address is basically a number this allows us to add to it and iterate though it.
            Adding 1 to a char pointer adds one byte (8 bits) to it.
        */ 
        byte = ((char*) &num)[i]; // same as '*(((char*) &num) + 1)' => pointer to the pointer of the address of num

        // Reverse iteration to get the right order
        for (int j = bitsInByte - 1; j >= 0; j--) {
            /* Now that the location of the byte is stored in the variable 'byte',
                we can iterate through the bits in that byte by using bit shifts.
                Bit shifts moves each digit in a numbers binary representation to
                either right (>>) or left (<<).

                Right shift:
                To be able to print in the correct order, bit shift right is used
                so that we move j steps to the right. The empty spaces are mark as 0.
                The bitwise operator '&1' creates a logical operation where only the last bit is
                taken into consideration, '&1' is the same as '& 0000 0001'.Resulting in either 0 or 1.
                Example bitwise: 0000 0101 & 1= 0000 0001  // only in the last bit we have two 1
                which results in a 1, in the other cases 0 and 1 are compared which results in a 0.
                Example (byte >> j) & 1:
                0000 1100 >> 7 ==> (0000 000)0 & 1 = 0
                0000 1100 >> 4 ==> (0000) 0000 & 1 = 0
                0000 1100 >> 2 ==> (00)00 0011 & 1 = 1
            */
            char bit = (byte >> j) & 1;
            printf("%hhd", bit); // %hhd print a char in decimal format
        }
    }
    return 0;
}

// Main program section
int main(int argc, char* argv[]) {
    // Print message if no arguments have been provided
    if(argc == 1) {
        printf("No arguments provided. Use '-h' for help.\n");
        return 2;   // Returns '2' according to specifications
    } // Prints message if the user provided '-h' as an argument
    else if(strcmp(argv[1], "-h") == 0) {
        printf("Enter a decimal number to convert to binary.\n");
    } // If one argument has been provided, convert input number to binary format
    else {
        // (((char*)argv[1]) + 1) is char pointer to the first argument and it is increase by 1
        if(argv[1] > 2147483647){ 
            printf("Error: Conversion unsuccessful.The input need to be a decimal.");
            return 2; 
        }
    // check all characters in the input are valid
        for(int i = 0; argv[1][i] != '\0';i++){
            if(!isdigit(argv[1][i])){
                printf("Error: Conversion unsuccessful. Use -h for more information.");
                return 2;
            }
        }

    // Covert program argument to integer and assign to variable 'num'
        int num = atoi(argv[1]);
        return convert2Binary(num);
    }
    return 0;   // End the program
}

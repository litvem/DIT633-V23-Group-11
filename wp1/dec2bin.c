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
        printf("Error: Conversion unsuccessful.");
        return 2;
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
        for (int j = bitsInByte-1; j >= 0; j--) {
            /*
            * The bit is stored in a char since it has one bit. It will have value 0 or 1.
            * j is set to '8-1' which equal 7, since we want an 8 iteration in the loop.

            * '&' is a bitwise AND operator. We get 1 when both sides have one in a specific index value.
                Rules: 0&1 = 0, 1&0 = 0, 0&0 = 0 , 1&1 = 1.
                Example:
                1101 & 0001  => 0001 alt 1101 & 1 => 0001
                1110 & 0001  => 0000 alt 1110 & 0 => 0000
                1110 & 1011  => 1010

            * Bit shifting. '<<' shifts to the left and '>>' shifts to the right.
                Example:
                1110 >> 1 => 111 (to the right)
                1000 << 1 => 000 (to the left)

                Since we want to bitshift to the right (>>) but we need to do it in reverse
                instead of using 'byte >>= 1' (same as 'byte = byte >> 1') which will shift 1 to the right,
                given us following:
                Example: 12 = 00001100 but byte stores it as 00110000

                Bit shifted right by j 0 = 0
                Bit shifted right by j 1 = 0
                Bit shifted right by j 2 = 1
                Bit shifted right by j 3 = 1
                Bit shifted right by j 4 = 0
                Bit shifted right by j 5 = 0
                Bit shifted right by j 6 = 0
                Bit shifted right by j 7 = 0        Wrong order
                ------------------------------------------------
                Bit shifted right by j 7 = 0    
                Bit shifted right by j 6 = 0    
                Bit shifted right by j 5 = 0    
                Bit shifted right by j 4 = 0    
                Bit shifted right by j 3 = 1    
                Bit shifted right by j 2 = 1    
                Bit shifted right by j 1 = 0    
                Bit shifted right by j 0 = 0        Right order
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
        printf("Enter a decimal number to convert to binary. The decimal should not be 0.\n");
    } // If one argument has been provided, convert input number to binary format
    else {
        // Covert program argument to integer and assign to variable 'num'
        int num = atoi(argv[1]);
        return convert2Binary(num);
    }
    return 0;   // End the program
}

// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 2
// Exercise 4 part 1
// Submission code: 9123

/*----------------------------------------------------------------------------------------------------------------
Exercise 4 part 1: The program packs bits into a byte storing 4 different values in a byte.
 The values are:

   Name          Range   Bits        Info
 engine_on       0..1     1          Is engine on or off. This is bit No. 7
                                     (MSB == Most Significant Bit, the one that carries the value 128 in decimal)
 gear_pos        0..4     3          The position of the gear. Three bits means that we can have 23 == 7 positions
 key_pos         0..2     2          Position of the key – 0 == stop, 1 == on, 2 == engine starter on
 brake1          0..1     1          Position of the front brakes
 brake2          0..1     1          Position of the rear brakes. Bit no 0 (LSB)

 The program stores bites in the bit in following order:
 [engine_on]   [gear_pos]   [key_pos]   [brake1]   [brake2]
     1 bit       3 bits      2 bits      1 bit      1 bit

 The program takes 5 arguments (fewer or more than 5 arguments treated as an error).
 Then it packs these values together in a byte (unsigned char) and prints it out to the console in hexadecimal form.
 After printing is done, program exits.
----------------------------------------------------------------------------------------------------------------*/

// Include section
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

// Function declarations
void to_hexadecimal(int engine, int gear, int key, int brake1, int brake2);

// Main function
int main(int argc, char** argv){

    // Check if 5 arguments are provided
    if(argc == 6) {
        // Convert provided arguments into integers accordingly
        int engine = atoi(argv[1]); 
        int gear = atoi(argv[2]);
        int key = atoi(argv[3]);
        int brake1 = atoi(argv[4]);
        int brake2 = atoi(argv[5]);

        // Notify user about format of first, fourth and fifth argument if they were provided incorrectly
        if(!(brake2 == 1 || brake2 == 0) || !(brake1 == 1 || brake1 == 0) || !(engine == 1 || engine == 0)) {
            printf("The first, fourth and fifth arguments must be 0 or 1.\n");
            return 1;
        } // Notify user about format of second argument if it was provided incorrectly
        else if(gear < 0 || gear > 4) {
            printf("The second argument must be a number between 0 and 4.\n");
            return 1;
        } // Notify user about format of third argument if it was provided incorrectly
        else if( key < 0 || key > 2) {
            printf("The third argument must be a number between 0 and 2.\n");
            return 1;
        } // Notify user if provided arguments are not decimal numbers
        else if( !isdigit(argv[1][0]) || !isdigit(argv[2][0]) || !isdigit(argv[3][0]) || !isdigit(argv[4][0]) || !isdigit(argv[5][0]) ){
            printf("All arguments must be a number.\n");
        } // Convert user input into hexadecimal number
        else {
            to_hexadecimal(engine, gear, key, brake1, brake2);
        }
    } // Notify user if wrong number of arguments was provided (more or less than 5)
    else {
        printf("Invalid number of arguments.");
        return 1;
    }
    return 0;
}

// Definition of function to convert input into hexadecimal number
void to_hexadecimal(int engine, int gear, int key, int brake1, int brake2) {
    // Variable declarations
    unsigned char byte;                 // Variable to store value of byte
    int first4bits;                     // Variable to store first 4 bits of byte
    int last4bits;                      // Variable to store last 4 bits of byte

    // Brake is the last number
    byte = brake2;
    // Brake1 shifted to the left by 1 and combined with byte
    byte = byte | (brake1 << 1);
    // Key shifted to the left by 2 and combined with byte
    byte = byte | (key << 2);
    // Value of byte assigned to the variable first4bits
    first4bits = byte;
    // Value of gear shifted to the left by 4 and combined with byte
    byte = byte | (gear << 4);
    // Value of engine shifted to the left by 7 and combined with byte
    byte = byte | (engine << 7);

    // Value of byte shifted to the right by 4 and assigned to variable last4bits
    last4bits = byte >> 4;
    // Case if last4bits bigger than 9
    if(last4bits > 9) {
        // Add 55 to obtain value of last4bits to print a letter
        last4bits += 55;
        // Print the value of last4bits
        printf("%c", last4bits);
    } // Case if last4bits smaller than or equal to 9
    else {
        // Print the value of last4bits
        printf("%d", last4bits);
    }

    // Case if first4bits bigger than 9
    if(first4bits > 9) {
        // Add 55 to obtain value of first4bits to print a letter
        first4bits += 55;
        // Print the value of first4bits
        printf("%c", first4bits);
    } // Case if first4bits smaller than or equal to 9
    else {
        printf("%d", first4bits);
    }
}

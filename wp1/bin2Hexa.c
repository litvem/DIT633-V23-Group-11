// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 1
// Exercise 4 part 2
// Submission code: XXXX

/*------------------------------------------------------------------------------------------
Exercise 4:
 The program accepts binary number, then converts it to hexadecimal value.
 Program execution includes following cases:
 - checks if the string of arguments contains the correct digits,
 - is able to provide help if the user provides parameter '-h',
 - outputs an error message if the conversion was not successful, and
 - returns 2 if the conversion is unsuccessful.

 If running files dec2bin and bin2Hexa in a pipeline, decimal number for conversion should
 be passes as program argument.
-------------------------------------------------------------------------------------------*/

// Include section
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Function that converts binary number to hexadecimal value
void convert(char* input){
    // Variables declaration
    int decimal = 0,    // Starting value for decimal
        remainder;      // Variable for remainder
    int i = 1;          // Value of each step in binary sequence

    // Convert input into integer
    int binary = atoi(input);

    // Convert to decimal if provided input is not 0
    while (binary != 0) {
        // Get the remained after division by 10
        remainder = binary % 10;
        // Incrementing value of decimal
        decimal += remainder * i;
        // Double the value of each step in binary sequence since they are connected by 2^n
        i = i * 2;
        // Get the whole value after division by 10
        binary = binary / 10;
    }
    // Print hexadecimal value
    printf("%d\n", decimal);
    if(decimal > 15) {   // Case if hexadecimal value is bigger than 15
      printf("%X", decimal); 
    } else {   // Case if hexadecimal value is equals or less than 15
      printf("0%X", decimal); 
    }
}

// Main program section
int main(int argc, char* argv[]) {
    // Variables declaration
    char input[11];     // Array to store 10 character values and has an extra space for '\0' since it is a string
    int j = 0;          // Index of element in the array

  // Case if no argument provided, check stdin from pipeline
  if(argc < 2) {
    int buffer = getc(stdin); // Read stdin, getc provides an int value. It reads characted by character.
	  
	// Prints message if getc() fails and no arguments provided
    if(buffer == EOF){ // EOF = -1 which is the fail number of getc();
      printf("No arguments provided. Use '-h' for help.\n");
      return 2;   // Exits with code 2 according to specifications
    }
    //
    while(buffer != EOF && buffer != '\n') {// while getc has not returned EOF or if it has reach the next line operator
      // Print message if given value is bigger than the size of array input
      if(j > 10) { // the 11th index is reserved for '\0'
        printf("The input is out of range.");
        return 1;
      }
      // Add stdin value from getc() to the array converting them to char
      input[j] = (char)buffer;
      // Read next stdin value from stdin
      buffer = getc(stdin);
      // Increment array index
      j++;
    }
    // Add '\0' to the string to mark its end
    input[j]= '\0';
    // Convert given input
    convert(input);
  } // Prints message if program argument is -h
  else if(strcmp(argv[1], "-h") == 0) {
    printf("Enter a decimal number to convert to binary. The decimal should not be 0.\n");
    return 1;
  } else { // Convert given program argument
    convert(argv[1]);
  }
  return 0;  // End of the program
} 

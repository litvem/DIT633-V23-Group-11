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
#include <ctype.h>

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

    if(decimal > 15) {   // Case if hexadecimal value is bigger than 15
      printf("%X", decimal); 
    } else {   // Case if hexadecimal value is equals or less than 15
       printf("0%X", decimal);
    }
}
// check if the input is a valid digit. Not equal to a letter or another number than 1 or 0.
int checkInput(char input){
  if(!isdigit(input) || !((char)input == '0' || (char)input == '1')){
        printf("Error: Conversion unsuccessful. Use -h for more information.");
        return 2;
  }
  return 0;
}

// method that divides the String input into bytes.
int divideIntoBytes(const char binary[], int length) {

    char byte[8]; // represents 8 bits
    int mod;
    for (int i = 0; i < length; i++) {
      // since the array must increase by 8, mod 8 is use to calculate the 
      // insertion of the values
      mod =i % 8;
      byte[mod] = binary[i];
      // when mod is 7 we have a full byte
      if (mod == 7) {
        // convert the byte into hexadecimal
        convert(byte);
      }
    }
    return 0;
}

// Main program section
int main(int argc, char* argv[]) {
  // Case if no argument provided, check stdin from pipeline
  if(argc < 2) {
    int buffer = getc(stdin); // Read stdin, getc provides an int value. It reads characted by character.
	  
	// Prints message if getc() fails and no arguments provided
    if(buffer == EOF){ // EOF = -1 which is the fail number of getc();
      printf("No arguments provided. Use '-h' for help.\n");
      return 2;   // Exits with code 2 according to specifications
    }
    
    // Variables declaration
    char input[32];     // Array to store 32 character values 
    int j = 0;          // Index of element in the array

    while(buffer != EOF && buffer != '\n') {// while getc has not returned EOF or if it has reach the next line operator
      // Print message if given value is bigger than the size of array input
      if(j > 32) { // the 32th index is reserved for '\0'
        printf("Error: Conversion unsuccessful. Use -h for more information.");
        return 1;
      }
      // returns an error if the input is not a number or if is it not 1 or 0
        checkInput((char)buffer);
        // Add stdin value from getc() to the array converting them to char
        input[j] = (char)buffer;
        // Read next stdin value from stdin
        buffer = getc(stdin);
        // Increment array index
        j++;
      //}
    }
    // Add '\0' to the string to mark its end
    input[j]= '\0';
    // Convert given input
    divideIntoBytes(input,j);
  } // Prints message if program argument is -h
  else if(strcmp(argv[1], "-h") == 0) {
    printf("Enter a binary sequence as numbers. The length of the binary sequence must be a modulo of 8. The minimun size is 8 digits and the maxium is 32 digits \n");
    return 0;
  } else { // Convert given program argument
    int i = 0; // contains the length of the input
    int error; 

    for(i; argv[1][i] != '\0';i++){
      error = checkInput(argv[1][i]);
      if(error != 0 ){
        return error;
      }
    }
    // if the input array a modulo of 8, the input is invalid
    if(i % 8 != 0){
      printf("Error: Conversion unsuccessful. Use -h for more information.");
    }
    // This helper function divided the array into bytes before converting into hexadecimals
    divideIntoBytes(argv[1],i);
  }
  return 0;  // End of the program
} 




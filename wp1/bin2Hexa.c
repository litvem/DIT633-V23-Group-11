#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
  dec2bin.c and bin2Hexa.c needs to be have different executions fields. 
  
*/

int main(int argc, char* argv[]) {
 
  if(argc < 2){  // if no argument provided check stdin from pipeline  
    int buffer = getc(stdin); // read stdin and returns a nr 
	
    if(buffer == EOF){ // if getc fails and no arguments are
      printf("No arguments provided. Use '-h' for help.\n");
      return 2;
    }

    char input[11]; // a long has 10 digits and a string always needs to end with \0 
    int j=0; 

    while(buffer != EOF && buffer != '\n'){
      if( j > 10){ 
        printf("The input is out of range."); 
        return 1;
      }
        input[j] = (char)buffer; // converts the nr is cast to char and inserted into the string
        buffer = getc(stdin); // getting the next value
        j++;
    }

    input[j]= '\0'; // inserting \0 at the end of the string
    printf("%s\n", input); // print input

    int binary = atoi(input); // convering the string to a int "1100" -> 1100
    int decimal = 0, remainder;
    int i = 1;
    // convering the binary to decimal format
    while (binary != 0) {
        remainder = binary % 10;
        decimal += remainder * i;
        i = i * 2;
        binary = binary / 10;
    }
   
    if(decimal > 15){ // if bigger than 15 two characters are printed
      printf("%X", decimal); 
    }else{
      printf("0%X", decimal); // if it is less than 16 only one character is printed therefore a 0 is added infront of it
    }

  }else if(strcmp(argv[1], "-h") == 0) {
    printf("Enter a decimal number to convert to binary. The decimal should not be 0.\n");
    return 1;
    
  }
  return 0;
} 

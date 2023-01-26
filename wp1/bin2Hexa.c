#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
  dec2bin.c and bin2Hexa.c needs to be have different executions fields. 
  
*/

void convert(char* input){
    int binary = atoi(input);
    int decimal = 0, remainder;
    int i = 1;
// convert to decimal
    while (binary != 0) {
        remainder = binary % 10;
        decimal += remainder * i;
        i = i * 2;
        binary = binary / 10;
    }
// print in hexadecimal	
    printf("%d\n",decimal);
    if(decimal > 15){
      printf("%X", decimal); 
    }else{
      printf("0%X", decimal); 
    }
}

int main(int argc, char* argv[]) {
 
  if(argc < 2){  // if no argument provided check stdin from pipeline  
    int buffer = getc(stdin); // read stdin
	
    if(buffer == EOF){ // if getc fails and no arguments are
      printf("No arguments provided. Use '-h' for help.\n");
      return 2;
    }

    char input[11];
    int j=0; 

    while(buffer != EOF && buffer != '\n'){
      if( j > 11){ 
        printf("The input is out of range.");
        return 1;
      }
        input[j] = (char)buffer;
        buffer = getc(stdin);
        j++;
    }

    input[j]= '\0';
    printf("%s\n", input);
    convert(input);

  }else if(strcmp(argv[1], "-h") == 0) {
    printf("Enter a decimal number to convert to binary. The decimal should not be 0.\n");
    return 1;
    
  }else{
    convert(argv[1]);
  }
  return 0;
} 

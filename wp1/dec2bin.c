#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define oneByteMAX 255
#define twoBytesMAX 65535
#define threeByterMAX 16777215
#define bitsInByte 8

//code inspired by CodeVault
//source:  https://www.youtube.com/watch?v=Kj3iboADvUc&t=460s

// Note: This aproach dont use extra memory.
int convert2Binary(int num ) {

    if (num == 0) {
        printf("Error: Conversion unsuccesful.");
        return 2;
    }
    // sizeof byteSize = 1 byte
    int byteSize = sizeof(char);

    char byte;
    // if the number is bigger than three bytes threshold
    if (num > threeByterMAX) {
        byteSize *= 4;
    }
    else if (num <= threeByterMAX && num > twoBytesMAX) {
        byteSize *= 3;
    }
    else if (num <= twoBytesMAX && num > oneByteMAX) {
        byteSize *= 2;
    }

    for (int i = byteSize-1; i >= 0; i--) { // reverse iteration
        /*
          - A byte is usually stored as a char   
          - We want to convert num to pointer.
            Therefore the address of num (&num) is converted to a pointer => (char *) &num
            Since the adress is basically a number this allows us to add to it and iterate though it.
            Adding one to a char pointer adds one byte ( 8 bits to it)
        */ 
        byte = ((char*)&num)[i]; // same as *(((char*)&num) +1) => pointer to the pointer of the adress of num
        
        for (int j = bitsInByte-1; j >= 0; j--) { // prints in reverse order 
            /*
            * The bit is stored in a char since it has one bit. Will have vallue 0 or 1
            * j is set to 8-1 which equal 7, since we want an 8 iteration in the loop

            * & is a Bitwise AND operator. We get 1 when both sides have one in a specific index value
                Rules: 0&1 = 0, 1&0 = 0, 0&0 = 0 , 1& 1 = 1
                Example:
                1101 & 0001  => 0001 alt 1101 & 1 => 0001
                1110 & 0001  => 0000 alt 1110 & 0 => 0000
                1110 & 1011  => 1010

            * Bit shifting. << shifts to the left and >> shifts to the right.
                Example:
                1110 >> 1 => 111 (to the right)
                1000 << 1 => 000 (to the left)

                Since we want to bit shift to the right (>>) but we need to do it in reverse
                instead of using byte >>= 1 ( same as byte = byte >> 1) which will shift 1 to the right,
                given us: 
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
                Bit shifted right by j 0 = 0 

            */
            char bit = (byte >> j) & 1;
            printf("%hhd", bit); //%hhd print a char in decimal

        }   
       //printf(" "); // create a space between each byte for readability purpose.
    }
    return 0;
}

int main(int argc, char* argv[]) {

    if (argc == 1) {
        printf("No arguments provided. Use '-h' for help.\n");
        return 2;
    }
    else if (strcmp(argv[1], "-h") == 0) {
        printf("Enter a decimal number to convert to binary. The decimal should not be 0.\n");
    }
    else {
        int num = atoi(argv[1]);
        return convert2Binary(num);
    }
    
    return 0;
}

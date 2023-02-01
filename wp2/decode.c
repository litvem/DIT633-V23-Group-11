#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printDecoded(unsigned char byte);
int checkInput(int input);

/*
    ADD check for: input bigger than CB
*/

int main(int argc , char** argv ){ 
    
    if(argc == 2){       
        int first4bits = argv[1][0];
        int last4bits = argv[1][1];
        first4bits = checkInput(first4bits);
        last4bits = checkInput(last4bits);
        printf("f: %d hex %X  l: %d hex %X \n", first4bits,  first4bits, last4bits, last4bits);

        if(last4bits > 13 || first4bits > 12){
            printf("Invalid input. The maximun Hexadecimal value is CB.");
            exit(1);
        }

        unsigned char byte = 0;
        byte = last4bits;
        byte = byte | (first4bits << 4);

        printDecoded(byte);

    }else{
        printf("Argument input is incorrect. Provide one arguement in ca");
     
    }
}


int checkInput(int input){
    if( input >= 48 && input < 57){
        return input -= 48;
    }else if(input >= 65 && input < 71){
        return input -= 55;
    }else if(input >= 97 && input < 103){
        return input -= 87;
    }else{
        printf("Invalid Hexadecimal number");
        exit(1);
    }
    return input;
}

void printDecoded(unsigned char byte){
    int engine= 0;
    int gear = 0;
    int key = 0;
    int brake1 = 0;
    int brake2 = 0;

    engine = byte >> 7; 
    byte = byte << 1;
    
    gear = byte >> 5;
    byte = byte << 3;
    
    key = byte >> 6;
    byte = byte << 2;

    brake1 = byte >> 7;
    byte = byte << 1;

    brake2 = byte >> 7;

    printf(" Name            Value  \n");
    printf("------------------------ \n");
    printf(" engine_on         %d\n", engine);
    printf(" gear_pos          %d\n", gear);
    printf(" key_pos           %d\n", key);
    printf(" brake1            %d\n", brake1);
    printf(" brake2            %d\n", brake2);

}



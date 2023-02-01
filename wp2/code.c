/* 
Write two programs – one that pack bits into a byte and the other one which unpacks into a string instructions.  
You need to store 4 different values in a byte.

We should store them in a byte like this: 
[engine_on]    [gear_pos]  [key_pos] [brake1] [brake2]     
 1 bit         3 bits      2 bits     1 bit       1 bit  

Name             Range   Bits      Info    
engine_on       0..1     1          Is engine on or off . This is bit no 7  
(MSB == Most Significant Bit, the one that carries the value 128 in decimal) 
gear_pos        0..4     3          The position of the gear. Three bits means that we can have 23 == 7 positions    
key_pos         0..2     2          Position of the key – 0 == stop, 1 == on, 2 == engine starter on     
brake1          0..1     1          Position of the front brakes   
brake2          0..1     1          Position of the rear brakes. Bit no 0 (LSB) 

The first program, code.c, 
takes 5 arguments (fewer or more than 5 arguments should be treated as an error).

- The  program  should  pack  these  values  together  in  a  byte  (unsigned  char)  and  print  it  out  to  the  console  in 
hexadecimal form. 

- After printing out the code to the console, the program should exit
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void toHexadecimal(int engine, int gear, int key, int brake1, int brake2);
void checkArguments(int engine, int gear, int key, int brake1, int brake2);

int main(int argc, char** argv){ 

//ADD the fail cases
    // check if 5 arguments are provided
    if(argc == 6){
    // check if -h is used and provide help return 0

        int engine = atoi(argv[1]); 
        int gear = atoi(argv[2]);
        int key = atoi(argv[3]);
        int brake1 = atoi(argv[4]);
        int brake2 = atoi(argv[5]);

        if( !(brake2 == 1 || brake2 == 0) || !(brake1 == 1 || brake1 == 0) || !(engine == 1 || engine == 0)){
            printf("The first, fourth and fifth arguments must be 0 or 1 ");
            return 1;
        }else if(gear < 0 || gear > 4){
            printf("The second argument must be a number between 0 and 4");
            return 1;
        }else if( key < 0 || key >2){
            printf("The third argument must be a number between 0 and 2");
            return 1;
        }else if( !isdigit(argv[1][0]) || !isdigit(argv[2][0]) || !isdigit(argv[3][0]) || !isdigit(argv[4][0]) || !isdigit(argv[5][0]) ){
            printf("All arguments must be a number.");
        } else{
            toHexadecimal(engine,gear,key,brake1,brake2);
        }

    }else{            
        printf("Invalid number of argumenet.");
        return 1;
    }
    return 0;
}


void toHexadecimal(int engine, int gear, int key, int brake1, int brake2){
    unsigned char byte = 0;
    int first4bits = 0;
    int last4bits = 0;

    byte = brake2; // brake is the last number =>  0000 0001
 
    byte = byte | (brake1 << 1); // combine byte with the value of brake1. => 0000 0011

    byte = byte | (key << 2); // key is shifted to the left twice and then combined with byte.

    first4bits = byte;

    byte = byte | (gear << 4); // 0000 1011 | 0010 (0000) =  0010 1011
    // is the last element 0000 0001 to 1(000 0000)
    byte = byte | (engine << 7); // 0010 1011 | 1(000 0000) = 1010 1011
    // adding 55 to obtain the value of the last 4 bits
    // substracting 200 to obtain the value of the first 4 bits
    
    last4bits = byte >> 4;
    if(last4bits > 9){
        last4bits += 55;
        printf("%c", last4bits);
    }else{
        printf("%d", last4bits);
    }

    if(first4bits > 9){
        first4bits += 55;
        printf("%c", first4bits);
    }else{
        printf("%d", first4bits);
    }

}

// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 1
// Exercise 2
// Submission code: XXXX

/*------------------------------------------------------------------------------------------
References:
 - ASCII table: https://www.asciitable.com/
-------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------
Exercise 2: Program reads the word inputted by the user, encrypts it using a very simple
 encryption algorithm based on "shifting characters" in the ASCII-code table by provided
 program argument (e.g., 13), and prints the encrypted word.
 Program keeps running until EOF.
-------------------------------------------------------------------------------------------*/

// Include section
#include <stdio.h>    // Needed to read input and print
#include <stdlib.h>   // Needed to convert program argument into integer
#include <string.h>   // Needed to get the length of the array

// Define section
#define MAX 30        // Maximum size of the input array

// Main program section
int main (int argc, char* argv[]) {

    // Variables declaration
    int i;                  // Index of element in the string
    char ch,                // Single character read form the console
         word[MAX];         // String that is read from the console character by character

    // Keep running the program until EOF button combination is entered
    do {
        // Prompt the user to type the word for encryption
        printf("\nEnter the word you like to encrypt: ");

        // Run the program for only one word at the time
        for(i = 0; word[i] != '\0'; ++i) {
            // Read the word from the console character by character
            while ((ch = getchar()) != '\n') {
                // Add character read by getchar() to the string
                word[i] = ch;
                // Update string position
                ++i;
                // Add '\0' to the string to mark its end
                word[i] = '\0';
            }
        }

        // Convert provided program argument into integer
        int key = atoi(argv[1]);

        // Run the loop to encrypt every letter of string 'word'
        for(i = 0; i < strlen(word); ++i) {
            // Conditional check if provided character is capital letter
            if(word[i] >= 'A' && word[i] <= 'Z') {
                /* Wrap array around using modulo operator,
                    where 65 - decimal number for character 'A' in ASCII table,
                          26 - number of alphabetic characters */
                word[i] = ((word[i] - 65 + key) % 26 ) + 65;
            // Conditional check if provided character is small letter
            } else if(word[i] >= 'a' && word[i] <= 'z') {
                /* Wrap array around using modulo operator,
                    where 97 - decimal number for character 'a' in ASCII table,
                          26 - number of alphabetic characters */
                word[i] = ((word[i] - 97 + key) % 26 ) + 97;
            }
        }
        // Print encrypted word
        printf("Encrypted word is %s\n", word);

    } while (i != feof(stdin));   // Program is terminated if EOF button combination is entered

    return 0;
}

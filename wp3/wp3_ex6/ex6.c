// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 3
// Exercise 6
// Submission code: XXXX

/*------------------------------------------------------------------------------------------
Exercise 6: The program reads a string with maximum of 20 characters from the keyboard and
 stores the string in a local variable.
 String is copied to another string by using:
 a) the library function strcpy(),
 b) custom-made function void copyString() without using any library function.
 Main program ends by printing out the copied string in the console.

 The program is able to read from both the keyboard and a text file 'myfile.txt' containing
 one string of characters. The file is created with any file editor.
 The reading from the text file is done by redirect the reading from command line when the
 program execution starts.
-------------------------------------------------------------------------------------------*/

// Include section
#include <stdio.h>
#include <string.h>

// Define section
#define MAX 20                       // Maximum size of the array

FILE *my_file;                       // Pointer to the file

// Function declaration
void copyString(char original[], char duplicate[]);

// Main function
int main (int argc, char* args[])
{
    // Variable declarations
    char word[MAX],                     // String that is read from the console
         copy[MAX];                     // String to copy word string

    // Case if no argument was provided
    if(args[1] == 0) {
        // Prompt user to type the string of characters
        printf("Enter the line of 20 characters: ");
        // Read the string inputted by user
        fgets(word, MAX, stdin);

        // Copy read from console string word into string copy
        // Option A: Using library function strcpy()
        strcpy(copy, word);

        // Option B: Using custom-made function
        // Uncomment next line to use custom-made function and comment line 48
        // copyString(word, copy);

        // Display copied string in the console
        printf("Your input was: %s", copy);
    }
    // Case if argument was provided
    else
    {
        // Open the file for reading using its name in the command line as argument
        my_file = fopen(args[1], "r");
        // Case if file doesn't exist or file name is wrong
        if (my_file == 0) 
        {
            // Notify user about error
            printf("Could not open the file.\n");
        }
        // Case when file exists
        else
        {
            // Variable to check every character in the file
            int i;
            // Run the loop until EOF
            while ((i = fgetc(my_file)) != EOF) 
            {
                // Print the character in the console
                printf("%c", i);
            }
            // Close the file
            fclose(my_file);
        }
    }
    // End of the program
    return 0;
}

// Custom-made function to copy a string
void copyString(char original[], char duplicate[])
{
    int i;
    // Run the function for every character in original string
    for(i = 0; i < MAX; i++)
    {
        // Copy every character from original to duplicate in order of appearance
        duplicate[i] = original[i];
    }
    // Add '\0' to the string to mark its end
    duplicate[i] = '\0';
}
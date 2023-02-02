// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 2
// Exercise 3
// Submission code: XXXX

/*------------------------------------------------------------------------------------------
References:
 - P. J. Deitel, C How to Program, Sixth Edition, 2010
-------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------
Exercise 3: The program manages a database of persons stored in a binary file.
 It provides the user with following options:
 1. Create a new and delete the old file (creates a new file with specified filename, writes
    a first dummy record to the file, and closes it),
 2. Add new person to the file (puts a person to a temporary record then add this record to
    the end of the file),
 3. Search for a person in the file (using first or last name as search criteria, prints out
    list of persons with that name),
 4. Print out all in the file (print out the whole list), and
 5. Exit the program.
 After the choice program executes the task and returns to the menu for new choices (only
 for options 1 to 4).
 Also, the program checks if the file exists and if it's empty and notifies user accordingly.
-------------------------------------------------------------------------------------------*/

// Include section
#include <stdio.h>
#include <string.h>

/*-----------------------------------Define section----------------------------------------*/
// Type definition
typedef struct {
    char firstname[20];
    char famname[20];
    char pers_number[13];               // yyyymmddnnnc
} PERSON;

FILE *database;                         // Pointer to the file

// Function declarations
void write_new_file(PERSON *inrecord);  // Creates a file and writes the first record
PERSON input_record(void);              // Reads a person's record
void append_file(PERSON *inrecord);     // Appends a new person to a file
void search_by_name(char *name);        // Prints out a person if in the list
void print_file(void);                  // Prints out all the persons in the file
/*-----------------------------------------------------------------------------------------*/

// Main function
int main(void)
{
    // Dummy record
    PERSON ppost = {"Harry", "Potter", "198007311331"};

    PERSON newPerson;                   // Structure of type PERSON to be added to database

    int choice;                         // Variable to store user choice (number from 1 to 5)
    char name[20];                      // Variable that stores user input to be used when searching by name

    do {
        // Prompt user to choose the option from given list
        printf("\nChoose one option from below:\n 1. Create a new and delete the old file.\n 2. Add a new person to the file.\n 3. Search for a person in the file.\n 4. Print out all in the file.\n 5. Exit the program.\n");
        printf("Your choice: ");
        // Stores the user's choice
        scanf("%d", &choice);

        // Perform different functionalities base on the user input
        switch (choice) {
            case 1:   // Case if the user entered 1
                // Call function to create a new file and store dummy data in it
                write_new_file(&ppost);
                break;
            case 2:   // Case if the user entered 2
                // Create a new person in database using input_record method
                newPerson = input_record();
                // Call function to add the new person to the database
                append_file(&newPerson);
                break;
            case 3:   // Case if the user entered 3
                // Prompt user to enter name to initiate search
                printf("Enter the first or last name of the person you're looking for: ");
                // Read user input
                scanf("%s", &name);
                // Call function to perform search
                search_by_name(name);
                break;
            case 4:   // Case if the user entered 4
                // Call method to print entire file contents
                print_file();
                break;
            case 5:   // Case if the user entered 5
                // Notify user about exiting the program
                printf("Exiting the program. Have a good day.\n");
                // Exit the program
                return 0;
            default:    // Case if the user entered number other that 1 to 5
                // Notify user about invalid input
                printf("Number you provided is outside of range. Please try again.\n");
                break;
        }
        // Run the program until user enters 5 wishing to leave the program
    } while (choice != 5);
    return (0);
}

// Definition of function to create a new file
void write_new_file(PERSON *inrecord)
{
    /* Open file in wb mode (writing in binary mode) that either opens file is it exists
        or creates a new binary file */
    database = fopen("database.bin", "wb");
    // Check if file exists
    if(database == NULL) {   // Case if file doesn't exist
        // Notify user
        printf("The file does not exist.\n");
    } else {   // Case if file exists
        // Store dummy record in the file
        fwrite(inrecord, sizeof(PERSON), 1, database);
        // Close file
        fclose(database);
        // Notify user that operation was completed successfully
        printf("New file has been created and the old one deleted successfully.\n");
    }
}

// Definition of function to create a new (temporary) record
PERSON input_record(void)
{
    char first_name[20],                // Variable to store user input for first name in new record
         fam_name[20],                  // Variable to store user input for family nane in new record
         pers_number[13];               // Variable to store user input for personal number in new record

         // Prompt user to enter the data for new record
         printf("Enter first name, last name and personal number you'd like to add to the file separated by whitespace:\n");
         // Read the user input and save it in dedicated variables
         scanf("%s %s %s", first_name, fam_name, pers_number);
         
         // Create new person from given user input
         PERSON newPerson;
         // Clear the memory to avoid junk between the file records
         memset(&newPerson, 0, sizeof(PERSON));
         // Copy string values from assign variables to newPerson attribute values accordingly
         strcpy(newPerson.firstname, first_name);
         strcpy(newPerson.famname, fam_name);
         strcpy(newPerson.pers_number, pers_number);
         return newPerson;
}

// Definition of function to append a new person to a file
void append_file(PERSON *inrecord)
{
    // Open file in binary mode to append (write at the end) new record
    database = fopen("database.bin", "ab");
    // Check if file exists
    if(database == NULL) {   // Case if file doesn't exist
        // Notify user
        printf("The file does not exist.\n");
    } else {   // Case if file exists
        // Append record
        fwrite(inrecord, sizeof(PERSON), 1, database);
        // Close file
        fclose(database);
        // Notify user that operation was completed successfully
        printf("New record has been saved successfully.\n");
    }
}

// Definition of function to search person by given first name
void search_by_name(char *name)
{
    // Open file in binary mode to read from it
    database = fopen("database.bin", "rb");
    // Check if file exists
    if(database == NULL) {   // Case if file doesn't exist
        // Notify user
        printf("The file does not exist.\n");
    } else {   // Case if file exists
        // Variable to record how many matches to the given name were found in the file
        int matches = 0;
        // Check if file is empty
        fseek(database, 0, SEEK_END);   // Set seek pointer to the end of the file
        // Check current file position of specified stream
        if (ftell(database) == 0) {   // Case if position is 0 (i.e., the file is empty)
            // Notify user about outcome
            printf("The file is empty.\n");
        } else {   // Case when file is not empty
            // Set seek pointer back to the beginning of the file
            fseek(database, 0, SEEK_SET);
            PERSON person;
            // Check all record in the file
            while(fread(&person, sizeof(PERSON), 1, database)){
             // Case if fist or last name matches search criteria (using strcmp() for comparing strings)
             if(strcmp(person.firstname, name) == 0 || strcmp(person.famname, name) == 0) {
                 // Print all record matching search criteria
                 printf("%s %s %s\n", person.pers_number, person.firstname, person.famname);
                 // Increase matches count
                 matches++;
                }
            }
            // Case if no matches were found
            if(matches == 0) {
                // Notify user
                printf("No matches to the given name were found.\n");
            }
        }
    }
    // Close file
    fclose(database);
}

// Definition of function to print all record in the file
void print_file(void)
{
    // Open file in binary mode to read from it
    database = fopen("database.bin", "rb");
    // Check if file exists
    if(database == NULL) {   // Case if file doesn't exist
        // Notify user
        printf("The file does not exist.\n");
    } else {   // Case if file exists
        // Check if file is empty
        fseek(database, 0, SEEK_END);   // Set seek pointer to the end of the file
        // Check current file position of specified stream
        if (ftell(database) == 0) {   // Case if position is 0 (i.e., the file is empty)
            // Notify user about outcome
            printf("The file is empty.\n");
        } else {   // Case when file is not empty
            // Set seek pointer back to the beginning of the file
            fseek(database, 0, SEEK_SET);
            PERSON person;
            // Read all records in the file and print them
            while (fread(&person, sizeof(PERSON), 1, database)) {
                printf("%13s %20s %20s\n", person.pers_number, person.firstname, person.famname);
            }
        }
        // Close file
        fclose(database);
    }
}
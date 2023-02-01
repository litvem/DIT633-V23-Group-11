// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 2
// Exercise 1
// Submission code: XXXX

/*------------------------------------------------------------------------------------------
Exercise 1: The program asks for robot's starting position (coordinates x and y ranging
 between 1 and 99) and a string of characters 'm' and 't,
 where m - tells robot to move one step in current direction,
       t - tells robot to turn 90 degrees clockwise.
 The program performs instructions from the strings provided by the user one by one.
 When all instructions have been executed, the robot stops and the program prints out
 robot's new current position.
 Then the program asks for a new starting position and string of characters.
 The process repeats until EOF is entered.
-------------------------------------------------------------------------------------------*/

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*-----------------------------------Define section----------------------------------------*/
#define MIN_COORDINATE 0        // Minimum value of coordinates x and y
#define MAX_COORDINATE 99       // Maximum value of coordinates x and y
#define SIZE 20                 // Size of array for robot's instructions
#define X_START 0               // Value of x coordinate at starting position
#define Y_START 0               // Value of y coordinate at starting position

enum DIRECTION {N, O, S, W};    // Enums for robot directions

typedef struct {                // Structure to represent robot and its properties
    int xpos;                   // Robot's x coordinate
    int ypos;                   // Robot's y coordinate
    enum DIRECTION dir;         // Robot's direction
} ROBOT;                        // Name for the object of struct type

// Function declarations
bool check_instructions(char instructions[]);
void move(ROBOT *robot);
void turn(ROBOT *robot);
void print_direction(ROBOT *robot);
/*-----------------------------------------------------------------------------------------*/

// Main function
int main(void)
{
    int x = X_START;            // Variable to store user input for x
    int y = Y_START;            // Variable to store user input for y
    char instructions[SIZE];    // Variable to store user instructions

    // Run the program in the loop
    do
    {   // Prompt user to enter starting position for robot
        printf("\nProvide two numbers as robot starting coordinates x and y in the range between 0 and 99 (inclusive)\n");
        // Store coordinates x and y
        scanf("%d %d", &x, &y);

        // Continue execution if given coordinates are within the range between 0 and 99
        if(x >= MIN_COORDINATE && x <= MAX_COORDINATE && y >= MIN_COORDINATE && y <= MAX_COORDINATE)
        {   // Declare pointer
            ROBOT *robot;
            // Dynamically allocate memory to store robot values
            robot = malloc(sizeof(ROBOT));
            // Update robot x coordinate according to user input
            robot->xpos = x;
            // Update robot y coordinate according to user input
            robot->ypos = y;
            // Starting position set to N according to specifications
            robot->dir = N;

            // Prompt user to provide instructions for robot
            printf("Provide a string consisting of letters m and t, where m - move one step forward, t - turn 90 degrees clockwise\n");
            // Store user instructions
            scanf("%s", &instructions);

            // Case if instructions are valid
            if(check_instructions(instructions))
            {   // Check instruction character by character
                for(int i = 0; i < sizeof instructions; i++)
                {   // Case if character in instruction is m
                    if(instructions[i] == 'm')
                    {   // Call function to move robot
                        move(robot);
                    } // Case if character in instructions is t
                    else if(instructions[i] == 't')
                    {   // Call function to turn robot
                        turn(robot);
                    }
                }
                // Print robot position after instructions were fully executed
                printf("Robot end position is %d %d, ", robot->xpos, robot->ypos);
                // Call method to print robot direction after instructions were fully executed
                print_direction(robot);
                // Free dynamically allocated space in memory
                free(robot);
                // Provide user with hint on how to exit the program
                printf("To exit enter EOF combination.\n");
            }  // Case if given instructions are invalid
            else
            {   // Print message to the user
                printf("! Instructions for robot should consist letters 'm' and 't' ONLY\n");
            }
        }  // Case if given coordinates are invalid
        else if(!feof(stdin))
        {   // Print message to the user
            printf("! Provided number(s) is out of range. Try again or press EOF to exit.\n");
        } // Run the program until EOF is entered
    } while(!feof(stdin));
    // End of main function
    return 0;
}

/* Define function to check if given instructions are valid,
    i.e., given instructions string consist only letters m and t */
bool check_instructions(char instructions[])
{   // Default value for the function
    bool check_instructions = 1;
    // Loop to check all the character in the string one by one
    for(int i = 0; i < strlen(instructions); i++)
    {   // Case if there's other characters in instructions other that m and t
        if(instructions[i] != 'm' && instructions[i] != 't')
        {   // Function value is false
            check_instructions = 0;
        }
    } // Return function value
    return check_instructions;
}

// Definition of function to move robot
void move(ROBOT *robot)
{   // Changes xpos and ypos depending on robot's current direction
    switch(robot->dir)
    {
        case N:   // When robot turned North, its y coordinate is increased by 1
            robot->ypos += 1;
            break;
        case O:   // When robot turned East, its x coordinate is increased by 1
            robot->xpos += 1;
            break;
        case S:   // When robot turned South, its y coordinate is decreased by 1
            robot->ypos -= 1;
            break;
        case W:   // When robot turned West, its x coordinate is decreased by 1
            robot->xpos -= 1;
            break;
        default:   // Notify user is something went wrong while moving robot
            printf("Error occurred while moving robot.\n");
            break;
    }
}

// Definition of function to turn robot
void turn(ROBOT *robot)
{   // Change current direction of the robot 90 degrees clockwise depending on current direction
    switch(robot->dir)
    {
        case N:   // When robot turned North, its direction changes to East
            robot->dir = O;
            break;
        case O:   // When robot turned East, its direction changes to South
            robot->dir = S;
            break;
        case S:   // When robot turned South, its direction changes to West
            robot->dir = W;
            break;
        case W:   // When robot turned West, its direction changes to North
            robot->dir = N;
            break;
        default:   // Notify the user is something went wrong while changing robot's direction
            printf("Error occurred while turning robot.\n");
            break;
    }
}

// Define function to print robot direction according to enum
void print_direction(ROBOT *robot)
{   // Take current direction for check
    switch(robot->dir)
    {   // Print message according to enum
        case 0:
            printf("current direction is North.\n");
            break;
        case 1:
            printf("current direction is East.\n");
            break;
        case 2:
            printf("current direction is South.\n");
            break;
        case 3:
            printf("current direction is West.\n");
            break;
    }
}
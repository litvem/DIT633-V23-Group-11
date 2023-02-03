// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 2
// Exercise 2
// Submission code: 9123

/*------------------------------------------------------------------------------------------
Exercise 2: The program generates random numbers and adds to a linked list.
 Extended functionality: the program adds a new record to the first position and assigns
    the fields numbers to the value data.
-------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------
References:
 - Check memory: CodeVault (https://www.youtube.com/watch?v=RYk8qSBbmQc&list=PLfqABt5AS4FmXeWuuNDS3XGENJO1VYGxl&index=3)
-------------------------------------------------------------------------------------------*/

// Include section
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

/*-----------------------------------Define section----------------------------------------*/
// Constant definitions
#define MAX 5                   // Max length of the linked list
#define addFirst 10             // Number that will be added first in the linked list in exercise B

// Type definition
typedef struct q {
        int number;             // Value in the list
        struct q *next;         // Pointer to the next element in the linked list
        struct q *prev;         // Pointer to the previous element in the linked list
} REGTYPE; 
 
// Function declarations
REGTYPE* random_list(void);                     // Create a linked list with random numbers
REGTYPE* add_first(REGTYPE* temp, int data);    // Add an element in the first position of the linked list
void printLinkedList(REGTYPE *act_post);        // Print the linked list
void deallocate(REGTYPE* head);                 // Free the memory allocated to the link list
/*-----------------------------------------------------------------------------------------*/

// Main function
int main(void)
{
    // Variable definitions
    REGTYPE *act_post,          // Pointer to the beginning of the list
            *head = NULL;       // Set pointer head of type REGTYPE to null
    srand(time(0));             // Random seed

// Exercise A
    // Create head element by calling random_list() function
    head = random_list();
    // Assign head to the beginning of the linked list
    act_post = head;
    printf("A) Printing the linked list:\n");
    // Print values of elements in te linked list
    printLinkedList(act_post);
    printf("------------------\n");

// Exercise B
    // Head is set to the returned first value in the add_first() function
    head = add_first(head, addFirst);
    // Assign newly created element as a beginning of the linked list
    act_post = head;
    printf(" B) Add a %d to the first position of the linked list:\n", addFirst);
    // Print the new linked list
    printLinkedList(act_post);
    printf("------------------"); 
       
    // Free dynamically allocated memory
    deallocate(head);

  return 0; 
} 

// Definition of function that free the memory used in the linked list
void deallocate(REGTYPE* head) {
    // Create a node pointer call current that is equal to head
    REGTYPE *current = head;
    // Keep running the loop while current is not null
    while(current != NULL) { 
        // Point both temp and current to the same element in the linked list
        REGTYPE* temp = current;
        // Move current one element forward in the linked list
        current = current -> next;
        // Free memory of current node
        free(temp);
    }
}

// Definition of function that creates a linked list with random numbers and with size MAX
REGTYPE* random_list(void) {
    // Variable declarations
    int nr,                     // Variable used to store random number
        i = 0;                  // Variable used to iterate over elements in the linked list
    REGTYPE *top,               // Pointer to the top element
            *old,               // Pointer to the previous element
            *item;              // Pointer to the value of element

    // Generates a random number between 0 and 100
    nr = rand() % 100;
    /* Allocating heap memory to contain the head node
    Top is the first node in the linked list, and it's set to a random number */
    top = (REGTYPE *) malloc(sizeof(REGTYPE)); 
    /* It is a good practice to check if malloc or calloc is NULL, since we want to check if there is enough memory.
    Reference: CodeVault (https://www.youtube.com/watch?v=RYk8qSBbmQc&list=PLfqABt5AS4FmXeWuuNDS3XGENJO1VYGxl&index=3)*/ 
    if(top == NULL){ 
        // If there is not enough memory, the program gets terminated and returns 1 as an error value
        // We dont free top since there were no memory for it
        printf("Memory cannot be allocated.\n");
        // exit the program with 1 as return
        exit(1);
    }
    // Assign random value to element value
    top -> number = nr; 
    // Since there is only one node in the list, next is set to NULL
    top -> next = NULL;
    // Since there is only one node in the list, prev is set to NULL
    top -> prev = NULL;
    // Old is set to equal top
    old = top;
    // Increment position in the linked list
    i++;

    // Run the loop until if i smaller than length of linked list (i should not be less than 1)
    while( i < MAX) {
        nr = rand() % 100; // Generates a random number between 0 and 100
        item = (REGTYPE *)malloc(sizeof(REGTYPE));
        /* Check if there is enough memory to contain the item structure
            if not, we terminate the program and return 1 as an error value */
        if(item == NULL) {
            // Notify user about error
            printf("Memory cannot be allocated.\n");
            // Free memory used the error sent by malloc
            deallocate(top);
            // Exit the program
            exit(1);
        }
        // The element number is set to a random number
        item -> number = nr;
        // Next is set to NULL since it is the last element in the linked list
        item -> next = NULL;
        // New element is linked to the previous one
        item -> prev = old;
        // Previous element is linked with the new one
        old -> next = item;
        // New element is assigned to last
        old = item;
        // Increment element in the linked list
        i++;
    }
    // The program returns the new first element in the linked list
    return(top);
} 
 
// Definition of function that creates a new element to the linked list and adds it to the first position
REGTYPE* add_first(REGTYPE* head, int data) {
    // Dynamic memory allocation to store values of REGTYPE variable
    REGTYPE *newNode = malloc(sizeof(REGTYPE));
    // Case if the linked list is empty
    if(head == NULL) { // Upon creating new element
        newNode -> prev = NULL;     // Set up pointer to previous element to NULL
        newNode -> next = NULL;     // Set up pointer to next element to NULL
        newNode -> number = data;   // Set up element value to random number
        head = newNode;             // Add element to the linked list
    } // Case if the kinked list is not empty
    else {   // Upon creating new element
        newNode -> prev = NULL;     // Set up pointer to previous element to NULL
        newNode -> next = head;     // Set up pointer to next element to previous top element
        newNode -> number = data;   // Set up element value to random number
        head = newNode;             // Add element to the linked list
    }
    return head;                    // return new element of REGTYPE
}

// Definition of function that print the linked list
void printLinkedList(REGTYPE *act_post) {
    // The function runs until NULL value (i.e., end of the linked list) is found
    while(act_post != NULL) {
        // Print each node in the linked list
        printf("%d\n", act_post -> number);
        // Set act_post to the next (it works as i++ in loop for array)
        act_post = act_post -> next;
    }
}
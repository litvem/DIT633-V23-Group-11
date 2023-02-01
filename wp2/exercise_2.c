// (C) Emma Litvin, Nicole Quinstedt. Group: 11 (2023)
// Work package 2
// Exercise 2
// Submission code: XXXX

/*------------------------------------------------------------------------------------------
Exercise 2: The program generates random numbers and adds the to a linked list.
-------------------------------------------------------------------------------------------*/
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

/*
a) Write a function that creates a linked list with a NUMBER of records of type REGTYPE (see below). 
The value of the variable data is given a random number between 0 and 100. 
 
         Function declaration :  REGTYPE * random_list (void); 
 
Test the function from the main() program.  
 
b) Extend the program with a function with the function declaration:  
 
         REGTYPE * add_first (REGTYPE * temp, int data); 
 
That adds a new record to the first position of the list and assign the field numbers the value of data. 
The function must return a pointer to the new first entry in the list. Extend main() so that this 
function is tested. 
*/


 
//#### Constants ##### 
#define MAX 5 // Max length of the Linked List
#define addFirst 10 // the number that will be added first in the linked list in exercise B

// Creates a Node
// ##### typedefs          #### 
typedef struct q{ 
        int number; // value in the list
        struct q *next; // pointer to the next element in the Linked List
        struct q *prev; // pointer to the previous element in the Linked List
} REGTYPE; 
 
// ##### Function declarations   ##### 

REGTYPE* random_list(void); 
REGTYPE* add_first(REGTYPE* temp, int data); 
void printLinkedList(REGTYPE *act_post);

// Function that print the Linked List
void printLinkedList(REGTYPE *act_post){
    while(act_post != NULL){ // since the end of the linked list is NULL we loop until we found it
        printf("%d\n", act_post -> number); // print each node in the linked list
        act_post = act_post -> next; // sets act_post to the next, works as i++ in a loop with an array
    }

    /*
        while( act_post!=NULL){ 
           printf("\n Post nr %d : %d" , nr++, act_post->number); 
           act_post=act_post->next;   
    */
}
 
 
//###### Main program ####### 
int main(int argc, char *argv[]) 
{ 
    int nr=0; 
    REGTYPE *act_post , *head=NULL; 
    srand(time(0));  //   Random seed  
// Exercise A
    head=random_list(); 
    act_post=head;
    printf(" A) Printing the Linked List:\n");
    printLinkedList(act_post);
    printf("------------------\n");
// Exercise B
    head = add_first(head, addFirst); // head is set to the returned first value in the add_first function
    act_post = head; // act_post is set to the head of the Linked List
    printf(" B) Add a %d to the first position of the Linked List:\n", addFirst);
    printLinkedList(act_post); // Printing the new Linked List
    printf("------------------"); 
       
 // --- Free the allocated memory  --- 
  while((act_post=head)!=NULL){ 
     head=act_post->next; 
     free(act_post); 
  } 
   
  return 0; 
} 
 
// ====     End of main   ====================================== 
 
REGTYPE* random_list(void ){ 
    int nr, i=0; 
    REGTYPE *top, *old, *item;

    if(MAX < 1 ){
        printf("The size of the Linked List is less than 1");
    }

    nr = rand() % 100; // Generates a random number between 0 to 100
    //TESTING PURPOSE
    printf("random number %d = %d\n", i, nr);
    /* Allocating heap memory to contain the head Node
    Top is the first node in the Linked list and it is set to a random number */
    top = (REGTYPE *) malloc(sizeof(REGTYPE)); 
    /* It is a good practice to check if malloc or calloc is NULL
    since we want to check if there is enough memory. 
    Reference: CodeVault (https://www.youtube.com/watch?v=RYk8qSBbmQc&list=PLfqABt5AS4FmXeWuuNDS3XGENJO1VYGxl&index=3)*/ 
    if(top == NULL){ 
        // if there is not enough memory we terminate the program and return 1 as an error value
        printf("Memomery cannot be allocated");
        exit(1);
    }

    top -> number = nr; 
    /* Since there is only one node in the list, next and prev are set to NULL
        and old is set to the top node.*/
    top -> next = NULL;
    top -> prev = NULL;
    old = top;
    i++;

    while( i < MAX){
        nr = rand() % 100; // Generates a random number between 0 to 100
        item = (REGTYPE *)malloc(sizeof(REGTYPE));
        /* Check if there is enough memory to contain the item structure
            if not, we terminate the program and return 1 as an error value*/
        if(item == NULL){
            printf("Memomery cannot be allocated");
            exit(1);
        }
        // The node number is set to a randowm number
        item -> number = nr;
        // Next is set to NULL since it is the last element in the Linked List
        item -> next = NULL;
        // The new node is linked to the previous node
        item -> prev = old;
        // Previous node is linked with the new node
        old -> next = item;
        // the new node is assigned to last 
        old = item;
        i++;
        
    }
    return(top); // return the new first entry in the Linked List.
} 
 
//==========================================================                 
 
REGTYPE* add_first(REGTYPE* temp, int data){ 
    REGTYPE *newNode = malloc(sizeof(REGTYPE));
    // If the Linked list is empty
    if(temp == NULL){
        newNode -> prev = NULL;
        newNode -> next = NULL;
        newNode -> number = data;
        temp = newNode;
    }else{
    // If the Linked list is not empty 
        newNode -> prev = NULL;
        newNode -> next = temp;
        newNode -> number = data;
        temp = newNode;
    }
    return temp;
} 
 